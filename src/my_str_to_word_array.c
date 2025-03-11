/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** my_str_to_word_array.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int is_separator(char c, char const *separator)
{
    for (int i = 0; separator[i] != '\0'; i++)
        if (separator[i] == c)
            return 1;
    return 0;
}

static int get_nb_element(char const *separator, char const *str)
{
    int nb_element = 0;

    if (separator == NULL || str == NULL)
        return -10;
    if (is_separator(str[0], separator) == 0)
        nb_element++;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], separator)
            && is_separator(str[i + 1], separator) == 0
            && str[i + 1] != '\0') {
            nb_element++;
        }
    }
    return nb_element;
}

static int get_nb_character(char const *separator, char const *str)
{
    int nb_character = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], separator))
            break;
        nb_character++;
    }
    return nb_character;
}

static int get_nb_skip_character(char const *separator, char const *str)
{
    int nb_skip = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], separator) == 0)
            break;
        nb_skip++;
    }
    return nb_skip;
}

bool principal_function(const char *str, const char *separator, char **tab)
{
    int nb_character = 0;
    int index = 0;

    for (int i = 0; str[i] != '\0';) {
        i += get_nb_skip_character(separator, &str[i]);
        nb_character = get_nb_character(separator, &str[i]);
        if (nb_character == 0)
            break;
        tab[index] = malloc(nb_character + 1);
        if (tab[index] == NULL)
            return (free((void *)tab), false);
        strncpy(tab[index], &str[i], nb_character);
        tab[index][nb_character] = '\0';
        i += nb_character;
        index++;
    }
    return true;
}

char **my_str_to_word_array(const char *str, const char *separator)
{
    int nb_element = get_nb_element(separator, str);
    char **tab;

    if (nb_element < 1)
        return NULL;
    tab = (char **)malloc(sizeof(char *) * (nb_element + 1));
    if ((void *)tab == NULL)
        return NULL;
    if (principal_function(str, separator, tab) == false)
        return NULL;
    tab[nb_element] = NULL;
    return tab;
}
