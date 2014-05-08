#include "kernel_usr.h"
User* users[3];

User* user_new(int uid, int gid, int user_type, char* usrname, char* passwd) {
    User* user = (User*) malloc(sizeof (User));
    user->uid = uid;
    user->gid = gid;
    user->user_type = user_type;
    strcpy(user->usrname, usrname);
    strcpy(user->passwd, passwd);
    return user;
}

int user_init() {
    users[0] = user_new(0, 1, SUPERUSER, "jacyli", "111111");
    users[1] = user_new(1, 1, SUPERUSER, "panda", "222222");
    users[2] = user_new(2, 2, REGUSER, "dummy", "333333");
    return 0;
}

int user_clean(){
    int i;
    for(i = 0; i < 3; i++){
        free(users[i]);
    }
    return 0;
}

int user_login() {
    int i;
    int login_success = FALSE;
    char usrname[MAX_PW_LEN];
    char passwd[MAX_PW_LEN];
    printf("Username: ");
    scanf("%s", usrname);
    printf("Password: ");
    scanf("%s", passwd);
    
    for(i = 0; i < 3; i++){
        if(strcmp(usrname, users[i]->usrname) == 0 && strcmp(passwd, users[i]->passwd) == 0){
            login_success = TRUE;
            break;
        }
    }

    if(!login_success){ 
        printf("Invalid password or user name\n");
        return -1;
    }
    
    set_user(users[i]);
    return users[i]->uid;
}


/**
 * Get integer permission value
 * @param owner permission
 * @param group permission
 * @param all permission
 * @return 
 */
int get_pm_val(char owner, char group, char all) {
    return owner * 100 + group * 10 + all;        
}
            
