/*
** EPITECH PROJECT, 2018
** client connection header
** File description:
** functions to manage client
*/

#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include "server.h"

void store_new_client(struct server *s);
void destroy_client(struct server *s, int client_index);

#endif