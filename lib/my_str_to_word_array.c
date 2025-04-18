/*
** EPITECH PROJECT, 2025
** day08
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static char *word(char const *str, int start, int stop)
{
    char *temp = malloc(sizeof(char) * (stop - start + 1));
    int compt = 0;

    if (temp == NULL)
        return NULL;
    for (int i = start; i < stop; i++) {
        temp[compt] = str[i];
        ++compt;
    }
    temp[compt] = '\0';
    return (temp);
}

static int check_sep(char const *str, int i, char const *sep)
{
    int j = 0;

    while (sep[j] != '\0') {
        if (sep[j] == str[i])
            return (0);
        j++;
    }
    return (1);
}

static bool count_nb_box(char const **string, int i)
{
    if ((check_sep(string[0], i, string[1]) == 0
        && (check_sep(string[0], i - 1, string[1]) == 1
        && check_sep(string[0], i - 1, string[2]) == 1))
        || (check_sep(string[0], i, string[2]) == 1
        && check_sep(string[0], i - 1, string[2]) == 0
        && check_sep(string[0], i - 1, string[1]) == 1)
        || (check_sep(string[0], i, string[2]) == 0
        && check_sep(string[0], i - 1, string[2]) == 1
        && check_sep(string[0], i - 1, string[1]) == 1)
        || (check_sep(string[0], i, string[2]) == 0
        && check_sep(string[0], i - 1, string[2]) == 0
        && string[0][i - 1] != string[0][i]))
        return true;
    return false;
}

static int sizearr(char const **string)
{
    int nbchar = 0;
    int i = 1;

    while (string[0][i] != '\0') {
        if (count_nb_box(string, i) == true)
            ++nbchar;
        i++;
    }
    if (check_sep(string[0], i - 1, string[1]) == 1)
        ++nbchar;
    return (nbchar + 1);
}

static void update_counter(char const **string, int i, int *runner, int *stay)
{
    if (check_sep(string[0], i, string[1]) == 1
        && check_sep(string[0], i, string[2]) == 1)
        (*runner)++;
    if (check_sep(string[0], i, string[2]) == 0)
        (*stay)++;
}

static char *fill_array(char const *str, int *index, int *nb_letter, int i)
{
    char *tmp = word(str, i - *nb_letter, i);

    (*index)++;
    *nb_letter = 0;
    return tmp;
}

static char *last_word(char const **string, int *index, int nb_letter, int i)
{
    if ((check_sep(string[0], i - 1, string[1]) == 1
        && check_sep(string[0], i - 1, string[2]) == 1)
        || check_sep(string[0], i - 1, string[2]) == 0)
        return fill_array(string[0], index, &nb_letter, i);
    return NULL;
}

static int make_array(char ***tab, char const **string)
{
    int index = 0;
    int runner = 0;
    int stay = 0;
    int i = 0;

    while (string[0][i] != '\0') {
        update_counter(string, i, &runner, &stay);
        if (((check_sep(string[0], i, string[1]) == 0)
            || (check_sep(string[0], i, string[2]) == 0)) && runner != 0)
            (*tab)[index] = fill_array(string[0], &index, &runner, i);
        if (check_sep(string[0], i, string[2]) == 0
            && check_sep(string[0], i + 1, string[2]) == 0
            && string[0][i + 1] != string[0][i])
            (*tab)[index] = fill_array(string[0], &index, &stay, i + 1);
        if (check_sep(string[0], i, string[2]) == 1 && stay != 0)
            (*tab)[index] = fill_array(string[0], &index, &stay, i);
        i++;
    }
    (*tab)[index] = last_word(string, &index, stay + runner, i);
    return index;
}

char **my_str_to_word_array(
    char const *str, char const *sep, char const *stay_sep)
{
    char **tab = NULL;
    char const *string[4] = {str, sep, stay_sep, NULL};
    int index = 0;

    tab = malloc(sizeof(char *) * sizearr(string));
    if (tab == NULL)
        return NULL;
    index = make_array(&tab, string);
    tab[index] = NULL;
    return tab;
}
