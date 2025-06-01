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

    #define EDIT_BACKGROUND sfColor_fromRGB(200, 200, 200)

    #define ANGLE_X RAD(0.0)
    #define ANGLE_Y RAD(35.0)

    #define MARGIN 150

    #define ZOOM 0.1
    #define MAX_ZOOM 3.0
    #define MIN_ZOOM 0.2

    #define MOVE 5

typedef enum str_edit_info_e {
    EDIT_INF_TITLE,
    EDIT_INF_NAME,
    EDIT_INF_X,
    EDIT_INF_Y,
    EDIT_INF_BACK,
    NB_EDIT_INF,
} str_edit_info_t;

typedef enum str_edit_map_e {
    EDIT_MAP_TITLE,
    EDIT_MAP_SAVE,
    EDIT_MAP_BACK,
    NB_EDIT_MAP,
} str_edit_map_t;

typedef struct edit_info_s {
    str_edit_info_t str;
    draw_textbox_t *draw;
    char string[NB_EDIT_INF][MAX_NAME + 1];
    char str_tmp[NB_EDIT_INF][MAX_NAME + 1];
} edit_info_t;

typedef struct edit_map_s {
    draw_textbox_t *draw;
    str_edit_map_t str;
    sfVector2f **map;
    sfVector2i size;
    sfVector2f pos;
    float rotate;
    float zoom;
    float coef;
    sfBool update;
    sfConvexShape *shape;
} edit_map_t;

void edit_info_events(system_t *sys, edit_info_t *edit_info);
void edit_map_events(system_t *sys, edit_map_t *edit_map);

void free_2d_map(sfVector2i size, sfVector2f **map);
sfVector2f **create_2d_map(edit_map_t *edit);

#endif /* !EDITOR_H_ */
