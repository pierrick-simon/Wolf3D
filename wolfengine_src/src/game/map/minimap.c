/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** map.c
*/

#include <stdio.h>
#include "wolfengine.h"
#include "hmap.h"

static void check_wall_type(sfRectangleShape *rect, int x, int y)
{
    if (map[y][x] == 1) {
        sfRectangleShape_setFillColor(rect, WALL_DEFAULT_COLOR);
    } else {
        sfRectangleShape_setFillColor(rect, WALL_INVISIBLE);
    }
}

static void set_walls(int x, int y, sfVector2f *xyoffset, game_t *game)
{
    sfRectangleShape *rect;

    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){MAP_S, MAP_S});
    check_wall_type(rect, x, y);
    xyoffset->x = x * MAP_S;
    xyoffset->y = y * MAP_S;
    sfRectangleShape_setPosition(rect, (sfVector2f){xyoffset->x, xyoffset->y});
    sfRenderWindow_drawRectangleShape(game->window, rect, sfFalse);
}

void draw_minimap(game_t *game)
{
    sfVector2f xyoffset = {0};

    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++) {
            set_walls(x, y, &xyoffset, game);
        }
    }
}