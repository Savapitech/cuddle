/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_

    #include <stddef.h>
    #include <stdbool.h>

    #define WC(fd, str) write(fd, str, sizeof str - 1)

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_type;
    void ***data;
} dataframe_t;

char **my_str_to_word_array(const char *str, const char *separator);
void my_free_array(char **array);
void free_data(void ***data, int nb_columns, int nb_rows);
void *my_memdup(const char *mem, size_t bytes);
bool data_storage(dataframe_t *dataframe, char **file, const char *separator);

dataframe_t *df_read_csv(const char *filename, const char *separator);

#endif /* !DATAFRAME_H_ */
