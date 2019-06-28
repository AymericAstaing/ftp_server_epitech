/*
** EPITECH PROJECT, 2018
** ftp command library: TRANSFER STATE
** File description:
** function to execute for FTP PROTOCOL
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../../sockets/include/sockets_basic.h"
#include "../../../sockets/include/sockets_com.h"
#include "../include/server.h"
#include "../include/utils.h"

/*
PASV <CRLF>                   : Enable "passive" mode for data transfer
PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer*/

void enable_passive_mode(struct server* s, char *sequence)
{
    (void)sequence;
    srand(time(0));
    int p1 = get_random_number(255);
    int p2 = get_random_number(255);
    int port = p1 * 256 + p2;

    s->clients[s->last_client_id].data_fd = create_socket();
    s->clients[s->last_client_id].address.sin_family = AF_INET;
    s->clients[s->last_client_id].address.sin_addr.s_addr = INADDR_ANY;
    s->clients[s->last_client_id].address.sin_port = htons(port);
    s->clients[s->last_client_id].transfer_type = PASSIV_TRANSFER;
    bind_socket(s->clients[s->last_client_id].data_fd,
    s->clients[s->last_client_id].address);
    if ((listen(s->clients[s->last_client_id].data_fd, 1)) == 0) {
        char * seq_info = get_pasv_message(s, p1, p2);
        write_message(s->clients[s->last_client_id].control_fd,
        seq_info, strlen(seq_info));
    }
}