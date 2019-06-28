##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile for FTP project
##

ROOT		=		./

F_CLIENT	=		$(ROOT)src/client/

F_SERVER	=		$(ROOT)src/server/

F_COMMANDS	=		$(ROOT)src/server/commands/

F_SOCKET	=		$(ROOT)sockets/

NAME_SERVER	=		myftp

NAME_CLIENT =		client

SRC2		=		$(F_SERVER)server.c					\
					$(F_SERVER)client_manager.c			\
					$(F_SERVER)init.c					\
					$(F_SERVER)events.c					\
					$(F_SERVER)utils.c					\
					$(F_SERVER)queue.c					\
					$(F_SERVER)commands_manager.c		\
					$(F_SERVER)files_transfer.c		\
					$(F_SERVER)replies.c				\
					$(F_COMMANDS)ftp_connection.c		\
					$(F_COMMANDS)ftp_data_transfer.c	\
					$(F_COMMANDS)ftp_managment.c		\
					$(F_COMMANDS)ftp_managment_2.c		\
					$(F_COMMANDS)ftp_transfer_state.c	\
					$(F_SERVER)main.c

SRC_SOCKET	=		$(F_SOCKET)sockets_basic.c		\
					$(F_SOCKET)sockets_com.c

OBJ2		=		$(SRC2:.c=.o)

OBJ_SOCKET	=		$(SRC_SOCKET:.c=.o)

CC			=		gcc

CFLAGS		+=		-Wall -Werror -Wextra -pedantic

all:				$(NAME_SERVER)

$(NAME_SERVER):			$(OBJ2) $(OBJ_SOCKET)
				$(CC) -o $(NAME_SERVER) $(CFLAGS) $(OBJ2) $(OBJ_SOCKET) $(LDFLAGS)

debug:				fclean $(OBJ2) $(OBJ_SOCKET)
				$(CC) -o $(CFLAGS) -g3 $(OBJ_SOCKET) $(LDFLAGS)
				$(CC) -o $(CFLAGS) -g3 $(OBJ2) $(OBJ_SOCKET) $(LDFLAGS)

clean:
				rm -f $(OBJ2) $(OBJ_SOCKET)

fclean:					clean
				rm -f $(NAME_SERVER)

re:				fclean all

.PHONY:				all clean fclean re

