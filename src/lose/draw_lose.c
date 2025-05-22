/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_win
*/

#include "quit.h"
#include "save.h"
#include <stdio.h>
#include <string.h>

static void draw_danse(system_t *sys, sprite_t *danse, sfClock *clock)
{
    sfInt64 time = sfClock_getElapsedTime(clock).microseconds;

    if (time > SEC_IN_MICRO / CHAIR_SWITCH) {
        move_rect(danse->sprite, &danse->rectangle, CHAIR_WIDTH, danse->tile);
        sfClock_restart(clock);
    }
    sfSprite_setPosition(danse->sprite, danse->posf);
    sfRenderWindow_drawSprite(sys->window, danse->sprite, NULL);
    sfSprite_setPosition(danse->sprite, (sfVector2f){WIN_WIDTH -
        CHAIR_WIDTH, WIN_HEIGHT});
    sfRenderWindow_drawSprite(sys->window, danse->sprite, NULL);
}

static void draw_info(system_t *sys, draw_textbox_t *draw, char *str)
{
    draw_textbox_t tmp = *draw;

    tmp.str = str;
    tmp.pos.y += WIN_OFFSET;
    draw_string(sys, sys->textbox, &tmp);
}

static void update_lose(save_t *save, lose_t *lose)
{
    int min = 0;
    int sec = 0;

    if (lose->update == sfFalse) {
        min = save->info->time / SEC_IN_MICRO / MIN_IN_SEC;
        sec = save->info->time / SEC_IN_MICRO % MIN_IN_SEC;
        sprintf(lose->score, "%09d", save->info->score);
        sprintf(lose->time, "%02d:%02d", min, sec);
        lose->update = sfTrue;
    }
}

void draw_lose(system_t *sys, void *structure)
{
    lose_t *lose = (lose_t *)structure;
    sfSoundStatus music = sfMusic_getStatus(sys->music);

    update_lose(sys->save, lose);
    lose_events(sys, lose);
    sfRenderWindow_clear(sys->window, sfWhite);
    sfRenderWindow_drawSprite(sys->window, sys->background->wallpaper_s, NULL);
    for (int i = 0; i < NB_LOSE; i++)
        draw_string(sys, sys->textbox, &lose->draw[i]);
    draw_info(sys, &lose->draw[LOSE_TIME], lose->time);
    draw_info(sys, &lose->draw[LOSE_SCORE], lose->score);
    draw_danse(sys, lose->spin_chair, lose->clock);
    sfMusic_stop(sys->save->music);
    if (music == sfStopped || music == sfPaused)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
