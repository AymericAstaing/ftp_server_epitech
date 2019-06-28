/*
** EPITECH PROJECT, 2018
** socket communication header
** File description:
** basic function to manage socket communication
*/

#ifndef SOCKETSCOM_H_
#define SOCKETSCOM_H_

#include "../../src/server/include/server.h"

typedef enum {
    DISCONNECT_MESSAGE,
    CONNECT_MESSAGE
} ConnectionMessage;

int     is_new_connection(struct server *s);
char*   receive_message(int socket_fd);
int     write_message(int socket_fd, char* message, int message_length);
void    print_connection_message(struct server *s,
ConnectionMessage type);
void    destroy_data_connection(struct server* s);

#endif