#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct node {
    int32_t priority;
    char* task;
    struct node* next;
    struct node* d_next;
} node_t;

typedef struct todo_list {
    node_t* head;
    node_t* del;
    int dummy;
} todo_list_t;

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

node_t* get_node_for_add_or_null(todo_list_t* todo_list, const int32_t priority);

void set_node_for_add_or_null(node_t* node, const int32_t priority, const char* task, node_t* next);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

void delete_node_for_add(todo_list_t* todo_list, node_t* node);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
