// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "runner.h"

void disassemble(
    char* source_buffer, 
    const int MAX_BIN_SIZE,
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
    char* fmt_source_buffer = malloc(MAX_BIN_SIZE * sizeof(char) + 1);

    int j = 0;
    for (int i = 0; i < MAX_BIN_SIZE - 1; i++) {
        if (j == 8) {
            strcat(fmt_source_buffer, "\t");
        } else if (j == 16) {
            strcat(fmt_source_buffer, "\n");
            j = 0;
        }

        sprintf(fmt_source_buffer, "%x\t", source_buffer[i]);
        j += 1;
    }

    log_info("Source file content as hexadecimal : \n%s\n", fmt_source_buffer);
    free(fmt_source_buffer);

    disassemble(source_buffer, MAX_BIN_SIZE, output_file);
    free(source_file);
    free(output_file);

    return 0;
}
