/*
** EPITECH PROJECT, 2018
** socket basic
** File description:
** basic command for socket managment
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "include/sockets_basic.h"

int close_socket(int socket)
{
    if (close(socket) == -1) {
        printf("Cant close sockets...\n");
        return (84);
    }
    return (0);
}

int create_socket()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        printf("Socket has not been initialised...\n");
        exit (84);
    }
    return (socket_fd);
}

int create_listener_socket(int socket_fd)
{
    int listener_socket = listen(socket_fd, 15);

    if (listener_socket < 0) {
        printf("Error: unable to listen\n");
        close(socket_fd);
        return (84);
    }
    return (listener_socket);
}

int accept_connection(int initial_socket, struct sockaddr_in adrr,
socklen_t addr_size)
{
    int listener_socket_fd = accept(initial_socket,
    (struct sockaddr*) &adrr, (socklen_t*)&addr_size);

    if (listener_socket_fd < 0) {
        perror("Error: unable to accept. Error\n");
        close(initial_socket);
        return (84);
    }
    return (listener_socket_fd);
}

void bind_socket(int socket_fd, struct sockaddr_in addr)
{
    if (bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("Bind failed. Error");
        close(socket_fd);
        exit(84);
    }
}