/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    for (; str[len] != '\0'; len++);
    return len;
}
