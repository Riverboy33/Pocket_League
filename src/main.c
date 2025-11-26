/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** main
*/

#include "funct.h"

int main(int argc, char **argv)
{
    if (argc == 1)
        return my_hunter();
    if (argc == 2 && my_strlen(argv[1]) == 2 &&
        argv[1][0] == '-' && argv[1][1] == 'h')
        display_helper();
    return EXIT_SUCCESS;
}
