#include "file.h"


extern Dev* cur_dev;
extern FileTable file_table;
extern iNodeTable inode_table;
int cur_dir_idx;

int f_open(char* path, const char* mode) {

    int create_flag = FALSE;
    int mode_v = 0;

    if (strcmp(mode, "r") == 0) {
        mode_v = mode_v | FP_READ;
    } else if (strcmp(mode, "r+") == 0) {
        mode_v = mode_v | FP_WRITE | FP_READ;
    }
    else if (strcmp(mode, "w") == 0) {
        mode_v = mode_v | FP_WRITE;
        create_flag = TRUE;
    }
    else if (strcmp(mode, "w+") == 0) {
        mode_v = mode_v | FP_READ | FP_WRITE;
        create_flag = TRUE;
    } else if (strcmp(mode, "a") == 0) {
        mode_v = mode_v | FP_WRITE | FP_APPEND;
    } else if (strcmp(mode, "a+") == 0) {
        mode_v = mode_v | FP_READ | FP_WRITE | FP_APPEND;
        create_flag = TRUE;
    } else return -1;

    char* dirs;
    int cur_idx;
    char this_path[strlen(path) + 1];

    if (path[0] == '/') {
        //Set current directory
        cur_idx = 2;
        strcpy(this_path, path + 1);
    } else {
        cur_idx = cur_dir_idx;
        strcpy(this_path, path);
    }


    /* Parse Path */
    dirs = strtok(this_path, "/");

    iNode cur_node;

    int parent_idx = cur_idx;
    int prev_idx = cur_idx;
    fs_get_inode(&cur_node, cur_idx, cur_dev);
    cur_idx = dir_lookup(&cur_node, dirs);

    int cnt = 0;
    char prev_name[FILE_NAME_MAX];
    //printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx); 
    if (create_flag == FALSE && cur_idx == -1) return -1;

    while (dirs != NULL) {

        parent_idx = prev_idx;
        prev_idx = cur_idx;
        strcpy(prev_name, dirs);
        dirs = strtok(NULL, "/");

        if (dirs != NULL && cur_idx == -1) return -1;
        if (dirs == NULL) break;
        fs_get_inode(&cur_node, cur_idx, cur_dev);
        cur_idx = dir_lookup(&cur_node, dirs);
        if (create_flag == FALSE && cur_idx == -1) return -1;

        cnt++;
    }

    /** If file already exists on file table **/
    iNode* inode = (iNode*) malloc(sizeof (iNode));
    int inode_idx;
    if (prev_idx == -1) {
        /** Create File **/
        inode_idx = fs_alloc_inode(cur_dev);
        fs_get_inode(inode, inode_idx, cur_dev);
        activate_inode(inode, FT_FILE, prev_name);
        fs_update_inode(inode, inode_idx, cur_dev);   
        
        
    } else fs_get_inode(inode, prev_idx, cur_dev);
    
    //check permission
    if(check_permission(inode, mode) == FALSE) return -1;

    
    
    it_put(inode, inode_idx);
    int fd = ft_put(inode_idx, mode_v);

    
    print_filetable();


    /** Add file to directory */
    iNode parent_node;
    fs_get_inode(&parent_node, parent_idx, cur_dev);
    dir_add(&parent_node, inode_idx, prev_name);
    fs_update_inode(&parent_node, parent_idx, cur_dev);

    return fd;
}

int f_read(void* ptr, size_t size, size_t nmemb, int fd) {

    int permission = ft_get_perm(fd);

    if (((permission >> 2) & 1) == 0) {
        return -1;
    }

    int inode_idx = ft_get_idx(fd);
    int cur_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);
    
    int byte_read = fl_read(cur_dev, inode, cur_pos, size * nmemb, ptr);    
    cur_pos += byte_read;    
    ft_set_pos(fd, cur_pos);
    return byte_read;    
}

int f_write(void* ptr, size_t size, size_t nmemb, int fd) {

    int permission = ft_get_perm(fd);
    int write_pos;
    
    //Check open mode permission
    if (((permission >> 1) & 1) == 0) {
        return -1;
    }
    
    int inode_idx = ft_get_idx(fd);
    write_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);
    
    //Check file permission
    if(check_permission(inode, PM_WRITE) == 0) return -1;

    if ((permission & 1) == 1) {
        write_pos = inode->size + 1;
    }

    int bytes_written = fl_write(cur_dev, inode, write_pos, size * nmemb, ptr);
    inode->size += bytes_written;
    fs_update_inode(inode, inode_idx, cur_dev);    
    write_pos += bytes_written;
    ft_set_pos(fd, write_pos);    
    return bytes_written;    

}

int f_remove(char* path) {

    printf("@-------- Now removing...%s ------\n", path);

    /* Parse Path */
    char* dirs;
    int cur_idx;
    char this_path[strlen(path) + 1];

    if (path[0] == '/') {
        //Set current directory
        cur_idx = 2;
        strcpy(this_path, path + 1);
    } else {
        cur_idx = cur_dir_idx;
        strcpy(this_path, path);
    }

    dirs = strtok(this_path, "/");
    iNode cur_node;


    int parent_idx = cur_idx;
    int prev_idx = cur_idx;
    fs_get_inode(&cur_node, cur_idx, cur_dev);
    cur_idx = dir_lookup(&cur_node, dirs);

    int cnt = 0;
    char prev_name[FILE_NAME_MAX];
    printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
    //printf("so it's here?? cur_idx %d\n", cur_idx);
    //printf("right now examining %s\n", dirs);
    if (cur_idx == -1) return -1;

    printf("current inode %s\n", cur_node.name);   


    while (dirs != NULL) {
        parent_idx = prev_idx;
        prev_idx = cur_idx;
        strcpy(prev_name, dirs);
        dirs = strtok(NULL, "/");

        if (dirs == NULL) break;
        fs_get_inode(&cur_node, cur_idx, cur_dev);
        cur_idx = dir_lookup(&cur_node, dirs);
        printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);

        if (cur_idx == -1) return -1;
        cnt++;
    }

    iNode parent_node;
    fs_get_inode(&parent_node, parent_idx, cur_dev);
    dir_remove_file(&parent_node, parent_idx, prev_idx); //Remove from directory
    fs_update_inode(&parent_node, parent_idx, cur_dev);

    fs_remove_file(cur_dev, prev_idx);
    return 0;
}

int f_remove_dir(char* path) {
    DirFileEntry entry;

    //Format path
    char this_path[strlen(path) + 1];
    strcpy(this_path, path);

    char ch = 1;
    int i = 0;
    while (ch != '\0') {
        ch = path[i++];
    }

    if (path[i - 2] != '/') {
        this_path[strlen(path)] = '/';
        this_path[strlen(path) + 1] = '\0';
    }

    printf("this_path %s\n", this_path);

    DirStream* ds = f_opendir(this_path);
    iNode dir_node;
    iNode cur_node;
    fs_get_inode(&dir_node, ds->inode_idx, cur_dev);
    int n_entries = dir_node.size / DIR_ENTRY_SZ;

    DirFileEntry cur_entry;
    int pos = 0;
    for (i = 0; i < n_entries; i++) {

        fl_read(cur_dev, &dir_node, pos, DIR_ENTRY_SZ, &cur_entry);

        char next_path[strlen(this_path) + strlen(entry.file_name) + 1];
        strcpy(next_path, this_path);
        printf("next path %s\n", next_path);
        strcat(next_path, cur_entry.file_name);
        printf("cur name %s\n", cur_entry.file_name);
        printf("##### ====>>>>> removing %s\n", next_path);

        fs_get_inode(&cur_node, cur_entry.inode_idx, cur_dev);

        if (cur_node.file_type == FT_DIR) {

            if (strcmp(cur_entry.file_name, ".") == 0 || strcmp(cur_entry.file_name, "..") == 0) {
                pos += DIR_ENTRY_SZ;
                continue;
            }
            f_remove_dir(next_path);
            //if(f_remove_dir(next_path) == -1) return -1;
        } else {
            printf("------ about to remove ------\n");
            list_dir(&dir_node);
            if (f_remove(next_path) == -1) {
                printf("does not exist\n");
                return -1;
            }
        }

    }

    printf("tiaochuqule\n");
    f_closedir(ds);
    f_remove(path);

    return 0;
}

int f_stat(int fd, char* buf) {
    int inode_idx = ft_get_idx(fd);
    iNode* inode = it_get_node(inode_idx);
    sprintf(buf, "File: %s\nSize: %d\n",
            inode->name, inode->size);
    return 0;
}

int f_close(int fd) {
    int inode_idx = ft_get_idx(fd);
    iNode* inode = it_get_node(inode_idx);
    fs_update_inode(inode, inode_idx, cur_dev);
    ft_remove(fd);
    it_remove(inode_idx);
    return 0;
}

int f_seek(int fd, long offset, int whence) {
    if (file_table.entries[fd] == NULL) return -1;
    file_table.entries[fd]->pos = offset;
    return 0;
}

int f_rewind(int fd) {
    if (file_table.entries[fd] == NULL) return -1;
    file_table.entries[fd]->pos = 0;
    return 0;
}

DirStream* f_opendir(char* path) {
    char this_path[strlen(path)];
    strcpy(this_path, path);

    char* dir;
    iNode cur_node;

    DirStream* ds = (DirStream*) malloc(sizeof (DirStream));

    if (path[0] == '/') {
        ds->inode_idx = 2;
    }

    dir = strtok(this_path, "/");
    while (dir != NULL) {
        fs_get_inode(&cur_node, ds->inode_idx, cur_dev);

        ds->inode_idx = dir_lookup(&cur_node, dir);
        if (ds->inode_idx == -1) return NULL;
        dir = strtok(NULL, "/");
    }

    return ds;
}

int f_readdir(DirStream* ds, DirFileEntry* entry) {
    iNode inode;
    fs_get_inode(&inode, ds->inode_idx, cur_dev);

    //printf("fl_read(cur_dev, &inode, %d, %d, entry) \n", ds->pos, DIR_ENTRY_SZ);
    if (fl_read(cur_dev, &inode, ds->pos, DIR_ENTRY_SZ, entry) == DIR_ENTRY_SZ) {
        //printf("entry filename: %s\n", entry);
        ds->pos += DIR_ENTRY_SZ;
    } else {
        entry = NULL;
        return -1;
    }

    return 0;
}

int f_closedir(DirStream* ds) {
    free(ds);
    return 0;
}

int f_mkdir(char* path) {
    char* dirs;
    char this_path[strlen(path) + 1];

    /** Parsing Path **/
    int cur_idx;
    if (path[0] == '/') {
        //Set current directory
        cur_idx = 2;
        strcpy(this_path, path + 1);
    } else {
        cur_idx = cur_dir_idx;
        strcpy(this_path, path);
    }

    dirs = strtok(this_path, "/");

    iNode cur_node;
    int parent_idx = cur_idx;
    int prev_idx = cur_idx;
    fs_get_inode(&cur_node, cur_idx, cur_dev);
    cur_idx = dir_lookup(&cur_node, dirs);

    int cnt = 0;
    char prev_name[FILE_NAME_MAX];
    //printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);

    while (dirs != NULL) {
        parent_idx = prev_idx;
        prev_idx = cur_idx;
        strcpy(prev_name, dirs);
        dirs = strtok(NULL, "/");
        if (dirs != NULL && cur_idx == -1) return -1;
        if (dirs == NULL) break;
        fs_get_inode(&cur_node, cur_idx, cur_dev);
        cur_idx = dir_lookup(&cur_node, dirs);
        //printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
        //printf("current %s\n", dirs);        
        cnt++;
    }

    //printf("When done: [%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
    //printf("File name is %s\n", prev_name);

    /** Create new inode for directory **/
    int inode_idx = fs_alloc_inode(cur_dev);
    iNode* inode = (iNode*) malloc(sizeof (iNode));
    fs_get_inode(inode, inode_idx, cur_dev);
    activate_inode(inode, FT_DIR, prev_name);
    fs_update_inode(inode, inode_idx, cur_dev);
    it_put(inode, inode_idx);


    /** Add . and .. **/
    dir_add(inode, inode_idx, ".");
    dir_add(inode, parent_idx, "..");

    fs_update_inode(inode, inode_idx, cur_dev);


    /** Add node to parent directory **/
    iNode parent_node;
    fs_get_inode(&parent_node, parent_idx, cur_dev);
    dir_add(&parent_node, inode_idx, prev_name);
    fs_update_inode(&parent_node, parent_idx, cur_dev);

    return 0;
}


int f_chmod(char* path, int type, int which, int mode) {
    int fd = f_open(path, "r");
    iNode* inode = it_get_node(fd);
    
//    if(type == )
    
    
    if(which == PM_ALL) {
        inode->permission = inode->permission - inode->permission % 10 + mode;
    }
    
    else if(which = PM_GROUP) {
        inode->permission = inode->permission - (inode->permission / 10 % 10) + mode * 10;
    }    
    else {
        inode->permission = inode->permission - inode->permission / 100 + mode * 100;
    }    

    return 0;
}