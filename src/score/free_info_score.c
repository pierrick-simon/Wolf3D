/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** free_info_score
*/

#include "score.h"
#include <stdlib.h>

void free_info_score(void *data)
{
    score_info_t *score = (score_info_t *)data;

    free(score->name);
    free(score->time);
    free(score->score);
}
