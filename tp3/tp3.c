#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INITIAL_DICT_DEGREE 512
#define LOAD_FACTOR 0.8

typedef struct Node
{
  char *key;
  char *value;
  struct Node *next;
} Node;

struct dictionary
{
  Node **buckets;
  size_t size;
  size_t degree;
  destroy_f destroy;
};

dictionary_t *dictionary_create(destroy_f destroy)
{
  dictionary_t *dictionary = malloc(sizeof(dictionary_t));
  if (dictionary == NULL)
  {
    return NULL;
  }

  dictionary->buckets = malloc(sizeof(Node *) * INITIAL_DICT_DEGREE);
  if (dictionary->buckets == NULL)
  {
    free(dictionary);
    return NULL;
  }
  dictionary->degree = INITIAL_DICT_DEGREE;
  dictionary->size = 0;
  dictionary->destroy = destroy;

  for (int i = 0; i < INITIAL_DICT_DEGREE; i++)
  {
    dictionary->buckets[i] = NULL;
  }

  return dictionary;
};

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value)
{
  if (dictionary->size / dictionary->degree > LOAD_FACTOR)
  {
    dictionary_rehash(dictionary);
  }

  Node *existing_node = dictionary_get_node(dictionary, key);
  if (existing_node != NULL)
  {
    if (dictionary->destroy != NULL)
    {
      dictionary->destroy(existing_node->value);
    }
    existing_node->value = value;
    return true;
  }

  Node *node = malloc(sizeof(Node));
  if (node == NULL)
  {
    return false;
  }

  node->key = malloc(strlen(key) + 1);
  if (node->key == NULL)
  {
    free(node);
    return false;
  }

  size_t index = get_bucket(key, dictionary->degree);

  strcpy(node->key, key);
  node->value = value;
  node->next = dictionary->buckets[index];

  dictionary->buckets[index] = node;
  dictionary->size++;
  return true;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err)
{
  Node *node = dictionary_get_node(dictionary, key);
  if (node != NULL)
  {
    *err = false;
    return node->value;
  }
  *err = true;
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key)
{
  size_t index = get_bucket(key, dictionary->degree);
  Node *node = dictionary->buckets[index];
  Node *prev = NULL;

  while (node != NULL)
  {
    if (strcmp(node->key, key) == 0)
    {
      if (prev == NULL)
      {
        dictionary->buckets[index] = node->next;
      }
      else
      {
        prev->next = node->next;
      }

      if (dictionary->destroy != NULL)
      {
        dictionary->destroy(node->value);
      }

      free(node->key);
      free(node);
      dictionary->size--;
      return true;
    }
    prev = node;
    node = node->next;
  }

  return false;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err)
{
  Node *node = dictionary_get_node(dictionary, key);
  if (node != NULL)
  {
    *err = false;

    void *value = node->value;
    destroy_f tmp_destroy = dictionary->destroy;
    dictionary->destroy = NULL;
    dictionary_delete(dictionary, key);
    dictionary->destroy = tmp_destroy;
    return value;
  }

  *err = true;
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key)
{
  return dictionary_get_node(dictionary, key) != NULL;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->size; };

void dictionary_destroy(dictionary_t *dictionary)
{
  for (int i = 0; i < dictionary->degree; i++)
  {
    Node *node = dictionary->buckets[i];
    while (node != NULL)
    {
      Node *next = node->next;
      if (dictionary->destroy != NULL)
      {
        dictionary->destroy(node->value);
      }
      free(node->key);
      free(node);
      node = next;
    }
  }
  free(dictionary->buckets);
  free(dictionary);
};

/* CUSTOM FUNCTIONS */

Node *dictionary_get_node(dictionary_t *dictionary, const char *key)
{
  size_t index = get_bucket(key, dictionary->degree);
  Node *node = dictionary->buckets[index];
  while (node != NULL)
  {
    if (strcmp(node->key, key) == 0)
    {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

bool dictionary_rehash(dictionary_t *dictionary)
{
  size_t new_degree = dictionary->degree * 2;
  Node **new_buckets = malloc(sizeof(Node *) * new_degree);
  if (new_buckets == NULL)
  {
    return false;
  }

  for (int i = 0; i < new_degree; i++)
  {
    new_buckets[i] = NULL;
  }

  for (int i = 0; i < dictionary->degree; i++)
  {
    Node *node = dictionary->buckets[i];
    while (node != NULL)
    {
      Node *next = node->next;
      size_t index = get_bucket(node->key, new_degree);
      node->next = new_buckets[index];
      new_buckets[index] = node;
      node = next;
    }
  }

  free(dictionary->buckets);
  dictionary->buckets = new_buckets;
  dictionary->degree = new_degree;
  return true;
}

size_t get_bucket(const char *key, size_t degree)
{
  return hash(key, (int)strlen(key), 42) % degree;
}

// Función de MurMurHash
uint32_t hash(const char *key, int len, uint32_t seed)
{
  const uint32_t m = 0x5bd1e995;
  const int r = 24;
  uint32_t h = seed ^ len;

  const unsigned char *data = (const unsigned char *)key;
  while (len >= 4)
  {
    uint32_t k = *(uint32_t *)data;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len)
  {
  case 3:
    h ^= data[2] << 16;
  case 2:
    h ^= data[1] << 8;
  case 1:
    h ^= data[0];
    h *= m;
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}