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

void Vec_print(Vector *v);
void Vec_free(Vector *v);
void Vec_push(Vector *v, int val);
PopResult Vec_pop(Vector *v);
Vector *Vec_new(size_t len);
Vector *Vec_slice(Vector *v, size_t left, size_t right);
int Vec_get(Vector *v, size_t index);

#endif
