#include "vector.h"
#include <assert.h>
#include <stdio.h>

void test_new();
void test_push();
void test_get();
void test_set();
void test_pop();
void test_swap();
void test_slice();

int main() {
  test_new();
  test_push();
  test_get();
  test_set();
  test_pop();
  test_swap();
  test_slice();
}

void test_new() {
  // Capacity 0
  Vector *vec = Vec_new(0);
  assert(vec);
  assert(vec->data);
  assert(vec->length == 0);
  assert(vec->capacity == 1);

  // Capacity 10
  Vector *vec_2 = Vec_new(10);
  assert(vec_2);
  assert(vec_2->data);
  assert(vec_2->length == 0);
  assert(vec_2->capacity == 10);

  Vec_free(vec);
  Vec_free(vec_2);
}

void test_push() {
  bool success;

  // Vector is NULL
  success = Vec_push(NULL, 1);
  assert(!success);

  // Push to valid vector
  Vector *v = Vec_new(10);
  for (int i = 0; i < 10; i++) {
    success = Vec_push(v, i);
    assert(success);
  }
  assert(v->length == 10);
  assert(v->capacity == 10);

  // Push beyond capacity
  success = Vec_push(v, 11);
  assert(success);
  assert(v->length == 11);
  assert(v->capacity == 15);

  Vec_free(v);
}

void test_get() {
  Vector *v = Vec_new(2);

  Vec_push(v, 1);
  Vec_push(v, 2);

  int val = Vec_get(v, 0);
  assert(val == 1);

  val = Vec_get(v, 1);
  assert(val == 2);

  Vec_free(v);
}

void test_set() {
  Vector *v = Vec_new(2);

  Vec_push(v, 1);
  Vec_push(v, 2);

  Vec_set(v, 0, 5);
  Vec_set(v, 1, 6);

  int val = Vec_get(v, 0);
  assert(val == 5);

  val = Vec_get(v, 1);
  assert(val == 6);

  Vec_free(v);
}

void test_pop() {
  PopResult result;

  // Vector is NULL
  result = Vec_pop(NULL);
  assert(!result.success);
  assert(result.val == -1);

  // Vector is empty
  Vector *v = Vec_new(1);
  result = Vec_pop(NULL);
  assert(!result.success);
  assert(result.val == -1);

  // Valid pop
  Vec_push(v, 3);
  Vec_push(v, 2);
  Vec_push(v, 1);

  for (int i = 1; i < 4; i++) {
    result = Vec_pop(v);
    assert(result.success);
    assert(result.val == i);
    assert(v->length == 3 - i);
  }

  Vec_free(v);
}

void test_swap() {
  Vector *v = Vec_new(2);

  Vec_push(v, 1);
  Vec_push(v, 2);

  Vec_swap(v, 0, 1);

  assert(Vec_get(v, 0) == 2);
  assert(Vec_get(v, 1) == 1);

  Vec_free(v);
}

void test_slice() {
  Vector *v = Vec_new(10);

  for (int i = 0; i < 10; i++) {
    Vec_push(v, i);
  }

  // Vector is NULL
  assert(Vec_slice(NULL, 1, 3) == NULL);

  // Left is larger or equal to right
  assert(Vec_slice(v, 3, 3) == NULL);

  // Valid slice
  Vector *slice = Vec_slice(v, 0, 5);
  assert(slice);
  assert(slice->length == 5);
  assert(slice->capacity == 5);
  for (int i = 0; i < 5; i++) {
    assert(Vec_get(slice, i) == i);
  }

  Vec_free(v);
}
