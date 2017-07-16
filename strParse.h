//
// Created by AngheloAlf10 on 16-07-2017.
//

#ifndef SO_TAREA2_MINISHELL_STRPARSE_H
#define SO_TAREA2_MINISHELL_STRPARSE_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *raw_input(char *outMessage);
char **split(char *string, char *delimiters);
void freeSplitted(char **string);

#endif //SO_TAREA2_MINISHELL_STRPARSE_H
