/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "wolf.h"
#include <math.h>

static sfBool is_end(sfVector2f *v, sfVector2f *pos, wich_line_t type)
{
    sfVector2i casted_pos = {(int)(pos->x / TILE_SIZE), (int)(pos->y / TILE_SIZE)};

    if (type == NONE)
        return sfFalse;
    if (casted_pos.x < 0 || casted_pos.y < 0 || casted_pos.x >= MAP_WIDTH || casted_pos.y >= MAP_WIDTH)
        return sfTrue;
    return map[casted_pos.y][casted_pos.x] == 1;
}

static wich_line_t jump_to_next_line(sfVector2f *pos, sfVector2f *v)
{
    sfVector2f distances = {0, 0};

    distances.x = fmod(pos->x, 1.0);
    if (v->x > 0)
        distances.x = 1.0 - distances.x;
    distances.y = fmod(pos->y, 1.0);
    if (v->y > 0)
        distances.y = 1.0 - distances.y;
    dprintf(1, "%f %f\n", distances.x, distances.y);
    if ((distances.x < distances.y && distances.x != 0) || distances.y == 0) {
        if (v->x > 0)
            pos->x += distances.x;
        else
            pos->x -= distances.x;
        if (v->y < 0 && v->x < 0)
            pos->y -= (distances.x * v->y) / v->x;
        else
            pos->y += (distances.x * v->y) / v->x;
        return HORIZONTAL;
    }
    if (v->y > 0)
        pos->y += distances.y;
    else
        pos->y -= distances.y;
    if (v->y < 0 && v->x < 0)
        pos->x -= (distances.y * v->x) / v->y;
    else
        pos->x += (distances.y * v->x) / v->y;
    return VERTICAL;
}

float cast_single_ray(player_t *player,
    float ray_angle, sfRenderWindow *window, float offest_x)
{
    sfVector2f pos = {player->x, player->y};
    sfVector2f start = pos;
    sfVector2f v = {cos(ray_angle), sin(ray_angle)};
    float len = 0.0;
    wich_line_t type = NONE;

    while ((is_end(&v, &pos, type) == sfFalse)) {
        type = jump_to_next_line(&pos, &v);
        len = sqrt(pow(pos.x - start.x, 2) + pow(pos.y - start.y, 2));
        dprintf(1, "%f %f %f %f\n", DEG(ray_angle), v.x, v.y, len);
        if (len > 500)
            return -1;
    }
    sfRectangleShape *line = sfRectangleShape_create();
    if (type == HORIZONTAL)
        sfRectangleShape_setFillColor(line, sfGreen);
    else if (type == VERTICAL)
        sfRectangleShape_setFillColor(line, sfBlack);
    else
        sfRectangleShape_setFillColor(line, sfWhite);
    float line_h = (TILE_SIZE * WIN_HEIGHT * 3) / len;
    float line_width = 6 * (float)NUM_RAYS / (float)WIN_WIDTH;
    sfRectangleShape_setSize(line, (sfVector2f){line_width, line_h});
    sfRectangleShape_setOrigin(line, (sfVector2f){line_width / 2, line_h / 2});
    sfRectangleShape_setPosition(line, (sfVector2f){offest_x, WIN_HEIGHT / 2});
    sfRenderWindow_drawRectangleShape(window, line, NULL);
    return len;
}

void cast_all_rays(sfRenderWindow *window, player_t *player)
{
    float offset = 0;

    for (int i = 0; i <= NUM_RAYS; i++) {
        //dprintf(1, "----------------------\n");
        cast_single_ray(player, ((i / (float)NUM_RAYS) * FOV) - (FOV / 3) + player->angle, window, offset);
        offset += 6 * (float)NUM_RAYS / (float)WIN_WIDTH;
    }
    dprintf(1, "----------------------\n");
    cast_single_ray(player, ((0 / (float)NUM_RAYS) * FOV) - (FOV / 3) + player->angle, window, WIN_WIDTH / 2);
    sfRectangleShape *line = sfRectangleShape_create();
    sfRectangleShape_setFillColor(line, sfRed);
    float line_h = 200;
    float line_width = 10;
    sfRectangleShape_setSize(line, (sfVector2f){line_width, line_h});
    sfRectangleShape_setPosition(line, (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT / 2});
    sfRectangleShape_setRotation(line, DEG(player->angle));
    sfRenderWindow_drawRectangleShape(window, line, NULL);
    dprintf(1, "POS :%d %d\n", (int)player->x / TILE_SIZE, (int)player->y / TILE_SIZE);
}
