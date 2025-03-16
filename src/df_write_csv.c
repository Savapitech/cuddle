/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "dataframe.h"

static
void write_value(void *vl, FILE *file, column_type_t type)
{
    switch (type) {
        case INT:
            fprintf(file, "%d", *(int *)vl);
            break;
        case UINT:
            fprintf(file, "%u", *(uint32_t *)vl);
            break;
        case FLOAT:
            fprintf(file, "%.2f", *(float *)vl);
            break;
        case BOOL:
        case STRING:
            fprintf(file, "%s", (char *)vl);
            break;
        default:
            return;
    }
}

static
void write_values(dataframe_t *df, FILE *file)
{
    char const *separator = df->separator == NULL ? "," : df->separator;

    for (int col = 0; col < df->nb_columns; col++)
        fprintf(file, "%s%s", df->column_names[col],
            col < df->nb_columns - 1 ? "," : "\n");
    for (int row = 0; row < df->nb_rows; row++) {
        for (int col = 0; col < df->nb_columns; col++) {
            write_value(df->data[row][col], file, df->column_type[col]);
            fprintf(file, "%s", col < df->nb_columns - 1 ? separator : "\n");
        }
    }
}

int df_write_csv(dataframe_t *df, char const *path)
{
    int fd;
    FILE *file;

    if (df == NULL || !df->nb_rows || !df->nb_columns)
        return -1;
    fd = open(path, O_CREAT | O_WRONLY, 0644);
    if (!fd)
        return -1;
    file = fdopen(fd, "w");
    if (file == NULL)
        return (close(fd), -1);
    write_values(df, file);
    fclose(file);
    close(fd);
    return 0;
}
