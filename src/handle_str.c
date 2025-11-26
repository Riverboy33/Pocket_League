/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** handle_str
*/

#include "funct.h"
#include <stddef.h>

static void loop_1(const char *s1, size_t len1, char *res, size_t *i)
{
    for (size_t j = 0; j < len1; j++) {
        res[*i] = s1[j];
        (*i)++;
    }
}

static void loop_2(const char *s2, size_t len2, char *res, size_t *i)
{
    for (size_t j = 0; j < len2; j++) {
        res[*i] = s2[j];
        (*i)++;
    }
}

static void loop_3(const char *s3, size_t len3, char *res, size_t *i)
{
    for (size_t j = 0; j < len3; j++) {
        res[*i] = s3[j];
        (*i)++;
    }
}

static char *get_res(const char *s1, const char *s2, const char *s3, char *res)
{
    size_t len1 = 0;
    size_t len2 = 0;
    size_t len3 = 0;
    size_t i = 0;

    len1 = my_strlen(s1);
    len2 = my_strlen(s2);
    len3 = my_strlen(s3);
    res = malloc(len1 + len2 + len3 + 1);
    if (!res)
        return NULL;
    loop_1(s1, len1, res, &i);
    loop_2(s2, len2, res, &i);
    loop_3(s3, len3, res, &i);
    res[i] = '\0';
    return res;
}

char *concat3(const char *s1, const char *s2, const char *s3)
{
    char *res = NULL;

    if (!s1 || !s2 || !s3)
        return NULL;
    res = get_res(s1, s2, s3, res);
    return res;
}

char *int_to_str(unsigned const int nb)
{
    unsigned int n = nb;
    int len = 1;
    char *str = NULL;

    while (n >= 10) {
        n /= 10;
        len++;
    }
    str = malloc(len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    n = nb;
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (n % 10) + '0';
        n /= 10;
    }
    return str;
}
