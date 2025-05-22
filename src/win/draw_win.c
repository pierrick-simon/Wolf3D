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
#include <math.h>

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

static void set_win(save_t *save, win_t *win)
{
    int min = 0;
    int sec = 0;

    if (win->update == sfFalse) {
        win->prev_score = save->info->score;
        win->score_update = save->info->score;
        save->info->score *= pow(MAX_BONUS / (save->info->time
            / SEC_IN_MICRO), BONUS_COEF) * save->info->difficulty;
        win->score_step = (save->info->score - win->prev_score) / DRAW_BONUS;
        if (save->info->score > MAX_SCORE || save->info->score < 0)
            save->info->score = MAX_SCORE;
        min = save->info->time / SEC_IN_MICRO / MIN_IN_SEC;
        sec = save->info->time / SEC_IN_MICRO % MIN_IN_SEC;
        sprintf(win->time, "%02d:%02d", min, sec);
        win->update = sfTrue;
    }
}

static void update_win(save_t *save, win_t *win)
{
    int len = strlen(win->name);

    sprintf(win->name_tmp, "%s", win->name);
    for (int i = len; i < MAX_NAME_SCORE; i++) {
        win->name_tmp[i] = '-';
    }
    win->name_tmp[MAX_NAME_SCORE] = '\0';
    if (win->score_update < save->info->score - win->score_step)
        win->score_update += win->score_step;
    else if (win->score_update < save->info->score)
        win->score_update++;
    sprintf(win->score, "%09d", win->score_update);
    sprintf(win->draw[WIN_BONUS_SCORE].str, "+ %d",
        win->score_update - win->prev_score);
}

static void show_info(system_t *sys, win_t *win)
{
    sfRenderWindow_drawSprite(sys->window, sys->background->wallpaper_s, NULL);
    for (int i = 0; i < NB_WIN; i++) {
        if (i == WIN_BONUS_SCORE
            && win->score_update == sys->save->info->score)
            continue;
        draw_string(sys, sys->textbox, &win->draw[i]);
    }
    draw_info(sys, &win->draw[WIN_TIME], win->time);
    draw_info(sys, &win->draw[WIN_SCORE], win->score);
    draw_danse(sys, win->danse, win->clock);
    sfMusic_stop(sys->save->music);
}

void draw_win(system_t *sys, void *structure)
{
    win_t *win = (win_t *)structure;
    sfSoundStatus music = sfMusic_getStatus(sys->music);

    set_win(sys->save, win);
    update_win(sys->save, win);
    win_events(sys, win);
    sfRenderWindow_clear(sys->window, sfWhite);
    show_info(sys, win);
    if (music == sfStopped || music == sfPaused)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
