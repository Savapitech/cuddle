/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** store_data
*/

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "utils.h"

static
void check_is_string_or_bool(dataframe_t *df, int index_rows, int
    index_columns, char *token)
{
    if (strcasecmp(token, "true") == 0 || strcasecmp(token, "false") == 0)
        df->column_type[index_columns] = BOOL;
    else
        df->column_type[index_columns] = STRING;
    df->data[index_rows][index_columns] = strdup(token);
}

static
void check_is_int_ot_uint(dataframe_t *df, int index_rows, int
    index_columns, char *token)
{
    int check_point = 0;
    union { int nb; uint32_t u_nb; float f_nb; } value;

    for (int a = 0; token[a] != '\0'; a++) {
        if (token[a] == '.')
            check_point++;
        if (check_point > 1)
            return;
    }
    if (check_point == 1) {
        value.f_nb = strtof(token, NULL);
        df->column_type[index_columns] = FLOAT;
        df->data[index_rows][index_columns] =
            my_memdup((uint8_t const *)&value.f_nb, sizeof(float));
    } else {
        value.nb = strtoul(token, NULL, 10);
        df->column_type[index_columns] = UINT;
        df->data[index_rows][index_columns] =
            my_memdup((uint8_t const *)&value.nb, sizeof(uint32_t));
    }
}

static
void check_type(dataframe_t *df, int index_rows, int
    index_columns, char *token)
{
    bool is_nb = true;

    for (int a = 0; token[a] != '\0'; a++)
        if (!isdigit(token[a]) && token[a] != '.' && token[0] != '-')
            is_nb = false;
    if (is_nb)
        check_is_int_ot_uint(df, index_rows, index_columns, token);
    else
        check_is_string_or_bool(df, index_rows, index_columns, token);
}

static
bool store_data_second_part(dataframe_t *df, const char *separator,
    char *token, int index_rows)
{
    for (int index_columns = 0; index_columns < df->nb_columns;
        index_columns++) {
        if (token == NULL)
            break;
        token[strcspn(token, "\t\n\r")] = '\0';
        check_type(df, index_rows, index_columns, token);
        if (df->data[index_rows][index_columns] == NULL)
            return (free(df->data[index_rows][index_columns]), false);
        token = strtok(NULL, separator);
    }
    return true;
}

static
bool store_data(dataframe_t *df, char **file, const char *separator)
{
    char *line = NULL;
    char *token = NULL;

    for (int index_rows = 0; index_rows < df->nb_rows; index_rows++) {
        line = strdup(file[index_rows + 1]);
        if (line == NULL)
            return false;
        token = strtok(line, separator);
        if (store_data_second_part(df, separator, token, index_rows) ==
            false)
            return (free(line), false);
        free(line);
    }
    return true;
}

bool data_storage(dataframe_t *df, char **file, const char *separator)
{
    df->data = (void ***)malloc(sizeof(void *) * df->nb_rows);
    if ((void *)df->data == NULL)
        return false;
    df->column_type = malloc(sizeof *df->column_type * df->nb_columns);
    if (df->column_type == NULL)
        return (free((void *)df->data), false);
    df->nb_rows--;
    for (int index_rows = 0; index_rows < df->nb_rows; index_rows++) {
        df->data[index_rows] = (void **)malloc(sizeof(void *) * df->
            nb_columns);
        if ((void *)df->data[index_rows] == NULL) {
            my_free_array((char **)df->data);
            return (free((void *)df->data), false);
        }
        df->data[index_rows][0] = NULL;
    }
    store_data(df, file, separator);
    return true;
}
