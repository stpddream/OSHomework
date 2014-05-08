#include "inode_list.h"

iList_node *iList_head, *iList_tail;

int inode_append(int inode_idx) {
    //create ilist node
    iList_node* node = (iList_node*) malloc(sizeof (iList_node));
    fs_get_inode(&node->inode, inode_idx, cur_dev);
    node->next = NULL;
    node->inode_idx = inode_idx;

    //if head is null, point both head and tail to current node
    if (iList_head == NULL) {
        iList_head = node;
        iList_tail = node;
    } else {
        iList_tail->next = node;
        iList_tail = node;
    }
    return 0;
}

int inode_remove_tail() {
    //remove the last noe from the list
    iList_node* tmp, *prev;

    if (iList_tail == NULL) {
        return -1;
    } else if (iList_tail == iList_head) {
        //if is in the root directory, remove nothing
    } else {
        for (tmp = iList_head; tmp != iList_tail; prev = tmp, tmp = tmp->next);
        free(iList_tail);
        iList_tail = prev;
        iList_tail->next = NULL;
    }
    return 0;
}

int gen_path(char* path) {
    iList_node* tmp;
    
    //if root is the only node in the path
    if(iList_head->next == NULL) strcat(path, iList_head->inode.name);

    for (tmp = iList_head->next; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->inode.name, "/") != 0) strcat(path, "/");
        strcat(path, tmp->inode.name);
    }
    return 0;
}