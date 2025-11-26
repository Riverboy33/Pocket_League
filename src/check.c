/*
** EPITECH PROJECT, 2025
** Pocket_League
** File description:
** check_sprite
*/

#include "struct.h"

void check_sprite(sfSprite *sprite)
{
    if (!sprite) {
        exit(84);
    }
}

void check_font(sfFont *font)
{
    if (!font) {
        exit(84);
    }
}

void check_music(sfMusic *music)
{
    if (!music) {
        exit(84);
    }
}

void check_sound_buff(sfSoundBuffer *buff)
{
    if (!buff) {
        exit(84);
    }
}
