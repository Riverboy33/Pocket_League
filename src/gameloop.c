/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** gameloop
*/

#include "funct.h"

void game_loop(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfClock *clock = sfClock_create();
    sfTime dt;

    while (sfRenderWindow_isOpen(window)) {
        dt = sfClock_restart(clock);
        events(window, game, car);
        if (game->life <= 0) {
            handle_death(window, game, car);
        }
        if (game->is_play) {
            update_cars(game, dt, car);
            update_highscore(game);
            update_demo(game);
            display(window, game, car);
        }
        if (!game->is_play){
            display_start(window, game);
        }
    }
    sfClock_destroy(clock);
}
