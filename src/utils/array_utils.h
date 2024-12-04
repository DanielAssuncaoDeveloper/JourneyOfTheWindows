
#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

void* reallocate_array(void* array, size_t new_count, size_t element_size);
void* allocate_array(size_t count, size_t element_size);
size_t get_array_size(void* arr);

#endif