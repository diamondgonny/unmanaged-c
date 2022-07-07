#include <stdio.h>
#include "parentheses.h"

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char* p_str = str;
    size_t len = 0;

    while (*p_str != '\0') {
        len = enqueue_parentheses(ringbuffer, str, p_str, len);
        ++p_str;
    }

    if (len > ringbuffer->max_size) {
        ringbuffer->start_index = len % ringbuffer->max_size;
    } else {
        ringbuffer->start_index = 0;
    }

    return len;
}

size_t enqueue_parentheses(ringbuffer_t* ringbuffer, const char* str, const char* p_str, size_t len)
{
    const char* p_str_start = p_str;
    char right_pair = *p_str;
    char left_pair;
    /* 0이 되면 Queue에 값 저장, 반복문 진입시 자기 자신을 1 더하고 시작 */
    int paren_matcher = -1;

    if (*p_str == ')') {
        left_pair = *p_str - 1;
    } else if (*p_str == '}' || *p_str == ']' || *p_str == '>') {
        left_pair = *p_str - 2;
    } else {
        return len;
    }

    for (; p_str >= str; --p_str) {
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
