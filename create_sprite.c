/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** create_sprite
*/

#include "struct.h"

sfSprite *create_sprite(char *filepath, sfIntRect *area, float sx, float sy)
{
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfSprite *sprite = NULL;

    if (!texture )
        return NULL;
    sprite = sfSprite_create();
    if (!sprite )
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    if (area)
        sfSprite_setTextureRect(sprite, *area);
    sfSprite_setScale(sprite, (sfVector2f){sx, sy});
    return sprite;
}
