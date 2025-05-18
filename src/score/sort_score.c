/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** sort_score
*/

#include "score.h"
#include <stdlib.h>

bool sort_by_time(void *data1, void *data2)
{
    int first = ((score_info_t *)data1)->time_sec;
    int second = ((score_info_t *)data2)->time_sec;

    if (first < second)
        return true;
    if (first > second)
        return false;
    if (atoi(((score_info_t *)data1)->score) >
        atoi(((score_info_t *)data2)->score))
        return true;
    return false;
}

bool sort_by_score(void *data1, void *data2)
{
    int first = atoi(((score_info_t *)data1)->score);
    int second = atoi(((score_info_t *)data2)->score);

    if (first > second)
        return true;
    if (first < second)
        return false;
    if (((score_info_t *)data1)->time_sec <
        ((score_info_t *)data2)->time_sec)
        return true;
    return false;
}
