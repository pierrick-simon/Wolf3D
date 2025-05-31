/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_edit_info
*/

#include "editor.h"
#include <stdlib.h>
#include <stdio.h>

void *init_edit_info(void)
{
    edit_info_t *edit_info = malloc(sizeof(edit_info_t));

    if (edit_info == NULL)
        return NULL;
    edit_info->str = EDIT_INF_NAME;
    edit_info->draw = init_from_conf(str_conf[CONF_EDIT_INF]);
    if (edit_info->draw == NULL)
        return NULL;
    sprintf(edit_info->draw[EDIT_INF_NAME].str, "NAME :");
    sprintf(edit_info->draw[EDIT_INF_X].str, "SIZE X :");
    sprintf(edit_info->draw[EDIT_INF_Y].str, "SIZE Y :");
    for (int i = EDIT_INF_NAME; i < EDIT_INF_BACK; i++) {
        for (int j = 0; j <= MAX_NAME; j++) {
            edit_info->string[i][j] = '\0';
            edit_info->str_tmp[i][j] = '\0';
        }
    }
    return (void *)edit_info;
}
