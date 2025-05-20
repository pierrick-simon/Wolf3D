/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_sys
*/

#include <stdlib.h>
#include "save.h"
#include "game.h"

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

void destroy_save(save_t *save)
{
    if (save->init == sfTrue) {
        if (save->map != NULL)
            free_map(save->size.y, save->map);
        if (save->name != NULL)
            free(save->name);
        if (save->music_path != NULL)
            free(save->music_path);
        if (save->music != NULL)
            sfMusic_destroy(save->music);
        if (save->mini_map != NULL)
            free_mini_map_color(save->mini_map,
                save->size.y + MINI_MAP_OFFSET * 2);
        if (save->doors != NULL)
            empty_linked_list(save->doors, free);
        if (save->enemies != NULL)
            empty_linked_list(save->enemies, free);
        if (save->items != NULL)
            empty_linked_list(save->items, free);
    }
}

static void destroy_all_save(save_t *save)
{
    destroy_save(save);
    if (save->info != NULL)
        free(save->info);
    if (save->doors != NULL)
        free_linked_list(save->doors, free);
    if (save->enemies != NULL)
        free_linked_list(save->enemies, free);
    if (save->items != NULL)
        free_linked_list(save->items, free);
    free(save);
}

void destroy_sys(system_t *sys)
{
    if (sys->music != NULL)
        sfMusic_destroy(sys->music);
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
    if (sys->state != NULL)
        free(sys->state);
    if (sys->save != NULL)
        destroy_all_save(sys->save);
}
