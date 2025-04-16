/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "wolf.h"
#include <math.h>

static sfBool is_end(sfVector2f *pos, which_line_t type)
{
    sfVector2i casted_pos = {(int)((int) pos->x / TILE_SIZE), (int)((int) (pos->y) / TILE_SIZE)};

    if (type == NONE)
        return sfFalse;
    if (type == TOP)
        --casted_pos.x;
    if (type == LEFT)
        --casted_pos.y;
    if (casted_pos.x < 0 || casted_pos.y < 0 || casted_pos.x >= MAP_WIDTH || casted_pos.y >= MAP_WIDTH)
        return sfTrue;
    return map[casted_pos.y][casted_pos.x] == 1;
}

static float get_line_len(sfVector2f *point)
{
    return sqrt(pow(point->x, 2) + pow(point->y, 2));
}

static void jump_to_next_line(sfVector2f *pos, sfVector2f *v, which_line_t *type)
{
    sfVector2f left = {0, 0};
    sfVector2f top = {0, 0};

    left.x = fmod(pos->x, TILE_SIZE);
    if (v->x > 0)
        left.x = TILE_SIZE - left.x;
    if (left.x == 0.0)
        left.x = 64.0;
    left.y = fabs((left.x * v->y) / v->x);

    top.y = fmod(pos->y, TILE_SIZE);
    if (v->y > 0)
        top.y = TILE_SIZE - top.y;
    if (top.y == 0.0)
        top.y = 64.0;
    top.x = fabs((top.y * v->x) / v->y);

    if (get_line_len(&left) < get_line_len(&top)) {
        if (v->x > 0)
            pos->x += left.x;
        else
            pos->x -= left.x;
        if (v->y > 0)
            pos->y += left.y;
        else
            pos->y -= left.y;
        if (v->x < 0)
            *type = TOP;
        else
            *type = BOTTOM;
    } else {
        if (v->y > 0)
            pos->y += top.y;
        else
            pos->y -= top.y;
        if (v->x > 0)
            pos->x += top.x;
        else
            pos->x -= top.x;
        if (v->y < 0)
            *type = LEFT;
        else
            *type = RIGHT;
    }
}

float cast_single_ray(player_t *player, float angle_offset)
{
    sfVector2f pos = {player->x, player->y};
    sfVector2f start = pos;
    sfVector2f v = {cos(player->angle + angle_offset), sin(player->angle + angle_offset)};
    float len = 0.0;
    which_line_t type = NONE;

    while ((is_end(&pos, type) == sfFalse)) {
        jump_to_next_line(&pos, &v, &type);
        len = sqrt(pow(pos.x - start.x, 2) + pow(pos.y - start.y, 2));
        if (len > RENDER_DISTANCE)
            return 0;
    }
    /*
    float line_h = (TILE_SIZE * WIN_HEIGHT * 3) / (len * cos(angle_offset));
    float line_width = 6 * (float)NUM_RAYS / (float)WIN_WIDTH;

    sfRectangleShape_setSize(line, (sfVector2f){line_width, line_h});
    sfRectangleShape_setOrigin(line, (sfVector2f){line_width / 2, line_h / 2});
    sfRectangleShape_setPosition(line, (sfVector2f){offest_x, WIN_HEIGHT / 2});
    sfRenderWindow_drawRectangleShape(window, line, NULL);
    */
    return len;
}

void cast_all_rays(sfRenderWindow *window, game_t *game)
{
    float offset = 0;

    for (int i = 0; i <= NUM_RAYS; i++) {
        cast_single_ray(game->player, ((i / (float)NUM_RAYS) * FOV) - (FOV / 2));
        offset += 6 * (float)NUM_RAYS / (float)WIN_WIDTH;
    }
}
