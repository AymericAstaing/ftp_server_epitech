/*
** EPITECH PROJECT, 2018
** queue
** File description:
** find the latest emmited signal and set as priority
*/

#include "include/queue.h"

void manage_queue(struct server* s)
{
    s->last_connected_socket_fd = s->master_socket_fd;
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (s->clients[i].connected == 0)
            continue;
        s->socket_in_treatment_fd = s->clients[i].control_fd;
        if (s->socket_in_treatment_fd > 0)
            FD_SET(s->socket_in_treatment_fd, &s->readfds);
        if (s->socket_in_treatment_fd > s->last_connected_socket_fd)
            s->last_connected_socket_fd = s->socket_in_treatment_fd;
    }
}