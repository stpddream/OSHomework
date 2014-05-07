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
    } else if (strcmp(mode, "w") == 0) {
        mode_v = mode_v | FP_WRITE;
        create_flag = TRUE;
    } else if (strcmp(mode, "w+") == 0) {
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
    char this_path[strlen(path)];

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
    printf("listing dir\n");
    list_dir(&cur_node);


    int cnt = 0;
    char prev_name[FILE_NAME_MAX];
    printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
    printf("here?? cur_idx %d\n", cur_idx);
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
        printf("Cur index is %d\n", cur_idx);
        if (create_flag == FALSE && cur_idx == -1) return -1;
        printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
        printf("current %s\n", dirs);
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
    it_put(inode, inode_idx);
    int fd = ft_put(inode_idx, mode_v);

    print_filetable();


    /** Add file to directory */
    iNode parent_node;
    fs_get_inode(&parent_node, parent_idx, cur_dev);
    printf("parent name is %s\n", parent_node.name);
    dir_add(&parent_node, inode_idx, prev_name);
    fs_update_inode(&parent_node, parent_idx, cur_dev);

    return fd;
}

int f_read(void* ptr, size_t size, size_t nmemb, int fd) {

    int permission = ft_get_perm(fd);

    if ((permission & 1) == 0) {
        return -1;
    }

    int inode_idx = ft_get_idx(fd);
    int cur_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);
    return fl_read(cur_dev, inode, cur_pos, size * nmemb, ptr);
}

int f_write(void* ptr, size_t size, size_t nmemb, int fd) {

    int permission = ft_get_perm(fd);
    int write_pos;
    if (((permission >> 1) & 1) == 0) {
        return -1;
    }

    int inode_idx = ft_get_idx(fd);
    write_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);

    if (((permission >> 2) & 1) == 1) {
        write_pos = inode->size + 1;
    }

    int bytes_written = fl_write(cur_dev, inode, write_pos, size * nmemb, ptr);
    inode->size += bytes_written;
    fs_update_inode(inode, inode_idx, cur_dev);
    return 0;
}

int f_remove() {

    //remove datafile
    //Iterate through all 

    return 0;
}

int f_stat(int fd, char* buf) {
    int inode_idx = ft_get_idx(fd);
    iNode* inode = it_get_node(inode_idx);
    //Print stuff?? //how to do this??
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
    //printf("inode size: %d\n", inode.size);

    // printf("fl_read(cur_dev, &inode, %d, %d, entry) \n", ds->pos, DIR_ENTRY_SZ);
    if (fl_read(cur_dev, &inode, ds->pos, DIR_ENTRY_SZ, entry) == DIR_ENTRY_SZ) {
        // printf("entry filename: %s\n", entry);
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
    char this_path[strlen(path)];

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
    printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);

    while (dirs != NULL) {
        parent_idx = prev_idx;
        prev_idx = cur_idx;
        strcpy(prev_name, dirs);
        dirs = strtok(NULL, "/");
        if (dirs != NULL && cur_idx == -1) return -1;
        if (dirs == NULL) break;
        fs_get_inode(&cur_node, cur_idx, cur_dev);
        cur_idx = dir_lookup(&cur_node, dirs);
        printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
        printf("current %s\n", dirs);
        cnt++;
    }

    printf("When done: [%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
    printf("File name is %s\n", prev_name);

    /** Create new inode for directory **/
    int inode_idx = fs_alloc_inode(cur_dev);
    printf("inode index is %d\n", inode_idx);
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
    printf("parent name is %s\n", parent_node.name);
    dir_add(&parent_node, inode_idx, prev_name);

    fs_update_inode(&parent_node, parent_idx, cur_dev);


    return 0;
}

int f_rmdir(char* path) {
    DirStream* ds = f_open(path);
    DirFileEntry entry;
    iNode cur_node;
    
    while (f_readdir(ds, &entry) != -1) {
        fs_get_inode(&cur_node, ds->inode_idx, cur_dev);
        if(cur_node.file_type == FT_DIR){
            f_rmdir(path+entry.file_name);
        }else{
            f_remove(path+entry.file_name);        
        }
    }
    f_close(ds);
    
    f_remove(path);
    
    return 0;
}