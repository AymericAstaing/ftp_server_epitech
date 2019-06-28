/*
** EPITECH PROJECT, 2018
** files transfer: FTP FILE MANAGER
** File description:
** functions to upload/down in passive/active mode (bttf)
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/server.h"
#include "../../sockets/include/sockets_basic.h"
#include "../../sockets/include/sockets_com.h"

int write_char_by_char(struct server* s, int fd)
{
    (void)s;
    (void)fd;
    return (0);
}