#include "filesys_util.h"

/**
 * Calculate number of inode in disk of size size
 * @param size
 * @return 
 */
int cal_n_ibit_blocks(int size) {
    int act_size = round_sz(size);
    printf("Actual disk size: %d\n", act_size);
    return act_size / GROUP_SIZE_BASE;    
}

/**
 * Calculate actual valid size of the disk
 * @param size
 * @return 
 */
int round_sz(int size) {    
    /* 1 byte has 8 bits */
    printf("base is %d\n", GROUP_SIZE_BASE);
    return rnd2sm(size - GRP_HEAD_SZ, GROUP_SIZE_BASE) + GRP_HEAD_SZ;
}

/**
 * Round val to the closest multiple smaller than val
 */
int rnd2sm(int val, int base) {   
    return (val / base) * base;
}

int find_data_ptr(iNode* inode, int pos, DataPos* dp){
    int remainder, data_pos;
    if(pos > inode->size || pos < 0) {
        return -1;
    }
        
    if(pos >= 0 && pos < DBLOCK_SZ) // if the position is within the direct blocks
    {
        dp->size_range = DP_DBLOCK;
        dp->layers[0] = pos/BLOCK_SZ;
        dp->offset = pos % BLOCK_SZ;;
    } //if the position is within the indirect blocks
    else if(pos >= DBLOCK_SZ && pos < DBLOCK_SZ+IBLOCK_SZ){
        dp->size_range = DP_IBLOCK;
        data_pos = pos - DBLOCK_SZ;
        dp->layers[0] = data_pos/ (N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*BLOCK_SZ);
        dp->layers[1] = remainder / BLOCK_SZ;
        dp->offset = remainder % BLOCK_SZ;
    } // if the position is within the second layer indirect blocks
    else if(pos >= DBLOCK_SZ+IBLOCK_SZ && pos < DBLOCK_SZ+IBLOCK_SZ+I2BLOCK_SZ){
        dp->size_range = DP_I2BLOCK;
        data_pos = pos - DBLOCK_SZ - IBLOCK_SZ;
        dp->layers[0] = 0; //there is only one second layer indirect pointer, so it is always zero
        dp->layers[1] = data_pos / (N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*BLOCK_SZ);
        dp->layers[2] = remainder /(BLOCK_SZ);
        dp->offset = remainder % BLOCK_SZ;
    } // if the position is within triple indirect blocks
    else if(pos >= DBLOCK_SZ+IBLOCK_SZ+I2BLOCK_SZ && pos < DBLOCK_SZ+IBLOCK_SZ+I2BLOCK_SZ+I3BLOCK_SZ){
        dp->size_range = DP_I3BLOCK;
        data_pos = pos - DBLOCK_SZ - IBLOCK_SZ - I2BLOCK_SZ; //there is only one third layer indirect pointer, so it is always zero
        dp->layers[0] = 0;
        dp->layers[1] = data_pos/(N_PTR*N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*N_PTR*BLOCK_SZ);
        dp->layers[2] = remainder / (N_PTR*BLOCK_SZ);
        remainder = remainder % (N_PTR*BLOCK_SZ);
        dp->layers[3] = remainder / BLOCK_SZ;
        dp->offset = remainder % BLOCK_SZ;
    } // if the position exceeds the triple indirect blocks
    else {
        return -1;
    }
    return 0;
}

int get_valid_size(iNode* inode, int pos, int bytes){
    if((inode->size - pos) >= bytes) {
        return bytes;
    } else {
        return (inode->size - pos);
    }
}

int calc_pos(Dev* device, iNode* inode, DataPos* dp){
    int pos, addr;
    int data_ptr[N_PTR];
    if(dp->size_range == DP_DBLOCK){
        addr = DATA_ADDR(inode->dblocks[dp->layers[0]]);
        pos = addr + dp->offset;
    }else if(dp->size_range == DP_IBLOCK){
        //get the addr of the indirect data block
        addr = DATA_ADDR(inode->iblocks[dp->layers[0]]);
        //read data block as a list of int pointers
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        //get the int pointer stored in the data block 
        addr = DATA_ADDR(data_ptr[dp->layers[1]]);
        pos = addr + dp->offset;
                
    }else if(dp->size_range == DP_I2BLOCK){
        addr = DATA_ADDR(inode->i2block);
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        addr = DATA_ADDR(data_ptr[dp->layers[1]]);
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        addr = DATA_ADDR(data_ptr[dp->layers[2]]);
        pos = addr + dp->offset; 
    }else{
        addr = DATA_ADDR(inode->i3block);
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        addr = DATA_ADDR(data_ptr[dp->layers[1]]);
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        addr = DATA_ADDR(data_ptr[dp->layers[2]]);
        dev_read(data_ptr, BLOCK_SZ, addr, device);
        addr = DATA_ADDR(data_ptr[dp->layers[3]]);
        pos = addr + dp->offset; 
    }
    return pos;
}

int calc_cur_size(DataPos* dp){
    int size;
    if(dp->size_range == DP_DBLOCK){
        size = dp->layers[0]*BLOCK_SZ+dp->offset;
    }else if(dp->size_range == DP_IBLOCK){
        size = DBLOCK_SZ+dp->layers[0]*(BLOCK_SZ*N_PTR)+dp->layers[1]*BLOCK_SZ+dp->offset;
    }else if(dp->size_range == DP_I2BLOCK){
        size = DBLOCK_SZ + IBLOCK_SZ + dp->layers[1]*(BLOCK_SZ*N_PTR)
                +dp->layers[2]*BLOCK_SZ+dp->offset;
    }else{
        size = DBLOCK_SZ + IBLOCK_SZ + I2BLOCK_SZ+ dp->layers[1]*(BLOCK_SZ*N_PTR*N_PTR)
                +dp->layers[2]*(BLOCK_SZ*N_PTR)+dp->layers[3]*BLOCK_SZ+dp->offset;
    }
    return size;
}

int find_next_block(DataPos* dp){
    if(dp->size_range == DP_DBLOCK){
        if(dp->layers[0] == N_DBLOCKS-1){
            dp->size_range = DP_IBLOCK;
            dp->layers[0] = 0;
            dp->layers[1] = 0;
        }else{
            dp->layers[0]++;
        }
    }else if(dp->size_range == DP_IBLOCK){
        if(dp->layers[0] == N_IBLOCKS-1 && dp->layers[1] == N_PTR-1){
            dp->size_range = DP_I2BLOCK;
            dp->layers[0] = 0;
            dp->layers[1] = 0;
            dp->layers[2] = 0;        
        }else if (dp->layers[1] == N_PTR-1){
            dp->layers[0]++;
            dp->layers[1] = 0;
        } else {
            dp->layers[1]++;
        }   
    }else if(dp->size_range == DP_I2BLOCK){
        if(dp->layers[1] == N_PTR-1 && dp->layers[2] == N_PTR-1){
            dp->size_range = DP_I3BLOCK;
            dp->layers[0] = 0;
            dp->layers[1] = 0;
            dp->layers[2] = 0;
            dp->layers[3] = 0;
        }else if (dp->layers[2] == N_PTR-1){
            dp->layers[1]++;
            dp->layers[2] = 0;
        } else {
            dp->layers[2]++;
        }           
    }else if(dp->size_range == DP_I3BLOCK){
        if(dp->layers[3] == N_PTR-1 && dp->layers[2] == N_PTR-1){
            dp->layers[1]++;
            dp->layers[2] = 0;
            dp->layers[3] = 0;
        } else if (dp->layers[3] == N_PTR-1){
            dp->layers[2]++;
            dp->layers[3] = 0;
        } else {
            dp->layers[3]++;
        }              
    }
    dp->offset = 0;
    return 0;
}

int alloc_data_ptr(Dev* device, iNode* inode, DataPos* dp){
    int addr;
    int data_ptrs[N_PTR];
    DataPos boundary;  
    find_data_ptr(inode, inode->size, &boundary);

    // if it is necessary to allocate a new data pointer
    if(calc_cur_size(&boundary) <= calc_cur_size(dp)){
        find_next_block(&boundary);
        if(inode->size == 0){ // if no data pointers as been allocated
            
            printf("alloc first!\n");
            
            
            inode->dblocks[0] = fs_alloc_databl(device);
            addr = DATA_ADDR(inode->dblocks[0]);
        }else if(boundary.size_range == DP_DBLOCK){
            
                        printf("alloc dir!\n");

            if(boundary.layers[0] == N_DBLOCKS-1){
                inode->iblocks[boundary.layers[0]] = fs_alloc_databl(device);
                addr = DATA_ADDR(inode->iblocks[boundary.layers[0]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            }else{
                inode->dblocks[boundary.layers[0]] = fs_alloc_databl(device);
            }
        }else if(boundary.size_range == DP_IBLOCK){
            
                        printf("alloc idir!\n");

            if(boundary.layers[0] == N_IBLOCKS-1 && boundary.layers[1] == N_PTR-1){         
                inode->i2block= fs_alloc_databl(device);
                addr = DATA_ADDR(inode->i2block);
                //read data block as a list of int pointers
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            }else if (boundary.layers[1] == N_PTR-1){
                inode->iblocks[boundary.layers[0]] = fs_alloc_databl(device);
                addr = DATA_ADDR(inode->iblocks[boundary.layers[0]]);
                //read data block as a list of int pointers
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            } else {
                addr = DATA_ADDR(inode->iblocks[boundary.layers[0]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            }   
        } else if(boundary.size_range == DP_I2BLOCK){
            
                        printf("alloc i2dir!\n");

            
            if(boundary.layers[1] == N_PTR-1 && boundary.layers[2] == N_PTR-1){
                inode->i2block = fs_alloc_databl(device);
                addr = DATA_ADDR(inode->i3block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[0]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            } else if (boundary.layers[2] == N_PTR-1){
                
                addr = DATA_ADDR(inode->i2block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            } else {
                addr = DATA_ADDR(inode->i2block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            }
        } else if(boundary.size_range == DP_I3BLOCK){
            
                        printf("alloc i3dir!\n");

            
            if(boundary.layers[3] == N_PTR-1 && boundary.layers[2] == N_PTR-1){
            
                addr = DATA_ADDR(inode->i3block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[1]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[2]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[3]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            } else if (boundary.layers[3] == N_PTR-1){
           
                addr = DATA_ADDR(inode->i3block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[2]] = fs_alloc_databl(device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[2]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[3]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            } else {
      
                addr = DATA_ADDR(inode->i3block);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[1]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                addr = DATA_ADDR(data_ptrs[boundary.layers[2]]);
                dev_read(data_ptrs, BLOCK_SZ, addr, device);
                data_ptrs[boundary.layers[3]] = fs_alloc_databl(device);
                dev_write(data_ptrs, BLOCK_SZ, addr, device);
            }
        }              
    }
    return 0;
}



int clear_data_bits(Dev* device, iNode* inode){
    DataPos boundary;  
    int i, j, k, databl_idx, addr;
    int data_ptrs[N_PTR];
    int data_ptrs2[N_PTR];
    int data_ptrs3[N_PTR];

    find_data_ptr(inode, inode->size, &boundary);
    
    //clear direct block data
    for(i = 0; i < (boundary.size_range > DP_DBLOCK ? N_DBLOCKS : boundary.layers[0]+1); i++){
        databl_idx = inode->dblocks[i]; 
        abit_off(device, databl_idx); 
    }
    
    //clear the data blocks storing the indirect pointers
    if(boundary.size_range > DP_DBLOCK){
        for(i = 0; i < (boundary.size_range > DP_IBLOCK ? N_IBLOCKS : boundary.layers[0]+1); i++){
            addr = DATA_ADDR(inode->iblocks[i]);
            dev_read(data_ptrs, BLOCK_SZ, addr, device);
            //turn off the bits of the current block in the alloc bitmap
            databl_idx = inode->iblocks[i];
            abit_off(device, inode->iblocks[i]);       
            //clear the bits 
            for(j = 0; j < (boundary.size_range > DP_IBLOCK ? N_PTR : boundary.layers[1]+1); j++){
                databl_idx = data_ptrs[j];
                abit_off(device, databl_idx);  
            }
        }
    }
    
    if(boundary.size_range > DP_IBLOCK){
        databl_idx = inode->i2block;
        addr = DATA_ADDR(inode->i2block);
        dev_read(data_ptrs, BLOCK_SZ, addr, device);
        abit_off(device, databl_idx);
        
        for(i = 0; i < (boundary.size_range > DP_I2BLOCK ? N_PTR : boundary.layers[1]+1); i++){
            databl_idx = data_ptrs[i];
            addr = DATA_ADDR(data_ptrs[i]);
            abit_off(device, databl_idx);
            dev_read(data_ptrs2, BLOCK_SZ, addr, device);
            for(j = 0; j < (boundary.size_range > DP_I2BLOCK ? N_PTR: boundary.layers[2]+1); j++){
                databl_idx = data_ptrs2[j];
                abit_off(device, databl_idx);
            }
        }
    }

    if(boundary.size_range == DP_I3BLOCK){
        databl_idx = inode->i3block;
        addr = DATA_ADDR(inode->i3block);
        dev_read(data_ptrs, BLOCK_SZ, addr, device);
        abit_off(device, databl_idx);
        
        for(i = 0; i < boundary.layers[1]+1; i++){
            databl_idx = data_ptrs[i];
            addr = DATA_ADDR(data_ptrs[i]);
            abit_off(device, databl_idx);
            
            dev_read(data_ptrs2, BLOCK_SZ, addr, device);
            for(j = 0; j < boundary.layers[2]+1; j++){                
                databl_idx = data_ptrs2[j];
                addr = DATA_ADDR(databl_idx);
                abit_off(device, databl_idx);
                
                dev_read(data_ptrs3, BLOCK_SZ, addr, device);
                for(k = 0; k < boundary.layers[3]+1; k++){
                    databl_idx = data_ptrs3[k];
                    abit_off(device, databl_idx);
                }
            }
        }
    }
    return 0;
}

/*
int inode_clr(iNode* node) {
    node->file_type = 0;
    node->permission = 0;
    node->nlink = 0;
    node->size = 0;
    node->uid
    
}*/

/**** Debug Printing ****/
/*
void superbl_print(Superblock* sb) {
    
    printf("==== Superblock ==== \n");
    printf("Num of inodes: %d\n", sb.inode_count);
    printf("Num of data blocks: %d\n", sb.block_count);
    
    printf("Num of free inodes: %d\n", sb.freeinode_count);
    printf("Num of free data blocks: %d\n", sb.freeblock_count);
  
    printf("Ibit offset: %d\n", sb.ibit_offset);
    printf("Abit offset: %d\n", sb.abit_offset);
    printf("Inode offset: %d\n", sb.inode_offset);
    printf("Data offset: %d\n", sb.data_offset);
    
    printf("Block size: %d\n", sb.block_size);
    printf("Disk size: %d\n", sb.size);
    printf("====    ====\n");
    
}*/
