#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

#define LINE_LENGTH (1024)
#define TRUE (1)
#define FALSE (0)

/* ↓p_str */
/* Egestas diam in arcu cursus euismod quis viverra. Nunc non blandit massa enim nec dui.\n\0 (str) */

/* ↓pp                           */
/* pa_sentence[0] -> Egestas     */
/* pa_sentence[1] -> diam        */
/* ...                           */
/* pa_sentence[끝] -> (null)     */

/* ↓ppp                          */
/* pa_paragraph[0][] -> Egestas diam in ... quis viverra. */
/* pa_paragraph[1][] -> Nunc non blandit massa enim nec dui. */
/* pa_paragraph[끝][] -> (null)     */

static char* text;
static char**** doc;

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

/* Source : https://dojang.io/mod/page/view.php?id=617 */
void get_text_from_file(FILE* fp) {
    int size;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    text = malloc(size + 1);
    memset(text, 0, size + 1);

    fseek(fp, 0, SEEK_SET);
    fread(text, size, 1, fp);
}

/* Source : https://github.com/engineeringwitharavind/hackerrank/blob/master/HackerRank%20C%20Solutions/021.%20Querying%20the%20Document.c */
void get_doc(void)
{
    int para = 0;
    int sent = 0;
    int word = 0;
    int i;

    doc = (char****)malloc(sizeof(char***));
    doc[para] = (char***)malloc(sizeof(char**));
    doc[para][sent] = (char**)malloc(sizeof(char*));
    doc[para][sent][word] = text;

    for(i = 0; text[i + 1] != '\0'; ++i)
    {
        if (text[i + 1] == '\n'){
            text[i++] = '\0';
        }

        switch(text[i])
        {
        case '\n':
            doc = (char****)realloc(doc, ++para * sizeof(char***));
            sent = 0;
            /* intentional fallthrough */
        case '.':
        case '!':
        case '?':
            doc[para] = (char***)realloc(doc[para], ++sent * sizeof(char**));
            word = 0;
            /* intentional fallthrough */
        case ' ':
        case ',':
            doc[para][sent] = (char**)realloc(doc[para][sent], ++word * sizeof(char*));
            doc[para][sent][word] = &text[i + 1];
            text[i] = '\0';
            break;
        default:
            break;
        }
    }
    text[i] = '\0';
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

}

unsigned int get_total_sentence_count(void);

unsigned int get_total_paragraph_count(void);

const char*** get_paragraph_or_null(const unsigned int paragraph_index);

unsigned int get_paragraph_word_count(const char*** paragraph);

unsigned int get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index);

unsigned int get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);
