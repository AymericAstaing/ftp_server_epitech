/*
** EPITECH PROJECT, 2018
** socket communication
** File description:
** basic function to manage socket communication
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "include/sockets_basic.h"
#include "include/sockets_com.h"

int is_new_connection(struct server *s)
{
    if (FD_ISSET(s->master_socket_fd, &s->readfds))
        return (1);
    return (0);
}

void print_connection_message(struct server* s, ConnectionMessage type)
{
    char ip[INET_ADDRSTRLEN] = {0};

    getpeername(s->listener_socket_fd, (struct sockaddr *)&s->address, &s->addr_size);
    inet_ntop(AF_INET, &(s->address.sin_addr), ip, INET_ADDRSTRLEN);
    switch ((int) type) {
        case DISCONNECT_MESSAGE:
            printf("Host disconnected with IP: %s and PORT: %d\n",
            ip, ntohs(s->address.sin_port));
            break;
        case CONNECT_MESSAGE:
            printf("Connection established with IP: %s and PORT: %d\n",
            ip, ntohs(s->address.sin_port));
            break;
        default:
            printf("Unknow event occurs.");
            break;
    }
}

int write_message(int socket_fd, char* message, int message_length)
{
    if ((write(socket_fd, message, message_length)) < 0) {
        printf("Write failed...\n");
        return (84);
    }
    return (0);
}

char* receive_message(int socket_fd)
{
    char buffer[1000000] = {0};
    char *message = malloc(sizeof(char) * 1000000);
    size_t size = 0;

    if (read(socket_fd, buffer, 1000000) < 0)
        return (NULL);
    size = sizeof(char) * (strlen(buffer) + 1);
    memcpy(message, buffer, size);
    return (message);
}

void destroy_data_connection(struct server* s)
{
    close_socket(s->clients[s->last_client_id].data_fd);
    s->clients[s->last_client_id].data_fd = 0;
    s->clients[s->last_client_id].transfer_type = NONE;
}