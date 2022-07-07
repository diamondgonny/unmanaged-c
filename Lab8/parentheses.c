#include <stdio.h>
#include "parentheses.h"

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char* p_str_start = str;
    size_t len = 0;

    while (*p_str_start != '\0') {
        len = enqueue_parentheses(ringbuffer, str, p_str_start, len);
        ++p_str_start;
    }

    if (len > ringbuffer->max_size) {
        ringbuffer->start_index = len % ringbuffer->max_size;
    } else {
        ringbuffer->start_index = 0;
    }

    return len;
}

size_t enqueue_parentheses(ringbuffer_t* ringbuffer, const char* str, const char* p_str_start, size_t len)
{
    const char* p_str = p_str_start;
    char right_pair = *p_str_start;
    char left_pair;
    size_t paren_matcher = 0;

    if (*p_str == ')') {
        left_pair = *p_str - 1;
    } else if (*p_str == '}' || *p_str == ']' || *p_str == '>') {
        left_pair = *p_str - 2;
    } else {
        return len;
    }

    for (; p_str >= str; --p_str) {
        if (p_str == p_str_start) {
            continue;
        }
        if (*p_str == right_pair) {
            ++paren_matcher;
        }
        if (*p_str == left_pair) {
            if (paren_matcher == 0) {
                size_t ring_index = len % ringbuffer->max_size;
                ringbuffer->parentheses[ring_index].closing_index = p_str_start - str;
                ringbuffer->parentheses[ring_index].opening_index = p_str - str;
                ++len;
                break;
            } else {
                --paren_matcher;
            }
        }
    }

    return len;
}

/* how the function 'enqueue parentheses' works on */
/*(str)    <------ ↓p_str --------    (↓p_str_start)    */
/* ( ( ( ] { { { < > < > < > [ m o r e } } { } } ) '\0' */

/*(parentheses[ring_index]) */
/* V V V ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
