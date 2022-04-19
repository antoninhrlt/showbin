// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "runner.h"

void disassemble(
    const int MAX_BIN_SIZE,
    char source_buffer[MAX_BIN_SIZE], 
    char* output_file
) {
    const bool is_output = output_file != NULL;
    if (is_output) {
        FILE* output_stream = fopen(output_file, "w+");
        fclose(output_stream);
    }
}

int run(char* source_file, char* output_file) {
    FILE* source_stream = fopen(source_file, "rb");

    // Get the file's size
    fseek(source_stream, 0, SEEK_END);
    const int MAX_BIN_SIZE = ftell(source_stream);
    fseek(source_stream, 0, SEEK_SET);

    // Read the binary file
    unsigned char source_buffer[MAX_BIN_SIZE];
    fread(source_buffer, sizeof(source_buffer), 1, source_stream);

    fclose(source_stream);

    // Print the binary file content as hexadecimal
    char* fmt_buffer = malloc(MAX_BIN_SIZE * 3 * sizeof(char) + 1);
    strcpy(fmt_buffer, ""); // avoid crazy appending of "@@" at begin

    // Using a position variable for `fmt_buffer` avoid `strlen()` calls
    unsigned int fmt_buffer_pos = 0;
    
    int j = 0;
    for (int i = 0; i < MAX_BIN_SIZE - 1; i++) {
        if (j == 8) {
            strcat(fmt_buffer, "\t");
            fmt_buffer_pos += 1;
        } else if (j == 16) {
            strcat(fmt_buffer, "\n");
            fmt_buffer_pos += 1;
            j = 0;
        }
        
        // The value returned by `sprintf()` is the appended string length 
        fmt_buffer_pos += sprintf(
            fmt_buffer + fmt_buffer_pos, 
            "%x\t", 
            source_buffer[i]
        );
        j += 1;
    }

    log_info("Source file content as hexadecimal : \n%s\n", fmt_buffer);
    free(fmt_buffer);

    //disassemble(MAX_BIN_SIZE, source_buffer, output_file);
    free(source_file);
    free(output_file);

    return 0;
}
