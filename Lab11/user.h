#ifndef USER_H
#define USER_H

typedef struct user {
    size_t id;
    char* username;
    char* email;
    char* password;
} user_t;

#endif /* USER_H */
