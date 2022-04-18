// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "runner.h"

int run(char* source_file, char* output_file) {
    bool with_output = (output_file == NULL);
    FILE* source_stream = fopen(source_file, "rb");

    fseek(source_stream, 0, SEEK_END);
    const int MAX_BIN_SIZE = ftell(source_stream);
    fseek(source_stream, 0, SEEK_SET);

    unsigned char source_buffer[MAX_BIN_SIZE];
    fread(source_buffer, sizeof(source_buffer), 1, source_stream);

    char* fmt_source_buffer = malloc(MAX_BIN_SIZE * sizeof(char) + 1);

    int j = 0;
    for (int i = 0; i < MAX_BIN_SIZE - 1; i++) {
        if (j == 8) {
            strcat(fmt_source_buffer, "\t");
        } else if (j == 16) {
            strcat(fmt_source_buffer, "\n");
            j = 0;
        }

        char* to_append = malloc(1);
        sprintf(to_append, "%x\t", source_buffer[i]);
        strcat(fmt_source_buffer, to_append);
        j += 1;
    }

    log_info("Formatted source file content : \n%s\n", fmt_source_buffer);

    return 0;
}
