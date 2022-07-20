#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef int index_t;

typedef struct node {
    int32_t order;
    char* task;
    index_t next;
    index_t d_next;
} node_t;

typedef struct todo_list {
    node_t* node;
    index_t head;
    index_t deleted;
    int dummy;
} todo_list_t;

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

index_t get_index_for_add(todo_list_t* todo_list, const int32_t priority);

void set_node_for_add(node_t* node, const int32_t priority, const char* task, index_t tmp);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

void delete_index_for_complete(todo_list_t* todo_list, index_t index);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
