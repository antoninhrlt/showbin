// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#include <argp.h>

#include "showbin.h"

struct Arguments {
    char* args[1]; // only the source file should be not an option 
    char* input_file;
    char* output_file; // if `== NULL`, no output file will be generated 
};

static struct argp_option args_options[] = {
    {
        "output", 'o', 0, 0, 
        "Set the output file path, if not set, no output file will be generated"
    }
};

static error_t args_parse_opt(int key, char* arg, struct argp_state* state) {
    struct Arguments* args = state->input;
    switch (key) {
        case ARGP_KEY_ARG:
            // Too many argument/s found
            if (state->arg_num >= 1) {
                argp_usage(state);
            }
            args->args[state->arg_num] = arg;
            break;
        case ARGP_KEY_END:
            // Not enough argument/s found
            if (state->arg_num < 1) {
                argp_usage(state);
            }
            break;
        case 'o':
            args->output_file = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static char args_doc[] = "source file";

static struct argp argp = {args_options, args_parse_opt, args_doc};

int main(int argc, char** argv) {
    struct Arguments args = {};
    argp_parse(&argp, argc, argv, 0, 0, &args);

    return 0;
}
