/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** init_frame.c
*/

#include "wolfengine.h"

frame_t *init_frame(frame_t *frame)
{
    frame->current_frame = 0;
    frame->prev_frame = 0;    
    return frame;
}
