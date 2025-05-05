/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_score
*/

#include "score.h"
#include "linked_list.h"
#include <stdlib.h>

void destroy_score(void *structure)
{
    score_t *score = (score_t *)structure;

    if (score->draw != NULL)
        free_draw_textbox(score->draw, -1);
    if (score->list != NULL)
        free_linked_list(score->list, &free_info_score);
    free(score);
}
