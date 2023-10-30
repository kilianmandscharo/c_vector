#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

Vector *Vec_new(size_t capacity) {
  Vector *vec = (Vector *)malloc(sizeof(Vector));

  if (vec == NULL) {
    return NULL;
  }

  int *data = (int *)malloc(capacity * sizeof(int));

  if (data == NULL) {
    return NULL;
  }

  vec->data = data;
  vec->length = 0;
  vec->capacity = capacity;

  return vec;
}

void Vec_free(Vector *v) {
  if (v == NULL)
    return;

  free(v->data);
  free(v);
}

int Vec_get(Vector *v, size_t index) { return v->data[index]; }

void Vec_set(Vector *v, size_t index, int val) { v->data[index] = val; }

void Vec_print(Vector *v) {
  if (v == NULL)
    return;

  for (int i = 0; i < v->length; i++) {
    printf((i < v->length - 1) ? "%d " : "%d", v->data[i]);
  }
  printf("\n");
}

void Vec_push(Vector *v, int val) {
  if (v == NULL)
    return;

  if (v->length >= v->capacity) {
    size_t new_capacity = v->capacity <= 1 ? 2 : (size_t)v->capacity * 1.5;
    int *new_data = (int *)realloc(v->data, new_capacity * sizeof(int));

    if (new_data == NULL) {
      // TODO: add error handling
    }

    v->data = new_data;
    v->capacity = new_capacity;
  }

  v->data[v->length++] = val;
}

PopResult Vec_pop(Vector *v) {
  PopResult result;

  if (v == NULL || v->length == 0) {
    result.success = false;
    result.val = -1;
    return result;
  }

  int val = v->data[v->length - 1];
  v->length--;

  result.success = true;
  result.val = val;

  return result;
}

void Vec_swap(Vector *v, size_t x, size_t y) {
  int tmp = v->data[x];
  v->data[x] = v->data[y];
  v->data[y] = tmp;
}

Vector *Vec_slice(Vector *v, size_t left, size_t right) {
  if (left >= right || v == NULL)
    return NULL;

  Vector *slice = (Vector *)malloc(sizeof(Vector));

  if (slice == NULL)
    return NULL;

  size_t slice_length = right - left;

  int *slice_data = (int *)malloc(slice_length * sizeof(int));

  if (slice_data == NULL)
    return NULL;

  for (int i = 0; i < slice_length; i++) {
    slice_data[i] = v->data[left + i];
  }

  slice->length = slice_length;
  slice->capacity = slice_length;
  slice->data = slice_data;

  return slice;
}
