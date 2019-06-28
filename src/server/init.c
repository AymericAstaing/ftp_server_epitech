/*
** EPITECH PROJECT, 2018
** server init
** File description:
** init
*/

#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include "include/server.h"
#include "include/client_manager.h"
#include "include/utils.h"
#include "../../sockets/include/sockets_basic.h"

struct server* get_initialised_server(int port, char* home_path)
{
    struct server *s = malloc(sizeof(struct server));

    s->user_home_path = home_path;
    s->master_socket_fd = create_socket();
    s->server_port = port;
    s->addr_size = sizeof(struct sockaddr);
    s->address = get_adress(port);
    s->clients = malloc(sizeof(struct client) * MAX_CLIENT);
    for (int i = 0; i < MAX_CLIENT; i++) { 
        s->clients[i].connected = 0;
        memset(&s->clients[i].address, 0, sizeof(struct sockaddr_in));
        s->clients[i].transfer_type = NONE;
        s->clients[i].authentication = NOT_AUTHENTICATED;
        s->clients[i].working_dir = malloc(sizeof(char) * 100);
        s->clients[i].working_dir = strcpy(s->clients[i].working_dir, home_path);
    }
    return (s);
}