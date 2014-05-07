#include "commands.h"

int cmd_ls(char** args, int n_args, int redir_mode, int fd) {
    int i;
    int lflag = FALSE;
    int fflag = FALSE;

    for (i = 0; i < n_args; i++) {
        // if it is a flag
        if (args[i][0] == '-') {
            if (args[i][1] == 'F') {
                fflag = TRUE;
            } else if (args[i][1] == 'l') {
                lflag = TRUE;
            } else {
                printf("ls: invalid option -- '%c'", args[i][1]);
                return -1;
            }
        } else {
            //ignore for now
        }
    }

    DirStream dir_stream;
    dir_stream.pos = 0;
    dir_stream.inode_idx = iList_tail->inode_idx;

    DirFileEntry entry;
    iNode* inode = (iNode*) malloc(sizeof (iNode));
    char display[FILE_NAME_MAX + 1];
    char str[MAX_PATH_LEN];

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

        strcpy(display, entry.file_name);
        if (fflag == TRUE && inode->file_type == FT_DIR) {
            strcat(display, "/");
        }

        if (redir_mode == WRITE_OVRWT || redir_mode == WRITE_APND) {
            if (lflag == TRUE) {
                sprintf(str, "permissions\t%d\t%d\t%d\t%d\t%d\t", inode->nlink, inode->uid, inode->gid, inode->size, inode->mtime);
                f_write(str, strlen(str), 1, fd);
            }
            f_write(display, strlen(display), 1, fd);
            if (lflag) f_write("\n", strlen("\n"), 1, fd);
        } else {
            if (lflag == TRUE) {
                printf("permissions ");
                printf("%d\t", inode->nlink);
                printf("%d\t", inode->uid);
                printf("%d\t", inode->gid);
                printf("%d\t", inode->size);
                printf("%d\t", inode->mtime);
            }
            printf("%s\t", display);
            if (lflag) printf("\n");
        }

        printf("%s\t", display);
        if (lflag) printf("\n");
    }

    if (redir_mode == WRITE_OVRWT || redir_mode == WRITE_APND) {
        f_write("\n", strlen("\n"), 1, fd);
        f_close(fd);
    } else {
        printf("\n");
    }

    free(inode);

    return 0;
}

int cmd_pwd(int redir_mode, int fd) {
    if (redir_mode == WRITE_OVRWT || redir_mode == WRITE_APND) {
        printf("write %s to fd %d\n", cur_dir, fd);
        f_write(cur_dir, strlen(cur_dir), 1, fd);
        f_close(fd);
    } else {
        printf("%s\n", cur_dir);
    }
    return 0;
}

int cmd_mkdir(char** dir_name, int n_args) {
    int i = 0;
    for (i = 0; i < n_args; i++) {
        f_mkdir(dir_name[i]);
    }
    return 0;
}

int cmd_rmdir(char** dir_name, int n_args) {
    int i = 0;
    for (i = 0; i < n_args; i++) {
        if (f_remove_dir(dir_name[i]) == -1) {
            printf("rm: cannot remove %s: No such directory\n", dir_name[i]);
        }
    }
    return 0;
}

int cmd_cat(char* path) {

    int fd = f_open(path, "r");

    char buffer[512];
    int act_size;
    while (1) {
        act_size = f_read(buffer, sizeof (buffer), 1, fd);
        if (act_size == 0) break;
        printf("%s", buffer);
    }
    while (act_size != 0);

    printf("\n");
    f_close(fd);
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
            if (strcmp(dir_name, "..") == 0) {
                inode_remove_tail();
            } else if (strcmp(dir_name, ".") == 0) {
                continue;
            } else {
                inode_append(entry.inode_idx);
            }

            cur_dir[0] = '\0';
            gen_path(cur_dir);
            found = TRUE;
            break;
        }
    }

    if (!found) printf("-mysh: cd: %s: No such file or directory\n", dir_name);

    set_cur_idx(iList_tail->inode_idx);
    return 0;
}

int cmd_rm(char** path, int n_args) {
    int i = 0;
    for (i = 0; i < n_args; i++) {
        if (f_remove(path[i]) == -1) {
            printf("rm: cannot remove %s: No such file\n", path[i]);
        }
    }
    return 0;
}

int cmd_chmod(char* mode, char** files, int n_files) {
    int i, who, what, symbol;
    printf("tada!\n");
    // parse symbolic mode
    if (strlen(mode) != 3) printf("chmod: invalid mode: ‘%s’\n", mode);
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

int chmod(char* args) {
    int fd = f_open(args, "r");
    int mult = 0;
    char grp = args[0];

    char op = args[1];
    int sum = 0;

    if (grp == 'x') mult = 1;
    else if (grp == 'g') mult = 10;
    else if (grp == 'u') mult = 100;



}