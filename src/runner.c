// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hex.h"
#include "log.h"
#include "runner.h"

int run(char* source_file, char* output_file) {
    FILE* source_stream = fopen(source_file, "rb");
    free(source_file);

    // Get the file's size
    fseek(source_stream, 0, SEEK_END);
    const int SOURCE_BUFFER_SIZE = ftell(source_stream);
    fseek(source_stream, 0, SEEK_SET);

    // Read the binary file
    unsigned char source_buffer[SOURCE_BUFFER_SIZE];
    fread(source_buffer, sizeof(source_buffer), 1, source_stream);
    fclose(source_stream);

    // Print binary source file content as hexadecimal characters
    char* fmt_buffer = fmt_hexstring(SOURCE_BUFFER_SIZE, source_buffer);
    log_info("Source file content as hexadecimal : \n%s\n", fmt_buffer);
    
    free(fmt_buffer);
    free(output_file);

    return 0;
}
