#ifndef PARSE_INPUT_H_
#define PARSE_INPUT_H_

#include "ConstantsAndStructs.h"
#include "FileOperations.h"

PossibleErrors parse_argv(int argc, char *argv[], TypesOfSort *sorting_type, const char **filename_in, const char **filename_out);;

PossibleErrors parse_arguments(int argc, char *argv[], size_t pos, const char **filename_in, const char **filename_out, TypesOfSort *sorting_modes);
PossibleErrors parse_sorting_modes(char *argv[], size_t pos, TypesOfSort *sorting_modes);
bool parse_in_out(char *argv[], size_t pos, const char *mode, const char **filename);
PossibleErrors check_sort_mode(char *str, TypesOfSort *type);

#endif //PARSE_INPUT_H_