// This file is part of "showbin"
// Under the MIT License
// Copyright (c) 2022 Antonin Hérault

#ifndef SHOWBIN_LOG_H
#define SHOWBIN_LOG_H

#include <showbin.h>
#include <stdio.h>

#define log_info(...)       printf("|\x1b[1;34minfo\x1b[0m| " __VA_ARGS__)
#define log_warning(...)    printf("|\x1b[1;33mwarning\x1b[0m| " __VA_ARGS__)
#define log_error(...)      fprintf(stderr, "|\x1b[1;31merror\x1b[0m| " __VA_ARGS__)

#endif // SHOWBIN_LOG_H