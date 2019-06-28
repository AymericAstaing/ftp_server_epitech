/*
** EPITECH PROJECT, 2018
** commands manager
** File description:
** pre-work to dispatch commmands before execution
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/utils.h"
#include "include/commands_manager.h"
#include "../../sockets/include/sockets_com.h"

const command_exec_t commands_exec[] =
{
    {REPUSER, check_username},
    {REPPASS, check_password},
    {REPCWD, change_working_directory},
    {REPCDUP, reset_directory},
    {REPQUIT, close_session},
    {REPQUIT2, close_session},
    {REPDELE, delete_file},
    {REPPWD, print_working_directory},
    {REPPASV, enable_passive_mode},
    {REPPORT, check_username},
    {REPHELP, print_help},
    {REPNOOP, noop},
    {REPRETR, download_file},
    {REPSTOR, noop},
    {REPLIST, noop}
};

void syntax_error(struct server* s, char* sequence)
{
    (void)sequence;
    char *bad_syntax = get_server_reply(REP500);
    write_message(s->clients[s->last_client_id].control_fd,
    bad_syntax, strlen(bad_syntax));
}

int authorized_execution(struct server*s, int code)
{
    char *need_connection = get_server_reply(REP530);

    if ((s->clients[s->last_client_id].authentication == NOT_AUTHENTICATED ||
    s->clients[s->last_client_id].authentication == PASS_REQUIRED) &&
    code > 1 && code != REPQUIT && code != REPQUIT2) {
        write_message(s->clients[s->last_client_id].control_fd,
        need_connection, strlen(need_connection));
        return(1);
    }
    if (s->clients[s->last_client_id].authentication == AUTHENTICATED &&
    code <= 1) {
        write_message(s->clients[s->last_client_id].control_fd,
        get_server_reply(REP530), strlen(get_server_reply(REP530)));
        return (1);
    }
    return (0);
}

void execution(struct server* s, char* sequence, int code)
{
    commands_exec[code].command(s, sequence);
}

void bind_sequence(struct server* s, char *sequence)
{
    char *need_connection = get_server_reply(REP530);
    for (int i = 0; i < NBR_OF_INTERACTIONS; i++) {
        if ((strstr(sequence, get_client_reply(i))) != NULL) {
            if (authorized_execution(s, i) == 0)
                execution(s, sequence, i);
            return;
        }
    }
    if (s->clients[s->last_client_id].authentication == AUTHENTICATED) {
        syntax_error(s, sequence);
    } else {
        write_message(s->clients[s->last_client_id].control_fd,
        need_connection, strlen(need_connection));
    }

}