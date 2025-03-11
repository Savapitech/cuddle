/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_read
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

#include "dataframe.h"

static
int set_nb_columns(dataframe_t *dataframe, char **file, const char *separator)
{
    int index_columns = 0;
    char **array_file = my_str_to_word_array(file[index_columns], separator);

    if (array_file == NULL)
        return 84;
    dataframe->nb_columns = 0;
    for (; array_file[index_columns] != NULL; index_columns++);
    my_free_array(array_file);
    return index_columns;
}

static
int set_nb_rows(dataframe_t *dataframe, char **file)
{
    int index_rows = 0;

    dataframe->nb_rows = 0;
    for (; file[index_rows] != NULL; index_rows++);
    return index_rows;
}

static
bool set_dataframe(dataframe_t *dataframe, char **file, const char *separator)
{
    dataframe->nb_columns = set_nb_columns(dataframe, file, separator);
    dataframe->nb_rows = set_nb_rows(dataframe, file);
    dataframe->column_names = malloc(sizeof(char *) *
        (dataframe->nb_columns + 1));
    if (dataframe->column_names == NULL)
        return false;
    for (int i = 0; i <= dataframe->nb_columns; i++)
        dataframe->column_names[i] = NULL;
    return true;
}

static
char *my_open_file(const char *filename)
{
    int fd = 0;
    char *buff = NULL;
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1)
        return NULL;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    buff = malloc(sizeof(char) * (file_stat.st_size + 1));
    if (buff == NULL) {
        close(fd);
        return (WC(2, "Error in opening file\n"), NULL);
    }
    if (read(fd, buff, file_stat.st_size) != file_stat.st_size) {
        close(fd);
        return (free(buff), NULL);
    }
    buff[file_stat.st_size] = '\0';
    return (close(fd), buff);
}

static
void set_name_column(char *array, int index, int a, dataframe_t *dataframe)
{
    if (index == 0) {
        dataframe->column_names[a] = strdup(array);
    }
}

static
bool set_names_columns(dataframe_t *dataframe, const char *separator,
    char **file)
{
    char **array = NULL;
    int a = 0;

    for (int index = 0; file[index] != NULL; index++) {
        array = my_str_to_word_array(file[index], separator);
        if (!array)
            return (my_free_array(file), false);
        for (; array[a] != NULL; a++)
            set_name_column(array[a], index, a, dataframe);
        my_free_array(array);
    }
    return true;
}

static
char **open_file_csv(const char *filename)
{
    char *file = my_open_file(filename);
    char **array = NULL;

    if (!file)
        return (WC(2, "ERROR: No such file or directory\n"), NULL);
    array = my_str_to_word_array(file, "\n");
    if (!array)
        return NULL;
    free(file);
    return array;
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *dataframe = malloc(sizeof(dataframe_t));
    char **file = NULL;

    if (!dataframe)
        return NULL;
    file = open_file_csv(filename);
    if (!file)
        return NULL;
    if (!separator)
        separator = ",";
    if (set_dataframe(dataframe, file, separator) == false) {
        my_free_array(file);
        return (free(dataframe), NULL);
    }
    if (set_names_columns(dataframe, separator, file) == false)
        return NULL;
    my_free_array(file);
    return dataframe;
}
