#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

#define TRUE (1)
#define FALSE (0)

/* Egestas diam in arcu cursus euismod quis viverra. Nunc non blandit massa enim nec dui.\n\0 (str) */

/* sent[0] -> Egestas     */
/* sent[1] -> diam        */
/* ...                           */
/* sent[끝] -> (null)     */

/* para[0][] -> Egestas diam in ... quis viverra. */
/* para[1][] -> Nunc non blandit massa enim nec dui. */
/* para[끝][] -> (null)     */

static char* text;
static char**** doc;

/* Source: https://dojang.io/mod/page/view.php?id=617 */
void get_text_from_file(FILE* fp) {
    int size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    text = malloc(size + 1);
    memset(text, 0, size + 1);

    fseek(fp, 0, SEEK_SET);
    fread(text, size, 1, fp);
}

/* Source: https://github.com/engineeringwitharavind/hackerrank/blob/master/HackerRank%20C%20Solutions/021.%20Querying%20the%20Document.c */
void get_doc(void)
{
    size_t para = 0;
    size_t sent = 0;
    size_t word = 0;
    size_t i;

    doc = (char****)malloc(sizeof(char***));
    doc[para] = (char***)malloc(sizeof(char**));
    doc[para][sent] = (char**)malloc(sizeof(char*));
    doc[para][sent][word] = text;

    for(i = 0; text[i + 1] != '\0'; ++i)
    {
        if (text[i + 1] == '\n') {
            text[i++] = '\0';
        }

        if (test[i] == ',' && text[i + 1] == ' ') {
            test[i++] = '\0';
        }

        switch(text[i]) {
        case '\n':
            doc[para][++sent] = NULL;
            ++para;
            sent = 0;
            word = 0;
            doc = (char****)realloc(doc, (para + 1) * sizeof(char***));
            doc[para] = (char***)realloc(doc[para], (sent + 1) * sizeof(char**));
            doc[para][sent] = (char**)realloc(doc[para][sent], (word + 1) * sizeof(char*));
            doc[para][sent][word] = &text[i + 1];
            text[i] = '\0';
            break;
        case '.':
            /* intentional fallthrough */
        case '!':
            /* intentional fallthrough */
        case '?':
            doc[para][sent][++word] = NULL;
            ++sent;
            word = 0;
            doc[para] = (char***)realloc(doc[para], (sent + 1) * sizeof(char**));
            doc[para][sent] = (char**)realloc(doc[para][sent], (word + 1) * sizeof(char*));
            doc[para][sent][word] = &text[i + 1];
            text[i] = '\0';
            break;
        case ' ':
            /* intentional fallthrough */
        case ',':
            ++word;
            doc[para][sent] = (char**)realloc(doc[para][sent], (word + 1) * sizeof(char*));
            doc[para][sent][word] = &text[i + 1];
            text[i] = '\0';
            break;
        default:
            break;
        }
    }
    doc[para] = NULL;
    text[i] = '\0';
}

int load_document(const char* document)
{
    FILE* fp = fopen(document, "rb");

    if (fp == NULL) {
        fprintf(stderr, "No file\n");
        return FALSE;
    }

    get_text_from_file(fp);
    get_doc();

    fclose(fp);
    return TRUE;
}

void dispose(void) {
    char** eraser_word = doc[0][0];
    char*** eraser_sent = doc[0];
    char**** eraser_para = doc;

    free(text);
    while (*eraser_word != NULL) {
        free(*eraser_word++);
    }
    while (*eraser_sent != NULL) {
        free(*eraser_sent++);
    }
    while (*eraser_para != NULL) {
        free(*eraser_para++);
    }
    free(doc);
}

unsigned int get_total_word_count(void)
{
    size_t i;
    size_t j;
    size_t k;
    unsigned int count = 0;

    for (i = 0; doc[i] != NULL; ++i) {
        for (j = 0; doc[i][j] != NULL; ++j) {
            for (k = 0; doc[i][j][k] != NULL; ++k) {
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

    for (i = 0; doc[i] != NULL; ++i) {
        for (j = 0; doc[i][j] != NULL; ++j) {
            ++count;
        }
    }
    return count;
}

unsigned int get_total_paragraph_count(void)
{
    size_t i;
    unsigned int count = 0;

    for (i = 0; doc[i] != NULL; ++i) {
        ++count;
    }
    return count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index);

unsigned int get_paragraph_word_count(const char*** paragraph);

unsigned int get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index);

unsigned int get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);
