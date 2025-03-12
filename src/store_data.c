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

static
bool store_data_second_part(dataframe_t *dataframe, const char *separator,
    char *token, int index_rows)
{
    for (int index_columns = 0; index_columns < dataframe->nb_columns;
        index_columns++) {
        if (token == NULL)
            break;
        dataframe->data[index_rows][index_columns] = strdup(token);
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
