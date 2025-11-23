/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** cleanup
*/

#include "struct.h"

static void free_btn(game_t *game)
{
    if (game->btn && game->btn->sprite)
        sfSprite_destroy(game->btn->sprite);
    if (game->btn)
        free(game->btn);
    if (game->btn_1 && game->btn_1->sprite)
        sfSprite_destroy(game->btn_1->sprite);
    if (game->btn_1)
        free(game->btn_1);
    if (game->btn_2 && game->btn_2->sprite)
        sfSprite_destroy(game->btn_2->sprite);
    if (game->btn_2)
        free(game->btn_2);
}

static void free_game(game_t *game)
{
    if (game->background)
        sfSprite_destroy(game->background);
    if (game->start)
        sfSprite_destroy(game->start);
    free_btn(game);
    if (game->font)
        sfFont_destroy(game->font);
    if (game->text)
        sfText_destroy(game->text);
    if (game->crosshair)
        sfSprite_destroy(game->crosshair->sprite);
    if (game->explo) {
        sfSprite_destroy(game->explo->sprite);
        sfClock_destroy(game->explo->clock);
    }
}

void cleanup_game(game_t *game, car_t **car)
{
    if (!game)
        return;
    free_game(game);
    free(game);
}

void cleanup_car(car_t **car)
{
    for (int i = 0; i < NB_CAR; i++) {
        if (car[i]->sprite)
            sfSprite_destroy(car[i]->sprite);
        if (car[i]->ball->anim_clock)
            sfClock_destroy(car[i]->ball->anim_clock);
        free(car[i]);
    }
    free(car);
}
