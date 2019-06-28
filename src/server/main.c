/*
** EPITECH PROJECT, 2018
** main bttf
** File description:
** core of program
*/

#include <stdlib.h>
#include <stdio.h>
#include "include/server.h"
#include "include/utils.h"

#define DEFAULT_PORT    8080

int get_port(int argc, char **argv)
{
    if (argc < 1)
        return (DEFAULT_PORT);
    return (atoi(argv[1]));
}

int error_managment(int argc, char **argv)
{
    if (argc < 2) {
        printf("Please, provide port (ex: 4242) and user \
        home path (ex:/home/). Cant start FTP SERVER...\n");
        return (0);
    }
    if (argc == 2) {
            printf("Please, provide home path (ex:/home/).\n");
        return (0);
    }
    if (argc > 3) {
        printf("Too much arguments provided...\n");
        return (0);
    }
    if (!is_port(argv[1])) {
        printf("Please provide valid port!\n");
        return (0);
    }
    return (1);
}

int main(int argc, char **argv) {
    struct server *s;

    if (!error_managment(argc, argv))
        return (84);
    s = get_initialised_server(get_port(argc, argv), argv[2]);
    start_listening(s);
    start_server(s);
    free(s);
}