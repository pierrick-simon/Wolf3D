/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** open a file
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char *open_file(const char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat info;
    int check = 0;
    char *buffer = NULL;

    check = stat(file, &info);
    if (fd == -1 || check == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (info.st_size + 1));
    if (buffer == NULL)
        return NULL;
    check = read(fd, buffer, info.st_size);
    close(fd);
    if (check == -1)
        return NULL;
    buffer[info.st_size] = '\0';
    return buffer;
}

char **get_tab(char const *file)
{
    char *fd = open_file(file);
    char **tab = NULL;

    if (fd == NULL)
        return NULL;
    tab = my_str_to_word_array(fd, "\n", "");
    free(fd);
    return tab;
}
