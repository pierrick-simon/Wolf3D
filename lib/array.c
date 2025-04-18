/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** array
*/

#include <unistd.h>
#include <stdlib.h>

int array_len(char **array)
{
    int i = 0;

    if (array == NULL)
        return -1;
    while (array[i] != NULL)
        i++;
    return i;
}

void free_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return;
    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
    free(array);
}
