/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_sys
*/

#include "wolf.h"
#include <stdlib.h>

static int init_textbox(textbox_t *textbox)
{
    textbox->text = sfText_create();
    textbox->font = sfFont_createFromFile("asset/font.ttf");
    if (textbox->text == NULL || textbox->font == NULL)
        return ERROR;
    sfText_setFont(textbox->text, textbox->font);
    return SUCCESS;
}

static int init_background(background_t *background)
{
    double scale = (double)WIN_HEIGHT / GUY_SPRITE_Y;

    background->guy_s = sfSprite_create();
    background->guy_t = sfTexture_createFromFile("asset/doom_guy.png", NULL);
    background->wallpaper_s = sfSprite_create();
    background->wallpaper_t =
        sfTexture_createFromFile("asset/wallpaper.png", NULL);
    if (background->guy_s == NULL || background->guy_t == NULL
        || background->wallpaper_s == NULL || background->wallpaper_t == NULL)
        return ERROR;
    sfSprite_setTexture(background->guy_s, background->guy_t, sfTrue);
    sfSprite_setTexture(
        background->wallpaper_s, background->wallpaper_t, sfTrue);
    sfSprite_setScale(background->guy_s, (sfVector2f){scale, scale});
    return SUCCESS;
}

int init_system(system_t *sys)
{
    sys->window = create_window(sfFullscreen, 1);
    sys->music = sfMusic_createFromFile("asset/music.ogg");
    if (sys->window == NULL || sys->music == NULL)
        return ERROR;
    sys->background = malloc(sizeof(background_t));
    if (sys->background == NULL || init_background(sys->background) == ERROR)
        return ERROR;
    sys->textbox = malloc(sizeof(textbox_t));
    if (sys->textbox == NULL || init_textbox(sys->textbox) == ERROR)
        return ERROR;
    sys->fullscreen = sfTrue;
    sys->scene = MENU;
    sys->volume = VOL_MAX;
    return SUCCESS;
}
