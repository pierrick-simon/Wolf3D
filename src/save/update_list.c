/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update_list
*/

#include "save.h"
#include "linked_list.h"
#include <math.h>

void update_list(info_save_t *info, char *dir)
{
    if (info->update == sfTrue)
        return;
    info->list = get_file(dir);
    info->nb_page = (int)ceil((double)get_list_len(info->list) / NB_SHOW_SAVE);
    if (info->nb_page < 1)
        info->nb_page = 1;
    info->current_file = info->list->head;
    info->update = sfTrue;
}
