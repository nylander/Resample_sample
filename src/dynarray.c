/*
 * dynarray.c
 * Mon 11 dec 2017 15:31:45
 * Johan.Nylander@{nbis|nrm}.se
 * Source: https://gist.githubusercontent.com/matugm/4708222/raw/ac5a5804c824e18c4ef1b1c760f54686adf602a1/array.c
 *
 */

#include "dynarray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct ArrayData *initArray() {
	struct ArrayData *newArray = malloc(sizeof(struct ArrayData));
	newArray->pointer = calloc(1000, sizeof(int));
	newArray->size = 1000;
	newArray->counter = 0;
	return newArray;
}

void resizeArray(struct ArrayData* array) {
	int newSize = (array->size * sizeof(int)) * 2;
	array->pointer = realloc(array->pointer, newSize);
	fflush (stdout);
	array->size *= 2;  // This is the number of elements, don't multiply by sizeof
}

int addElement(struct ArrayData *array, long int number) {
	if (array->counter >= array->size) {
		resizeArray(array);
	}

	*(array->pointer + array->counter) = number;  // Pointer arithmetic JN: SIGSEGV here on large (array length of 1,033,005,693 characters) data!
	array->counter += 1;

	return 0;
}

int getElement(struct ArrayData *array, long int index) {
	if (array->counter >= array->size) {
		return -1;
	}

	int *data = array->pointer + index;
	return *data;
}
