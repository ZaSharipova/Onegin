#ifndef PARSE_INPUT_H_
#define PARSE_INPUT_H_

#include "ConstantsAndStructs.h"
#include "FileOperations.h"

PossibleErrors parse_argv(int argc, char *argv[], ArgumentModes *flags);

PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, ArgumentModes *flags);
PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sort_mode);
bool parse_in_out(char *argv[], size_t pos, const char *mode, const char **filename); //поменять mode на другую переменную
PossibleErrors check_sort_mode(char *str, TypesOfSort *sort_mode);

#endif //PARSE_INPUT_H_