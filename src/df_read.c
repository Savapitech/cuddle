/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_read
*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dataframe.h"
#include "debug.h"

static
int get_nb_columns(dataframe_t *dataframe, char **file, const char *separator)
{
    int index_columns = 0;
    char *tmp = strdup(file[0]);

    if (tmp == NULL)
        return 84;
    for (char *token = strtok(file[0], separator); token != NULL;
        token = strtok(NULL, separator))
        index_columns++;
    strcpy(file[0], tmp);
    free(tmp);
    return index_columns;
}

static
int get_nb_rows(dataframe_t *dataframe, char **file)
{
    int index_rows = 0;

    dataframe->nb_rows = 0;
    for (; file[index_rows] != NULL; index_rows++);
    return index_rows;
}

static
bool set_dataframe(dataframe_t *dataframe, char **file, const char *separator)
{
    dataframe->nb_columns = get_nb_columns(dataframe, file, separator);
    dataframe->nb_rows = get_nb_rows(dataframe, file);
    dataframe->column_names = (char **)malloc(sizeof(char *) *
        (dataframe->nb_columns + 1));
    if ((void *)dataframe->column_names == NULL)
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
bool set_names_columns(dataframe_t *dataframe, const char *separator,
    char **file)
{
    int a = 0;
    char *tmp = strdup(file[0]);

    if (tmp == NULL)
        return 84;
    for (char *token = strtok(file[0], separator); token != NULL;
        token = strtok(NULL, separator)) {
        dataframe->column_names[a] = strdup(token);
        if (dataframe->column_names[a] == NULL)
            return (free(tmp), false);
        a++;
    }
    strcpy(file[0], tmp);
    free(tmp);
    return true;
}

static
char **open_file_csv(const char *filename)
{
    char *file = my_open_file(filename);
    char **array = NULL;

    if (file == NULL)
        return (WC(2, "ERROR: No such file or directory\n"), NULL);
    array = my_str_to_word_array(file, "\n");
    if (array == NULL)
        return (free((void *)file), NULL);
    free(file);
    return array;
}

void free_data(void ***data, int nb_columns, int nb_rows)
{
    if (data == NULL)
        return;
    for (int i = 0; i < nb_columns; i++) {
        for (int j = 0; j < nb_rows; j++) {
            free(data[j][i]);
        }
        free(data[i]);
    }
    free(data);
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *dataframe = malloc(sizeof(dataframe_t));
    char **file = NULL;

    if (dataframe == NULL)
        return NULL;
    file = open_file_csv(filename);
    if ((void *)file == NULL)
        return (free(dataframe), NULL);
    if (separator == NULL)
        separator = ",";
    if (set_dataframe(dataframe, file, separator) == false) {
        my_free_array(file);
        return (free(dataframe), NULL);
    }
    if (set_names_columns(dataframe, separator, file) == false)
        return (free(dataframe), NULL);
    data_storage(dataframe, file, separator);
    my_free_array(file);
    return dataframe;
}
