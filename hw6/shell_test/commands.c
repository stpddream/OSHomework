#include "commands.h"

int cmd_ls(char* flags) {
    int i;
    int lflag = FALSE;
    int fflag = FALSE;

    for (i = 0; i < strlen(flags); i++) {
        if (flags[i] == 'F') {
            fflag = TRUE;
        } else if (flags[i] == 'l') {
            lflag = TRUE;
        } else {
            continue;
        }
    }

    DirStream dir_stream;
    dir_stream.pos = 0;
    dir_stream.inode_idx = iList_tail->inode_idx;

    DirFileEntry entry;
    iNode* inode;
    char display[FILE_NAME_MAX + 1];

    while (f_readdir(&dir_stream, &entry) != -1) {
        //ignore the previous/cur directory
        if (strcmp(entry.file_name, ".") == 0) continue;
        if (strcmp(entry.file_name, "..") == 0) continue;

        strcpy(display, entry.file_name);
        if (it_exist(entry.inode_idx) == TRUE) {
            inode = it_get_node(entry.inode_idx);
        } else {
            fs_get_inode(inode, entry.inode_idx, cur_dev);
        }

        if (fflag == TRUE && inode->file_type == FT_DIR) {
            strcat(display, "/");
        }
        if (lflag == TRUE) {
            printf("permissions ");
            printf("%d ", inode->nlink);
            printf("%d\t", inode->uid);
            printf("%d\t", inode->gid);
            printf("%d\t", inode->size);
            printf("%d\t", inode->mtime);
        }
        printf("%s\t", display);
        if (lflag) printf("\n");
    }
    printf("\n");

    return 0;
}

int cmd_mkdir(char* dir_name) {
    f_mkdir(dir_name);
    return 0;
}

int cmd_rmdir(char* dir_name) {
    f_rmdir(dir_name);
    return 0;
}

int cmd_cat(int fd) {
    /*    char buffer[512];
        int act_size;
        do {
           // act_size = f_read(buffer, sizeof(buffer), 1, fd);
            printf("%s", buffer);
        } while(act_size != 0);*/
    return 0;
}

int cmd_cd(char* dir_name) {
    int found = FALSE;
    DirStream ds;
    DirFileEntry entry;

    ds.inode_idx = iList_tail->inode_idx;
    ds.pos = 0;

    while (f_readdir(&ds, &entry) != -1) {

        if (strcmp(entry.file_name, dir_name) == 0) {
            inode_append(entry.inode_idx);
            cur_dir[0] = '\0';
            gen_path(cur_dir);
            found = TRUE;
            break;
        }
    }

    if (!found) printf("-mysh: cd: %s: No such file or directory\n", dir_name);

    return 0;
}

int cmd_pwd() {
    printf("%s\n", cur_dir);
    return 0;
}

int cmd_rm(char* path) {
    f_remove(path);
    return 0;
}

int cmd_chmod(){
    return 0;
}

/** More coming */
int cmd_more(char* content) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row - 1;
    int col = w.ws_col;

    char* ch = content;

    while (1) {
        while (ch != '\0') {
            putchar(*ch);
            switch (*ch) {
                case '\n':
                    row--;
                    col = w.ws_col;
                    break;
                default:
                    col--;
                    if (col == 0) {
                        row--;
                        col = w.ws_col;
                    }
            }
            if (row == 1) {
                printf("---- More ----");
                sleep(3);
                printf("\r");
                int i;
                for (i = 0; i < w.ws_col; i++) printf(" ");
                //while (enter != '\r' && enter != '\n') { enter = getchar(); } 
                row = 2;
            }
            ch++;
        }


    }

}



