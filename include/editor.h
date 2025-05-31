/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** editor
*/

#ifndef EDITOR_H_
    #define EDITOR_H_

    #include "wolf.h"
    #include "save.h"

typedef enum str_edit_info_e {
    EDIT_INF_TITLE,
    EDIT_INF_NAME,
    EDIT_INF_X,
    EDIT_INF_Y,
    EDIT_INF_BACK,
    NB_EDIT_INF,
} str_edit_info_t;

typedef struct edit_info_s {
    str_edit_info_t str;
    draw_textbox_t *draw;
    sfRectangleShape *rect;
    char string[NB_EDIT_INF][MAX_NAME + 1];
    char str_tmp[NB_EDIT_INF][MAX_NAME + 1];
} edit_info_t;

void edit_info_events(system_t *sys, edit_info_t *edit_info);

#endif /* !EDITOR_H_ */
