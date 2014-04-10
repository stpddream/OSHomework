#include "defrag.h"

Superblock sb;
FILE* fp;
int inode_begin, inode_end;


int main(int argc, char** argv) {
    
    fp = fopen("datafile-frag", "r");
    
    fseek(fp, 512, SEEK_SET); //Skip the first 512 byte
    fread(&sb, sizeof(Superblock), 1, fp); //read the superblock
    
    // set the begining and end location of the iNode chunck
    inode_begin = 1024+sb.inode_offset*sb.size;
    inode_end = 1024+sb.data_offset*sb.size;
    
    int i, tmp, curNode;
    printf("printing inode list ... \n");
    for(i = 0, curNode = inode_begin; (tmp = next_inode(curNode)) != -1; curNode = tmp, i++) {
      printf("curNode [%d]\t %d \t %s\n", i, curNode, (isFreeNode(curNode)? "free": "occupied"));
    }
   
    printf("printing occupied inode list ... \n");
    for(i = 0, curNode = inode_begin; (tmp = next_occupied_inode(curNode)) != -1; curNode = tmp, i++) {
      printf("curNode [%d]\t %d\n", i, curNode);
    } 
    
    return 0;    
}

/* return true if the current inode is free
 * false otherwise */
int isFreeNode(int curNode){
  iNode cur;
  fseek(fp, curNode, SEEK_SET);
  fread(&cur, sizeof(iNode), 1, fp);
  return (cur.nlink == 0 ? TRUE : FALSE);
}

/* find the next inode in the list,
 * return -1 when there is no nextNode (curNode is the tail */
int next_inode(int curNode){
  int nextNode = curNode + INODE_SIZE;
  if(nextNode > inode_begin && nextNode < inode_end){
    //check if the current inode address is valid 
    int nextBlock = (nextNode/BLOCK_SIZE+1)*BLOCK_SIZE;
    if(nextBlock-nextNode < INODE_SIZE) {
      nextNode = nextBlock;
    }
    return nextNode;
  }
  return -1;
}

/* find the next occupied inode in the list
 * return -1 when there is no next occupied node */
int next_occupied_inode(int curNode){
  while((curNode = next_inode(curNode)) != -1 && isFreeNode(curNode));
  return curNode;
}

