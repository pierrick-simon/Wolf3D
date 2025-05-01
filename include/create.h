/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** create
*/

#ifndef CREATE_H_
    #define CREATE_H_

    #include "wolf.h"

    #ifndef MAX_STRLEN
        #define MAX_STRLEN 3
    #endif
    #ifndef MAX_STRLEN_POS
        #define MAX_STRLEN_POS 5
    #endif
    #ifndef MAX_NAME
        #define MAX_NAME 25
    #endif
    #define FOUR 51
    #define SIX 56

    #define NB_TEXTBOX 6

typedef enum {
    NAME,
    SIZE_X,
    SIZE_Y,
    POS_X,
    POS_Y,
    ANGLE,
    SAVE,
    BACK,
    NB_CREATE,
} str_create_t;

typedef struct create_s {
    int str;
    draw_textbox_t *draw;
    char **strings;
    int *len_strings;
    int **map;
    sfVector2f **height;
    sfVector2i prev_size;
} create_t;

void *init_create(void);
void draw_create(system_t *sys, void *structure);
void create_events(system_t *sys, create_t *create);
void destroy_create(void *structure);

#endif /* !CREATE_H_ */
