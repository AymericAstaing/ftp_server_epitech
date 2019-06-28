/*
** EPITECH PROJECT, 2018
** server core, storage
** File description:
** core of server, basic server instruction
*/


#ifndef SERVER_H_
#define SERVER_H_

#include <arpa/inet.h>

#define MAX_CLIENT              15
#define NBR_OF_INTERACTIONS     15


typedef enum {
        NONE,
        ACTIVE_TRANSFER,
        PASSIV_TRANSFER
} DataTransferType;


typedef enum {
        NOT_AUTHENTICATED,
        PASS_REQUIRED,
        AUTHENTICATED
} AuthenticationState;

typedef enum {
        REP120,
        REP125,
        REP150,
        REP200,
        REP214,
        REP220,
        REP221,
        REP226,
        REP227,
        REP230,
        REP250,
        REP257,
        REP331,
        REP332,
        REP430,
        REP500,
        REP503,
        REP530,
        REP550
} ServerReplies;

typedef enum {
        REPUSER,
        REPPASS,
        REPCWD,
        REPCDUP,
        REPQUIT,
        REPQUIT2,
        REPDELE,
        REPPWD,
        REPPASV,
        REPPORT,
        REPHELP,
        REPNOOP,
        REPRETR,
        REPSTOR,
        REPLIST
} ClientReplies;


struct server*      get_initialised_server(int port, char* home_path);
void                start_listening(struct server *s);
int                 start_server(struct server* s);
void                destroy(struct server* s);
void                check_for_new_client(struct server *s);
void                store_new_socket(struct server *s);
char*               get_server_reply(ServerReplies sr);
char*               get_client_reply(ClientReplies cr);


/****************** commands_ftp header zone ******************/

void                check_username(struct server* s, char *sequence);
void                check_password(struct server* s, char *sequence);
void                download_file(struct server* s, char *sequence);
void                enable_passive_mode(struct server* s, char *sequence);
void                list_available_commands(struct server* s, char *sequence);
void                close_session(struct server* s, char* sequence);
void                delete_file(struct server* s, char* sequence);
void                change_working_directory(struct server* s, char* sequence);
void                noop(struct server* s, char* sequence);
void                print_help(struct server* s, char* sequence);
void                reset_directory(struct server* s, char* sequence);
void                print_working_directory(struct server* s, char* sequence);

/****************** init server ******************/

struct server* get_initialised_server(int port, char* home_path);


/****************** file transfer header zone ******************/

int write_char_by_char(struct server* s, int fd);

struct server
{
    char*               user_home_path;
    int                 last_client_id;
    int                 server_port;
    int                 master_socket_fd;
    int                 socket_in_treatment_fd;
    int                 select_event_fd;
    int                 listener_socket_fd;
    int                 last_connected_socket_fd;
    fd_set              writefds;
    fd_set              readfds;
    struct sockaddr_in  address;
    socklen_t           addr_size;
    struct client       *clients;
};

struct client
{
    int                 connected;
    int                 control_fd;
    int                 data_fd;
    char*               working_dir;
    char*               username;
    struct sockaddr_in  address;
    AuthenticationState authentication;
    DataTransferType    transfer_type;
};

typedef struct server_replies
{
    ServerReplies       sr;
    char*               value;
} server_replies_t;

typedef struct client_replies
{
    ClientReplies       cr;
    char*               value;
} client_replies_t;

typedef struct command_exec
{
    ClientReplies       cr;
    void (*command)(struct server* s, char* sequence);
} command_exec_t;

#endif