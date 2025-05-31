/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_edit_info
*/

#include "editor.h"
#include "save.h"
#include "my.h"
#include <stdio.h>
#include <string.h>

static void update_info(edit_info_t *edit_info)
{
    int len = strlen(edit_info->string[EDIT_INF_NAME]);

    sprintf(edit_info->str_tmp[EDIT_INF_NAME], "%s",
        edit_info->string[EDIT_INF_NAME]);
    for (int i = len; i < MAX_NAME; i++) {
        edit_info->str_tmp[EDIT_INF_NAME][i] = '-';
    }
    edit_info->str_tmp[EDIT_INF_NAME][MAX_NAME] = '\0';
    for (int j = EDIT_INF_X; j < EDIT_INF_BACK; j++) {
        len = strlen(edit_info->string[j]);
        sprintf(edit_info->str_tmp[j], "%s", edit_info->string[j]);
        for (int i = len; i < MAX_STRLEN; i++) {
            edit_info->str_tmp[j][i] = '-';
        }
        edit_info->str_tmp[j][MAX_NAME] = '\0';
    }
}

static void draw_info(system_t *sys, edit_info_t *edit_info)
{
    draw_textbox_t draw = {0};

    for (int i = EDIT_INF_NAME; i < EDIT_INF_BACK; i++) {
        draw = edit_info->draw[i];
        draw.str = edit_info->str_tmp[i];
        draw.pos.x += 300;
        draw_string(sys, sys->textbox, &draw);
    }
}

void draw_edit_info(system_t *sys, void *structure)
{
    edit_info_t *edit_info = (edit_info_t *)structure;

    edit_info_events(sys, edit_info);
    update_info(edit_info);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_EDIT_INF; i++)
        draw_string(sys, sys->textbox, &edit_info->draw[i]);
    draw_info(sys, edit_info);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
