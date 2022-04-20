// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include "fmt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* fmt_hexstring(
    const int SOURCE_BUFFER_SIZE, 
    char source_buffer[SOURCE_BUFFER_SIZE]
) {
    char* dest_buffer = malloc(SOURCE_BUFFER_SIZE * 3 * sizeof(char) + 1);
    strcpy(dest_buffer, ""); // avoid crazy appending of "@@" at begin

    // Using a position variable for `fmt_buffer` to avoid `strlen()` calls
    unsigned int buffer_pos = 0;

    int j = 0;
    for (int i = 0; i < SOURCE_BUFFER_SIZE - 1; i++) {
        if (j == 8) {
            strcat(dest_buffer, "\t");
            buffer_pos += 1;
        } else if (j == 16) {
            strcat(dest_buffer, "\n");
            buffer_pos += 1;
            j = 0;
        }

        // The value returned by `sprintf()` is the appended string length 
        buffer_pos += sprintf(
            dest_buffer + buffer_pos, 
            "%x\t", 
            source_buffer[i]
        );
        j += 1;
    }

    return dest_buffer;
}
