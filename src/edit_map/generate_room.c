/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** generate_room
*/

#include "editor.h"
#include "entities.h"
#include <stdlib.h>

static void generate_enemy_item(
    generate_t *generate, system_t *sys, edit_map_t *edit)
{
    sfVector2i pos = {0, 0};

    for (int i = 0; i < generate->room.x + generate->room.y; i++) {
        while (edit->draw_map->map[pos.y][pos.x] != 0)
            pos = (sfVector2i){rand() % sys->save->size.x,
                rand() % sys->save->size.y};
        edit->draw_map->map[pos.y][pos.x] = rand() % NB_ITEM
            + EDIT_SMALL_HEALTH;
        while (edit->draw_map->map[pos.y][pos.x] != 0)
            pos = (sfVector2i){rand() % sys->save->size.x,
                rand() % sys->save->size.y};
        edit->draw_map->map[pos.y][pos.x] = rand() % NB_ENEMY
            + EDIT_SWORD_ENEMY;
    }
}

static void add_horizontal_wall(
    generate_t *generate, system_t *sys, edit_map_t *edit, sfVector2i *pos)
{
    if (generate->map_horizontal[pos->y][pos->x] == sfFalse)
        return;
    pos->x = pos->x * 4;
    pos->y = pos->y * 4 + 4;
    for (int i = pos->x; i <= pos->x + 4; i++) {
        if (sys->save->size.x <= i || pos->y >= sys->save->size.y)
            break;
        edit->draw_map->map[pos->y][i] = EDIT_WALL;
    }
}

static void add_vertical_wall(
    generate_t *generate, system_t *sys, edit_map_t *edit, sfVector2i *pos)
{
    if (generate->map_vertical[pos->y][pos->x] == sfFalse)
        return;
    pos->x = pos->x * 4 + 4;
    pos->y = pos->y * 4;
    for (int i = pos->y; i <= pos->y + 4; i++) {
        if (sys->save->size.y <= i || pos->x >= sys->save->size.x)
            break;
        edit->draw_map->map[i][pos->x] = EDIT_WALL;
    }
}

static void generate_wall(
    generate_t *generate, system_t *sys, edit_map_t *edit)
{
    for (int i = 0; i < generate->wall_vertical.y; i++) {
        for (int j = 0; j < generate->wall_vertical.x; j++)
            add_vertical_wall(generate, sys, edit, &(sfVector2i){j, i});
    }
    for (int i = 0; i < generate->wall_horizontal.y; i++) {
        for (int j = 0; j < generate->wall_horizontal.x; j++)
            add_horizontal_wall(generate, sys, edit, &(sfVector2i){j, i});
    }
}

static void handle_vertical(generate_t *generate, sfVector2i *pos)
{
    int one = generate->room_map[pos->y][pos->x + 1];
    int two = generate->room_map[pos->y][pos->x];

    if (replace_nb_room(generate, one, two) == sfTrue)
        generate->map_vertical[pos->y][pos->x] = sfFalse;
    else
        generate->map_vertical[pos->y][pos->x] = SKIP;
}

static void handle_horizontal(generate_t *generate, sfVector2i *pos)
{
    int one = generate->room_map[pos->y + 1][pos->x];
    int two = generate->room_map[pos->y][pos->x];

    if (replace_nb_room(generate, one, two) == sfTrue)
        generate->map_horizontal[pos->y][pos->x] = sfFalse;
    else
        generate->map_horizontal[pos->y][pos->x] = SKIP;
}

void generate_room(system_t *sys, edit_map_t *edit, generate_t *generate)
{
    sfVector2i tmp = {0};
    sfBool vertical = sfFalse;

    for (int i = count_wall(generate); i != 0; i = count_wall(generate)) {
        tmp = get_n_wall_pos(generate, rand() % i, &vertical);
        if (vertical == sfTrue)
            handle_vertical(generate, &tmp);
        else
            handle_horizontal(generate, &tmp);
    }
    generate_wall(generate, sys, edit);
    generate_enemy_item(generate, sys, edit);
}
