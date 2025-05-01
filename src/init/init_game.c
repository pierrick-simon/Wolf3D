/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"
#include <stdlib.h>
#include <string.h>
#include "my.h"

static int init_crossair(crossair_t *crossair)
{
    crossair->circle = sfCircleShape_create();
    if (crossair->circle == NULL)
        return ERROR;
    sfCircleShape_setFillColor(crossair->circle, sfTransparent);
    sfCircleShape_setRadius(crossair->circle, 40.0);
    sfCircleShape_setOutlineThickness(crossair->circle, 3.0);
    sfCircleShape_setRadius(crossair->circle, CROSSAIR_RADIUS);
    sfCircleShape_setPosition(crossair->circle, (sfVector2f){(WIN_WIDTH / 2) -
        CROSSAIR_RADIUS, (WIN_HEIGHT / 2) - CROSSAIR_RADIUS});
    crossair->state.transform = sfTransform_Identity;
    crossair->state.blendMode = (sfBlendMode) {
        .colorSrcFactor = sfBlendFactorOneMinusDstColor,
        .colorDstFactor = sfBlendFactorOneMinusSrcColor,
        .colorEquation = sfBlendEquationAdd,
        .alphaSrcFactor = sfBlendFactorOne,
        .alphaDstFactor = sfBlendFactorZero,
        .alphaEquation = sfBlendEquationAdd
    };
    return SUCCESS;
}

int init_weapon(char *info, weapon_info_t *weapon)
{
    char **tab = my_str_to_word_array(info, ":", "");

    weapon->texture = NULL;
    weapon->sound = NULL;
    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != 5) {
        free_array(tab);
        return ERROR;
    }
    weapon->texture = sfTexture_createFromFile(tab[0], NULL);
    weapon->sound = sfMusic_createFromFile(tab[1]);
    weapon->size = (sfVector2f){atoi(tab[2]), atoi(tab[3])};
    weapon->nb_tile = atoi(tab[4]);
    weapon->size.x /= weapon->nb_tile;
    weapon->rectangle = (sfIntRect){0, 0, weapon->size.x, weapon->size.y};
    weapon->current_tile = 0;
    weapon->posf = (sfVector2f){WIN_WIDTH / 2, TOOLBAR_POS};
    return SUCCESS;
}

int get_weapon_info(weapon_info_t *info)
{
    char **tab = get_tab("config_file/weapon.conf");
    int return_value = SUCCESS;

    if (tab == NULL)
        return ERROR;
    for (int i = 0; i < NB_WEAPON; i++) {
        if (init_weapon(tab[i], &info[i]) == ERROR)
            return_value = ERROR;
    }
    free_array(tab);
    return return_value;
}

static int init_weapons(weapon_t *weapon)
{
    *weapon = (weapon_t){NULL};
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->weapon = 0;
    weapon->sprite = sfSprite_create();
    weapon->info = malloc(sizeof(weapon_info_t) * NB_WEAPON);
    if (weapon->sprite == NULL || weapon->info == NULL
        || get_weapon_info(weapon->info) == ERROR)
        return ERROR;
    sfSprite_setOrigin(weapon->sprite,
        (sfVector2f){weapon->info[0].size.x / 2, weapon->info[0].size.y});
    sfSprite_setTexture(weapon->sprite, weapon->info[0].texture, sfTrue);
    sfSprite_setTextureRect(weapon->sprite, weapon->info[0].rectangle);
    sfSprite_setScale(weapon->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(weapon->sprite, weapon->info[0].posf);
    return SUCCESS;
}

static int init_state(map_t *map)
{
    map->wall_state.texture =
        sfTexture_createFromFile("asset/wall.png", NULL);
    if (map->wall_state.texture == NULL)
        return ERROR;
    map->wall_state.transform = sfTransform_Identity;
    map->wall_state.blendMode = sfBlendAlpha;
    return SUCCESS;
}

static int init_map(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    *map = (map_t){NULL};
    map->ceiling_floor = sfRectangleShape_create();
    if (map->ceiling_floor == NULL)
        return ERROR;
    sfRectangleShape_setSize(map->ceiling_floor, pos);
    map->quads = sfVertexArray_create();
    if (map->quads == NULL || init_state(map) == ERROR)
        return ERROR;
    sfVertexArray_setPrimitiveType(map->quads, sfQuads);
    return SUCCESS;
}

static int init_player(player_t *player)
{
    player->angle = 0;
    player->pos.x = -1;
    player->pos.y = -1;
    player->type = NONE;
    player->v.x = 0;
    player->v.y = 0;
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    player->crossair = malloc(sizeof(crossair_t));
    if (player->crossair == NULL || init_crossair(player->crossair) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int init_time_info(time_info_t *time_info)
{
    time_info->clock = sfClock_create();
    if (time_info->clock == NULL)
        return ERROR;
    time_info->time = 0;
    time_info->prev_time = 0;
    time_info->delta = 0.0;
    return SUCCESS;
}

void *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return NULL;
    *game = (game_t){NULL};
    game->map = malloc(sizeof(map_t));
    game->player = malloc(sizeof(player_t));
    game->weapon = malloc(sizeof(weapon_t));
    game->time_info = malloc(sizeof(time_info_t));
    if (game->map == NULL || init_map(game->map) == ERROR
        || game->player == NULL || game->weapon == NULL
        || init_weapons(game->weapon) == ERROR
        || init_player(game->player) == ERROR
        || init_time_info(game->time_info) == ERROR) {
        destroy_game(game);
        return NULL;
    }
    game->player->save = NULL;
    return (void *)game;
}
