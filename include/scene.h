/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** scene
*/

#ifndef SCENE_H_
    #define SCENE_H_

    #include "wolf.h"

void *init_difficulty(void);
void destroy_difficulty(void *structure);
void draw_difficulty(system_t *sys, void *structure);

void *init_menu(void);
void destroy_menu(void *structure);
void draw_menu(system_t *sys, void *structure);

void *init_pause(void);
void destroy_pause(void *structure);
void draw_pause(system_t *sys, void *structure);

void *init_settings(void);
void draw_settings(system_t *sys, void *structure);
void destroy_settings(void *structure);

void *init_lose(void);
void draw_lose(system_t *sys, void *structure);
void destroy_lose(void *structure);


void *init_win(void);
void draw_win(system_t *sys, void *structure);
void destroy_win(void *structure);

void *init_score(void);
void draw_score(system_t *sys, void *structure);
void destroy_score(void *structure);

void *init_map(void);
void draw_map(system_t *sys, void *structure);
void destroy_map(void *structure);

void *init_maps(void);
void draw_maps(system_t *sys, void *structure);
void destroy_maps(void *structure);

void draw_game(system_t *sys, void *structure);
void destroy_game(void *structure);
void *init_game(void);

void *init_leave(void);
void draw_leave(system_t *sys, void *structure);
void destroy_leave(void *structure);

typedef struct scene_func_s {
    int id;
    void *(*init)(void);
    void (*destroy)(void *);
    void (*draw)(system_t *sys, void *structure);
} scene_func_t;

static const scene_func_t SCENE[] __maybe_unused = {
    {GAME, &init_game, &destroy_game, &draw_game},
    {MENU, &init_menu, &destroy_menu, &draw_menu},
    {SETTINGS, &init_settings, &destroy_settings, &draw_settings},
    {PAUSE, &init_pause, &destroy_pause, &draw_pause},
    {MAPS, &init_maps, &destroy_maps, &draw_maps},
    {MAP, &init_map, &destroy_map, &draw_map},
    {SCORE, &init_score, &destroy_score, &draw_score},
    {LEAVE, &init_leave, &destroy_leave, &draw_leave},
    {WIN, &init_win, &destroy_win, &draw_win},
    {LOSE, &init_lose, &destroy_lose, &draw_lose},
    {DIFFICULTY, &init_difficulty, &destroy_difficulty, &draw_difficulty}
};

#endif
