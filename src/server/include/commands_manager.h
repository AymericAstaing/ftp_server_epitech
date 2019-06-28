/*
** EPITECH PROJECT, 2018
** commands manager header
** File description:
** pre-work to dispatch commmands before execution
*/

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_

#include "server.h"

void bind_sequence(struct server* s, char *sequence);
void execution(struct server* s, char* sequence, int code);

#endif