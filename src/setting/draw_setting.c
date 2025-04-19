/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_setting
*/

#include "wolf.h"

static void draw_rectangle(system_t *sys, setting_t *setting)
{
    double size = setting->draw[SETTING_ON_OFF].size;

    sfRectangleShape_setTexture(setting->rect, NULL, sfFalse);
    sfRectangleShape_setPosition(
        setting->rect, setting->draw[SETTING_ON_OFF].pos);
    sfRectangleShape_setFillColor(setting->rect, sfTransparent);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){SWITCH, size});
    sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    sfRectangleShape_setTexture(
        setting->rect, sys->background->wallpaper_t, sfFalse);
    sfRectangleShape_setFillColor(setting->rect, sfWhite);
    sfRectangleShape_setSize(setting->rect, (sfVector2f){SWITCH / 2, size});
}

static void draw_fullscreen(system_t *sys, setting_t *setting)
{
    double x = setting->draw[SETTING_ON_OFF].pos.x;
    double y = setting->draw[SETTING_ON_OFF].pos.y;

    draw_rectangle(sys, setting);
    if (sys->fullscreen == sfTrue) {
        setting->draw[SETTING_ON_OFF].color = sfGreen;
        sfRectangleShape_setPosition(
            setting->rect, (sfVector2f){x + SWITCH / 2, y});
        sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    } else {
        setting->draw[SETTING_ON_OFF].color = sfRed;
        sfRenderWindow_drawRectangleShape(sys->window, setting->rect, NULL);
    }
}

void draw_setting(system_t *sys, void *structure)
{
    setting_t *setting = (setting_t *)structure;

    setting_events(sys, setting);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_SETTING; i++) {
        draw_string(sys, sys->textbox, &setting->draw[i]);
    }
    draw_fullscreen(sys, setting);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
