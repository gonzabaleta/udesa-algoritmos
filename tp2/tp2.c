#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

struct node;
typedef struct node node_t;

struct node
{
    void *value;
    node_t *next;
    node_t *prev;
};

typedef struct list
{
    node_t *head;
    node_t *tail;
    size_t size;
} list_t;

struct list_iter
{
    list_t *list;
    node_t *curr;
};

list_t *list_new()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL)
    {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

size_t list_length(const list_t *list)
{
    return list->size;
}

bool list_is_empty(const list_t *list)
{
    return list->size == 0;
}

bool list_insert_head(list_t *list, void *value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        return false;
    }

    node->value = value;
    node->next = list->head;
    node->prev = NULL;
    if (list->head)
    {
        list->head->prev = node;
    }
    list->head = node;
    if (list->tail == NULL)
    {
        list->tail = node;
    }
    list->size++;
    return true;
}

bool list_insert_tail(list_t *list, void *value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        return false;
    }

    node->value = value;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = node;
    }

    if (list->head == NULL)
    {
        list->head = node;
    }

    list->tail = node;
    list->size++;
    return true;
}

void *list_peek_head(const list_t *list)
{
    if (list && list->head)
    {
        return list->head->value;
    }
    return NULL;
}

void *list_peek_tail(const list_t *list)
{
    if (list && list->tail)
    {
        return list->tail->value;
    }
    return NULL;
}

void *list_pop_head(list_t *list)
{
    node_t *tmp = list->head;

    if (list->head == NULL)
        return NULL;

    list->head = list->head->next;
    if (list->head)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }
    list->size--;
    return tmp->value;
}

void *list_pop_tail(list_t *list)
{
    if (list->tail == NULL)
        return NULL;

    node_t *tmp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }

    list->size--;

    return tmp->value;
}

void list_destroy(list_t *list, void destroy_value(void *))
{
    if (list == NULL)
        return;
    node_t *curr = list->tail;
    if (destroy_value)
    {
        while (curr != NULL)
        {
            node_t *prev = curr->prev;
            destroy_value(curr);
            curr = prev;
        }
    }

    free(list);
}

list_iter_t *list_iter_create_head(list_t *list)
{
    list_iter_t *iter = (list_iter_t *)malloc(sizeof(list_iter_t));
    if (iter == NULL)
        return NULL;

    iter->list = list;
    iter->curr = list->head;
    return iter;
}

list_iter_t *list_iter_create_tail(list_t *list)
{
    list_iter_t *iter = (list_iter_t *)malloc(sizeof(list_iter_t));
    if (iter == NULL)
        return NULL;

    iter->list = list;
    iter->curr = list->tail;
    return iter;
}

bool list_iter_forward(list_iter_t *iter)
{
    if (iter->curr == NULL || iter->curr->next == NULL)
        return false;

    iter->curr = iter->curr->next;
    return true;
}

bool list_iter_backward(list_iter_t *iter)
{
    if (iter->curr == NULL || iter->curr->prev == NULL)
        return false;

    iter->curr = iter->curr->prev;
    return true;
}

void *list_iter_peek_current(const list_iter_t *iter)
{
    if (iter->curr == NULL)
    {
        return NULL;
    }
    return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter)
{
    return iter->curr->next == NULL;
}

bool list_iter_at_first(const list_iter_t *iter)
{
    return iter->curr->prev == NULL;
}

void list_iter_destroy(list_iter_t *iter)
{
    free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value)
{

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        return false;
    }

    node->value = value;
    node->prev = iter->curr;

    if (iter->curr == NULL)
    {
        node->next = NULL;
        iter->list->head = node;
        iter->list->tail = node;
        iter->curr = node;
    }
    else if (iter->curr == iter->list->tail)
    {
        node->next = NULL;
        iter->list->tail = node;
        iter->curr->next = node;
    }
    else
    {
        node->next = iter->curr->next;
        iter->curr->next->prev = node;
        iter->curr->next = node;
    }

    return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value)
{

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        return false;
    }

    node->value = value;
    node->next = iter->curr;

    if (iter->curr == NULL)
    {
        node->prev = NULL;
        iter->list->head = node;
        iter->list->tail = node;
        iter->curr = node;
    }
    else if (iter->curr == iter->list->head)
    {
        node->prev = NULL;
        iter->list->head = node;
        iter->curr->prev = node;
    }
    else
    {
        node->prev = iter->curr->prev;
        iter->curr->prev->next = node;
        iter->curr->prev = node;
    }

    return true;
}

void *list_iter_delete(list_iter_t *iter)
{
    node_t *node = iter->curr;
    if (node == NULL || iter->curr == NULL)
    {
        return false;
    }
    void *value = node->value;
    if (iter->curr->prev == NULL)
    {
        iter->list->head = iter->curr->next;
        iter->curr = iter->curr->next;
    }
    else
    {

        iter->curr->prev->next = iter->curr->next;
        iter->curr = iter->curr->prev;
    }

    iter->list->size--;
    free(node);
    return value;
}