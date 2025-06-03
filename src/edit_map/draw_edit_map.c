/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_edit_map
*/

#include "editor.h"
#include "save.h"
#include "my.h"
#include "game.h"
#include "linked_list.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

static void set_point_draw_it(
    system_t *sys, edit_map_t *edit, sfVector2i indice, sfVector2f **iso_map)
{
    sfConvexShape_setFillColor(edit->draw_map->shape,
        edit->color[edit->draw_map->map[indice.y][indice.x]]);
    sfConvexShape_setPointCount(
        edit->draw_map->shape, 4);
    sfConvexShape_setPoint(
        edit->draw_map->shape, 0, iso_map[indice.y][indice.x]);
    sfConvexShape_setPoint(
        edit->draw_map->shape, 1, iso_map[indice.y + 1][indice.x]);
    sfConvexShape_setPoint(
        edit->draw_map->shape, 2, iso_map[indice.y + 1][indice.x + 1]);
    sfConvexShape_setPoint(
        edit->draw_map->shape, 3, iso_map[indice.y][indice.x + 1]);
    sfRenderWindow_drawConvexShape(
        sys->window, edit->draw_map->shape, NULL);
}

static void tmp_map(system_t *sys, draw_map_t *draw_map, sfVector2i *size)
{
    sfVector2i tile = {0, 0};

    draw_map->map = malloc(sizeof(int *) * size->y);
    for (int i = 0; i < size->y; i++) {
        draw_map->map[i] = malloc(sizeof(int) * size->x);
        for (int j = 0; j < size->x; j++) {
            draw_map->map[i][j] = sys->save->map[i][j];
        }
    }
    tile.x = floor(sys->save->info->start_pos.x / TILE_SIZE);
    tile.y = floor(sys->save->info->start_pos.y / TILE_SIZE);
    draw_map->map[tile.y][tile.x] = EDIT_START;
    for (node_t *head = sys->save->entities->head;
        head != NULL; head = head->next) {
        tile.x = floor(((entity_t *)(head->data))->pos.x / TILE_SIZE);
        tile.y = floor(((entity_t *)(head->data))->pos.y / TILE_SIZE);
        draw_map->map[tile.y][tile.x] = ((entity_t *)(head->data))->type
            + EDIT_SMALL_HEALTH;
    }
}

static void update_edit(
    system_t *sys, draw_map_t *draw_map, sfVector2i *size, edit_map_t *edit)
{
    if (edit->update == sfFalse) {
        draw_map->size = (sfVector2i){size->x + 1, size->y + 1};
        draw_map->coef = fmin((float)(WIN_WIDTH - (2 * MARGIN)) /
            draw_map->size.x, (float)(WIN_HEIGHT - (2 * MARGIN)) /
            draw_map->size.y);
        draw_map->pos = (sfVector2f){0, 0};
        draw_map->rotate = 0;
        draw_map->zoom = 1;
        tmp_map(sys, draw_map, size);
        edit->current = NULL;
        edit->update = sfTrue;
        empty_linked_list(sys->save->entities, &free);
    }
    draw_map->coor = create_2d_map(draw_map);
}

void draw_edit_map(system_t *sys, void *structure)
{
    edit_map_t *edit_map = (edit_map_t *)structure;

    update_edit(sys, edit_map->draw_map, &sys->save->size, edit_map);
    sfRenderWindow_setMouseCursorVisible(sys->window, sfTrue);
    sfRenderWindow_clear(sys->window, EDIT_BACKGROUND);
    for (int y = 0; y < edit_map->draw_map->size.y - 1; y++) {
        for (int x = 0; x < edit_map->draw_map->size.x - 1; x++)
            set_point_draw_it(sys, edit_map,
            (sfVector2i){x, y}, edit_map->draw_map->coor);
    }
    for (int i = 0; i < NB_EDIT_MAP; i++)
        draw_string(sys, sys->textbox, &edit_map->draw[i]);
    draw_button(sys, edit_map->buttons, edit_map);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
    edit_map_events(sys, edit_map);
    free_2d_map(edit_map->draw_map->size, edit_map->draw_map->coor);
}
