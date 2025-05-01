/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_create
*/

#include "create.h"

static void draw_strings(system_t *sys, create_t *create)
{
    draw_textbox_t draw = {NULL};

    for (int i = 0; i < NB_CREATE; i++) {
        draw_string(sys, sys->textbox, &create->draw[i]);
        if (i < NB_TEXTBOX) {
            draw = create->draw[i];
            draw.pos.y += FOUR;
            draw.str = create->strings[i];
            draw.color = sfBlue;
            draw_string(sys, sys->textbox, &draw);
        }
    }
}

void draw_create(system_t *sys, void *structure)
{
    create_t *create = (create_t *)structure;

    create_events(sys, create);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_strings(sys, create);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
