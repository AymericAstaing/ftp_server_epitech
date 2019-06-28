/*
** EPITECH PROJECT, 2018
** ftp command library: DATA TRANSFER
** File description:
** function to execute for FTP PROTOCOL
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../../sockets/include/sockets_basic.h"
#include "../../../sockets/include/sockets_com.h"
#include "../include/server.h"
#include "../include/utils.h"
#include "../include/server.h"

/*
RETR <SP> <pathname> <CRLF>   : Download file from server to client
STOR <SP> <pathname> <CRLF>   : Upload file from client to server
LIST [<SP> <pathname>] <CRLF> : List files in the current working directory*/

void download_file(struct server* s, char *sequence)
{
    int fd = 0;
    int data_connection = 0;
    int write_data = 0;
    int file_data = -1;
    int buff_size = 1000;
    char buf[buff_size];
    char *transfer_success = NULL;

    if (s->clients[s->last_client_id].transfer_type != PASSIV_TRANSFER) {
        return;
    }
    transfer_success = get_server_reply(REP226);
    if ((fd = open(sequence_message_extractor(sequence), O_RDONLY)) < 0) {
            close(fd);
            return;
    }
    data_connection = accept_connection(s->clients[s->last_client_id].data_fd,
        s->address, s->addr_size);
    if (data_connection < 0)
        return;
    while (1) {
        file_data = read(fd, buf, buff_size);
        if (file_data == 0)
            break;
        for (int i = 0; i < file_data; i += write_data)
            write_data = write(data_connection, buf + i, file_data - i);
    }
    close(fd);
    destroy_data_connection(s);
    write_message(s->clients[s->last_client_id].control_fd,
        transfer_success, strlen(transfer_success));
}