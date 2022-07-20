#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

index_t get_index(todo_list_t* todo_list)
{
    // 프리리스트 비었을 때, 아닐 때
    if (todo_list->deleted == INT_MIN) {
        return INT_MIN;
    } else {
        index_t index = todo_list->deleted;
        todo_list->deleted = todo_list->node[index].d_next;
        return index;
    }
}

void delete_index(todo_list_t* todo_list, index_t index)
{
    // 프리리스트 비었을 때, 아닐 때
    if (todo_list->deleted == INT_MIN) {
        todo_list->deleted = index;
        todo_list->node[index].d_next = INT_MIN;
    } else {
        index_t tmp = todo_list->deleted;
        todo_list->deleted = index;
        todo_list->node[index].d_next = tmp;
    }
}

void set_node(node_t* node, const int32_t priority, const char* task, index_t tmp)
{
    node->order = priority;
    node->task = (char*)malloc(strlen(task) + 1);
    strcpy(node->task, task);
    node->next = tmp;
}

todo_list_t init_todo_list(size_t max_size)
{
    size_t i;
    todo_list_t todo_list;

    todo_list.node = malloc(max_size * sizeof(node_t));
    // 프리리스트 초기 세팅
    for (i = max_size; i != 0; --i) {
        index_t tmp = todo_list.deleted;
        todo_list.deleted = i - 1;
        todo_list.node[i - 1].d_next = tmp;
    }

    todo_list.head = INT_MIN;
    todo_list.dummy = 0;

    return todo_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    while (complete_todo(todo_list) == true) {
    }

    free(todo_list->node);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    index_t index;
    index_t tmp = todo_list->head;
    index_t* p = &todo_list->head; // 첫 번째 노드를 가리킴
    index_t* next_p;

    // priority가 음수일 때
    if (priority < 0) {
        return false;
    }

    // 노드가 꽉찼을 때
    index = get_index(todo_list);
    if (index == INT_MIN) {
        return false;
    }

    // 노드가 없을 때 혹은 최고 우선순위일 때 (첫 번째 위치에 배치)
    if (*p == INT_MIN || (&todo_list->node[*p])->order < priority) {
        todo_list->head = index;
        set_node(&todo_list->node[index], priority, task, tmp);
        ++todo_list->dummy;
        return true;
    }
    // 두 번째 노드를 가리킴 (단, 노드 한 개일 때는 INT_MIN)
    next_p = &(&todo_list->node[*p])->next;

    // 내림차순 정렬된 연결리스트에 추가하기
    while (*next_p != INT_MIN) {
        if ((&todo_list->node[*next_p])->order < priority) {
            break;
        }
        p = next_p; // ++p;
        next_p = &(&todo_list->node[*p])->next; // ++next_p;
    }

    tmp = (&todo_list->node[*p])->next;
    (&todo_list->node[*p])->next = index;
    set_node(&todo_list->node[index], priority, task, tmp);
    ++todo_list->dummy;

    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    index_t tmp;

    if (todo_list->head == INT_MIN) {
        return false;
    }

    tmp = todo_list->node[todo_list->head].next;
    free((&todo_list->node[todo_list->head])->task);
    // ***포인터 관련 테스트 검토
    delete_index(todo_list, todo_list->head);
    todo_list->head = tmp;
    --todo_list->dummy;

    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->head == INT_MIN) {
        return NULL;
    }

    return todo_list->node[todo_list->head].task;
}

size_t get_count(const todo_list_t* todo_list)
{
    return (size_t)todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->head == INT_MIN ? true : false;
}
