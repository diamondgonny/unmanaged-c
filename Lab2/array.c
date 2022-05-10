#include <limits.h>
#include "array.h"


int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    int index_count = -1;
    int i = 0;
    for(i = 0; i < element_count; i++) {
        if(numbers[i] == num) {
            index_count = i;
            break;
        }
    }
    return index_count;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    int index_count = -1;
    int i = 0;
    for(i = element_count-1; i >= 0 ; i--) {
        if(numbers[i] == num) {
            index_count = i;
            break;
        }
    }
    return index_count;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    int index_count = -1;
    int i = 0;
    int max = 0;
    /*
    if(element_count = 0)
    {
        index_count = -1;
    }
    */
    for(i = 0; i < element_count; i++) {
        if(numbers[i] > max) {
            index_count = i;
        }
    }
    return index_count;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int index_count = -1;
    int i = 0;
    int min = INT_MAX;
    /*
    if(array is empty)
    {
        index_count = -1;
    }
    */
    for(i = 0; i < element_count; i++) {
        if(numbers[i] < min) {
            index_count = i;
        }
    }
    return index_count;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    int all_positive = 1;
    int i = 0;
    /*
    if(array is empty)
    {
        all_positive = FALSE;
    }
    */
    for(i = 0; i < element_count; i++) {
        if(numbers[i] <= 0) {
            all_positive = 0;
            break;
        }
    }
    return all_positive;
}

int has_even(const int numbers[], const size_t element_count)
{
    int even = 0;
    int i = 0;
    for(i = 0; i < element_count; i++) {
        if(numbers[i] % 2 == 0) {
            even = 1;
            break;
        }
    }
    return even;    
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    int insert_done = 0;
    int i = 0;
    /* 오류 조건 더 생각해보기...
    if(array is full, ele < pos)
    {
        insert_done = FALSE;
        return remove_done;
    }
    */
    for(i = element_count; i >= 0; i--) {
        if(i > pos) {
            numbers[i] = numbers[i-1];
        }

        else {
            numbers[i] = num;
            insert_done = 1;
            break;
        }
    }
    return insert_done;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    int remove_done = 0;
    int i = 0;
    /* 오류 조건 더 생각해보기...
    if(...)
    {
        remove_done = FALSE;
        return remove_done;  
    }
    */
    for(i = 0; i < element_count; i++) {
        if(i >= index) {
            numbers[i] = numbers[i+1];
        }
    }
    remove_done = 1;
    return remove_done;
} 
