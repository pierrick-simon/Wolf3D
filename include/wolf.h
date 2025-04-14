/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** header
*/

#ifndef HEADER_H_
    #define HEADER_H_

    #define EXIT_S 0
    #define EXIT_F 84

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

    #define VOL_MAX 100.0
    #define VOL_MIN 0.0
    #define VOL_GAP 5.0

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define WIN_BITS 64
    #define WIN_FRAME 60
    #define WIN_NAME "Wolf3D"

    #define SEC_IN_MICRO 1000000

    #define SHOTGUN_FRAME 0.05
    #define SHOTGUN_NB_TILE 5
    #define SHOTGUN_SPRITE_X 320
    #define SHOTGUN_SPRITE_Y 180

typedef struct game {
    sfRenderWindow *window;
    sfClock *clock;
    sfMusic *music;
} game_t;

typedef struct sprite {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f posf;
    sfVector2f scale;
    sfIntRect rectangle;
    int tile;
} sprite_t;

typedef struct {
    sprite_t sprite;
    sfTexture **texture;
    sfMusic **sound;
    sfInt64 shot;
    int weapon;
} weapon_t;

void init_game(game_t *game);
sfRenderWindow *create_window(void);
void init_weapon(weapon_t *weapon);
void events(game_t *game, weapon_t *weapon);
void move_rect(sprite_t *sprite, int offset, int max_value);
void game_loop(game_t *game, weapon_t *weapon);

#endif
