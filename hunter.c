/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** main
*/

// RECORD:
// Gregoire: 358 (avec revive: 561)
// Adan: 196 (avec revive: 543)
// Alexandre: 92

#include "funct.h"

static void alloc_game(game_t *game)
{
    game->btn = malloc(sizeof(btn_t));
    game->btn_1 = malloc(sizeof(btn_t));
    game->btn_2 = malloc(sizeof(btn_t));
    game->car = malloc(sizeof(car_sprite_t));
    game->demo = malloc(sizeof(sound_t));
    game->save = malloc(sizeof(sound_t));
    game->crosshair = malloc(sizeof(crosshair_t));
    game->chat = malloc(sizeof(chat_t));
    game->chat->msg = malloc(sizeof(sound_t));
    game->explo = malloc(sizeof(explo_t));
}

static void alloc_cars(car_t **car)
{
    for (int i = 0; i < NB_CAR; i++) {
        car[i] = malloc(sizeof(car_t));
        car[i]->ball = malloc(sizeof(ball_t));
        car[i]->boost = malloc(sizeof(boost_t));
    }
}

int my_hunter(void)
{
    sfVideoMode mode = {1920, 1080};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Pocket League",
        sfDefaultStyle | sfResize | sfClose, NULL);
    game_t *game = malloc(sizeof(game_t));
    car_t **car = NULL;

    srand(time(NULL));
    if (!game || !window)
        return EXIT_ERROR;
    car = malloc(sizeof(car_t *) * NB_CAR);
    if (!car)
        return EXIT_ERROR;
    alloc_game(game);
    alloc_cars(car);
    init_game(game);
    init_cars(car);
    game_loop(window, game, car);
    cleanup_game(game, car);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
