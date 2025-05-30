/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "wolf.h"

    #define VOL_MAX 100.0
    #define VOL_MIN 0.0
    #define VOL_GAP 5.0

    #define FPS_MAX 200
    #define FPS_MIN 50
    #define FPS_GAP 10

    #define START_DIFFICULTY 0.5
    #define DIFFICULTY_GAP 0.25

    #define SWITCH 170
    #define PAD sfColor_fromRGB(255, 230, 200)

    #define SETTING_FILL 400
    #define ON_OFF_CURSOR 50
    #define SETTING_OFFSET 30

typedef enum str_menu_e {
    MENU_TITLE,
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_QUIT,
    NB_MENU,
} str_menu_t;

typedef enum str_pause_e {
    PAUSE_TITLE,
    PAUSE_RESUME,
    PAUSE_RESTART,
    PAUSE_SETTINGS,
    PAUSE_BACK,
    NB_PAUSE,
} str_pause_t;

typedef enum str_setting_e {
    SETTING_ON,
    SETTING_OFF,
    SETTING_ZERO,
    SETTING_HUNDRED,
    SETTING_FIVE,
    SETTING_TWO,
    SETTING_TITLE,
    SETTING_FULL,
    SETTING_SOUND,
    SETTING_FPS,
    SETTING_BACK,
    NB_SETTINGS,
} str_setting_t;

typedef enum str_difficulty_e {
    DIFF_TITLE,
    DIFF_ONE,
    DIFF_TWO,
    DIFF_THREE,
    DIFF_FOUR,
    DIFF_FIVE,
    DIFF_BACK,
    NB_DIFFICULTY,
} str_difficulty_t;

typedef struct setting_s {
    str_setting_t str;
    draw_textbox_t *draw;
    sfRectangleShape *rect;
} setting_t;

typedef struct pause_s {
    str_pause_t str;
    draw_textbox_t *draw;
} pause_t;

typedef struct menu_s {
    str_menu_t str;
    draw_textbox_t *draw;
} menu_t;

typedef struct difficulty_s {
    str_difficulty_t str;
    draw_textbox_t *draw;
} difficulty_t;

typedef enum str_choose_e {
    CHOOSE_TITLE,
    CHOOSE_LEVELS,
    CHOOSE_YOURS_MAPS,
    CHOOSE_BACK,
    NB_CHOOSE,
} str_choose_t;

typedef struct choose_s {
    str_choose_t str;
    draw_textbox_t *draw;
} choose_t;

void menu_events(system_t *sys, menu_t *menu);
void choose_events(system_t *sys, choose_t *choose);
void pause_events(system_t *sys, pause_t *pause);
void setting_events(system_t *sys, setting_t *setting);
void difficulty_events(system_t *sys, difficulty_t *difficulty);

#endif /* !MENU_H_ */
