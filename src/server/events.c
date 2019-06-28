/*
** EPITECH PROJECT, 2018
** event manager
** File description:
** set of function to detect new events from client
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/events.h"
#include "include/client_manager.h"
#include "include/commands_manager.h"
#include "../../sockets/include/sockets_basic.h"
#include "../../sockets/include/sockets_com.h"

int new_event_detected(struct server *s)
{
    if (FD_ISSET(s->socket_in_treatment_fd, &s->readfds))
        return (1);
    return (0);
}

void sequence_received(struct server *s, char buffer[1000], int socket_from)
{
    buffer[socket_from] = '\0';
    if (strcmp(buffer, "quit") == 0)
        exit(84);
    bind_sequence(s, buffer);
}

void check_for_socket_event(struct server *s)
{
    char buffer[1000];
    int received_fd = 0;

    for (int i = 0; i < MAX_CLIENT; i++) {
        if (s->clients[i].connected == 0)
            continue;
        s->socket_in_treatment_fd = s->clients[i].control_fd;
        if (!new_event_detected(s))
            continue;
        received_fd = read(s->socket_in_treatment_fd, buffer, 1000);
        if (received_fd == 0) {
            destroy_client(s, i);
            continue;
        }
        s->last_client_id = i;
        sequence_received(s, buffer, received_fd);
    }
}
