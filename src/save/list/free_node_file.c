/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free_node_file
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>

void free_node_file(void *data)
{
    file_t *file = (file_t *)data;

    free(file->name);
    free(file->path);
}
