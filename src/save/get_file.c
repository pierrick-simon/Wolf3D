/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** get_file
*/

#include "save.h"
#include "linked_list.h"
#include <sys/types.h>
#include <dirent.h>
#include "string.h"

static bool pass_file(DIR *dir, struct dirent **next)
{
    int len = strlen((*next)->d_name) - strlen(".legend");

    if ((*next)->d_name[0] == '.' || len < 1
        || strcmp((*next)->d_name + len, ".legend")) {
        *next = readdir(dir);
        return true;
    }
    return false;
}

linked_list_t *get_file(char *path)
{
    linked_list_t *list = initialize_linked_list();
    DIR *dir = NULL;
    struct dirent *next = NULL;

    if (list == NULL)
        return NULL;
    dir = opendir(path);
    if (dir == NULL)
        return list;
    next = readdir(dir);
    while (next != NULL) {
        if (pass_file(dir, &next) == true)
            continue;
        add_node_file(list, next->d_name, path);
        next = readdir(dir);
    }
    sort_linked_list(list, &sort_node_file);
    closedir(dir);
    return list;
}
