/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** generate_calcul
*/

#include "editor.h"

static void count_vertical_x(generate_t *generate, int i, int *count)
{
    for (int j = 0; j < generate->wall_vertical.x; j++)
        if (generate->map_vertical[i][j] == sfTrue)
            (*count)++;
}

static void count_horizontal_x(generate_t *generate, int i, int *count)
{
    for (int j = 0; j < generate->wall_horizontal.x; j++)
        if (generate->map_horizontal[i][j] == sfTrue)
            (*count)++;
}

int count_wall(generate_t *generate)
{
    int count = 0;

    for (int i = 0; i < generate->wall_vertical.y; i++)
        count_vertical_x(generate, i, &count);
    for (int i = 0; i < generate->wall_horizontal.y; i++)
        count_horizontal_x(generate, i, &count);
    return count;
}

static void replace_nb_room_x(generate_t *generate, int i, int one, int two)
{
    for (int j = 0; j < generate->room.x; j++)
        if (generate->room_map[i][j] == two)
            generate->room_map[i][j] = one;
}

sfBool replace_nb_room(generate_t *generate, int one, int two)
{
    int tmp = one;

    if (one == two)
        return sfFalse;
    if (one > two) {
        one = two;
        two = tmp;
    }
    for (int i = 0; i < generate->room.y; i++)
        replace_nb_room_x(generate, i, one, two);
    return sfTrue;
}

static sfBool get_n_vertical_pos_x(
    generate_t *generate, int i, int *count, sfVector2i *pos)
{
    for (int j = 0; j < generate->wall_vertical.x; j++) {
        if (generate->map_vertical[i][j] == sfTrue && *count == 0) {
            pos->x = j;
            pos->y = i;
            return sfTrue;
        }
        if (generate->map_vertical[i][j] == sfTrue)
            (*count)--;
    }
    return sfFalse;
}

static sfBool get_n_horizontal_pos_x(
    generate_t *generate, int i, int *count, sfVector2i *pos)
{
    for (int j = 0; j < generate->wall_horizontal.x; j++) {
        if (generate->map_horizontal[i][j] == sfTrue && *count == 0) {
            pos->x = j;
            pos->y = i;
            return sfTrue;
        }
        if (generate->map_horizontal[i][j] == sfTrue)
            (*count)--;
    }
    return sfFalse;
}

sfVector2i get_n_wall_pos(generate_t *generate, int n, sfBool *vertical)
{
    sfVector2i pos = {0};

    *vertical = sfTrue;
    for (int i = 0; i < generate->wall_vertical.y; i++)
        if (get_n_vertical_pos_x(generate, i, &n, &pos) == sfTrue)
            return pos;
    *vertical = sfFalse;
    for (int i = 0; i < generate->wall_horizontal.y; i++)
        if (get_n_horizontal_pos_x(generate, i, &n, &pos) == sfTrue)
            return pos;
    return pos;
}
