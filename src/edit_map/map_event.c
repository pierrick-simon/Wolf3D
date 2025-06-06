/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** map_event
*/

#include "editor.h"
#include "linked_list.h"

static void set_orientation(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyA, sfFalse, 0)) {
        edit->draw_map->rotate -= RAD(1);
    }
    if (is_input(event, sfKeyE, sfFalse, 0)) {
        edit->draw_map->rotate += RAD(1);
    }
}

static void set_zoom(sfEvent event, edit_map_t *edit)
{
    float zoom = 0;

    if (event.type == sfEvtMouseWheelScrolled) {
        zoom = event.mouseWheelScroll.delta;
        if (zoom > 0)
            zoom = ZOOM * -1;
        else
            zoom = ZOOM;
        edit->draw_map->zoom += zoom;
        if (edit->draw_map->zoom > MAX_ZOOM)
            edit->draw_map->zoom = MAX_ZOOM;
        if (edit->draw_map->zoom < MIN_ZOOM)
            edit->draw_map->zoom = MIN_ZOOM;
    }
}

static void move_map(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyZ, sfFalse, 0)) {
        edit->draw_map->pos.y -= MOVE;
        if (edit->draw_map->pos.y < -1 * (WIN_HEIGHT / 2))
            edit->draw_map->pos.y = -1 * (WIN_HEIGHT / 2);
    }
    if (is_input(event, sfKeyS, sfFalse, 0)) {
        edit->draw_map->pos.y += MOVE;
        if (edit->draw_map->pos.y > WIN_HEIGHT / 2)
            edit->draw_map->pos.y = WIN_HEIGHT / 2;
    }
    if (is_input(event, sfKeyQ, sfFalse, 0)) {
        edit->draw_map->pos.x -= MOVE;
        if (edit->draw_map->pos.x < -1 * (WIN_WIDTH / 2))
            edit->draw_map->pos.x = -1 * (WIN_WIDTH / 2);
    }
    if (is_input(event, sfKeyD, sfFalse, 0)) {
        edit->draw_map->pos.x += MOVE;
        if (edit->draw_map->pos.x > WIN_WIDTH / 2)
            edit->draw_map->pos.x = WIN_WIDTH / 2;
    }
}

static void reset_pos(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyC, sfFalse, 0)) {
        edit->draw_map->pos = (sfVector2f){0, 0};
        edit->draw_map->rotate = 0;
        edit->draw_map->zoom = 1;
    }
}

void map_event(sfEvent event, edit_map_t *edit_map)
{
    move_map(event, edit_map);
    set_zoom(event, edit_map);
    set_orientation(event, edit_map);
    reset_pos(event, edit_map);
}

static sfBool find_edit(int **map, int edit, sfVector2i size, int i)
{
    for (int j = 0; j < size.x; j++) {
        if (map[i][j] == edit) {
            map[i][j] = EDIT_NONE;
            return sfTrue;
        }
    }
    return sfFalse;
}

static void only_one(int **map, int edit, sfVector2i size)
{
    if (edit != EDIT_END && edit != EDIT_START)
        return;
    for (int i = 0; i < size.y; i++) {
        if (find_edit(map, edit, size, i))
            break;
    }
}

void mouse_click(system_t *sys, edit_map_t *edit, sfVector2f **map)
{
    sfVector2i tile = {0, 0};

    for (edit_t i = 0; i < NB_EDIT; i++)
        if (edit->buttons->hover[i] == sfTrue)
            return;
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        tile = which_tile(sys, edit->draw_map, map);
        if (tile.x != -1 && tile.y != -1
            && edit->buttons->press == sfTrue) {
            del_head_history(edit);
            add_node_history(edit);
            edit->current = edit->history->head;
            only_one(edit->draw_map->map, edit->edit, sys->save->size);
            edit->draw_map->map[tile.y][tile.x] = edit->edit;
        }
    }
}
