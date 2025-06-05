/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** generate_map
*/

#include "editor.h"
#include "stdlib.h"
#include "time.h"
#include "linked_list.h"
#include "entities.h"
#include <math.h>

static void reset(system_t *sys, edit_map_t *edit)
{
    for (int i = 1; i < sys->save->size.y - 1; i++) {
        for (int j = 1; j < sys->save->size.x - 1; j++)
            edit->draw_map->map[i][j] = 0;
    }
}

static void generate_start_end(system_t *sys, edit_map_t *edit)
{
    sfVector2i pos = {0, 0};

    while (edit->draw_map->map[pos.y][pos.x] != 0)
        pos = (sfVector2i){rand() % sys->save->size.x,
            rand() % sys->save->size.y};
    edit->draw_map->map[pos.y][pos.x] = EDIT_START;
    while (edit->draw_map->map[pos.y][pos.x] != 0)
        pos = (sfVector2i){rand() % sys->save->size.x,
            rand() % sys->save->size.y};
    edit->draw_map->map[pos.y][pos.x] = EDIT_END;
}

static void get_coor(system_t *sys, generate_t *generate)
{
    generate->room = (sfVector2i){ceil((float)sys->save->size.x / 4),
        ceil((float)sys->save->size.y / 4)};
    generate->wall_horizontal = (sfVector2i)
        {generate->room.x, generate->room.y - 1};
    generate->wall_vertical = (sfVector2i)
        {generate->room.x - 1, generate->room.y};
}

static void init_generate(system_t *sys, generate_t *generate)
{
    int count = 0;

    get_coor(sys, generate);
    for (int i = 0; i < generate->wall_vertical.y; i++) {
        for (int j = 0; j < generate->wall_vertical.x; j++)
            generate->map_vertical[i][j] = sfTrue;
    }
    for (int i = 0; i < generate->wall_horizontal.y; i++) {
        for (int j = 0; j < generate->wall_horizontal.x; j++)
            generate->map_horizontal[i][j] = sfTrue;
    }
    for (int i = 0; i < generate->room.y; i++) {
        for (int j = 0; j < generate->room.x; j++) {
            generate->room_map[i][j] = count;
            count++;
        }
    }
}

void generate_map(system_t *sys, edit_map_t *edit)
{
    generate_t generate = {0};

    srand(time(NULL));
    reset(sys, edit);
    if (sys->save->size.x > 6 && sys->save->size.x > 6) {
        init_generate(sys, &generate);
        generate_room(sys, edit, &generate);
    }
    generate_start_end(sys, edit);
    del_head_history(edit);
    add_node_history(edit);
    edit->current = edit->history->head;
}
