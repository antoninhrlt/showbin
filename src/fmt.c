// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "fmt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* fmt_hexstring(
    const int BIN_BUFFER_SIZE, 
    char binary_content[BIN_BUFFER_SIZE]
) {
    char* dest_buffer = malloc(BIN_BUFFER_SIZE * 4 * sizeof(char) + 1);
    strcpy(dest_buffer, ""); // avoid crazy appending of "@@" at begin

    // Using a position variable for `fmt_buffer` to avoid `strlen()` calls
    unsigned int buffer_pos = 0;

    int j = 0;
    for (int i = 0; i < BIN_BUFFER_SIZE - 1; i++) {
        if (j == 8) {
            strcat(dest_buffer, "\t");
            buffer_pos += 1;
        } else if (j == 16) {
            strcat(dest_buffer, "\n");
            buffer_pos += 1;
            j = 0;
        }

        int saved_buffer_pos = buffer_pos;

        // The value returned by `sprintf()` is the appended string length 
        buffer_pos += sprintf(
            dest_buffer + buffer_pos, 
            "%x ", 
            binary_content[i]
        );

        // Prettier print
        if (saved_buffer_pos != buffer_pos - 3) {
            strcat(dest_buffer, " ");
            buffer_pos += 1;
        }

        j += 1;
    }

    return dest_buffer;
}
