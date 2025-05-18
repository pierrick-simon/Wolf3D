/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** score
*/

#ifndef SCORE_H_
    #define SCORE_H_

    #include "wolf.h"
    #include <stdbool.h>

    #define SCORE_LEN 12
    #define TIME_LEN 7
    #define NB_SHOW_SCORE 10
    #define SCORE_OFFSET 55

typedef struct linked_list_s linked_list_t;
typedef struct node_s node_t;

typedef enum {
    LOAD_S_NAME,
    LOAD_S_SCORE,
    LOAD_S_TIME,
    NB_S_LOAD,
} load_score_t;

typedef enum score_str_e {
    SCORE_TITLE,
    SCORE_SUB,
    SCORE_RANG,
    SCORE_NAME,
    SCORE_TIME,
    SCORE_SCORE,
    SCORE_BACK,
    NB_SCORE,
} score_str_t;

typedef struct score_info_s {
    char *name;
    char *time;
    char *score;
    int time_sec;
} score_info_t;

typedef struct score_s {
    int nb_page;
    int current;
    linked_list_t *list;
    node_t *current_score;
    sfBool update;
    int str;
    sfBool sort;
    draw_textbox_t *draw;
} score_t;

void free_info_score(void *data);
linked_list_t *get_score(char *name);
bool sort_by_score(void *data1, void *data2);
bool sort_by_time(void *data1, void *data2);

void *init_score(void);
void draw_score(system_t *sys, void *structure);
void score_events(system_t *sys, score_t *score);
void destroy_score(void *structure);

#endif /* !SCORE_H_ */
