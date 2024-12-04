#include <stdlib.h>
#include "array_utils.h"

void* reallocate_array(void* array, size_t new_count, size_t element_size) {
	if (!array) {
		return allocate_array(new_count, element_size);
	}

	size_t* original_ptr = (size_t*)array - 1;

	size_t* new_ptr = realloc(original_ptr, new_count * element_size + sizeof(size_t));
	if (!new_ptr) {
		return NULL;
	}

	*new_ptr = new_count;
	return (void*)(new_ptr + 1);
}

void* allocate_array(size_t count, size_t element_size) {
	size_t* ptr = calloc(count, element_size);
	if (!ptr) return NULL;
	*ptr = count;
	return (void*)(ptr + 1);
}

size_t get_array_size(void* arr) {
	if (arr == NULL) return 0;

	size_t* ptr = (size_t*)arr - 1;
	return *ptr;
}