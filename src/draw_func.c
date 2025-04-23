/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_func
*/

#include "wolf.h"

void draw_string(system_t *sys, textbox_t *textbox, draw_textbox_t *draw)
{
    sfText_setPosition(textbox->text, draw->pos);
    sfText_setCharacterSize(textbox->text, draw->size);
    sfText_setString(textbox->text, draw->str);
    sfText_setColor(textbox->text, draw->color);
    sfRenderWindow_drawText(sys->window, sys->textbox->text, NULL);
}

void draw_background(system_t *sys, background_t *background)
{
    sfRenderWindow_drawSprite(sys->window, background->wallpaper_s, NULL);
    sfRenderWindow_drawSprite(sys->window, background->guy_s, NULL);
}
