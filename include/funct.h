/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** funct
*/

#include "struct.h"

#ifndef FUNCT_H_
    #define FUNCT_H_

char *concat3(const char *s1, const char *s2, const char *s3);
char *int_to_str(unsigned const int nb);
void handle_click(sfRenderWindow *window, game_t *game, car_t **car);
void start_click(sfRenderWindow *window, game_t *game, car_t **car);
void events(sfRenderWindow *window, game_t *game, car_t **car);
void is_boost(car_t *c);
void wait_time(car_t *c);
void update_ball_animation(ball_t *ball);
void update_boost_animation(boost_t *boost);
void update_cars(game_t *game, sfTime elapsed, car_t **car);
void update_highscore(game_t *game);
void change_car(int car_nb, car_t **car, game_t *game);
void init_game(game_t *game);
void init_cars(car_t **car);
void display(sfRenderWindow *window, game_t *game, car_t **car);
void display_start(sfRenderWindow *window, game_t *game);
void cleanup_game(game_t *game, car_t **car);
void game_loop(sfRenderWindow *window, game_t *game, car_t **car);
sfSprite *create_sprite(char *filepath, sfIntRect *area, float sx, float sy);
void handle_death(sfRenderWindow *window, game_t *game, car_t **car);
int my_strlen(char const *str);
int my_hunter(void);
void display_helper(void);
void update_demo(game_t *game);

#endif /* !FUNCT_H_ */
