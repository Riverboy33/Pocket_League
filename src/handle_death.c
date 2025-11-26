/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** handle_death
*/

#include "struct.h"

void handle_death(sfRenderWindow *window, game_t *game, car_t **car)
{
    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);
    float bgW = sizeTex.x * scale.x;

    game->life = 3;
    game->score = 0;
    game->is_play = false;
    for (int i = 0; i < NB_CAR; i++)
        car[i]->pos = (sfVector2f){bgW * 0.2f, rand() % 700 + 100};
    sfMusic_stop(game->music);
}
