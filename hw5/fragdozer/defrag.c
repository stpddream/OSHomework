#include "defrag.h"

Superblock sb;
FILE* fp_r, *fp_w;
int inode_begin, inode_end;


int main(int argc, char** argv) {
    int i, tmp, curNode;
    iNode inode;
    //open the read and write files
    fp_r = fopen("datafile-frag", "r");
    fp_w = fopen("datafile-defrag", "w"); 

    fseek(fp_r, 512, SEEK_SET); //Skip the first 512 byte
    fread(&sb, sizeof(Superblock), 1, fp_r); //read the superblock
    
    char block[BLOCK_SIZE];
    while(!feof(fp_r)){
      fread(&block, sizeof(block), 1, fp_r);
      fwrite(&block, sizeof(block), 1, fp_w);
    }



    // set the begining and end location of the iNode chunck
    inode_begin = 1024+sb.inode_offset*sb.size;
    inode_end = 1024+sb.data_offset*sb.size;
    
    
    printf("printing inode list ... \n");
    for(i = 0, curNode = inode_begin; (tmp = next_inode(curNode)) != -1; curNode = tmp, i++) {
      printf("curNode [%d]\t %d \t %s\t", i, curNode, (is_free_inode(curNode)? "free   ": "occupied"));
    get_inode_by_index(i, &inode);
    print_inode(&inode);
    }
   
  /*  printf("printing occupied inode list ... \n");
    for(i = 0, curNode = inode_begin; (tmp = next_occupied_inode(curNode)) != -1; curNode = tmp, i++) {
      get_inode_by_addr(curNode, &inode);
      // while(next_data(&inode) != NULL)
      printf("[%d] inode loc =%d \t nlink = %d \t\t size = %d\n", i, curNode, inode.nlink, inode.size);

    }*/

    printf("\n\n");
    for(i = 0; i < 20; i++){
      int inode_addr = 1024+i*100;
      get_inode_by_addr(inode_addr, &inode);
      printf("curNode[%d]\t %d\t %s\t", i, inode_addr, (is_free_inode(inode_addr)? "free   ": "occupied"));
      print_inode(&inode);
    }
    
    iNode freehead, tmpfree;
    get_inode_by_index(sb.free_inode, &freehead);
    tmpfree = freehead;
    
    while(tmpfree.next_inode != -1) {
      printf("freenode idx: %d\n", tmpfree.next_inode);
      get_inode_by_index(tmpfree.next_inode, &tmpfree);
    }

    //close both file
    fclose(fp_r);
    fclose(fp_w);
    return 0;    
}

int get_inode_by_index(int idx, iNode* cur){
  get_inode_by_addr(INODE_ADDR_BY_IDX(idx), cur);
  return 0;
}

int get_inode_by_addr(int curNode, iNode* cur){
  fseek(fp_r, curNode, SEEK_SET);
  fread(cur, sizeof(iNode), 1, fp_r);
  return 0;
}

/* return true if the current inode is free
 * false otherwise */
int is_free_inode(int curNode){
  iNode cur;
  get_inode_by_addr(curNode, &cur);
  return (cur.nlink == 0 ? TRUE : FALSE);
}

/* find the next inode in the list,
 * return -1 when there is no nextNode (curNode is the tail */
int next_inode(int curNode){
  int nextNode = curNode + INODE_SIZE;
  if(nextNode > inode_begin && nextNode < inode_end){
    return nextNode;
  }
  return -1;
}

/* find the next occupied inode in the list
 * return -1 when there is no next occupied node */
int next_occupied_inode(int curNode){
  while((curNode = next_inode(curNode)) != -1 && is_free_inode(curNode));
  return curNode;
}

void print_inode(iNode* inode){
  printf("nlink = %d \t", inode->nlink);
  printf("size = %d\n", inode->size);
}
