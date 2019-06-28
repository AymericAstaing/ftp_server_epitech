/*
** EPITECH PROJECT, 2018
** ftp command library: CONNECTION
** File description:
** function to execute for FTP PROTOCOL
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../sockets/include/sockets_com.h"
#include "../include/server.h"
#include "../include/utils.h"

/*
USER <SP> <username> <CRLF>   : Specify user for authentication
PASS <SP> <password> <CRLF>   : Specify password for authentication
QUIT <CRLF>                   : Disconnection
NOOP <CRLF>                   : Do nothing*/

int is_allowed_user(struct server* s, char *username)
{
    (void)s;
    if (strcmp(username, "Anonymous") == 0)
        return (0);
    return (1);
}

void check_username(struct server* s, char *sequence)
{
    char *message = sequence_message_extractor(sequence);

    s->clients[s->last_client_id].username = NULL;
    s->clients[s->last_client_id].username = malloc(sizeof(char) * strlen(message));
    s->clients[s->last_client_id].username = message;
    write_message(s->socket_in_treatment_fd, get_server_reply(REP331),
    strlen(get_server_reply(REP331)));
    s->clients[s->last_client_id].authentication = PASS_REQUIRED;
}

void check_password(struct server* s, char *sequence)
{
    char *message = sequence_message_extractor(sequence);

    if (s->clients[s->last_client_id].authentication == PASS_REQUIRED &&
    is_allowed_user(s, s->clients[s->last_client_id].username) == 0 &&
    strcmp(message, "") == 0) {
        write_message(s->socket_in_treatment_fd, get_server_reply(REP230),
        strlen(get_server_reply(REP230)));
        s->clients[s->last_client_id].authentication = AUTHENTICATED;
    } else if (s->clients[s->last_client_id].authentication == NOT_AUTHENTICATED) {
        write_message(s->socket_in_treatment_fd, get_server_reply(REP503),
        strlen(get_server_reply(REP503)));
    } else {
        write_message(s->socket_in_treatment_fd, get_server_reply(REP530),
        strlen(get_server_reply(REP530)));
    }
}

void noop(struct server* s, char *sequence)
{
    (void)sequence;
    write_message(s->clients[0].control_fd, get_server_reply(REP200),
        strlen(get_server_reply(REP200)));
}
