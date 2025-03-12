/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** store_data
*/

#include "dataframe.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static
void check_is_string_or_bool(dataframe_t *dataframe, int index_rows, int
    index_columns, char *token)
{
    if (strcmp(token, "true") == 0 || strcmp(token, "true") == 0) {
        dataframe->column_type[index_columns] = BOOL;
        dataframe->data[index_rows][index_columns] =
            my_memdup(token, sizeof(bool));
    } else {
        dataframe->column_type[index_columns] = STRING;
        dataframe->data[index_rows][index_columns] =
            my_memdup(token, strlen(token));
    }
}

static
void check_is_int_ot_uint(dataframe_t *dataframe, int index_rows, int
    index_columns, char *token)
{
    int check_point = 0;

    for (int a = 0; token[a] != '\0'; a++) {
        if (token[a] == '.')
            check_point++;
        if (check_point > 1)
            return;
    }
    if (check_point == 1) {
        dataframe->column_type[index_columns] = INT;
        dataframe->data[index_rows][index_columns] =
            my_memdup(token, sizeof(int));
    } else {
        dataframe->column_type[index_columns] = FLOAT;
        dataframe->data[index_rows][index_columns] =
            my_memdup(token, sizeof(float));
    }
}

static
void check_type(dataframe_t *dataframe, int index_rows, int
    index_columns, char *token)
{
    bool is_nb = false;

    for (int a = 0; token[a] != '\0'; a++) {
        if (!isdigit(token[a]) && token[a] != '.' && token[0] != '-')
            is_nb = false;
        else
            is_nb = true;
    }
    if (is_nb)
        check_is_int_ot_uint(dataframe, index_rows, index_columns, token);
    else
        check_is_string_or_bool(dataframe, index_rows, index_columns, token);
}

static
bool store_data_second_part(dataframe_t *dataframe, const char *separator,
    char *token, int index_rows)
{
    for (int index_columns = 0; index_columns < dataframe->nb_columns;
        index_columns++) {
        if (token == NULL)
            break;
        token[strcspn(token, " \t\n\r")] = '\0';
        check_type(dataframe, index_rows, index_columns, token);
        if (dataframe->data[index_rows][index_columns] == NULL)
            return (free(dataframe->data[index_rows][index_columns]), false);
        token = strtok(NULL, separator);
    }
    return true;
}

static
bool store_data(dataframe_t *dataframe, char **file, const char *separator)
{
    char *line = NULL;
    char *token = NULL;

    for (int index_rows = 0; index_rows < dataframe->nb_rows; index_rows++) {
        line = strdup(file[index_rows + 1]);
        if (line == NULL)
            return false;
        token = strtok(line, separator);
        if (store_data_second_part(dataframe, separator, token, index_rows) ==
            false)
            return (free(line), false);
        free(line);
    }
    return true;
}

bool data_storage(dataframe_t *dataframe, char **file, const char *separator)
{
    dataframe->data = malloc(sizeof(void *) * dataframe->nb_rows);
    if (dataframe->data == NULL)
        return false;
    dataframe->nb_rows--;
    for (int index_rows = 0; index_rows < dataframe->nb_rows; index_rows++) {
        dataframe->data[index_rows] = malloc(sizeof(void *) * dataframe->
            nb_columns);
        if (dataframe->data[index_rows] == NULL) {
            my_free_array((char **)dataframe->data);
            free(dataframe->data);
            return false;
        }
        dataframe->data[index_rows][0] = NULL;
    }
    store_data(dataframe, file, separator);
    return true;
}
