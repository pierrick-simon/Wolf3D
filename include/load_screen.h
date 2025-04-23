/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** load_screen
*/

#ifndef LOAD_SCREEN_H_
    #define LOAD_SCREEN_H_

    #include "wolf.h"

    #define RECT_OFFSET 50

typedef struct load_screen_s {
    sfRenderWindow *window;
    sfRectangleShape *rect;
    int nb_init;
} load_screen_t;

int load_screen(void ***structure, system_t *sys);
void draw_load_screen(load_screen_t *start, double ind);
void **init_struct(load_screen_t *start);
int init_system(system_t *sys, load_screen_t *start);

#endif
