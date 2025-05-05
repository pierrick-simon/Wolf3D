/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** sort_score
*/

#include "score.h"
#include <stdlib.h>

bool sort_score(void *data1, void *data2)
{
    if (atoi(((score_info_t *)data1)->score) >
        atoi(((score_info_t *)data2)->score))
        return true;
    return false;
}
