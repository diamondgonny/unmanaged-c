#ifndef DOCUMENT_ANALYZER_H
#define DOCUMENT_ANALYZER_H

#define TRUE (1)
#define FALSE (0)

int load_document(const char* document);

void dispose(void);

unsigned int get_total_word_count(void);

unsigned int get_total_sentence_count(void);

unsigned int get_total_paragraph_count(void);

const char*** get_paragraph_or_null(const unsigned int paragraph_index);

unsigned int get_paragraph_word_count(const char*** paragraph);

unsigned int get_paragraph_sentence_count(const char*** paragraph);

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index);

unsigned int get_sentence_word_count(const char** sentence);

int print_as_tree(const char* filename);

#endif /* DOCUMENT_ANALYZER_H */
