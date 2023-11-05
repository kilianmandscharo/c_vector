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
void test_map();
int test_map_helper(int val);

int main() {
  printf("[INFO]: starting tests...\n");
  test_new();
  test_push();
  test_get();
  test_set();
  test_pop();
  test_swap();
  test_slice();
  test_map();
  printf("[INFO]: all tests executed successfully\n");
}

void test_new() {
  // Capacity 0
  Vector *vec = vec_new(0);
  assert(vec);
  assert(vec->data);
  assert(vec->length == 0);
  assert(vec->capacity == 1);

  // Capacity 10
  Vector *vec_2 = vec_new(10);
  assert(vec_2);
  assert(vec_2->data);
  assert(vec_2->length == 0);
  assert(vec_2->capacity == 10);

  vec_free(vec);
  vec_free(vec_2);
}

void test_push() {
  bool success;

  // Vector is NULL
  success = vec_push(NULL, 1);
  assert(!success);

  // Push to valid vector
  Vector *v = vec_new(10);
  for (int i = 0; i < 10; i++) {
    success = vec_push(v, i);
    assert(success);
  }
  assert(v->length == 10);
  assert(v->capacity == 10);

  // Push beyond capacity
  success = vec_push(v, 11);
  assert(success);
  assert(v->length == 11);
  assert(v->capacity == 15);

  vec_free(v);
}

void test_get() {
  Vector *v = vec_new(2);

  vec_push(v, 1);
  vec_push(v, 2);

  int val = vec_get(v, 0);
  assert(val == 1);

  val = vec_get(v, 1);
  assert(val == 2);

  vec_free(v);
}

void test_set() {
  Vector *v = vec_new(2);

  vec_push(v, 1);
  vec_push(v, 2);

  vec_set(v, 0, 5);
  vec_set(v, 1, 6);

  int val = vec_get(v, 0);
  assert(val == 5);

  val = vec_get(v, 1);
  assert(val == 6);

  vec_free(v);
}

void test_pop() {
  PopResult result;

  // Vector is NULL
  result = vec_pop(NULL);
  assert(!result.success);
  assert(result.val == -1);

  // Vector is empty
  Vector *v = vec_new(1);
  result = vec_pop(NULL);
  assert(!result.success);
  assert(result.val == -1);

  // Valid pop
  vec_push(v, 3);
  vec_push(v, 2);
  vec_push(v, 1);

  for (int i = 1; i < 4; i++) {
    result = vec_pop(v);
    assert(result.success);
    assert(result.val == i);
    assert(v->length == 3 - i);
  }

  vec_free(v);
}

void test_swap() {
  Vector *v = vec_new(2);

  vec_push(v, 1);
  vec_push(v, 2);

  vec_swap(v, 0, 1);

  assert(vec_get(v, 0) == 2);
  assert(vec_get(v, 1) == 1);

  vec_free(v);
}

void test_slice() {
  Vector *v = vec_new(10);

  for (int i = 0; i < 10; i++) {
    vec_push(v, i);
  }

  // Vector is NULL
  assert(vec_slice(NULL, 1, 3) == NULL);

  // Left is larger or equal to right
  assert(vec_slice(v, 3, 3) == NULL);

  // Valid slice
  Vector *slice = vec_slice(v, 0, 5);
  assert(slice);
  assert(slice->length == 5);
  assert(slice->capacity == 5);
  for (int i = 0; i < 5; i++) {
    assert(vec_get(slice, i) == i);
  }

  vec_free(v);
}

void test_map() {
  Vector *v = vec_new(10);

  for (int i = 1; i < 5; i++) {
    vec_push(v, i);
  }

  Vector *mapped = vec_map(v, test_map_helper);

  assert(v->length == mapped->length);
  assert(vec_get(mapped, 0) == 2);
  assert(vec_get(mapped, 1) == 4);
  assert(vec_get(mapped, 2) == 6);
  assert(vec_get(mapped, 3) == 8);

  vec_free(v);
  vec_free(mapped);
}

int test_map_helper(int val) { return val * 2; }
