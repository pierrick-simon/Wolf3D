/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** ray_cast.c
*/

#include "wolf.h"
#include <math.h>

static void check_wall_type(sfRectangleShape *rect, int x, int y)
{
    sfRectangleShape_setOutlineThickness(rect, 1);
    if (map[y][x] == 1) {
        sfRectangleShape_setFillColor(rect, sfWhite);
        sfRectangleShape_setOutlineColor(rect, sfBlack);
    } else {
        sfRectangleShape_setFillColor(rect, sfBlack);
        sfRectangleShape_setOutlineColor(rect, sfWhite);
    }
}

static void set_walls(int x, int y, sfVector2f *xyoffset, sfRenderWindow *window)
{
    sfRectangleShape *rect;

    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){(TILE_SIZE / 2), (TILE_SIZE / 2)});
    check_wall_type(rect, x, y);
    xyoffset->x = x * (TILE_SIZE / 2);
    xyoffset->y = y * (TILE_SIZE / 2);
    sfRectangleShape_setPosition(rect, (sfVector2f){xyoffset->x, xyoffset->y});
    sfRenderWindow_drawRectangleShape(window, rect, sfFalse);
}

void draw_minimap(sfRenderWindow *window, player_t *player)
{
    sfVector2f xyoffset = {0};

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            set_walls(x, y, &xyoffset, window);
        }
    }
    sfCircleShape *player_point = sfCircleShape_create();
    sfCircleShape_setRadius(player_point, 5);
    sfCircleShape_setOutlineColor(player_point, sfRed);
    sfCircleShape_setOutlineThickness(player_point, 2);
    sfCircleShape_setPosition(player_point, (sfVector2f){(player->x / 2) - 5, (player->y / 2) - 5});
    sfRenderWindow_drawCircleShape(window, player_point, NULL);
}

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

static void jump_to_next_line(sfVector2f *pos, sfVector2f *v, which_line_t *type, sfRenderWindow *window)
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

float cast_single_ray(player_t *player,
    float ray_angle, sfRenderWindow *window, float offest_x, float angle_offset, sfVertex *point)
{
    sfVector2f pos = {player->x, player->y};
    sfVector2f start = pos;
    sfVector2f v = {cos(ray_angle + angle_offset), sin(ray_angle + angle_offset)};
    float len = 0.0;
    which_line_t type = NONE;

    while ((is_end(&pos, type) == sfFalse)) {
        jump_to_next_line(&pos, &v, &type, window);
        len = sqrt(pow(pos.x - start.x, 2) + pow(pos.y - start.y, 2));
        if (len > RENDER_DISTANCE) {
            point->color = sfGreen;
            point->position.x = pos.x / 2;
            point->position.y = pos.y / 2;
            return 0;
        }
    }
    point->position.x = pos.x / 2;
    point->position.y = pos.y / 2;
    sfRectangleShape *line = sfRectangleShape_create();
    if (type == TOP || type == BOTTOM)
        sfRectangleShape_setFillColor(line, sfGreen);
    else if (type == LEFT || type == RIGHT)
        sfRectangleShape_setFillColor(line, sfBlack);
    else
        sfRectangleShape_setFillColor(line, sfWhite);

    float line_h = (TILE_SIZE * WIN_HEIGHT * 3) / (len * cos(angle_offset));

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
    sfVertexArray *vertex = sfVertexArray_create();
    sfVertexArray *v_vertex = sfVertexArray_create();
    sfVector2f v = {cos(player->angle) * 100.0, sin(player->angle) * 100.0};
    sfVertex tmp = {0};

    draw_minimap(window, player);
    sfVertexArray_setPrimitiveType(vertex, sfLines);
    sfVertexArray_setPrimitiveType(v_vertex, sfLines);
    for (int i = 0; i <= NUM_RAYS; i++) {
        tmp.color = sfYellow;
        tmp.position = (sfVector2f){(player->x / 2), (player->y / 2)};
        sfVertexArray_append(v_vertex, tmp);
        tmp.position.x = v.x + (player->x / 2);
        tmp.position.y = v.y + (player->y / 2);
        sfVertexArray_append(v_vertex, tmp);
        sfRenderWindow_drawVertexArray(window, v_vertex, NULL);

        tmp.position = (sfVector2f){(player->x / 2), (player->y / 2)};
        tmp.color = sfRed;
        sfVertexArray_append(vertex, tmp);
        cast_single_ray(player, player->angle, window, offset, ((i / (float)NUM_RAYS) * FOV) - (FOV / 2), &tmp);
        sfVertexArray_append(vertex, tmp);
        offset += 6 * (float)NUM_RAYS / (float)WIN_WIDTH;
        sfRenderWindow_drawVertexArray(window, vertex, NULL);
    }
}
