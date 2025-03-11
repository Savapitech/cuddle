/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_

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

dataframe_t *df_read_csv(const char *filename, const char *separator);

#endif /* !DATAFRAME_H_ */
