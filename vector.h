#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *data;
  size_t capacity;
  size_t length;
} Vector;

typedef struct {
  bool success;
  int val;
} PopResult;

Vector *vec_new(size_t len);
void vec_free(Vector *v);
int vec_get(Vector *v, size_t index);
void vec_set(Vector *v, size_t index, int val);
void vec_print(Vector *v);
bool vec_push(Vector *v, int val);
PopResult vec_pop(Vector *v);
Vector *vec_slice(Vector *v, size_t left, size_t right);
void vec_swap(Vector *v, size_t x, size_t y);
Vector *vec_map(Vector *v, int (*f)(int));

#endif
