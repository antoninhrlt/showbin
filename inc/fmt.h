// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef SHOWBIN_FMT_H
#define SHOWBIN_FMT_H

/**
 * Format the binary file content buffer (array of hexadecimal characters)
 * 
 * @param binary_content The binary file content buffer
*/
char* fmt_hexstring(
    const int BIN_BUFFER_SIZE, 
    char binary_content[BIN_BUFFER_SIZE]
);

#endif // SHOWBIN_FMT_H
