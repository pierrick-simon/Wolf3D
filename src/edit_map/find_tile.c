/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** find_tile
*/

#include "editor.h"

int find_side(sfVector2f mouse, sfVector2f p1, sfVector2f p2)
{
    return (p2.x - p1.x) * (mouse.y - p1.y) - (p2.y - p1.y) * (mouse.x - p1.x);
}

int is_inside_quad(sfVector2f mouse, sfVector2f point[4])
{
    int area = 0;
    sfVector2f p1 = {0};
    sfVector2f p2 = {0};

    for (int i = 0; i < 4; i++) {
        p1 = point[i];
        p2 = point[(i + 1) % 4];
        if (p1.y <= mouse.y && p2.y > mouse.y && find_side(mouse, p1, p2) > 0)
            area++;
        if (p1.y > mouse.y && p2.y <= mouse.y && find_side(mouse, p1, p2) < 0)
            area--;
    }
    if (area != 0)
        return 1;
    return 0;
}

static int loop_tile(
    sfVector2f mouse, draw_map_t *edit, int y, sfVector2f **map)
{
    sfVector2f point[4];

    for (int x = edit->size.x - 3; x >= 1; x--) {
        point[0] = map[y][x];
        point[1] = map[y + 1][x];
        point[2] = map[y + 1][x + 1];
        point[3] = map[y][x + 1];
        if (is_inside_quad(mouse, point) == 1)
            return x;
    }
    return -1;
}

sfVector2i which_tile(system_t *sys, draw_map_t *edit, sfVector2f **map)
{
    sfVector2i tmp_mouse = sfMouse_getPositionRenderWindow(sys->window);
    sfVector2f mouse = {(float)tmp_mouse.x, (float)tmp_mouse.y};
    sfVector2i tile = {-1, -1};
    int x = -1;

    if (sys->state->fullscreen == false) {
        mouse.x *= 2.0;
        mouse.y *= 2.0;
    }
    for (int y = edit->size.y - 3; y >= 1; y--) {
        x = loop_tile(mouse, edit, y, map);
        if (x != -1) {
            tile.x = x;
            tile.y = y;
            return tile;
        }
    }
    return tile;
}
