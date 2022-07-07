#include <stdio.h>
#include "parentheses.h"

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char* p_rparen = str;
    size_t len = 0;

    while (*p_rparen != '\0') {
        if (*p_rparen == ')' || *p_rparen == '}' || *p_rparen == ']' || *p_rparen == '>') {
            len = enqueue_parentheses(ringbuffer, str, p_rparen, len);
        }
        ++p_rparen;
    }

    if (len > ringbuffer->max_size) {
        ringbuffer->start_index = len % ringbuffer->max_size;
    } else {
        ringbuffer->start_index = 0;
    }

    return len;
}

size_t enqueue_parentheses(ringbuffer_t* ringbuffer, const char* str, const char* p_rparen, size_t len)
{
    const char* p = p_rparen;
    char rparen = *p_rparen;
    char lparen;
    size_t paren_matcher = 0;

    /* note : the function works as if only ')}]>' have accepted, and ASCII code was referred  */
    *p_rparen == ')' ? lparen = rparen - 1 : (lparen = rparen - 2);

    for (; p >= str; --p) {
        if (p == p_rparen) {
            continue;
        }
        if (*p == rparen) {
            ++paren_matcher;
        }
        if (*p == lparen) {
            if (paren_matcher == 0) {
                size_t ring_index = len % ringbuffer->max_size;
                ringbuffer->parentheses[ring_index].closing_index = p_rparen - str;
                ringbuffer->parentheses[ring_index].opening_index = p - str;
                ++len;
                break;
            } else {
                --paren_matcher;
            }
        }
    }

    return len;
}

/* how the while loop in 'find_matching...' works on... */
/* (str)          ----------- ↓p_rparen -------->        */
/*  ( ( ( ] { { { < > < > < > [ m o r e } } { } } ) '\0'  */

/* how the function 'enqueue parentheses' works on...   */
/* (str)          <------ ↓p --------  (↓p_rparen)       */
/*  ( ( ( ] { { { < > < > < > [ m o r e } } { } } ) '\0'  */

/* 'ring buffer'                      */
/* (parentheses[ring_index])         */
/*  V V V ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ  */
