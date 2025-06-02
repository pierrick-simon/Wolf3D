/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** add_node_history
*/

#include "editor.h"
#include "linked_list.h"

void check_history(edit_map_t *edit, history_t *history, int i, sfBool *equal)
{
    node_t *current = edit->history->head;

    for (int j = 0; j < edit->draw_map->size.x - 1; j++) {
        history->map[i][j] = edit->draw_map->map[i][j];
        if (current == NULL || history->map[i][j]
            != ((history_t *)current->data)->map[i][j])
            *equal = sfFalse;
    }
}

void add_node_history(edit_map_t *edit)
{
    history_t *history = malloc(sizeof(history_t));
    sfBool equal = sfTrue;

    history->map = malloc(sizeof(int *) * (edit->draw_map->size.y - 1));
    for (int i = 0; i < edit->draw_map->size.y - 1; i++) {
        history->map[i] = malloc(sizeof(int) * (edit->draw_map->size.x - 1));
        check_history(edit, history, i, &equal);
    }
    history->size = edit->draw_map->size.y - 1;
    if (equal == sfFalse)
        push_to_head(edit->history, history);
    else {
        free_node_history(history);
        free(history);
    }
}

void free_node_history(void *data)
{
    history_t *history = data;

    free_map(history->size, history->map);
}

void del_head_history(edit_map_t *edit)
{
    while (edit->current != edit->history->head) {
        delete_node(edit->history, edit->history->head, &free_node_history);
    }
}
