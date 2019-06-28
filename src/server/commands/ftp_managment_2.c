/*
** EPITECH PROJECT, 2018
** ftp command library: FTP SERVER MANAGMENT
** File description:
** function to execute for FTP PROTOCOL
*/

#include <string.h>
#include <stdio.h>
#include "../include/client_manager.h"
#include "../../../sockets/include/sockets_com.h"
#include "../include/server.h"

//CDUP <CRLF>                   : Change working directory to parent directory

void reset_directory(struct server* s, char* sequence)
{
    (void)sequence;
    s->clients[s->last_client_id].working_dir =
    strcpy(s->clients[s->last_client_id].working_dir, s->user_home_path);
    write_message(s->clients[s->last_client_id].control_fd,
    get_server_reply(REP250), strlen(get_server_reply(REP250)));
}