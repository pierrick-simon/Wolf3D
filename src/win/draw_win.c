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

    if (time > SEC_IN_MICRO / DANSE_SWITCH) {
        move_rect(danse->sprite, &danse->rectangle, DANSE_WIDTH, danse->tile);
        sfClock_restart(clock);
    }
    sfSprite_setPosition(danse->sprite, danse->posf);
    sfRenderWindow_drawSprite(sys->window, danse->sprite, NULL);
    sfSprite_setPosition(danse->sprite, (sfVector2f){WIN_WIDTH -
        (DANSE_WIDTH * DANSE_SCALE) - DANSE_OFFSET, WIN_HEIGHT});
    sfRenderWindow_drawSprite(sys->window, danse->sprite, NULL);
}

static void draw_info(system_t *sys, draw_textbox_t *draw, char *str)
{
    draw_textbox_t tmp = *draw;

    tmp.str = str;
    tmp.pos.y += WIN_OFFSET;
    draw_string(sys, sys->textbox, &tmp);
}

static void update_win(save_t *save, win_t *win)
{
    int min = 0;
    int sec = 0;
    int len = strlen(win->name);

    sprintf(win->name_tmp, "%s", win->name);
    for (int i = len; i < MAX_NAME_SCORE; i++) {
        win->name_tmp[i] = '-';
    }
    win->name_tmp[MAX_NAME_SCORE] = '\0';
    if (win->update == sfFalse) {
        min = save->info->time / SEC_IN_MICRO / MIN_IN_SEC;
        sec = save->info->time / SEC_IN_MICRO % MIN_IN_SEC;
        sprintf(win->score, "%09d", save->info->score);
        sprintf(win->time, "%02d:%02d", min, sec);
        win->update = sfTrue;
    }
}

void draw_win(system_t *sys, void *structure)
{
    win_t *win = (win_t *)structure;
    sfSoundStatus music = sfMusic_getStatus(sys->music);

    update_win(sys->save, win);
    win_events(sys, win);
    sfRenderWindow_clear(sys->window, sfWhite);
    sfRenderWindow_drawSprite(sys->window, sys->background->wallpaper_s, NULL);
    for (int i = 0; i < NB_WIN; i++)
        draw_string(sys, sys->textbox, &win->draw[i]);
    draw_info(sys, &win->draw[WIN_NAME], win->name_tmp);
    draw_info(sys, &win->draw[WIN_TIME], win->time);
    draw_info(sys, &win->draw[WIN_SCORE], win->score);
    draw_danse(sys, win->danse, win->clock);
    sfMusic_stop(sys->save->music);
    if (music == sfStopped || music == sfPaused)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
