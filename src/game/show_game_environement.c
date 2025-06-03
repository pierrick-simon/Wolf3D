/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_game_environement.c
*/

#include "game.h"
#include <math.h>

static void smooth_night_day(sfUint64 time, light_t *light)
{
    int sec = time / (SEC_IN_MICRO / NIGHT_NB) % (MIN_IN_SEC * NIGHT_NB);
    int tmp = sec - SMOOTH_OVERLAY;

    if (sec > light->sec || (sec == 0 && light->sec != 1))
        light->sec = sec;
    if (light->sec == 0) {
        if (light->night_on == sfFalse)
            light->night_on = sfTrue;
        else
            light->night_on = sfFalse;
        light->sec = 1;
    }
    if (tmp <= 0)
        return;
    if (light->night_on == sfFalse)
        sfRectangleShape_setFillColor(light->overlay,
            sfColor_fromRGBA(0, 0, 0, tmp * OVERLAY_STEP));
    else
        sfRectangleShape_setFillColor(light->overlay,
            sfColor_fromRGBA(0, 0, 0, OVERLAY_MAX - (tmp * OVERLAY_STEP)));
}

static void draw_coor(system_t *sys, game_t *game)
{
    sfVector2f pos = {0, (WIN_HEIGHT / 2) + game->player->cam_angle};

    sfRectangleShape_setSize(game->map->ceiling_floor,
        (sfVector2f){WIN_WIDTH, (WIN_HEIGHT / 2) - game->player->cam_angle});
    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, FLOOR_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
    pos = (sfVector2f){0, 0};
    if (game->player->cam_angle != 0)
        sfRectangleShape_setSize(game->map->ceiling_floor, (sfVector2f)
        {WIN_WIDTH, (WIN_HEIGHT / 2) + game->player->cam_angle});
    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, CEILING_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
}

static void draw_overlay(system_t *sys, game_t *game)
{
    sfRectangleShape_setSize(game->map->ceiling_floor,
        (sfVector2f){WIN_WIDTH, WIN_HEIGHT});
    if (game->time_info->shot > 0) {
        sfRectangleShape_setFillColor(game->map->ceiling_floor, SHOT_OVERLAY);
        sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
        game->time_info->shot -= game->time_info->delta;
    }
    if (game->time_info->weapon > 0) {
        sfRectangleShape_setFillColor(game->map->ceiling_floor, WEPON_OVERLAY);
        sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
        game->time_info->weapon -= game->time_info->delta;
    }
    if (game->time_info->item > 0) {
        sfRectangleShape_setFillColor(game->map->ceiling_floor, ITEM_OVERLAY);
        sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
        game->time_info->item -= game->time_info->delta;
    }
}

static void draw_point_bar(system_t *sys, toolbar_t *tool, int ind, float nb)
{
    sfVector2f pos = (sfVector2f){tool->draw[ind].pos.x + tool->draw[ind].size
        + OFFSET_POINT_BAR, TOOLBAR_POS + OFFSET_POINT_BAR};
    int size = OFFSET_POINT_BAR * 2;
    double fill = nb * (TOOLBAR_HEIGHT - size) / MAX_JOYSTICK;

    sfRectangleShape_setPosition(tool->rectangle, pos);
    sfRectangleShape_setSize(tool->rectangle,
        (sfVector2f){OFFSET_POINT_BAR, TOOLBAR_HEIGHT - size});
    sfRectangleShape_setOutlineColor(tool->rectangle, sfWhite);
    sfRectangleShape_setFillColor(tool->rectangle, sfTransparent);
    sfRenderWindow_drawRectangleShape(sys->window,
        tool->rectangle, NULL);
    sfRectangleShape_setPosition(tool->rectangle,
        (sfVector2f){pos.x, pos.y + TOOLBAR_HEIGHT - size - fill});
    sfRectangleShape_setSize(tool->rectangle,
        (sfVector2f){OFFSET_POINT_BAR, fill});
    sfRectangleShape_setFillColor(tool->rectangle, tool->draw[ind].color);
    sfRenderWindow_drawRectangleShape(sys->window,
        tool->rectangle, NULL);
}

static void draw_tool_strings(system_t *sys, toolbar_t *tool)
{
    for (int i = 0; i < NB_TOOLBAR; i++) {
        if ((tool->fps == sfFalse && i == TOOL_FPS)
            || (tool->saving == sfFalse && i == TOOL_SAVE)
            || (tool->interact == sfFalse && i == TOOL_INTERACT)
            || i == TOOL_FLASH_NB || i == TOOL_BOSS)
            continue;
        draw_string(sys, sys->textbox, &tool->draw[i]);
    }
    draw_point_bar(sys, tool, TOOL_FLASH_NB,
        sys->save->info->item_info[INFO_FLASHLIGHT]);
    draw_point_bar(sys, tool, TOOL_HEALTH_NB,
        sys->save->info->item_info[INFO_HEALTH]);
    draw_point_bar(sys, tool, TOOL_STAM_NB,
        sys->save->info->item_info[INFO_STAMINA]);
}

static void draw_toolbar(system_t *sys, toolbar_t *tool)
{
    sfVector2f pos = (sfVector2f){0, TOOLBAR_POS};

    sfRectangleShape_setPosition(tool->rectangle, pos);
    sfRectangleShape_setSize(tool->rectangle,
        (sfVector2f){WIN_WIDTH, TOOLBAR_HEIGHT});
    sfRectangleShape_setFillColor(tool->rectangle, GREY);
    sfRectangleShape_setTexture(tool->rectangle, tool->background, sfTrue);
    sfRectangleShape_setOutlineColor(tool->rectangle, sfTransparent);
    sfRenderWindow_drawRectangleShape(sys->window,
        tool->rectangle, NULL);
    sfRectangleShape_setTexture(tool->rectangle, NULL, sfTrue);
    sfRenderWindow_drawSprite(sys->window, tool->head->sprite, NULL);
    sfRenderWindow_drawSprite(sys->window, tool->flashlight->sprite, NULL);
    draw_tool_strings(sys, tool);
}

static void draw_lines(system_t *sys, game_t *game)
{
    map_t *map = game->map;

    for (int i = 0; i < NB_RAYS; ++i) {
        for (int j = 0; j < RAY_LENGTH; ++j) {
            sfVertexArray_append(map->line, map->rays[i].down);
            sfVertexArray_append(map->line, map->rays[i].up);
            ++map->rays[i].down.position.x;
            ++map->rays[i].up.position.x;
        }
    }
    sfRenderWindow_drawVertexArray(sys->window,
        map->line, &map->wall_states);
    sfVertexArray_clear(map->line);
    draw_entities(game, sys);
}

static void flash_light(system_t *sys, light_t *light, game_t *game)
{
    weapon_t *weapon = game->weapon;

    smooth_night_day(sys->save->info->time, light);
    sfRenderTexture_clear(light->night_render, sfTransparent);
    sfRenderTexture_drawRectangleShape(
        light->night_render, light->overlay, NULL);
    if (light->flash_on == sfTrue) {
        sfCircleShape_setPosition(light->flashlight, (sfVector2f)
                {(WIN_WIDTH / 2) + (cos((double)(game->time_info->time /
                (SEC_IN_MICRO / MOV_OFFSET_GUN))) * MOV_OFFSET_GUN) +
                MOV_OFFSET_GUN, (WIN_HEIGHT / 2) + game->player->cam_angle / 10
                + weapon->horizontal_offset});
        sfRenderTexture_drawCircleShape(light->night_render,
            light->flashlight, &light->state);
    }
    sfRenderTexture_display(light->night_render);
    sfRenderWindow_drawSprite(sys->window, light->night, NULL);
}

static void draw_head_shot(system_t *sys, player_t *player)
{
    sfConvexShape_setPoint(player->headshot, 0, (sfVector2f){(WIN_WIDTH / 2) -
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) - CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 1, (sfVector2f){(WIN_WIDTH / 2) -
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) - CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 2, (sfVector2f){(WIN_WIDTH / 2) +
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) + CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 3, (sfVector2f){(WIN_WIDTH / 2) +
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) + CROSS_HEAD_SIZE});
    sfRenderWindow_drawConvexShape(sys->window,
        player->headshot, NULL);
    sfConvexShape_setPoint(player->headshot, 0, (sfVector2f){(WIN_WIDTH / 2) +
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) - CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 1, (sfVector2f){(WIN_WIDTH / 2) +
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) - CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 2, (sfVector2f){(WIN_WIDTH / 2) -
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) + CROSS_HEAD_SIZE});
    sfConvexShape_setPoint(player->headshot, 3, (sfVector2f){(WIN_WIDTH / 2) -
        CROSS_HEAD_SIZE, (WIN_HEIGHT / 2) + CROSS_HEAD_SIZE});
    sfRenderWindow_drawConvexShape(sys->window,
        player->headshot, NULL);
}

void show_game_environement(system_t *sys, game_t *game)
{
    draw_coor(sys, game);
    draw_lines(sys, game);
    sfRenderWindow_drawSprite(sys->window,
        game->weapon->sprite, NULL);
    sfRenderWindow_drawCircleShape(sys->window,
        game->player->crossair, NULL);
    if (game->map->is_weakness && game->map->entity_center !=
        NO_ENTITIE && game->weapon->weapon != PUNCH)
        draw_head_shot(sys, game->player);
    flash_light(sys, game->light, game);
    draw_boss_health(sys, sys->save->boss,
        game->tool->rectangle, game->tool->draw);
    draw_toolbar(sys, game->tool);
    draw_minimap(sys, game->mini_map, game->cursor, game->tool->border);
    draw_overlay(sys, game);
}
