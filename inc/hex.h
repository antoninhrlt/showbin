// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef SHOWBIN_HEX_H
#define SHOWBIN_HEX_H

/**
 * Format the binary file content buffer (array of hexadecimal characters)
 * 
 * @param source_buffer The binary file content buffer
*/
char* fmt_hexstring(
    const int SOURCE_BUFFER_SIZE, 
    char source_buffer[SOURCE_BUFFER_SIZE]
);

#endif // SHOWBIN_HEX_H
