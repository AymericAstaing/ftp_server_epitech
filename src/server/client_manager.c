/*
** EPITECH PROJECT, 2018
** client connection
** File description:
** functions to manage client
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "include/client_manager.h"
#include "../../sockets/include/sockets_com.h"

void store_new_client(struct server *s)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (s->clients[i].connected == 0) {
            s->clients[i].control_fd = s->listener_socket_fd;
            s->clients[i].connected = 1;
            s->clients[i].transfer_type = NONE;
            s->clients[i].username = NULL;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
}

void destroy_client(struct server *s, int client_index)
{
    print_connection_message(s, DISCONNECT_MESSAGE);
    close(s->clients[client_index].control_fd);
    s->clients[client_index].data_fd = 0;
    s->clients[client_index].connected = 0;
    s->clients[client_index].control_fd = 0;
    s->clients[client_index].transfer_type = NONE;
    s->clients[client_index].transfer_type = NONE;
}