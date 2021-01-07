#ifndef DB_H
#define DB_H

#include "utils.h"

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer();

#endif
