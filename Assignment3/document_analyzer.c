#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "document_analyzer.h"

static char* s_text = NULL;
static char**** s_doc = NULL;

/* Source: https://dojang.io/mod/page/view.php?id=617 */
int get_text_from_file(FILE* fp) {
    void* tmp;
    size_t size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    tmp = (char*)malloc(size + 1);
    if (tmp != NULL) {
        s_text = tmp;
    } else {
        return FALSE;
    }
    memset(s_text, 0, size + 1);

    fseek(fp, 0, SEEK_SET);
    fread(s_text, size, 1, fp);
    s_text[size] = '\0';

    return TRUE;
}

void get_doc(void)
{
    /* the numbers of indexes, not counts (count == index + 1) */
    size_t para = 0;
    size_t sent = 0;
    size_t word = 0;
    size_t i;
    void* tmp;

    s_doc = (char****)malloc(sizeof(char***));
    s_doc[0] = (char***)malloc(sizeof(char**));
    s_doc[0][0] = (char**)malloc(sizeof(char*));
    s_doc[0][0][0] = s_text;

    if (*s_doc[0][0][0] == '\0') {
        return;
    }

    for(i = 0; s_text[i + 1] != '\0'; ++i) {
        switch(s_text[i]) {
        case ',':
        /* intentional fallthrough */
        case ' ':
            if (s_text[i + 1] == ' ') {
                s_text[i++] = '\0';
            }
            ++word;
            tmp = (char **)realloc(s_doc[para][sent], (word + 1) * sizeof(char *));
            if (tmp != NULL) {
                s_doc[para][sent] = tmp;
            }
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        case '.':
        /* intentional fallthrough */
        case '!':
        /* intentional fallthrough */
        case '?':
            if (s_text[i + 1] == ' ') {
                s_text[i++] = '\0';
            }
            ++word;
            tmp = (char **)realloc(s_doc[para][sent], (word + 1) * sizeof(char *));
            if (tmp != NULL) {
                s_doc[para][sent] = tmp;
            }
            s_doc[para][sent][word] = NULL;
            ++sent;
            word = 0;
            tmp = (char ***)realloc(s_doc[para], (sent + 1) * sizeof(char **));
            if (tmp != NULL) {
                s_doc[para] = tmp;
            }
            s_doc[para][sent] = (char **)malloc(sizeof(char *));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        case '\n':
            if(s_text[i + 1] == '\n') {
                s_text[i] = '\0';
                break;
            }
            tmp = (char ***)realloc(s_doc[para], (sent + 1) * sizeof(char **));
            if (tmp != NULL) {
                s_doc[para] = tmp;
            }
            s_doc[para][sent] = NULL;
            ++para;
            sent = 0;
            word = 0;
            tmp = (char****)realloc(s_doc, (para + 1) * sizeof(char ***));
            if (tmp != NULL) {
                s_doc = tmp;
            }
            s_doc[para] = (char***)malloc(sizeof(char**));
            s_doc[para][sent] = (char**)malloc(sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        default:
            break;
        }
    }

    if (s_text[i] == '.' || s_text[i] == '!' || s_text[i] == '?') {
        ++word;
            tmp = (char **)realloc(s_doc[para][sent], (word + 1) * sizeof(char *));
            if (tmp != NULL) {
                s_doc[para][sent] = tmp;
            }
        s_doc[para][sent][word] = NULL;
        ++sent;
        word = 0;
    }
    tmp = (char ***)realloc(s_doc[para], (sent + 1) * sizeof(char **));
    if (tmp != NULL) {
        s_doc[para] = tmp;
    }
    s_doc[para][sent] = NULL;
    ++para;
    sent = 0;
    word = 0;
    tmp = (char****)realloc(s_doc, (para + 1) * sizeof(char ***));
    if (tmp != NULL) {
        s_doc = tmp;
    }
    s_doc[para] = NULL;
    s_text[i] = '\0';
}

int load_document(const char* document)
{
    FILE* fp = fopen(document, "rb");

    if (fp == NULL) {
        return FALSE;
    }

    if (get_text_from_file(fp) == FALSE) {
        return FALSE;
    }

    get_doc();

    fclose(fp);
    return TRUE;
}

void dispose(void) {

    size_t i;
    size_t j;

    if (*s_doc[0][0][0] == '\0') {
        free(s_text);
        s_text = NULL;
        free(s_doc[0][0]);
        free(s_doc[0]);
        free(s_doc);
        s_doc = NULL;
        return;
    }

    free(s_text);
    s_text = NULL;

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            free(s_doc[i][j]);
        }
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        free(s_doc[i]);
    }

    free(s_doc);
    s_doc = NULL;

/*
    free(s_text);
    s_text = NULL;

    for (i = 0; *(del_doc + i) != NULL; ++i) {
        for (j = 0; *(*(del_doc + i) + j) != NULL; ++j) {
            free(*(*(del_doc + i) + j));
        }
    }

    del_doc = s_doc;

    for (i = 0; *(del_doc + i) != NULL; ++i) {
        free(*(del_doc + i));
    }

    free(s_doc);
    s_doc = NULL;
*/
}

unsigned int get_total_word_count(void)
{
    size_t i;
    size_t j;
    size_t k;
    unsigned int count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    if (*s_doc[0][0][0] == '\0') {
        return 0;
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                ++count;
                /* printf("print[%lu][%lu][%lu] : %s\n", i, j, k, s_doc[i][j][k]); */
            }
        }
    }
    return count;
}

unsigned int get_total_sentence_count(void)
{
    size_t i;
    size_t j;
    unsigned int count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    if (*s_doc[0][0][0] == '\0') {
        return 0;
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            ++count;
        }
    }
    return count;
}

unsigned int get_total_paragraph_count(void)
{
    size_t i;
    unsigned int count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    if (*s_doc[0][0][0] == '\0') {
        return 0;
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        ++count;
    }
    return count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    size_t i;
    const char*** paragraph;

    if (s_doc == NULL) {
        return NULL;
    }

    paragraph = (const char***)s_doc[paragraph_index];

    for (i = 0; s_doc[i] != NULL; ++i) {
    }
    if (paragraph_index >= i) {
        return NULL;
    }

    return paragraph;
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    size_t i;
    size_t j;
    unsigned int count = 0;

    for (i = 0; paragraph[i] != NULL; ++i) {
        for (j = 0; paragraph[i][j] != NULL; ++j) {
            ++count;
        }
    }
    return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    size_t i;
    unsigned int count = 0;

    for (i = 0; paragraph[i] != NULL; ++i) {
        ++count;
    }
    return count;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    size_t i;
    size_t j;
    const char** sentence;

    if (s_doc == NULL) {
        return NULL;
    }

    sentence = (const char**)s_doc[paragraph_index][sentence_index];

    for (i = 0; s_doc[i] != NULL; ++i) {
    }
    if (paragraph_index >= i) {
        return NULL;
    }

    for (j = 0; s_doc[paragraph_index][j] != NULL; ++j) {
    }
    if (sentence_index >= j) {
        return NULL;
    }

    return sentence;
}

unsigned int get_sentence_word_count(const char** sentence)
{
    size_t i;
    unsigned int count = 0;

    for (i = 0; sentence[i] != NULL; ++i) {
        ++count;
    }
    return count;
}

int print_as_tree(const char* filename)
{
    FILE* fp = fopen(filename, "w");
    size_t i;
    size_t j;
    size_t k;

    if (fp == NULL) {
        return FALSE;
    }

    if (s_doc == NULL) {
        return FALSE;
    }

    if (*s_doc[0][0][0] == '\0') {
        return FALSE;
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        fprintf(fp, "Paragraph %lu:\n", i);
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            fprintf(fp, "    Sentence %lu:\n", j);
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                fprintf(fp, "        %s\n", s_doc[i][j][k]);
            }
        }
        if (s_doc[i + 1] != NULL) {
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
    return TRUE;
}

/* addon into 'load_document' for check
void show_doc(void)
{
    size_t i;
    size_t j;
    size_t k;
    size_t count = 0;

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                ++count;
                printf("s_doc[%lu][%lu][%lu] : %lu\n", i, j, k, count);
            }
        }
    }
}
*/
