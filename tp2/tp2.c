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
    return list->head == NULL;
}

bool list_insert_head(list_t *list, void *value)
{
    node_t *node = (node_t *)create_node(value, list->head, NULL);
    if (node == NULL)
        return false;

    link_node_in_list(list, node, list->head, NULL);
    return true;
}

bool list_insert_tail(list_t *list, void *value)
{
    node_t *node = create_node(value, NULL, list->tail);
    if (node == NULL)
        return false;

    link_node_in_list(list, node, NULL, list->tail);
    return true;
}

void *list_peek_head(const list_t *list)
{
    if (list_is_empty(list))
        return NULL;

    return list->head->value;
}

void *list_peek_tail(const list_t *list)
{
    if (list_is_empty(list))
        return NULL;

    return list->tail->value;
}

void *list_pop_head(list_t *list)
{
    if (list_is_empty(list))
        return NULL;

    node_t *tmp = list->head;

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

    void *value = tmp->value;
    free(tmp);
    return value;
}

void *list_pop_tail(list_t *list)
{
    if (list_is_empty(list))
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
    void *value = tmp->value;
    free(tmp);
    return value;
}

void list_destroy(list_t *list, void destroy_value(void *))
{
    if (list == NULL)
        return;

    while (!list_is_empty(list))
    {
        void *value = list_pop_head(list);
        if (destroy_value)
            destroy_value(value);
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
    if (list_is_empty(iter->list))
        return NULL;

    return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter)
{
    if (list_is_empty(iter->list))
        return true;

    return iter->curr->next == NULL;
}

bool list_iter_at_first(const list_iter_t *iter)
{
    if (list_is_empty(iter->list))
        return true;

    return iter->curr->prev == NULL;
}

void list_iter_destroy(list_iter_t *iter)
{
    if (iter != NULL)
        free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value)
{

    node_t *node = create_node(value, NULL, iter->curr);
    if (node == NULL)
        return false;

    if (iter->curr == NULL)
    {
        link_node_in_list(iter->list, node, NULL, NULL);
        iter->curr = node;
    }
    else if (list_iter_at_last(iter))
    {
        link_node_in_list(iter->list, node, NULL, iter->curr);
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

    node_t *node = create_node(value, iter->curr, NULL);
    if (node == NULL)
    {
        return false;
    }

    if (list_is_empty(iter->list))
    {
        link_node_in_list(iter->list, node, NULL, NULL);
        iter->curr = node;
    }
    else if (list_iter_at_first(iter))
    {
        link_node_in_list(iter->list, node, iter->curr, NULL);
    }
    else
    {
        link_node_in_list(iter->list, node, iter->curr, iter->curr->prev);
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

    if (iter->list->size == 1)
    {
        iter->list->head = NULL;
        iter->list->tail = NULL;
        iter->curr = NULL;
    }
    else if (list_iter_at_first(iter))
    {
        iter->list->head = iter->curr->next;
        iter->list->head->prev = NULL;
        iter->curr = iter->curr->next;
    }
    else if (list_iter_at_last(iter))
    {
        iter->list->tail = iter->curr->prev;
        iter->list->tail->next = NULL;
        iter->curr = iter->curr->prev;
    }
    else
    {
        iter->curr->prev->next = iter->curr->next;
        iter->curr->next->prev = iter->curr->prev;
        iter->curr = iter->curr->next;
    }

    iter->list->size--;
    free(node);
    return value;
}

// CUSTOM FUNCTIONS
void *create_node(void *value, node_t *next, node_t *prev)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        return NULL;
    }

    node->value = value;
    node->next = next;
    node->prev = prev;
    return node;
}

void link_node_in_list(list_t *list, node_t *node, node_t *next, node_t *prev)
{
    if (prev)
    {
        prev->next = node;
    }
    else
    {
        list->head = node;
    }
    if (next)
    {
        next->prev = node;
    }
    else
    {
        list->tail = node;
    }
    list->size++;
}