/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_sys
*/

#include "wolf.h"
#include <stdlib.h>

static void destroy_textbox(textbox_t *textbox)
{
    if (textbox->font != NULL)
        sfFont_destroy(textbox->font);
    if (textbox->text != NULL)
        sfText_destroy(textbox->text);
}

static void destroy_background(background_t *background)
{
    if (background->guy_t != NULL)
        sfTexture_destroy(background->guy_t);
    if (background->guy_s != NULL)
        sfSprite_destroy(background->guy_s);
    if (background->wallpaper_t != NULL)
        sfTexture_destroy(background->wallpaper_t);
    if (background->wallpaper_s != NULL)
        sfSprite_destroy(background->wallpaper_s);
}

void destroy_sys(system_t *sys)
{
    if (sys->music != NULL)
        sfMusic_destroy(sys->music);
    if (sys->clock != NULL)
        sfClock_destroy(sys->clock);
    if (sys->window != NULL)
        sfRenderWindow_destroy(sys->window);
    if (sys->background != NULL) {
        destroy_background(sys->background);
        free(sys->background);
    }
    if (sys->textbox != NULL) {
        destroy_textbox(sys->textbox);
        free(sys->textbox);
    }
}
