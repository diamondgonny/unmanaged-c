#include <limits.h>
#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    const int* p = numbers;

    while (p < numbers + element_count && *p++ != num) {
    }

    return *--p == num ? p - numbers : -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    const int* p = numbers + element_count - 1;

    while (numbers <= p && *p-- != num) {
    }

    return *++p == num ? p - numbers : -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    const int* p = numbers;
    const int* p_max = numbers;

    if(element_count == 0) {
        return -1;
    }

    while (p < numbers + element_count) {
        if (*p > *p_max) {
            p_max = p;
        }
        ++p;
    }

    return *p_max != INT_MIN ? p_max - numbers : -1;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    const int* p = numbers;
    const int* p_min = numbers;

    if(element_count == 0) {
        return -1;
    }

    while (p < numbers + element_count) {
        if (*p < *p_min) {
            p_min = p;
        }
        ++p;
    }

    return *p_min != INT_MIN ? p_min - numbers : -1;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    const int* p = numbers;

    while (p < numbers + element_count && *p++ > 0) {
    }

    return *--p > 0 ? TRUE : FALSE;
}

int has_even(const int numbers[], const size_t element_count)
{
    const int* p = numbers;

    while (p < numbers + element_count && *p++ % 2 != 0) {
    }

    return *--p % 2 == 0 ? TRUE : FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    int* p = numbers + element_count;

    if (element_count < pos) {
        return FALSE;
    }

    while (numbers + pos <= p) {
        numbers + pos < p ? (*p = *(p - 1)) : (*p = num);
        --p;
    }

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    int* p = numbers + index;

    if (element_count == 0 || element_count <= index) {
        return FALSE;
    }

    while (p < numbers + element_count - 1) {
        *p = *(p + 1);
        ++p;
    }
    *p = INT_MIN;

    return TRUE;
}
