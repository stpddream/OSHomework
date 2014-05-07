#include "inode_list.h"
#include "jobs.h"

iList_node *iList_head, *iList_tail;

int inode_append(int inode_idx) {
    //create ilist node
    iList_node node = (iList_node*) malloc(sizeof (iList_node));
    fs_get_inode(&node->inode, inode_idx, cur_dev);
    node->next = NULL;

    //if head is null, point both head and tail to current node
    if (iList_head == NULL) {
        iList_head = &node;
        iList_tail = &node;
    } else {
        tail->next = &node;
        tail = &node;
    }
    return 0;
}

int inode_remove_tail() {
    //remove the last noe from the list
    iList_node* tmp, *prev;

    if (tail == NULL) {
        return -1;
    } else if (tail == head) {
        //if is in the root directory, remove nothing
    } else {
        for (tmp = head; tmp != tail; prev = tmp, tmp = tmp->next);
        free(tail);
        tail = prev;
    }
    return 0;
}

int gen_path(char* path) {
    iList_node* tmp;
    for (tmp = head; tmp != tail; tmp = tmp->next) {
        strcat(path, tmp->inode.name);
        if(strcmp(tmp->inode.name, "/") != 0) strcat(path, "/");
    }
    return 0;
}