/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** scene
*/

#ifndef SCENE_H_
    #define SCENE_H_

    #include "wolf.h"

void *init_normal_map(void);
void draw_normal_map(system_t *sys, void *structure);
void destroy_normal_map(void *structure);

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
    {SETTINGS, &init_settings, &destroy_settings, &draw_settings},
    {PAUSE, &init_pause, &destroy_pause, &draw_pause},
    {NOR_MAP, &init_normal_map, &destroy_normal_map, &draw_normal_map},
};

#endif
