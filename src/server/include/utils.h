/*
** EPITECH PROJECT, 2018
** utils header
** File description:
** set of small and useful functions;
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include "server.h"

int         is_port(char *str);
char*       sequence_message_extractor(char* sequence);
char*       get_pasv_message(struct server* s, int p1, int p2);
int         get_random_number(int max);
struct sockaddr_in  get_adress(int port);

#endif