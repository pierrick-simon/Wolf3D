/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include <math.h>
#include "save.h"
#include "game.h"
#include "element.h"

static void draw_coor(system_t *sys, game_t *game)
{
    sfVector2f pos = {0, 0};

    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, CEILING_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
    pos = (sfVector2f){0, WIN_HEIGHT / 2};
    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, FLOOR_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
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
            || i == TOOL_FLASH_NB)
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

/*
static void draw_enemy(system_t *sys,
    enemy_t *enemy, game_t *game, ray_t rays[NB_RAYS])
{
    // player->angle = M_PI;
    // player->center_ray.v.x = cos(player->angle);
    // player->center_ray.v.y = sin(player->angle);
    player_t *player = game->player;
    //player->angle = M_PI;

    //position de l'enemie relatif au joueur
    double spriteX = enemy->pos.x - player->pos.x;
    double spriteY = enemy->pos.y - player->pos.x;

    double dirY = player->center_ray.v.x;
    double dirX = player->center_ray.v.y; // vecteur directeur

    double planeX = (-player->center_ray.v.y * (DEG(FOV) / 100)) +
        player->center_ray.v.x;
    double planeY = (player->center_ray.v.x * (DEG(FOV) / 100)) +
        player->center_ray.v.y;
    printf("%f %f\n", planeX, planeY); // vecteur joueur to end plane
    int h = WIN_HEIGHT;
    int w = WIN_WIDTH;


    double invDet = 1.0 / (planeX * dirY - dirX * planeY);

    double transformX = invDet * (dirY * spriteX - dirX * spriteY);
    double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

    // int spriteScreenX = w - (int)((w / 2) * (1 + transformX / transformY));
    //before
    int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

    int spriteHeight = abs((int)(h / (transformY)) * SOLDIER_Y);

    int drawStartY = -spriteHeight / 2 + h / 2;
    int drawEndY = spriteHeight / 2 + h / 2;

    int spriteWidth = abs((int)(h / (transformY)) * SOLDIER_X);
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    int drawEndX = spriteWidth / 2 + spriteScreenX;

    sfVertex tmp = {.color = sfWhite};
    for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
        if (transformY > 0 && stripe > 0 &&
            stripe < w /&& transformY < rays[stripe].len/) {
            float f = ((float)(stripe - drawStartX) /
                (float)(drawEndX - drawStartX)) * SOLDIER_X;
            tmp.position = (sfVector2f){stripe, drawStartY};
            tmp.texCoords = (sfVector2f){f, 0};
            sfVertexArray_append(game->map->line, tmp);
            tmp.position = (sfVector2f){stripe, drawEndY};
            tmp.texCoords = (sfVector2f){f, SOLDIER_Y};
            sfVertexArray_append(game->map->line, tmp);
        }
    }
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->line, &game->state_enemies[enemy->type]);
    sfVertexArray_clear(game->map->line);
}
*/
static void draw_lines(system_t *sys, game_t *game)
{
    map_t *map = game->map;
    node_t *node = game->player->save->enemies->tail;

    for (int i = 0; i < NB_RAYS; ++i) {
        for (int j = 0; j < RAY_LENGTH; ++j) {
            sfVertexArray_append(map->line, map->rays[i].down);
            sfVertexArray_append(map->line, map->rays[i].up);
            ++map->rays[i].down.position.x;
            ++map->rays[i].up.position.x;
        }
        sfRenderWindow_drawVertexArray(sys->window,
            map->line, &map->wall_states);
        sfVertexArray_clear(map->line);
    }
    while (node != NULL) {
        node = node->prev;
    }
}

static void smooth_night_day(system_t *sys, light_t *light)
{
    int sec = sys->save->info->time / (SEC_IN_MICRO / 2) % (MIN_IN_SEC * 2);
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

static void flash_light(system_t *sys, light_t *light)
{
    smooth_night_day(sys, light);
    sfRenderTexture_clear(light->night_render, sfTransparent);
    sfRenderTexture_drawRectangleShape(
        light->night_render, light->overlay, NULL);
    if (light->flash_on == sfTrue)
        sfRenderTexture_drawCircleShape(
            light->night_render, light->flashlight, &light->state);
    sfRenderTexture_display(light->night_render);
    sfRenderWindow_drawSprite(sys->window, light->night, NULL);
}

void draw_game(system_t *sys, void *structure)
{
    game_t *game = (game_t *)structure;

    update_all(sys, game);
    sfMusic_pause(sys->music);
    if (sfMusic_getStatus(sys->save->music) == sfStopped
        || sfMusic_getStatus(sys->save->music) == sfPaused)
        sfMusic_play(sys->save->music);
    game_events(sys, game);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_coor(sys, game);
    draw_lines(sys, game);
    sfRenderWindow_drawSprite(sys->window,
        game->weapon->sprite, NULL);
    sfRenderWindow_drawCircleShape(sys->window,
        game->player->crossair, NULL);
    flash_light(sys, game->light);
    draw_toolbar(sys, game->tool);
    draw_minimap(sys, game->mini_map, game->cursor, game->tool->background);
    sfRenderWindow_display(sys->window);
    update_time_end(game->time_info);
}
