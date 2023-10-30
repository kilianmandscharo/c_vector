#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/**
 * Create a new vector with the specified initial capacity.
 *
 * @param capacity The initial capacity of the vector.
 *                If capacity is less than 1, it will be set to 1.
 * @return A pointer to the newly created vector.
 *         Returns NULL if memory allocation fails.
 */
Vector *Vec_new(size_t capacity) {
  Vector *vec = (Vector *)malloc(sizeof(Vector));

  if (vec == NULL) {
    return NULL;
  }

  capacity = (capacity < 1) ? 1 : capacity;

  int *data = (int *)malloc(capacity * sizeof(int));

  if (data == NULL) {
    return NULL;
  }

  vec->data = data;
  vec->length = 0;
  vec->capacity = capacity;

  return vec;
}

/**
 * Deallocate the memory used by the vector and its data.
 *
 * This function releases the memory allocated for the vector structure and the
 * data array. It is safe to call this function with a NULL pointer, in which
 * case it has no effect.
 *
 * @param v A pointer to the vector to be deallocated. It can be NULL.
 */
void Vec_free(Vector *v) {
  if (v == NULL)
    return;

  free(v->data);
  free(v);
}

/**
 * Get the integer value at the specified index in the vector.
 *
 * If the provided index is out of bounds (i.e., less than 0 or greater than
 * or equal to the vector's length), the behavior is undefined.
 *
 * @param v A pointer to the vector from which the integer is to be retrieved.
 * @param index The index at which to retrieve the integer.
 * @return The integer value at the specified index.
 */
int Vec_get(Vector *v, size_t index) { return v->data[index]; }

/**
 * Set the integer value at the specified index in the vector.
 *
 * If the provided index is out of bounds (i.e., less than 0 or greater than
 * or equal to the vector's length), the behavior is undefined.
 *
 * @param v A pointer to the vector in which the integer value is to be set.
 * @param index The index at which to set the integer.
 * @param val The integer value to be set at the specified index.
 */
void Vec_set(Vector *v, size_t index, int val) { v->data[index] = val; }

/**
 * Print the elements of the vector to the standard output.
 *
 * If the provided vector is NULL, this function has no effect.
 *
 * @param v A pointer to the vector whose elements should be printed.
 */
void Vec_print(Vector *v) {
  if (v == NULL)
    return;

  for (int i = 0; i < v->length; i++) {
    printf((i < v->length - 1) ? "%d " : "%d", v->data[i]);
  }
  printf("\n");
}

/**
 * Push an integer onto the end of the vector.
 *
 * If the vector is full, it automatically reallocates memory to accommodate
 * the new element, expanding its capacity by 5ß% if necessary. If reallocation
 * fails, the function returns false, and the vector remains unchanged.
 *
 * @param v A pointer to the vector to which the integer should be pushed.
 *          It can be NULL.
 * @param val The integer value to be added to the end of the vector.
 * @return true if the push operation is successful; false if reallocation fails
 *         or if the provided vector pointer is NULL.
 */
bool Vec_push(Vector *v, int val) {
  if (v == NULL)
    return false;

  if (v->length >= v->capacity) {
    size_t new_capacity = v->capacity <= 1 ? 2 : (size_t)v->capacity * 1.5;
    int *new_data = (int *)realloc(v->data, new_capacity * sizeof(int));

    if (new_data == NULL) {
      return false;
    }

    v->data = new_data;
    v->capacity = new_capacity;
  }

  v->data[v->length++] = val;

  return true;
}

/**
 * Remove and return the last element from the vector.
 *
 * If the provided vector is NULL or empty, the result's "success" field is set
 * to false, and the "val" field is set to -1. Otherwise, the last element is
 * removed from the vector, and the result's "success" field is set to true, and
 * "val" holds the removed element's value.
 *
 * @param v A pointer to the vector from which to pop the last element.
 * @return A PopResult structure indicating the success of the operation and the
 *         removed element's value.
 */
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

/**
 * Swap the elements at the specified positions in the vector.
 *
 * This function swaps the elements at positions x and y within the vector. If
 * either position is out of bounds (i.e., less than 0 or greater than or equal
 * to the vector's length), the behavior is undefined.
 *
 * @param v A pointer to the vector containing the elements to be swapped.
 * @param x The index of the first element to swap.
 * @param y The index of the second element to swap.
 */
void Vec_swap(Vector *v, size_t x, size_t y) {
  int tmp = v->data[x];
  v->data[x] = v->data[y];
  v->data[y] = tmp;
}

/**
 * Create a new vector that is a slice of the original vector.
 *
 * This function creates a new vector containing elements from the original
 * vector within the specified range [left, right). If the provided vector is
 * NULL or if the left index is greater than or equal to the right index, the
 * function returns NULL.
 *
 * @param v A pointer to the original vector from which to create a slice.
 * @param left The left index (inclusive) of the range to include in the slice.
 * @param right The right index (exclusive) of the range to include in the
 * slice.
 * @return A pointer to the newly created slice vector or NULL on failure.
 */
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
