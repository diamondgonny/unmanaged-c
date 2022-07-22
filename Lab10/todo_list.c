#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t todo_list;
    node_t* p;

    todo_list.dummy = 0;
    todo_list.head = NULL;
    todo_list.del = NULL;

    for (size_t i = 0; i < max_size; ++i) {
        node_t* tmp = todo_list.del;
        todo_list.del = p = malloc(sizeof(node_t));
        p->d_next = tmp;
    }

    return todo_list;
}

// free of init (bunch of node_ts)
void finalize_todo_list(todo_list_t* todo_list)
{
    while (complete_todo(todo_list) == true) {
    }

    while (todo_list->del != NULL) {
        node_t* tmp = todo_list->del->d_next;
        free(todo_list->del);
        todo_list->del = tmp;
    }
}

node_t* get_node_for_add_or_null(todo_list_t* todo_list, const int32_t priority)
{
    node_t* p;

    if (todo_list->del == NULL || priority < 0) {
        return NULL;
    } else {
        p = todo_list->del;
        todo_list->del = p->d_next;
        return p;
    }
}

void set_node_for_add_or_null(node_t* node, const int32_t priority, const char* task, node_t* next)
{
    node->priority = priority;
    node->task = (char*)malloc(strlen(task) + 1);
    strcpy(node->task, task);
    node->next = next;
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    // case 1, 2, 3;
    node_t* p = get_node_for_add_or_null(todo_list, priority);
    node_t* tmp;

    if (p == NULL || priority < 0) {
        return false;
    }

    if (todo_list->head == NULL || todo_list->head->priority < priority) {
        tmp = todo_list->head;
        todo_list->head = p;
        set_node_for_add_or_null(p, priority, task, tmp);
        ++todo_list->dummy;
        return true;
    }

    node_t** pp = &todo_list->head;
    node_t** next_pp = &(*pp)->next;

    while (*next_pp != NULL) {
        if ((*next_pp)->priority < priority) {
            break;
        }
        pp = next_pp;
        next_pp = &(*pp)->next;
    }
    tmp = (*pp)->next;
    (*pp)->next = p;
    set_node_for_add_or_null(p, priority, task, tmp);
    ++todo_list->dummy;
    return true;
}

void delete_node_for_add(todo_list_t* todo_list, node_t* node)
{
    node_t* tmp = todo_list->del;
    todo_list->del = node;
    node->d_next = tmp;
}

// free of set_node (string)
bool complete_todo(todo_list_t* todo_list)
{
    // case 1, 2;
    if (todo_list->head == NULL) {
        return false;
    }

    node_t* tmp = todo_list->head->next;
    free(todo_list->head->task);
    delete_node_for_add(todo_list, todo_list->head);
    todo_list->head = tmp;
    --todo_list->dummy;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->head == NULL) {
        return NULL;
    }
    return todo_list->head->task;
}

size_t get_count(const todo_list_t* todo_list)
{
    return (size_t)todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->head == NULL ? true : false;
}
