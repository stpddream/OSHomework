#include "commands.h"

/*int ls(char* flags) {
    int i;
    int lflag = FALSE;
    int fflag = FALSE;
    
    char* cur_dir = "/usr/jacy/home";
    
    for(i =0; i < strlen(flags); i++){
        if(flags[i] == 'F'){
            fflag = TRUE;
        }else if(flags[i] == 'l'){
            lflag = TRUE;
        }else{
            continue;
        }
    }

    DirStream* dir_stream = f_opendir(cur_dir);
    DirFileEntry entry;
    iNode inode;
    char display[FILE_NAME_MAX + 1];

    while (f_readdir(dir_stream, &entry) != -1) {
        //ignore the previous/cur directory
        if (strcmp(entry.file_name, ".") == 0) continue;
        if (strcmp(entry.file_name, "..") == 0) continue;
        
        strcpy(display, entry.file_name);
        if(it_exist(entry.inode_idx) == TRUE){
            &inode = it_get_node(entry.inode_idx);
        }else{
            fs_get_inode(&inode, entry.inode_idx, cur_dev);
        }
        
        if (fflag == TRUE && inode.file_type == FT_DIR) {
            strcat(display, "/");
        }
        if (lflag == TRUE) {
            printf("permissions ");
            printf("%d ", inode.nlink);
            printf("%d\t", inode.uid);
            printf("%d\t", inode.gid);
            printf("%d\t", inode.size);
            printf("%d\t", inode.mtime);
        }
        printf("%s\t", display);
        if(lflag) printf("\n");
    }
    printf("\n");

    f_closedir(dir_stream);
    return 0;
}

int mkdir(char* dir_name){
    char dir[strlen(cur_dir)+strlen(dir_name)+1];
    strcpy(dir, cur_dir);
    if(dir_name[1] != '/'){
        strcat(dir, dir_name);
    }
    f_mkdir(dir);
    return 0;
}

int rmdir(char* dir_name){
    char dir[strlen(cur_dir)+strlen(dir_name)+1];
    strcpy(dir, cur_dir);
    if(dir_name[1] != '/'){
        strcat(dir, dir_name);
    }
    f_rmdir(dir);
    return 0;
}

int cat(int fd) {
    char buffer[512];
    int act_size;
    do {
       // act_size = f_read(buffer, sizeof(buffer), 1, fd);
        printf("%s", buffer);
    } while(act_size != 0);
    return 0;
}
*/




/** More coming */
/*int more(char* content) {    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row - 1;
    int col = w.ws_col;
    
    char* ch = content;
    
    while(1) {
        while(ch != '\0') {                
            putchar(*ch);
            switch(*ch) {
                case '\n':
                    row--;
                    col = w.ws_col;
                    break;
                default:
                    col--;       
                    if(col == 0) {
                        row--;
                        col = w.ws_col;
                    }
            }
            if(row == 1) {
                printf("---- More ----");                     
                sleep(3);
                printf("\r");
                int i;
                for(i = 0; i < w.ws_col; i++) printf(" ");
                //while (enter != '\r' && enter != '\n') { enter = getchar(); } 
                row = 2;
            }      
            ch++;
        }


    }
    
}*/



