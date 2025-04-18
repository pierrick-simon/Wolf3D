/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** menu_str
*/

#include "wolf.h"

const draw_textbox_t str_menu[] = {
    {"BOOM", (sfVector2f){WIN_WIDTH * 4 / 7, WIN_HEIGHT * 5 / 100},
        250, MENU},
    {"Play", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 2 / 5},
        100, GAME},
    {"Setting", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 3 / 5},
        100, MENU},
    {"Quit", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 4 / 5},
        100, QUIT},
};
