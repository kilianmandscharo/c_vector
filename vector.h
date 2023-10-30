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

Vector *Vec_new(size_t len);
void Vec_free(Vector *v);
int Vec_get(Vector *v, size_t index);
void Vec_set(Vector *v, size_t index, int val);
void Vec_print(Vector *v);
void Vec_push(Vector *v, int val);
PopResult Vec_pop(Vector *v);
Vector *Vec_slice(Vector *v, size_t left, size_t right);
void Vec_swap(Vector *v, size_t x, size_t y);

#endif
