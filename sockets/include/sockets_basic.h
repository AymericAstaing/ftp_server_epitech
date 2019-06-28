/*
** EPITECH PROJECT, 2018
** socket basic header
** File description:
** basic command for socket managment
*/

#ifndef     SOCKETS_BASIC_H_
#define     SOCKETS_BASIC_H_

#include <arpa/inet.h>
#include <sys/types.h>

int     create_socket();
int     close_socket(int socket);
int     create_listener_socket(int socket_fd);
void    bind_socket(int socket_fd, struct sockaddr_in addr);
int     accept_connection(int initial_socket, struct sockaddr_in adrr, socklen_t addr_size);

#endif