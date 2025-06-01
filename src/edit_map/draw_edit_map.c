/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_edit_map
*/

#include "editor.h"
#include "save.h"
#include "my.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

static void set_point_draw_it(
    system_t *sys, edit_map_t *edit, sfVector2i indice, sfVector2f **iso_map)
{
    sfConvexShape_setPointCount(
        edit->shape, 4);
    sfConvexShape_setPoint(
        edit->shape, 0, iso_map[indice.y][indice.x]);
    sfConvexShape_setPoint(
        edit->shape, 1, iso_map[indice.y + 1][indice.x]);
    sfConvexShape_setPoint(
        edit->shape, 2, iso_map[indice.y + 1][indice.x + 1]);
    sfConvexShape_setPoint(
        edit->shape, 3, iso_map[indice.y][indice.x + 1]);
    sfRenderWindow_drawConvexShape(
        sys->window, edit->shape, NULL);
}

static sfVector2f **update_edit(edit_map_t *edit_map, sfVector2i *size)
{
    if (edit_map->update == sfFalse) {
        edit_map->size = *size;
        edit_map->coef = fmin((float)(WIN_WIDTH - (2 * MARGIN)) /
            edit_map->size.x, (float)(WIN_HEIGHT - (2 * MARGIN)) /
            edit_map->size.y);
        edit_map->pos = (sfVector2f){0, 0};
        edit_map->rotate = 0;
        edit_map->zoom = 1;
        edit_map->update = sfTrue;
    }
    return create_2d_map(edit_map);
}

void draw_edit_map(system_t *sys, void *structure)
{
    edit_map_t *edit_map = (edit_map_t *)structure;
    sfVector2f **iso_map = update_edit(edit_map, &sys->save->size);

    sfRenderWindow_setMouseCursorVisible(sys->window, sfTrue);
    edit_map_events(sys, edit_map);
    sfRenderWindow_clear(sys->window, EDIT_BACKGROUND);
    for (int y = 0; y < edit_map->size.y - 1; y++) {
        for (int x = 0; x < edit_map->size.x - 1; x++)
            set_point_draw_it(sys, edit_map, (sfVector2i){x, y}, iso_map);
    }
    for (int i = 0; i < NB_EDIT_MAP; i++)
        draw_string(sys, sys->textbox, &edit_map->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    free_2d_map(edit_map->size, iso_map);
    sfRenderWindow_display(sys->window);
}
