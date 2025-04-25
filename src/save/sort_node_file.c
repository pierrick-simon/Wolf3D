/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** sort_node_file
*/

#include "save.h"
#include <string.h>

bool sort_node_file(void *data_first, void *data_second)
{
    file_t *first = (file_t *)data_first;
    file_t *second = (file_t *)data_second;

    if (strcmp(first->name, second->name) <= 0)
        return true;
    return false;
}

