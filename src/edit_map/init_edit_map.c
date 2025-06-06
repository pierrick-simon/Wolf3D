/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_edit_map
*/

#include "editor.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

static void init_color(sfColor *color)
{
    int offset = 0;

    color[EDIT_NONE] = sfWhite;
    color[EDIT_WALL] = GREY;
    color[EDIT_DESTRUCTIBLE] = LIGHT_GREY;
    color[EDIT_DOOR] = DARK_GREY;
    color[EDIT_END] = sfGreen;
    color[EDIT_START] = sfBlue;
    for (int i = 1; i <= 12; i++) {
        offset = 100 * i / 10;
        color[EDIT_START + i] =
            sfColor_fromRGB(255 - offset, 128 - offset / 2, 0);
    }
    for (int i = 1; i <= 7; i++) {
        offset = 100 * i / 7;
        color[EDIT_WEAPON_FIVE + i] = sfColor_fromRGB(255 - offset, 0, 0);
    }
    for (int i = EDIT_BOSS + 1; i < NB_EDIT; i++)
        color[i] = sfMagenta;
}

static int init_draw_map(draw_map_t *draw_map)
{
    draw_map->shape = sfConvexShape_create();
    if (draw_map->shape == NULL)
        return ERROR;
    sfConvexShape_setOutlineColor(draw_map->shape, sfBlack);
    sfConvexShape_setOutlineThickness(draw_map->shape, 1);
    draw_map->map = NULL;
    return SUCCESS;
}

static int init_buttons(buttons_t *buttons)
{
    buttons->rectangle = sfRectangleShape_create();
    if (buttons->rectangle == NULL)
        return ERROR;
    buttons->press = sfFalse;
    sfRectangleShape_setSize(buttons->rectangle,
        (sfVector2f){SIZE_X_BUTTON, SIZE_Y_BUTTON});
    sfRectangleShape_setOutlineThickness(buttons->rectangle, 5);
    sfRectangleShape_setOutlineColor(buttons->rectangle, sfTransparent);
    for (int i = 0; i < NB_EDIT; i++) {
        sfRectangleShape_setPosition(buttons->rectangle, BUTTON[i].pos);
        buttons->bounds[i] = sfRectangleShape_getGlobalBounds(
            buttons->rectangle);
    }
    return SUCCESS;
}

void init_edit(edit_map_t *edit_map)
{
    for (int i = 0; i < NB_EDIT_MAP; i++)
        edit_map->draw[i].color = sfBlack;
    edit_map->update = sfFalse;
    edit_map->edit = EDIT_NONE;
    init_color(edit_map->color);
    edit_map->saving = sfFalse;
}

void *init_edit_map(void)
{
    edit_map_t *edit_map = malloc(sizeof(edit_map_t));

    if (edit_map == NULL)
        return NULL;
    edit_map->draw_map = malloc(sizeof(draw_map_t));
    if (edit_map->draw_map == NULL
        || init_draw_map(edit_map->draw_map) == ERROR)
        return NULL;
    edit_map->buttons = malloc(sizeof(buttons_t));
    if (edit_map->buttons == NULL || init_buttons(edit_map->buttons) == ERROR)
        return NULL;
    edit_map->str = EDIT_MAP_SAVE;
    edit_map->draw = init_from_conf(str_conf[CONF_EDIT_MAP]);
    edit_map->history = initialize_linked_list();
    edit_map->clock = sfClock_create();
    if (edit_map->draw == NULL || edit_map->history == NULL)
        return NULL;
    init_edit(edit_map);
    return (void *)edit_map;
}
