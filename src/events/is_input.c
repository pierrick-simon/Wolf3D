/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** is_input.c
*/

#include "wolf.h"

sfBool is_input(sfEvent event, sfKeyCode key,
    sfBool is_joysick, unsigned int joytick_button)
{
    if (event.type == sfEvtKeyPressed && event.key.code == key)
        return sfTrue;
    if (is_joysick == sfTrue && event.type == sfEvtJoystickButtonPressed
        && event.joystickButton.button == joytick_button)
        return sfTrue;
    return sfFalse;
}
