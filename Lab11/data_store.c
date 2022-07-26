#include <stdio.h>
#include <string.h>
#include "user.h"
#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    user_t** p = users_or_null;

    if (p == NULL) {
        return NULL;
    }

    while (*p != NULL) {
        if ((*p)->id == id) {
            return *p;
        }
        ++p;
    }

    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    user_t** p = users_or_null;

    if (p == NULL) {
        return NULL;
    }

    while (*p != NULL) {
        if (strcmp((*p)->username, username) == 0) {
            return *p;
        }
        ++p;
    }

    return NULL;
}

void release_mode_for_email(char* p)
{
    ++p;
    if (*p == '@') {
        *(p - 1) = '*';
    } else if (*(p + 1) == '@') {
        *p = '*';
    } else {
        while (*(p + 1) != '@') {
            *p = '*';
            ++p;
        }
    }
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    user_t** p = users_or_null;
    FILE* fp;
    char old_email[51];
    char new_email[51];

    if (p == NULL) {
        return false;
    }

    while (*p != NULL) {
        if ((*p)->id == id) {
            fp = fopen("log.txt", "a+");
            strcpy(old_email, (*p)->email);
            strcpy(new_email, email);
#ifdef RELEASE
            release_mode_for_email(old_email);
            release_mode_for_email(new_email);
#endif
            fprintf(fp, "TRACE: User %zu updated email from \"%s\" to \"%s\"\n", id, old_email, new_email);
            fclose(fp);
            // ------------------------
            strcpy((*p)->email, email);
            return true;
        }
        ++p;
    }

    return false;
}

void release_mode_for_password(char* p)
{
    ++p;
    if (*p == '\0') {
        *(p - 1) = '*';
    } else if (*(p + 1) == '\0') {
        *p = '*';
    } else {
        while (*(p + 1) != '\0') {
            *p = '*';
            ++p;
        }
    }
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t** p = users_or_null;
    FILE* fp;
    char old_password[51];
    char new_password[51];

    if (p == NULL) {
        return false;
    }

    while (*p != NULL) {
        if ((*p)->id == id) {
            fp = fopen("log.txt", "a+");
            strcpy(old_password, (*p)->password);
            strcpy(new_password, password);
#ifdef RELEASE
            release_mode_for_password(old_password);
            release_mode_for_password(new_password);
#endif
            fprintf(fp, "TRACE: User %zu updated password from \"%s\" to \"%s\"\n", id, old_password, new_password);
            fclose(fp);
            // ------------------------------
            strcpy((*p)->password, password);
            return true;
        }
        ++p;
    }

    return false;
}
