/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_score
*/

#include "score.h"
#include "save.h"
#include "linked_list.h"
#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

static void draw_page(
    system_t *sys, score_t *score, draw_textbox_t *draw)
{
    char *str = malloc(sizeof(char) *
        (get_nblen(score->current) + get_nblen(score->nb_page) + 2));
    draw_textbox_t tmp = {NULL};

    if (str == NULL)
        return;
    sprintf(str, "%d/%d", score->current, score->nb_page);
    tmp = *draw;
    tmp.pos.x += strlen(tmp.str) * tmp.size / POS_COEFF;
    tmp.pos.y += POS_OFFSET;
    tmp.str = str;
    tmp.size /= 2;
    draw_string(sys, sys->textbox, &tmp);
    free(str);
}

static void update_score(char *name, score_t *score)
{
    if (score->update == sfTrue)
        return;
    score->list = get_score(name);
    score->current = 1;
    score->nb_page = (int)ceil(
        (double)get_list_len(score->list) / NB_SHOW_SCORE);
    if (score->nb_page < 1)
        score->nb_page = 1;
    sprintf(score->draw[SCORE_TITLE].str, "%*s",
        get_offset(name, MAX_NAME), name);
    sort_linked_list(score->list, &sort_score);
    score->current_score = score->list->head;
    score->update = sfTrue;
}

static void draw_info(system_t *sys, draw_textbox_t *draw, char *str, int ind)
{
    draw_textbox_t tmp = *draw;

    tmp.str = str;
    tmp.pos.y += ind * SCORE_OFFSET;
    draw_string(sys, sys->textbox, &tmp);
}

static void draw_rang(system_t *sys, draw_textbox_t *draw, int ind, int nb)
{
    char *tmp = malloc(sizeof(char) * get_nblen(nb) + 1);

    if (tmp == NULL)
        return;
    sprintf(tmp, "%d", nb);
    draw_info(sys, draw, tmp, ind);
    free(tmp);
}

static void draw_list(system_t *sys, score_t *score)
{
    node_t *head = score->current_score;
    score_info_t *tmp = NULL;

    for (int i = 1; i <= NB_SHOW_SCORE; i++) {
        draw_rang(sys, &score->draw[SCORE_RANG],
            i, i + NB_SHOW_SCORE * (score->current - 1));
        if (head != NULL) {
            tmp = head->data;
            draw_info(sys, &score->draw[SCORE_NAME], tmp->name, i);
            draw_info(sys, &score->draw[SCORE_TIME], tmp->time, i);
            draw_info(sys, &score->draw[SCORE_SCORE], tmp->score, i);
            head = head->next;
        } else {
            draw_info(sys, &score->draw[SCORE_NAME], "---", i);
            draw_info(sys, &score->draw[SCORE_TIME], "--:--", i);
            draw_info(sys, &score->draw[SCORE_SCORE], "---------", i);
        }
    }
}

void draw_score(system_t *sys, void *structure)
{
    score_t *score = (score_t *)structure;

    update_score(sys->save->name, score);
    score_events(sys, score);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_SCORE; i++)
        draw_string(sys, sys->textbox, &score->draw[i]);
    draw_page(sys, score, &score->draw[SCORE_SUB]);
    draw_list(sys, score);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
