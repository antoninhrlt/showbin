// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmt.h"
#include "log.h"
#include "runner.h"

int run(char* binary_file, char* output_file) {
    FILE* stream = fopen(binary_file, "rb");
    free(binary_file);

    // Get the file's size
    fseek(stream, 0, SEEK_END);
    const int BIN_BUFFER_SIZE = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    // Read the binary file
    unsigned char binary_content[BIN_BUFFER_SIZE];
    fread(binary_content, sizeof(binary_content), 1, stream);
    fclose(stream);

    // Print binary binary file content as hexadecimal characters
    char* fmt_buffer = fmt_hexstring(BIN_BUFFER_SIZE, binary_content);
    log_info("Binary file content as hexadecimal : \n%s\n", fmt_buffer);
    
    free(fmt_buffer);
    free(output_file);

    return 0;
}
