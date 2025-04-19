#ifndef SAFE_INPUT_H
#define SAFE_INPUT_H

#include <stddef.h>
#include <stdbool.h>

bool get_int(const char *prompt, int *out_value);
bool get_long(const char *prompt, long *out_value);
bool get_string(const char *prompt, char *buffer, size_t buffer_size);
bool get_bool(const char *prompt, bool *out_value);
#endif // SAFE_INPUT_H