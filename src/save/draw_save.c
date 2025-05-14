/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_save
*/

#include "save.h"
#include "linked_list.h"
#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void draw_page(
    system_t *sys, info_save_t *info, draw_textbox_t *draw, int start)
{
    int current = info->file / NB_SHOW_SAVE + 1;
    char *str = malloc(sizeof(char) *
        (get_nblen(current) + get_nblen(info->nb_page) + 2));
    draw_textbox_t tmp = {NULL};

    if (str == NULL)
        return;
    sprintf(str, "%d/%d", current, info->nb_page);
    tmp = draw[start - 1];
    tmp.pos.x += strlen(tmp.str) * tmp.size / POS_COEFF;
    tmp.pos.y += POS_OFFSET;
    tmp.str = str;
    tmp.size /= 2;
    draw_string(sys, sys->textbox, &tmp);
    free(str);
}

void draw_save_loop(
    system_t *sys, node_t *head, draw_textbox_t *draw, int start)
{
    draw_textbox_t tmp = {NULL};
    int count = 0;

    for (int i = start; i < start + NB_SHOW_SAVE; i++) {
        if (head == NULL)
            break;
        tmp = draw[i];
        tmp.str = ((file_t *)head->data)->name;
        draw_string(sys, sys->textbox, &tmp);
        head = head->next;
        count++;
    }
    for (int i = count + start; i < start + NB_SHOW_SAVE; i++) {
        tmp = draw[i];
        tmp.str = "---";
        tmp.color = GREY;
        draw_string(sys, sys->textbox, &tmp);
    }
}

void draw_save(
    system_t *sys, info_save_t *info, draw_textbox_t *draw, int start)
{
    node_t *head = info->current_file;
    draw_textbox_t tmp = {NULL};

    draw_page(sys, info, draw, start);
    if (head == NULL) {
        tmp = draw[start];
        tmp.str = "There is no file!!";
        tmp.color = GREY;
        draw_string(sys, sys->textbox, &tmp);
        return;
    }
    draw_save_loop(sys, head, draw, start);
}
