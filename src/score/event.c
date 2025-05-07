/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "score.h"
#include "linked_list.h"

static void switch_scene(
    sfEvent event, score_t *score, state_info_t *state)
{
    if ((is_input(event, sfKeyEnter, sfTrue, 0) && score->str == SCORE_BACK)
        || is_input(event, sfKeyEscape, sfFalse, 0)) {
        state->old_scene = state->scene;
        state->scene = score->draw[SCORE_BACK].scene;
        free_linked_list(score->list, &free_info_score);
        score->list = NULL;
        score->current_score = NULL;
        score->update = sfFalse;
        score->str = SCORE_SUB;
        score->draw[SCORE_BACK].color = sfWhite;
    }
}

static void switch_str(sfEvent event, score_t *score)
{
    score->draw[score->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK
        || is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK) {
        if (score->str == SCORE_SUB)
            score->str = SCORE_BACK;
        else
            score->str = SCORE_SUB;
    }
    score->draw[score->str].color = sfRed;
}

static void move_right(score_t *score)
{
    if (score->current < score->nb_page) {
        score->current++;
        for (int i = 0; i < NB_SHOW_SCORE; i++)
            score->current_score = score->current_score->next;
    }
}

static void move_left(score_t *score)
{
    if (score->current > 1) {
        score->current--;
        for (int i = 0; i < NB_SHOW_SCORE; i++)
            score->current_score = score->current_score->prev;
    }
}

static void change_page(sfEvent event, score_t *score)
{
    if (score->str == SCORE_SUB) {
        if (is_input(event, sfKeyRight, sfFalse, 0))
            move_right(score);
        if (is_input(event, sfKeyLeft, sfFalse, 0))
            move_left(score);
    }
}

void score_events(system_t *sys, score_t *score)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, score);
        switch_scene(event, score, sys->state);
        change_page(event, score);
    }
}
