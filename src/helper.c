/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** helper
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void display_helper(void)
{
    int fd = open("helper.txt", O_RDONLY);
    char buffer[1024];
    int bytes;

    if (fd == -1)
        return;
    bytes = read(fd, buffer, sizeof(buffer));
    while ((bytes) > 0) {
        write(1, buffer, bytes);
        bytes = read(fd, buffer, sizeof(buffer));
    }
    close(fd);
}
