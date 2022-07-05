#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

/* Egestas diam in arcu cursus euismod quis viverra. Nunc non blandit massa enim nec dui.\n\0 (str) */

/* sent[0] -> Egestas     */
/* sent[1] -> diam        */
/* ...                           */
/* sent[끝] -> (null)     */

/* para[0][] -> Egestas diam in ... quis viverra. */
/* para[1][] -> Nunc non blandit massa enim nec dui. */
/* para[끝][] -> (null)     */

static char* s_text;
static char**** s_doc;

/* Source: https://dojang.io/mod/page/view.php?id=617 */
void get_text_from_file(FILE* fp)
{
    int size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    s_text = malloc(size + 1);
    memset(s_text, 0, size + 1);

    fseek(fp, 0, SEEK_SET);
    fread(s_text, size, 1, fp);
}

/* Source: https://github.com/engineeringwitharavind/hackerrank/blob/master/HackerRank%20C%20Solutions/021.%20Querying%20the%20Document.c */
void get_doc(void)
{
    size_t para = 0;
    size_t sent = 0;
    size_t word = 0;
    size_t i;

    s_doc = (char****)malloc(2 * sizeof(char***));
    s_doc[para] = (char***)malloc(2 * sizeof(char**));
    s_doc[para][sent] = (char**)malloc(2 * sizeof(char*));
    s_doc[para][sent][word] = s_text;

    for (i = 0; s_text[i + 1] != '\0'; ++i) {
        switch (s_text[i]) {
        case '\n':
            if (s_text[i + 1] == '\n') {
                s_text[i++] = '\0';
            }
            s_doc[para][++sent] = NULL;
            ++para;
            sent = 0;
            word = 0;
            s_doc = (char****)realloc(s_doc, (para + 2) * sizeof(char***));
            s_doc[para] = (char***)malloc(2 * sizeof(char**));
            s_doc[para][sent] = (char**)malloc(2 * sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        case '.':
            /* intentional fallthrough */
        case '!':
            /* intentional fallthrough */
        case '?':
            if (s_text[i + 1] == '\n') {
                s_text[i] = '\0';
                break;
            } else if (s_text[i + 1] == ' ') {
                s_text[i++] = '\0';
            }
            s_doc[para][sent][++word] = NULL;
            ++sent;
            word = 0;
            s_doc[para] = (char***)realloc(s_doc[para], (sent + 2) * sizeof(char**));
            s_doc[para][sent] = (char**)malloc(2 * sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        case ' ':
            /* intentional fallthrough */
        case ',':
            if (s_text[i + 1] == ' ') {
                s_text[i++] = '\0';
            }
            ++word;
            s_doc[para][sent] = (char**)realloc(s_doc[para][sent], (word + 2) * sizeof(char*));
            s_doc[para][sent][word] = &s_text[i + 1];
            s_text[i] = '\0';
            break;
        default:
            break;
        }
    }
    s_doc[++para] = NULL;
    s_text[i] = '\0';
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

void dispose(void)
{

    size_t i;
    size_t j;

    free(s_text);

    for (i = 0; s_doc[i] != NULL; ++i) {
        for (j = 0; s_doc[i][j] != NULL; ++j) {
            free(s_doc[i][j]);
        }
    }

    for (i = 0; s_doc[i] != NULL; ++i) {
        free(s_doc[i]);
    }

    free(s_doc);
}

unsigned int get_total_word_count(void)
{
    size_t i;
    size_t j;
    size_t k;
    unsigned int count = 0;

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

    for (i = 0; s_doc[i] != NULL; ++i) {
        ++count;
    }
    return count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    const char*** paragraph = (const char***)s_doc[paragraph_index];

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
    const char** sentence = (const char**)s_doc[paragraph_index][sentence_index];

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
        fprintf(stderr, "No txt file\n");
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
