/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** quit
*/

#ifndef QUIT_H_
    #define QUIT_H_

    #include "wolf.h"

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

void *init_leave(void);
void draw_leave(system_t *sys, void *structure);
void leave_events(system_t *sys, leave_t *leave);
void destroy_leave(void *structure);

#endif /* !QUIT_H_ */
