#ifndef MY_STRING_H
#define MY_STRING_H


void swap(char* a, char* b);

size_t get_str_length(const char* str);

size_t cmp_str(const char* str, const char* word);

void reverse(char* str);

int index_of(const char* str, const char* word);

void reverse_by_words(char* str);

char* tokenize(char* str_or_null, const char* delims);

char* reverse_tokenize(char* str_or_null, const char* delims);

#endif /* MY_STRING_H */
