/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** quit
*/

#ifndef QUIT_H_
    #define QUIT_H_

    #include "wolf.h"

    #define DANSE_TILE 8
    #define DANSE_HEIGHT 83
    #define DANSE_WIDTH 75
    #define DANSE_SCALE 6
    #define DANSE_OFFSET 60
    #define DANSE_SWITCH 10

    #define CHAIR_TILE 8
    #define CHAIR_HEIGHT 87
    #define CHAIR_WIDTH 356
    #define CHAIR_SCALE 5
    #define CHAIR_OFFSET 80
    #define CHAIR_SWITCH 10

    #define WIN_OFFSET 125
    #define WIN_SIZE 50

    #define MAX_NAME_SCORE 10
    #define DEAULT_NAME_SCORE 3

    #define MAX_BONUS 300
    #define BONUS_COEF 1.2
    #define DRAW_BONUS 200

typedef enum {
    LEAVE_TITLE,
    LEAVE_SAVE,
    LEAVE_NO_SAVE,
    LEAVE_CANCEL,
    NB_LEAVE,
} str_leave_t;

typedef struct leave_s {
    int str;
    draw_textbox_t *draw;
} leave_t;

typedef enum {
    WIN_TITLE,
    WIN_TIME,
    WIN_SCORE,
    WIN_BONUS_SCORE,
    WIN_ENTER,
    WIN_SEE_SCORE,
    WIN_RESTART,
    WIN_MENU,
    NB_WIN,
} str_win_t;

typedef enum {
    LOSE_TITLE,
    LOSE_TIME,
    LOSE_SCORE,
    LOSE_RESTART,
    LOSE_SEE_SCORE,
    LOSE_MENU,
    NB_LOSE,
} str_lose_t;

typedef struct win_s {
    str_win_t str;
    draw_textbox_t *draw;
    sprite_t *danse;
    sfClock *clock;
    char *name;
    char name_tmp[MAX_NAME_SCORE + 1];
    char time[7];
    char score[10];
    int score_update;
    int prev_score;
    int score_step;
    sfBool update;
} win_t;

typedef struct lose_s {
    str_lose_t str;
    draw_textbox_t *draw;
    sprite_t *spin_chair;
    sfClock *clock;
    char *name;
    char time[7];
    char score[10];
    sfBool update;
} lose_t;

void leave_events(system_t *sys, leave_t *leave);
void win_events(system_t *sys, win_t *win);
void lose_events(system_t *sys, lose_t *lose);

#endif /* !QUIT_H_ */
