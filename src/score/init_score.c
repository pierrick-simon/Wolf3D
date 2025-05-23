/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_score
*/

#include "score.h"
#include <stdlib.h>

void *init_score(void)
{
    score_t *score = malloc(sizeof(score_t));

    if (score == NULL)
        return NULL;
    score->str = SCORE_SUB;
    score->current_score = NULL;
    score->list = NULL;
    score->nb_page = 0;
    score->update = sfFalse;
    score->sort = sfTrue;
    score->draw = init_from_conf(str_conf[CONF_SCORE]);
    if (score->draw == NULL)
        return NULL;
    return (void *)score;
}
