/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** scene
*/

#ifndef SCENE_H_
    #define SCENE_H_

    #include "wolf.h"

void *init_maps(void);
void draw_maps(system_t *sys, void *structure);
void destroy_maps(void *structure);

void draw_game(system_t *sys, void *structure);
void destroy_game(void *structure);
void *init_game(void);

typedef struct scene_func_s {
    int id;
    void *(*init)(void);
    void (*destroy)(void *);
    void (*draw)(system_t *sys, void *structure);
} scene_func_t;

static const scene_func_t SCENE[] = {
    {GAME, &init_game, &destroy_game, &draw_game},
    {MENU, &init_menu, &destroy_menu, &draw_menu},
    {SETTING, &init_setting, &destroy_setting, &draw_setting},
    {PAUSE, &init_pause, &destroy_pause, &draw_pause},
    {NOR_MAP, &init_maps, &destroy_maps, &draw_maps},
};

#endif
