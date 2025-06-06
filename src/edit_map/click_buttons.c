/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** click_buttons
*/

#include "entities.h"
#include "save.h"
#include "editor.h"
#include "linked_list.h"
#include <math.h>

void reset_button(system_t *sys, edit_map_t *edit)
{
    for (int i = 1; i < sys->save->size.y - 1; i++) {
        for (int j = 1; j < sys->save->size.x - 1; j++)
            edit->draw_map->map[i][j] = 0;
    }
    del_head_history(edit);
    add_node_history(edit);
    edit->current = edit->history->head;
}

void center_button(__maybe_unused system_t *sys, edit_map_t *edit)
{
    edit->draw_map->pos = (sfVector2f){0, 0};
    edit->draw_map->rotate = 0;
    edit->draw_map->zoom = 1;
}

void refresh_button(system_t *sys, edit_map_t *edit)
{
    sfVector2i tile = {0, 0};

    for (int i = 0; i < sys->save->size.y; i++) {
        for (int j = 0; j < sys->save->size.x; j++)
            edit->draw_map->map[i][j] = sys->save->map[i][j];
    }
    tile.x = floor(sys->save->info->start_pos.x / TILE_SIZE);
    tile.y = floor(sys->save->info->start_pos.y / TILE_SIZE);
    edit->draw_map->map[tile.y][tile.x] = EDIT_START;
    for (node_t *head = sys->save->entities->head;
        head != NULL; head = head->next) {
        tile.x = floor(((entity_t *)(head->data))->pos.x / TILE_SIZE);
        tile.y = floor(((entity_t *)(head->data))->pos.y / TILE_SIZE);
        edit->draw_map->map[tile.y][tile.x] = ((entity_t *)(head->data))->type
            + EDIT_SMALL_HEALTH;
    }
    del_head_history(edit);
    add_node_history(edit);
    edit->current = edit->history->head;
}

void prev_button(system_t *sys, edit_map_t *edit)
{
    history_t *history = NULL;

    if (edit->current == NULL || edit->current->next == NULL)
        return;
    edit->current = edit->current->next;
    history = edit->current->data;
    free_map(sys->save->size.y, edit->draw_map->map);
    edit->draw_map->map = malloc(sizeof(int *) * sys->save->size.y);
    for (int i = 0; i < sys->save->size.y; i++) {
        edit->draw_map->map[i] = malloc(sizeof(int) * sys->save->size.x);
        for (int j = 0; j < sys->save->size.x; j++)
            edit->draw_map->map[i][j] = history->map[i][j];
    }
}

void next_button(system_t *sys, edit_map_t *edit)
{
    history_t *history = NULL;

    if (edit->current == NULL || edit->current->prev == NULL)
        return;
    edit->current = edit->current->prev;
    history = edit->current->data;
    free_map(sys->save->size.y, edit->draw_map->map);
    edit->draw_map->map = malloc(sizeof(int *) * sys->save->size.y);
    for (int i = 0; i < sys->save->size.y; i++) {
        edit->draw_map->map[i] = malloc(sizeof(int) * sys->save->size.x);
        for (int j = 0; j < sys->save->size.x; j++)
            edit->draw_map->map[i][j] = history->map[i][j];
    }
}
