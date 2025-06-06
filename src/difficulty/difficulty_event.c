/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "game_menu.h"
#include "save.h"

static void change_difficulty(system_t *sys, str_difficulty_t difficulty)
{
    if (difficulty == DIFF_BACK)
        return;
    sys->save->info->difficulty = START_DIFFICULTY;
    for (str_difficulty_t i = DIFF_ONE; i < difficulty; i++)
        sys->save->info->difficulty += DIFFICULTY_GAP;
}

static void switch_scene(sfEvent event, system_t *sys,
    difficulty_t *difficulty, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        difficulty->draw[difficulty->str].color = sfWhite;
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            difficulty->str = DIFF_BACK;
        change_difficulty(sys, difficulty->str);
        state->old_scene = state->scene;
        state->scene = difficulty->draw[difficulty->str].scene;
        difficulty->draw[difficulty->str].color = sfWhite;
        difficulty->str = DIFF_THREE;
    }
}

static void switch_str(sfEvent event, difficulty_t *difficulty)
{
    difficulty->draw[difficulty->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        difficulty->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        difficulty->str++;
    if (difficulty->str == NB_DIFFICULTY)
        difficulty->str = DIFF_ONE;
    if (difficulty->str == DIFF_TITLE)
        difficulty->str = DIFF_BACK;
    difficulty->draw[difficulty->str].color = sfRed;
}

void difficulty_events(system_t *sys, difficulty_t *difficulty)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, difficulty);
        switch_scene(event, sys, difficulty, sys->state);
    }
}
