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

#include "dataframe.h"

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
    if (buff == NULL)
        return (WC(2, "Error in opening file\n"), NULL);
    if (read(fd, buff, file_stat.st_size) != file_stat.st_size) {
        free(buff);
        return (WC(2, "Error in reading file\n"), NULL);
    }
    buff[file_stat.st_size] = '\0';
    return (close(fd), buff);
}

static
char **open_file_csv(char *filename)
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
    for (int a = 0; file[a] != NULL; a++)
        printf("%s\n", file[a]);
    return dataframe;
}
