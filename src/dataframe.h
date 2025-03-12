/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #define WC(fd, str) write(fd, str, sizeof str - 1)

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

    #define TYPES_NB 5

typedef struct {
    char const *name;
    size_t sz;
} types_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_type;
    void ***data;
} dataframe_t;


extern const types_t TYPES[];

// Core
dataframe_t *df_read_csv(const char *filename, const char *separator);
dataframe_t *df_head(dataframe_t *df, int nb_rows);

// Utils (will me moved to another header)
char **my_str_to_word_array(const char *str, const char *separator);
void my_free_array(char **array);
void free_data(void ***data, int nb_columns, int nb_rows);
void *my_memdup(const uint8_t *mem, size_t bytes);
bool data_storage(dataframe_t *dataframe, char **file, const char *separator);

#endif /* !DATAFRAME_H_ */
