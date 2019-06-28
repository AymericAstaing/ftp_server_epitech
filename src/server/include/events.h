/*
** EPITECH PROJECT, 2018
** event manager header
** File description:
** set of function to detect new events from client
*/

#ifndef EVENTS_H_
#define EVENTS_H_

#include "server.h"

int     new_event_detected(struct server *s);
void    check_for_socket_event(struct server *s);
void    sequence_received(struct server *s, char buffer[1000],
int socket_from);

#endif