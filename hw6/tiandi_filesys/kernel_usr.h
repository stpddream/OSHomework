/* 
 * File:   usr.h
 * Author: jacyli
 *
 * Created on May 7, 2014, 8:17 AM
 */

#ifndef USR_H
#define	USR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "util.h"
    
#define MAX_PW_LEN 20
#define SUPERUSER 0
#define REGUSER 1
    
    typedef struct {
        int uid;
        int gid;
        int user_type;
        char usrname[MAX_PW_LEN];
        char passwd[MAX_PW_LEN];
    } User;

extern User* users[3];
           
int user_init();
int user_login();
int user_clean();
User* user_new(int uid, int gid, int user_type, char* usrname, char* passwd);
int get_pm_val(char owner, char group, char all);

    

#ifdef	__cplusplus
}
#endif

#endif	/* USR_H */

