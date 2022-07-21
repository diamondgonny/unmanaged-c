#include <stdlib.h>
#include <string.h>
#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    size_t i;
    todo_list_t todo_list;

    // todo_list.node에 '(node_t단위)배열'로 힙에 할당된 메모리 안에서, '연결리스트와 같은 구조'를 가짐
    // (구조도는 맨 아래 링크 이미지 참조)
    todo_list.node = malloc(max_size * sizeof(node_t));
    todo_list.head = INT_MIN;
    todo_list.deleted = INT_MIN;
    todo_list.dummy = 0;

    // 프리리스트 세팅 ('활성화' '비활성화' 두 개의 연결리스트를 사용할건데, 먼저 후자에 전부 세팅하면서 시작)
    for (i = max_size; i != 0; --i) {
        index_t tmp = todo_list.deleted;
        todo_list.deleted = i - 1;
        (todo_list.node + i - 1)->d_next = tmp;
    }
    return todo_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    while (complete_todo(todo_list) == true) {
    }
    free(todo_list->node);
}

index_t get_index_for_add(todo_list_t* todo_list, const int32_t priority)
{
    if (todo_list->deleted == INT_MIN || priority < 0) {
        return INT_MIN;
    } else {
        index_t index = todo_list->deleted;
        todo_list->deleted = (todo_list->node + index)->d_next;
        return index;
    }
}

void set_node_for_add(node_t* node, const int32_t priority, const char* task, index_t next)
{
    node->priority = priority;
    node->task = (char*)malloc(strlen(task) + 1);
    strcpy(node->task, task);
    node->next = next;
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    index_t index = get_index_for_add(todo_list, priority);
    index_t tmp;

    // case 1) '할일목록'이 꽉찼을 때 혹은 priority가 음수일 때의 false 반환
    if (index == INT_MIN || priority < 0) {
        return false;
    }

    // case 2) '할일목록'이 비었을 때 혹은 가장 높은 priority가 들어올 때의 삽입 (최전방 노드)
    if (todo_list->head == INT_MIN || (todo_list->node + todo_list->head)->priority < priority) {
        tmp = todo_list->head;
        todo_list->head = index;
        set_node_for_add(todo_list->node + index, priority, task, tmp);
        ++todo_list->dummy;
        return true;
    }

    index_t* p = &todo_list->head;
    index_t* next_p = &(todo_list->node + *p)->next;

    // case 3) 내림차순 검색 및 삽입
    while (*next_p != INT_MIN) {
        if ((todo_list->node + *next_p)->priority < priority) {
            break;
        }
        p = next_p;
        next_p = &(todo_list->node + *p)->next;
    }
    tmp = (todo_list->node + *p)->next;
    (todo_list->node + *p)->next = index;
    set_node_for_add(todo_list->node + index, priority, task, tmp);
    ++todo_list->dummy;
    return true;
}

void delete_index_for_complete(todo_list_t* todo_list, index_t index)
{
    if (todo_list->deleted == INT_MIN) {
        todo_list->deleted = index;
        (todo_list->node + index)->d_next = INT_MIN;
    } else {
        index_t tmp = todo_list->deleted;
        todo_list->deleted = index;
        (todo_list->node + index)->d_next = tmp;
    }
}

bool complete_todo(todo_list_t* todo_list)
{
    index_t tmp;

    // case 1) '할일목록'이 비었을 때의 false 반환
    if (todo_list->head == INT_MIN) {
        return false;
    }

    // case 2) '할일목록' 중 가장 높은 priority를 가진 task 삭제 (최전방 노드)
    tmp = (todo_list->node + todo_list->head)->next;
    free((todo_list->node + todo_list->head)->task);
    delete_index_for_complete(todo_list, todo_list->head);
    todo_list->head = tmp;
    --todo_list->dummy;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->head == INT_MIN) {
        return NULL;
    }
    return (todo_list->node + todo_list->head)->task;
}

size_t get_count(const todo_list_t* todo_list)
{
    return (size_t)todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->head == INT_MIN ? true : false;
}

// 참고) Doit_자료구조와함께배우는알고리즘입문_C언어편_Chap09(커서로연결리스트만들기)
// https://drive.google.com/file/d/1szWjGb_hAZadx2e9sH4Qlu4ykcRts8Vw/view
// https://velog.velcdn.com/images%2Fdkswlgus00%2Fpost%2Fda7627e1-fe27-4f28-948d-a22b66edd222%2Fimage.png
