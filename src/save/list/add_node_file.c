/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_file
*/

#include "save.h"
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

static int get_name(char **name, char *file, char *ext)
{
    int total = strlen(file) - strlen(ext);

    *name = malloc(sizeof(char) * (total + 1));
    if (*name == NULL)
        return ERROR;
    strncpy(*name, file, total);
    (*name)[total] = '\0';
    return SUCCESS;
}

static int get_path(char **path, char *file, char *dir)
{
    *path = malloc(sizeof(char) * (strlen(file) + strlen(dir) + 2));
    if (*path == NULL)
        return ERROR;
    strcpy(*path, dir);
    strcat(*path, "/");
    strcat(*path, file);
    return SUCCESS;
}

int add_node_file(linked_list_t *list, char *file, char *dir)
{
    file_t *info = malloc(sizeof(file_t));

    if (info == NULL)
        return ERROR;
    if (get_path(&info->path, file, dir) == ERROR) {
        free(info);
        return ERROR;
    }
    if (get_name(&info->name, file, ".legend") == ERROR) {
        free(info->path);
        free(info);
        return ERROR;
    }
    push_to_tail(list, info);
    return SUCCESS;
}
