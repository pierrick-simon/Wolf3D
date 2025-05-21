/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_settings
*/

#include "wolf.h"

static void draw_fps(system_t *sys, setting_t *setting)
{
    double x = setting->draw[SETTING_FIVE].pos.x + SETTING_OFFSET * 1.5;
    double y = setting->draw[SETTING_FIVE].pos.y + SETTING_OFFSET / 2;
    double size_x = SETTING_FILL;
    double size_y = setting->draw[SETTING_FIVE].size / 3;
    double fill = size_x * (sys->state->fps - FPS_MIN) / (FPS_MAX - FPS_MIN);

    sfRectangleShape_setPosition(setting->rect, (sfVector2f){x, y});
    sfRectangleShape_setFillColor(setting->rect, sfTransparent);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){size_x, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    sfRectangleShape_setFillColor(setting->rect, sfMagenta);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){fill, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    sfRectangleShape_setPosition(setting->rect,
        (sfVector2f){x + fill - VOL_GAP, y - size_y / 2});
    sfRectangleShape_setFillColor(setting->rect, sfWhite);
    sfRectangleShape_setSize(setting->rect,
        (sfVector2f){VOL_GAP * 2, size_y * 2});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
}

static void draw_sound(system_t *sys, setting_t *setting)
{
    double x = setting->draw[SETTING_ZERO].pos.x + SETTING_OFFSET;
    double y = setting->draw[SETTING_ZERO].pos.y + SETTING_OFFSET / 2;
    double size_x = SETTING_FILL;
    double size_y = setting->draw[SETTING_ZERO].size / 3;
    double fill = size_x * sys->state->volume / VOL_MAX;

    sfRectangleShape_setPosition(setting->rect, (sfVector2f){x, y});
    sfRectangleShape_setFillColor(setting->rect, sfTransparent);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){size_x, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    sfRectangleShape_setFillColor(setting->rect, sfMagenta);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){fill, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    sfRectangleShape_setPosition(setting->rect,
        (sfVector2f){x + fill - VOL_GAP, y - size_y / 2});
    sfRectangleShape_setFillColor(setting->rect, sfWhite);
    sfRectangleShape_setSize(setting->rect,
        (sfVector2f){VOL_GAP * 2, size_y * 2});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
}

static void draw_fullscreen(system_t *sys, setting_t *set)
{
    double x = set->draw[SETTING_ON].pos.x + (double)SETTING_OFFSET * 1.5;
    double y = set->draw[SETTING_ON].pos.y + SETTING_OFFSET / 2;
    double size_y = set->draw[SETTING_ON].size / 3;
    double fill = 0;

    if (sys->state->fullscreen == sfFalse)
        fill = SETTING_FILL;
    sfRectangleShape_setPosition(set->rect, (sfVector2f){x, y});
    sfRectangleShape_setFillColor(set->rect, sfTransparent);
    sfRectangleShape_setSize(set->rect, (sfVector2f){SETTING_FILL, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, set->rect, NULL);
    sfRectangleShape_setFillColor(set->rect, sfMagenta);
    sfRectangleShape_setSize(set->rect, (sfVector2f){fill, size_y});
    sfRenderWindow_drawRectangleShape(sys->window, set->rect, NULL);
    sfRectangleShape_setPosition(set->rect,
        (sfVector2f){x + fill - VOL_GAP, y - size_y / 2});
    sfRectangleShape_setFillColor(set->rect, sfWhite);
    sfRectangleShape_setSize(set->rect,
        (sfVector2f){VOL_GAP * 2, size_y * 2});
    sfRenderWindow_drawRectangleShape(sys->window, set->rect, NULL);
}

void draw_settings(system_t *sys, void *structure)
{
    setting_t *setting = (setting_t *)structure;

    setting_events(sys, setting);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_SETTINGS; i++) {
        draw_string(sys, sys->textbox, &setting->draw[i]);
    }
    draw_fullscreen(sys, setting);
    draw_sound(sys, setting);
    draw_fps(sys, setting);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
