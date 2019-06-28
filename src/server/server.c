/*
** EPITECH PROJECT, 2018
** server core
** File description:
** core of server, basic server instruction
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "include/server.h"
#include "include/client_manager.h"
#include "include/queue.h"
#include "include/events.h"
#include "include/utils.h"
#include "../../sockets/include/sockets_com.h"
#include "../../sockets/include/sockets_basic.h"

#define DEFAULT_PORT            21
#define SERVER_IS_RUNNING       1

void start_listening(struct server *s)
{
    bind_socket(s->master_socket_fd, s->address);
    printf("Listen for connexion on port %d...\n", s->server_port);
    create_listener_socket(s->master_socket_fd);
}

void check_for_new_client(struct server *s)
{
    if (is_new_connection(s)) {
        s->listener_socket_fd = accept_connection(s->master_socket_fd,
        s->address, s->addr_size);
        if (s->listener_socket_fd < 0)
            printf("Connection error with client...");
        print_connection_message(s, CONNECT_MESSAGE);
        write_message(s->listener_socket_fd, get_server_reply(REP220),
        strlen(get_server_reply(REP220)));
        store_new_client(s);
    }
}

void destroy(struct server* s)
{
    free(s);
}

int start_server(struct server* s) {
    while (SERVER_IS_RUNNING) {
        FD_ZERO(&s->readfds);
        FD_SET(s->master_socket_fd, &s->readfds);
        manage_queue(s);
        s->select_event_fd = select(s->last_connected_socket_fd + 1,
        &s->readfds, &s->writefds, NULL , NULL);
        if (s->select_event_fd < 0)
            printf("Select error...");
        check_for_new_client(s);
        check_for_socket_event(s);
    }
    close_socket(s->master_socket_fd);
    close_socket(s->listener_socket_fd);
    return (0);
}