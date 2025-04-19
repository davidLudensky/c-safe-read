#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define INPUT_BUFFER_SIZE 256
#define NULL_CHARACTER '\0'
#define NEW_LINE '\n'
#define DECIMAL_BASE 10

static void clear_stdin_buffer(void) {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Trims newline and trailing spaces
static void trim_newline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == NEW_LINE || isspace((unsigned char)str[len - 1])))
    {
        str[--len] = NULL_CHARACTER;
    }
}

// Lowercase a string
static void to_lowercase(char *str, size_t str_length) {
    for (; *str; ++str) {
        *str = (char)tolower(*str);
    }
}

static bool get_something(const char *prompt, char *buffer, long *p_input_long)
{
    char *endptr = "";
    
    if (!get_string(prompt, buffer, INPUT_BUFFER_SIZE))
    {
        return false;  
    }

    errno = 0;
    *p_input_long = strtol(buffer, &endptr, DECIMAL_BASE);
    // No numeric conversion done at all?
    // Numeric input outside long range?
    // Junk after the numeric text?
    // printf()
    if (endptr == buffer || *endptr != NULL_CHARACTER || errno == ERANGE) {
        return false;
    }
    return true;
}

bool get_string(const char *prompt, char *buffer, size_t buffer_size) {
    if (!prompt || !buffer || buffer_size == 0)
    {
        return false;  
    }

    printf("%s", prompt);
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }
    if (strchr(buffer, '\n') == NULL) {
        // Line was too long
        clear_stdin_buffer();
        printf("Input was too long! Only first %zu characters were kept.\n", buffer_size - 1);
    }

    trim_newline(buffer);
    return true;
}

bool get_int(const char *prompt, int *out_value) {
    long input_long = 0;
    char buffer[INPUT_BUFFER_SIZE] = "";

    while (true) {
        if (!get_something(prompt, buffer, &input_long))
        {
            printf("Invalid integer. Please try again.\n");
            continue;
        }

        // Outside int range?
        if (input_long < INT_MIN || input_long > INT_MAX) {
            printf("Invalid integer. Please try again.\n");
            continue;
        }

        *out_value = (int)input_long;
        return true;
    }
}

bool get_long(const char *prompt, long *out_value) {
    long input_long = 0;
    char buffer[INPUT_BUFFER_SIZE] = "";

    while (true) {
        if (!get_something(prompt, buffer, &input_long))
        {
            continue;
        }

        *out_value = input_long;
        return true;
    }
}

bool get_bool(const char *prompt, bool *out_value) {
    char buffer[INPUT_BUFFER_SIZE] = "";
    static const char *const true_strings[] = { "yes", "y", "true", "1", NULL };
    static const char *const false_strings[] = { "no", "n", "false", "0", NULL };

    while (true) {
        if (!get_string(prompt, buffer, sizeof(buffer)))
        {
            return false;  
        }
        to_lowercase(buffer, (size_t)INPUT_BUFFER_SIZE);
        
        for (int i = 0; true_strings[i]; i++)
        {
            if (strcmp(buffer, true_strings[i]) == 0)
            {
                *out_value = true;
                return true;
            }
        }
        for (int i = 0; false_strings[i]; i++)
        {
            if (strcmp(buffer, false_strings[i]) == 0)
            {
                *out_value = false;
                return true;
            }
        }
        printf("Invalid input. Please enter yes/y/true/1 or no/n/false/0.\n");
    }
}