/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** proba
*/

#include "struct.h"

void is_boost(car_t *c)
{
    int boost = rand() % 6 + 1;

    if (boost == 1) {
        c->boost->is_visibe = true;
        c->speed = 2 * SPEED;
    }
}

void wait_time(car_t *c)
{
    int nb = rand() % 3 + 1;

    if (nb == 1) {
        c->sleep = rand() % 2 + 0.5;
        sfClock_restart(c->sleep_clock);
        c->is_visible = false;
    }
}
