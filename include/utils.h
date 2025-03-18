/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef UTILS_H
    #define UTILS_H
    #include <stdbool.h>
    #include <stdint.h>

    #include "dataframe.h"

char **my_str_to_word_array(const char *str, const char *separator);
void my_free_array(char **array);
void free_data(void ***data, int nb_columns, int nb_rows);
void *my_memdup(const uint8_t *mem, size_t bytes);
bool data_storage(dataframe_t *dataframe, char **file, const char *separator);
void mini_qsort(void ***arr, size_t size, int col,
    bool compare(void *, void *));
int get_col_idx(dataframe_t *df, char const *name);
#endif
