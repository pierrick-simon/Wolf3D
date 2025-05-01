/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "create.h"
#include <string.h>

static void switch_scene(
    sfEvent event, state_info_t *state, create_t *create)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0) &&
        create->str == BACK) {
        state->old_scene = state->scene;
        state->scene = create->draw[BACK].scene;
    }
}

static void switch_str(sfEvent event, create_t *create)
{
    create->draw[create->str].color = sfBlack;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100)
        create->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100)
        create->str++;
    if (create->str == NB_CREATE)
        create->str = 0;
    if (create->str == -1)
        create->str = NB_CREATE - 1;
    create->draw[create->str].color = sfRed;
}

static void nb_textbox(sfEvent event, char *str, int len_str)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyNum0 && event.key.code <= sfKeyNum9
            && len < len_str)
            str[len] = event.key.code + '0' - sfKeyNum0;
        if (event.key.code == FOUR && len < len_str)
            str[len] = '4';
        if (event.key.code == SIX && len < len_str)
            str[len] = '6';
    }
}

static void text_textbox(sfEvent event, char *str)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyA && event.key.code <= sfKeyZ
            && len < MAX_NAME) {
            str[len] = event.key.code + 'a' - sfKeyA;
            str[len + 1] = '\0';
        }
    }
}

void create_events(system_t *sys, create_t *create)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, create);
        switch_scene(event, sys->state, create);
        if (create->str >= NB_TEXTBOX)
            break;
        if (create->str == NAME)
            text_textbox(event, create->strings[create->str]);
        else
            nb_textbox(event, create->strings[create->str],
                create->len_strings[create->str]);
    }
}
