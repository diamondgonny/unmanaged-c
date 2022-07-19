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

index_t get_index(todo_list_t* todo_list);

void delete_index(todo_list_t* todo_list, index_t index);

void set_node(node_t* node, const int32_t priority, const char* task, index_t tmp);

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
