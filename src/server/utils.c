/*
** EPITECH PROJECT, 2018
** utils
** File description:
** set of small and useful functions;
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "include/utils.h"
#include "include/server.h"

int is_port(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 57 || str[i] < 48)
            return (0);
    }
    return (1);
}

char* sequence_message_extractor(char* sequence)
{
    int start = 0;
    int i = 0;
    char *message = malloc(sizeof(char) * 50);

    for (; sequence[start] != 32; start++);
    start++;
    for (; sequence[start] != 13 && sequence[start] != '\0'; i++, start++)
        message[i] = sequence[start];
    message[i] = '\0';
    message = (char *)realloc(message, i + 1);
    return (message);
}

int get_random_number(int max)
{
    return (rand() % max);
}

struct sockaddr_in  get_adress(int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return (address);
}

char* get_pasv_message(struct server* s, int p1, int p2)
{
    char *server_code = get_server_reply(REP227);
    char *server_ip = malloc(sizeof(char) * INET_ADDRSTRLEN);
    char *message = NULL;
    size_t needed = 0;

    getpeername(s->master_socket_fd, (struct sockaddr *)&s->address,
    &s->addr_size);
    inet_ntop(AF_INET, &(s->address.sin_addr), server_ip, INET_ADDRSTRLEN);
    for (int i = 0; server_ip[i] != '\0'; i++)
        if (server_ip[i] == 46)
            server_ip[i] = 44;
    needed = snprintf(NULL, 0,  "%s (%s,%d,%d)\r\n", server_code, server_ip,
    p1, p2) + 1;
    message = malloc(sizeof(char) * needed);
    snprintf(message, needed, "%s (%s,%d,%d)\r\n", server_code,
    server_ip, p1, p2);
    return (message);
}

