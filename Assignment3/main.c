#include <assert.h>
#include <string.h>
#include "document_analyzer.h"

void test_empty(void)
{
    assert(load_document("input_empty.txt") == TRUE);
    assert(print_as_tree("output_empty.txt") == FALSE);
    assert(get_total_word_count() == 0U);
    assert(get_total_sentence_count() == 0U);
    assert(get_total_paragraph_count() == 0U);
 
    dispose();
 
    puts("test_empty");
}
 
void test_document(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    assert(get_paragraph_or_null(0) == NULL);
    assert(get_sentence_or_null(0, 0) == NULL);
    assert(get_total_word_count() == 0U);
    assert(get_total_sentence_count() == 0U);
    assert(get_total_paragraph_count() == 0U);
    assert(print_as_tree("output_document.txt") == FALSE);
 
    assert(load_document("document.txt") == TRUE);
 
    assert(get_total_word_count() == 62U);
    assert(get_total_sentence_count() == 6U);
    assert(get_total_paragraph_count() == 3U);
 
    paragraph = get_paragraph_or_null(0);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 19);
    assert(get_paragraph_sentence_count(paragraph) == 1);
    sentence = get_sentence_or_null(0, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 19);
    assert(get_sentence_or_null(0, 1) == NULL);
 
    paragraph = get_paragraph_or_null(1);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 28);
    assert(get_paragraph_sentence_count(paragraph) == 3);
    sentence = get_sentence_or_null(1, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 10);
    sentence = get_sentence_or_null(1, 1);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 9);
    sentence = get_sentence_or_null(1, 2);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 9);
    assert(get_sentence_or_null(1, 3) == NULL);
 
    paragraph = get_paragraph_or_null(2);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 15);
    assert(get_paragraph_sentence_count(paragraph) == 2);
    sentence = get_sentence_or_null(2, 0);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 8);
    sentence = get_sentence_or_null(2, 1);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 7);
    assert(get_sentence_or_null(2, 2) == NULL);
 
    assert(get_paragraph_or_null(3) == NULL);
 
    assert(print_as_tree("output_document.txt") == TRUE);
 
    dispose();
 
    puts("test_document");
}

int main(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    unsigned int i = 0U;
    unsigned int j = 0U;

    assert(load_document("doesntexist.txt") == FALSE);
    assert(load_document("input.txt") == TRUE);

    assert(get_total_word_count() == 58U);
    assert(get_total_sentence_count() == 9U);
    assert(get_total_paragraph_count() == 3U);

    assert(get_paragraph_or_null(3) == NULL);

    paragraph = get_paragraph_or_null(1);
    assert(paragraph != NULL);
    assert(get_paragraph_word_count(paragraph) == 14);
    assert(get_paragraph_sentence_count(paragraph) == 2);

    assert(strcmp(paragraph[i][j++], "This") == 0);
    assert(strcmp(paragraph[i][j++], "is") == 0);
    assert(strcmp(paragraph[i][j++], "the") == 0);
    assert(strcmp(paragraph[i][j++], "second") == 0);
    assert(strcmp(paragraph[i++][j++], "paragraph") == 0);

    j = 0U;

    assert(strcmp(paragraph[i][j++], "I") == 0);
    assert(strcmp(paragraph[i][j++], "wonder") == 0);
    assert(strcmp(paragraph[i][j++], "how") == 0);
    assert(strcmp(paragraph[i][j++], "many") == 0);
    assert(strcmp(paragraph[i][j++], "sentences") == 0);
    assert(strcmp(paragraph[i][j++], "you") == 0);
    assert(strcmp(paragraph[i][j++], "will") == 0);
    assert(strcmp(paragraph[i][j++], "see") == 0);
    assert(strcmp(paragraph[i][j++], "here") == 0);

    sentence = get_sentence_or_null(0, 2);
    assert(sentence != NULL);
    assert(get_sentence_word_count(sentence) == 4);

    i = 0U;

    assert(strcmp(sentence[i++], "Is") == 0);
    assert(strcmp(sentence[i++], "this") == 0);
    assert(strcmp(sentence[i++], "too") == 0);
    assert(strcmp(sentence[i++], "easy") == 0);

    assert(print_as_tree("output.txt") == TRUE);

    dispose();

    test_empty();
    test_document();

    return 0;
}
