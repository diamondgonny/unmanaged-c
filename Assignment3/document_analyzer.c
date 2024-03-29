#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "document_analyzer.h"

/* save entire texts to 's_text(string)' from .txt file */
/* nested structure, named 's_doc' */
static char* s_text = NULL;
static char**** s_doc = NULL;

int load_document(const char* document)
{
    FILE* fp;
    size_t size;

    if (s_doc != NULL) {
        return FALSE;
    }

    fp = fopen(document, "r");

    if (fp == NULL) {
        return FALSE;
    }

    /* Source: https://dojang.io/mod/page/view.php?id=617 */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    s_text = (char*)malloc(size + 1);
    memset(s_text, 0, size + 1);

    fseek(fp, 0, SEEK_SET);
    fread(s_text, size, 1, fp);
    s_text[size] = '\0';
    /* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

    get_doc();

    fclose(fp);
    return TRUE;
}

void get_doc(void)
{
    size_t para = 0;
    size_t sent = 0;
    size_t word = 0;
    size_t i;

    if (s_text[0] == '\0') {
        return;
    }

    s_doc = (char****)malloc(sizeof(char***));
    s_doc[0] = (char***)malloc(sizeof(char**));
    s_doc[0][0] = (char**)malloc(sizeof(char*));
    s_doc[0][0][0] = s_text;

    for (i = 0; s_text[i + 1] != '\0'; ++i) {
        switch (s_text[i]) {
        case ',':
            s_text[i++] = '\0';
        /* intentional fallthrough */
        case ' ':
            ++word;
            s_doc[para][sent] = (char**)realloc(s_doc[para][sent], (word + 1) * sizeof(char*));
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
            if (s_text[i + 1] == '\r' || s_text[i + 1] == '\n') {
                s_text[i++] = '\0';
                break;
            }
            ++word;
            s_doc[para][sent] = (char**)realloc(s_doc[para][sent], (word + 1) * sizeof(char*));
            s_doc[para][sent][word] = NULL;
            ++sent;
            word = 0;
            s_doc[para] = (char***)realloc(s_doc[para], (sent + 1) * sizeof(char**));
            s_doc[para][sent] = (char**)malloc(sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        case '\r':
        /* intentional fallthrough */
        case '\n':
            if (s_text[i + 1] == '\r' || s_text[i + 1] == '\n') {
                s_text[i] = '\0';
                break;
            }
            ++word;
            s_doc[para][sent] = (char**)realloc(s_doc[para][sent], (word + 1) * sizeof(char*));
            s_doc[para][sent][word] = NULL;
            ++sent;
            word = 0;
            s_doc[para] = (char***)realloc(s_doc[para], (sent + 1) * sizeof(char**));
            s_doc[para][sent] = NULL;
            ++para;
            sent = 0;
            word = 0;
            s_doc = (char****)realloc(s_doc, (para + 1) * sizeof(char***));
            s_doc[para] = (char***)malloc(sizeof(char**));
            s_doc[para][sent] = (char**)malloc(sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        default:
            break;
        }
    }
    ++word;
    s_doc[para][sent] = (char**)realloc(s_doc[para][sent], (word + 1) * sizeof(char*));
    s_doc[para][sent][word] = NULL;
    ++sent;
    word = 0;
    s_doc[para] = (char***)realloc(s_doc[para], (sent + 1) * sizeof(char**));
    s_doc[para][sent] = NULL;
    ++para;
    sent = 0;
    word = 0;
    s_doc = (char****)realloc(s_doc, (para + 1) * sizeof(char***));
    s_doc[para] = NULL;
    s_text[i] = '\0';
}

void dispose(void)
{
    size_t i;
    size_t j;

    if (s_doc == NULL) {
        if (s_text == NULL) {
            return;
        } else if (s_text[0] == '\0') {
            free(s_text);
            s_text = NULL;
            return;
        }
    } else {
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
    }
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

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                ++count;
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

    for (i = 0; s_doc[i] != NULL; ++i) {
    }
    if (paragraph_index >= i) {
        return NULL;
    }

    paragraph = (const char***)s_doc[paragraph_index];

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

    sentence = (const char**)s_doc[paragraph_index][sentence_index];

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
    FILE* fp;
    size_t i;
    size_t j;
    size_t k;

    if (s_doc == NULL) {
        return FALSE;
    }

    fp = fopen(filename, "w");

    if (fp == NULL) {
        return FALSE;
    }

    for (i = 0; s_doc[i + 1] != NULL; ++i) {
        fprintf(fp, "Paragraph %zu:\n", i);
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            fprintf(fp, "    Sentence %zu:\n", j);
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                fprintf(fp, "        %s\n", s_doc[i][j][k]);
            }
        }
        if (s_doc[(i + 1) + 1] != NULL) {
            fprintf(fp, "\n");
        }
    }

    for (; s_doc[i] != NULL; ++i) {
        fprintf(fp, "\nParagraph %zu:", i);
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            fprintf(fp, "\n    Sentence %zu:", j);
            for (k = 0; s_doc[i][j][k] != NULL; ++k) {
                fprintf(fp, "\n        %s", s_doc[i][j][k]);
            }
        }
    }

    fclose(fp);
    return TRUE;
}
