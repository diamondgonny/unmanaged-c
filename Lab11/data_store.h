#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "user.h"

char* get_user_by_id_or_null(user_t** users_or_null, size_t id);

char* get_user_by_username_or_null(user_t** users_or_null, const char* username);

bool update_email(user_t** users_or_null, size_t id, const char* email);

bool update_password(user_t** users_or_null, size_t id, const char* password);

#endif /* DATA_STORE_H */
