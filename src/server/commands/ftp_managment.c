/*
** EPITECH PROJECT, 2018
** ftp command library: FTP SERVER MANAGMENT
** File description:
** function to execute for FTP PROTOCOL
*/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../../../sockets/include/sockets_com.h"
#include "../include/server.h"
#include "../include/client_manager.h"

/*
HELP [<SP> <string>] <CRLF>   : List available commands
CWD  <SP> <pathname> <CRLF>   : Change working directory
CDUP <CRLF>                   : Change working directory to parent directory
DELE <SP> <pathname> <CRLF>   : Delete file on the server
PWD  <CRLF>                   : Print working directory*/

void close_session(struct server* s, char* sequence)
{
    (void)sequence;
    char *seq_info = get_server_reply(REP221);
    write_message(s->clients[s->last_client_id].control_fd,
    seq_info, strlen(seq_info));
    destroy_client(s, s->last_client_id);
}

void delete_file(struct server* s, char* sequence)
{
    char *file_name = sequence_message_extractor(sequence);
    char *no_file = get_server_reply(REP550);
    char *success = get_server_reply(REP250);
    int file_to_remove = 0;
    file_to_remove = open(file_name, O_RDONLY);
    if (file_to_remove < 0) {
        write_message(s->clients[s->last_client_id].control_fd,
        no_file, strlen(no_file));
        return;
    }
    file_to_remove = remove(file_name);
    if (file_to_remove != 0) {
        write_message(s->clients[s->last_client_id].control_fd,
        no_file, strlen(no_file));
        return;
    }
    write_message(s->clients[s->last_client_id].control_fd,
    success, strlen(no_file));
}

void print_help(struct server* s, char* sequence)
{
    (void)sequence;
    char *help = get_server_reply(REP214);
    write_message(s->clients[s->last_client_id].control_fd,
    help, strlen(help));
}

void change_working_directory(struct server* s, char* sequence)
{
    (void)sequence;
    int fd = 0;

    char *dir = malloc(sizeof(char) * (strlen(s->clients[s->last_client_id].working_dir)
    + strlen(sequence_message_extractor(sequence)) + 3));
    dir = strcpy(dir, s->clients[s->last_client_id].working_dir);
    dir = strcat(dir, sequence_message_extractor(sequence));
    if ((fd = open(dir, O_RDONLY)) < 0) {
            write_message(s->clients[s->last_client_id].control_fd,
            get_server_reply(REP550), strlen(get_server_reply(REP550)));
            return;
    }
    close(fd);
    s->clients[s->last_client_id].working_dir = 
    strcpy(s->clients[s->last_client_id].working_dir, dir);
    write_message(s->clients[s->last_client_id].control_fd,
    get_server_reply(REP250), strlen(get_server_reply(REP250)));
}

void print_working_directory(struct server* s, char* sequence)
{
    (void)sequence;
    int out_size = (strlen(s->clients
    [s->last_client_id].working_dir) + 20);
    char *output = malloc(sizeof(char) * out_size);
    strcpy(output, "257 \"");
    strcat(output, s->clients[s->last_client_id].working_dir);
    strcat(output, "\"\r\n");
    write_message(s->clients[s->last_client_id].control_fd,
    output, strlen(output));
}