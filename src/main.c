// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "runner.h"
#include "showbin.h"

void help(const char* self) {
    printf(
        "Usage : %s <source file> [options...]\n"
        "Options :\n"
            "\t-h : Show this help page\n"
            "\t-o : Set the output file path\n",
        self
    );
    exit(0);
}

/**
 * Check if the command line arguments are valid and update some values
 * 
 * @param source_file Update the source file value got from the arguments
 * @param output_file Can be updated if option "-o" found
*/
void check_args(int argc, char** argv, char** source_file, char** output_file) {
    bool to_ignore = false;

    for (int i = 1; i < argc; i++) {
        if (to_ignore) { // the previous flag was an option
            continue;
        }

        // Define the source file
        if (argv[i][0] != '-') {
            if (*source_file != NULL) {
                log_warning("Source file already defined as '%s'\n", *source_file);
                continue;
            }

            *source_file = (char*) malloc(strlen(argv[i]) * sizeof(char) + 1);
            strcpy(*source_file, argv[i]);
            continue;
        }

        // Check for the an option
        switch (argv[i][1]) {
            case 'h':
                help(argv[0]);
                break;
            case 'o':
                if (i == argc - 1) {
                    log_error(
                        "Option '-o' should be followed by a value : path for the output\n"
                    );
                    exit(1);
                }
                *output_file = (char*) malloc(
                    strlen(argv[i + 1]) * sizeof(char) + 1
                );
                strcpy(*output_file, argv[i + 1]);
                to_ignore = true;
                break;
            default:
                log_warning(
                    "Invalid option '%s' found, the option flag and the value next to it will be ignored\n", 
                    argv[i]
                );
                to_ignore = true;
                break;
        } 
    }

    if (*source_file == NULL) {
        log_error("No source input file\n");
        exit(1);
    }
}

int main(int argc, char** argv) {
    char* source_file = NULL; // the binary file to disassemble
    // If the output file is still null, there will be no output generation
    char* output_file = NULL; 

    check_args(argc, argv, &source_file, &output_file);

    log_info("File to disassemble : '%s'\n", source_file);
    if (output_file != NULL) {
        log_info("Output file : '%s'\n", output_file);
    }

    return run(source_file, output_file);
}
