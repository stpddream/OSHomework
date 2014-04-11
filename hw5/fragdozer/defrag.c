#include <stdio.h>

#define SUPER_ITEMS 6
#define BLOCK_BASE 1024
#define INODE_ITEMS 25
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define BLOCK_SIZE sb.size
#define N_FIRST_INDIR N_DBLOCKS + sb.size
#define N_DOUBLE_INDIR N_DBLOCKS + sb.size * sb.size
#define N_TRIPLE_INDIR N_DBLOCKS + sb.size * sb.size * sb.size
#define DATA_POS BLOCK_BASE + sb.data_offset + index * BLOCK_SIZE
#define DATA_IDX(INDEX) BLOCK_BASE + sb.data_offset + INDEX * BLOCK_SIZE
#define ADDR_IDX(IDX, OFFSET) DATA_IDX(IDX) + OFFSET * sizeof(int)
#define N_INDIR_PT BLOCK_SIZE / sizeof(int)
#define INODE_IDX 1

#define MIN(A, B) (A > B) ? A : B

typedef struct{
  int size;
  int inode_offset;
  int data_offset;
  int swap_offset;
  int free_inode;
  int free_iblock;
}Superblock;

typedef struct{
  int next_inode;
  int protect;
  int nlink;
  int size;
  int uid;
  int gid;
  int ctime;
  int mtime;
  int atime;
  int dblocks[N_DBLOCKS];
  int iblocks[N_IBLOCKS];
  int i2block;
  int i3block;
} iNode;



Superblock sb;
FILE* fp_w;
FILE* fp_r;
int wr_idx;


int deref(int index) {
    int data;
    fseek(fp_r, index, SEEK_SET);    
    fread((void*)&data, sizeof(int), 1, fp_r);
    return data;
}



void super_process(iNode* inode) {
    
    char zongguan_blocks[BLOCK_BASE];
    fread((void*)zongguan_blocks, BLOCK_BASE, 1, fp_r);
    fwrite(zongguan_blocks, BLOCK_BASE, 1, fp_w);
    
    process(inode);
    
    
    
    
}



void process(iNode* inode, int in_idx) {
        
    int i, j, k, l;
    int remain = inode->size;
    
    //write direct blocks
    for(i = 0; i < N_DBLOCKS; i++) {
        copy_data(inode->dblocks[i], wr_idx);
        //inode->dblocks[i] = wr_idx++;       
       
        write_addr(INODE_IDX + 9 * sizeof(int) + i);
        wr_idx++;
        if((remain -= BLOCK_SIZE) <= 0) return ;
    }
  
  
    //write indirect blocks        
    for(i = 0; i < N_IBLOCKS; i++) {
        int iblo_idx = wr_idx++;
        
        fseek(fp_r, DATA_IDX(inode->iblocks[i]), SEEK_SET);
        for(j = 0; j < N_INDIR_PT; j++) {
            //write indirect blocks                  
            int data_idx;
            fread((void*)&data_idx, sizeof(int), 1, fp_r);   
            
            copy_data(data_idx, wr_idx);
            inode->dblocks[i] = wr_idx++;                                  

            if((remain -= BLOCK_SIZE) < 0) return ;            
        }
    }                    
    
    //Write double indirect blocks

    for(i = 0; i < N_INDIR_PT; i++) {              
        int first_idx = deref(ADDR_IDX(inode->i2block, i));
     
        for(j = 0; j < N_INDIR_PT; j++) {            
            int sec_idx = deref(ADDR_IDX(first_idx, j));
                                    
            for(k = 0; k < N_INDIR_PT; k++) {                    
                int data_idx = deref(ADDR_IDX(first_idx, k));
                fread((void*)&data_idx, sizeof(int), 1, fp_r);
                
                copy_data(data_idx, wr_idx);
                inode->dblocks[i] = wr_idx++;    
                                                           
            }
        }
    }
    
    
    //Triple indirect blocks    
    for(i = 0; i < N_INDIR_PT; i++) {
        int first_idx = deref(ADDR_IDX(inode->i2block, i));

        for(j = 0; j < N_INDIR_PT; j++) {            
            int sec_idx = deref(ADDR_IDX(first_idx, j));
                                    
            for(k = 0; k < N_INDIR_PT; k++) {                    
                int third_idx = deref(ADDR_IDX(sec_idx, k));
                
                for(l = 0; l < N_INDIR_PT; l++) {                    
                    int data_idx = deref(ADDR_IDX(third_idx, l));
                         
                    copy_data(data_idx, wr_idx);
                    inode->dblocks[i] = wr_idx++;    
                    
                }                                              
            }
        }
    }
    
    
    
    
    
    
    
 
}


int write_addr(int idx) {
    fseek(fp_w, idx, SEEK_SET);
    fwrite(&wr_idx, sizeof(int), 1, fp_w);
}


int copy_data(int from_idx, int to_idx) {
    char* data = read_data(from_idx);
    write_data(to_idx, data);
    free(data);       
    return 0;
}


char* read_data(int index) {
    fseek(fp_r, DATA_POS, SEEK_SET);    
    char* data = (char*)malloc(BLOCK_SIZE);    
    fread(data, BLOCK_SIZE, 1, fp_r);
    return data;    
}

int write_data(int index, char* data) {
    fseek(fp_r, DATA_POS, SEEK_SET);    
    char* data = (char*)malloc(BLOCK_SIZE);    
    fwrite(data, BLOCK_SIZE, 1, fp_r);
    return data;   
}




int main(int argc, char** argv) {
    
   
    fp_r = fopen("datafile-frag", "r");
    
    fseek(fp_r, 512, SEEK_SET); //Skip the first 512 byte
    
    //int super_block[SUPER_ITEMS];    
    fread(&sb, sizeof(Superblock), 1, fp_r);
    printf("size = %d\n", sb.size);
    printf("inode offset = %d\n", sb.inode_offset); 
    printf("data offset = %d\n", sb.data_offset);
    printf("swap offset = %d\n", sb.swap_offset);
    printf("free inode index = %d\n", sb.free_inode);
    printf("free iblock index = %d\n", sb.free_iblock);
   
    printf("size of inode = %ld\n", sizeof(iNode)); 
    printf("number of iNodes = %d\n", (int)(sb.size/sizeof(iNode)*4));
    /*inode free_head;
    fseek(fp, sb.free_inode*sb.size, SEEK_CUR);
    fread(&free_head, sizeof(inode), 1, fp);
    */
        
        
    return 0;
    
    
}
