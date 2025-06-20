/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_sys
*/

#include "load_screen.h"
#include "save.h"
#include "game_menu.h"
#include "linked_list.h"
#include <stdlib.h>

static int init_textbox(textbox_t *textbox, load_screen_t *start)
{
    textbox->text = sfText_create();
    textbox->font = sfFont_createFromFile(str_asset[FONT_ASSET]);
    if (textbox->text == NULL || textbox->font == NULL)
        return ERROR;
    sfText_setFont(textbox->text, textbox->font);
    draw_load_screen(start, NB_SCENE - 0.6);
    return SUCCESS;
}

static int init_background(background_t *background, load_screen_t *start)
{
    double scale = (double)WIN_HEIGHT / GUY_SPRITE_Y;

    background->guy_s = sfSprite_create();
    background->guy_t = sfTexture_createFromFile(str_asset[GUY_ASSET], NULL);
    background->wallpaper_s = sfSprite_create();
    background->wallpaper_t =
        sfTexture_createFromFile(str_asset[WALLPAPER_ASSET], NULL);
    if (background->guy_s == NULL || background->guy_t == NULL
        || background->wallpaper_s == NULL || background->wallpaper_t == NULL)
        return ERROR;
    sfSprite_setTexture(background->guy_s, background->guy_t, sfTrue);
    sfSprite_setTexture(
        background->wallpaper_s, background->wallpaper_t, sfTrue);
    sfSprite_setScale(background->guy_s, (sfVector2f){scale, scale});
    draw_load_screen(start, NB_SCENE - 0.8);
    return SUCCESS;
}

static void init_state(state_info_t *state, load_screen_t *start)
{
    state->fullscreen = sfTrue;
    state->scene = MENU;
    state->old_scene = MENU;
    state->volume = VOL_MAX;
    state->fps = WIN_FRAME;
    draw_load_screen(start, NB_SCENE - 0.4);
}

static int init_save(save_t *save)
{
    save->info = malloc(sizeof(player_info_t));
    save->doors = initialize_linked_list();
    save->entities = initialize_linked_list();
    save->boss = initialize_linked_list();
    if (save->info == NULL || save->entities == NULL
        || save->doors == NULL || save->boss == NULL)
        return ERROR;
    save->init = sfFalse;
    save->music = NULL;
    save->mini_map = NULL;
    save->map = NULL;
    save->name = NULL;
    save->music_path = NULL;
    save->music = NULL;
    return SUCCESS;
}

int init_system(system_t *sys, load_screen_t *start)
{
    sys->background = malloc(sizeof(background_t));
    if (sys->background == NULL ||
        init_background(sys->background, start) == ERROR)
        return ERROR;
    sys->textbox = malloc(sizeof(textbox_t));
    if (sys->textbox == NULL || init_textbox(sys->textbox, start) == ERROR)
        return ERROR;
    sys->state = malloc(sizeof(state_info_t));
    if (sys->state == NULL)
        return ERROR;
    init_state(sys->state, start);
    sys->save = malloc(sizeof(save_t));
    if (sys->save == NULL || init_save(sys->save) == ERROR)
        return ERROR;
    sys->window = create_window(sfFullscreen, 1);
    sys->music = sfMusic_createFromFile(str_asset[MENU_MUSIC_ASSET]);
    if (sys->window == NULL || sys->music == NULL)
        return ERROR;
    sys->controler = sfJoystick_isConnected(0);
    return SUCCESS;
}
