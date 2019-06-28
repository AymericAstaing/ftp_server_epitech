/*
** EPITECH PROJECT, 2018
** replies storage file
** File description:
** storage of server/client answers
*/

#include "include/server.h"

const server_replies_t ftp_replies[] = {
    {REP120, "120 Service ready in n minutes\r\n"},
    {REP125, "125 Data connection is open; transfer is starting...\r\n"},
    {REP150, "150 File status ok; about to open data connection.\r\n"},
    {REP200, "200 Command okay.\r\n"},
    {REP214, "214-The following commands are recognized.\n\
 ABOR ACCT ALLO APPE CDUP CWD  DELE EPRT EPSV FEAT HELP LIST MDTM MKD\n\
 MODE NLST NOOP OPTS PASS PASV PORT PWD  QUIT REIN REST RETR RMD  RNFR\n\
 RNTO SITE SIZE SMNT STAT STOR STOU STRU SYST TYPE USER XCUP XCWD XMKD\n\
 XPWD XRMD\n\
214 Help OK.\r\n"},
    {REP220, "220 Service ready for new user. Username: \r\n"},
    {REP221, "221 Service closing control connection, bye.\r\n"},
    {REP226, "226 Data successfuly transfered, closing data connection.\r\n"},
    {REP227, "227 Entering passive mode\r\n"},
    {REP230, "230 User logged in, proceed. \r\n"},
    {REP250, "250 Requested file action okay, completed.\r\n"},
    {REP257, "257 PATHNAME created"},
    {REP331, "331 User name okey, need password now: \r\n"},
    {REP332, "332 Need account for login\r\n"},
    {REP430, "430 Wrong username, retry.\r\n"},
    {REP500, "500 Bad syntax, unrecognized command ...\r\n"},
    {REP503, "503 Login with USER first.\r\n"},
    {REP530, "530 connection not established...\r\n"},
    {REP550, "550 Request not executed: Unavailable file...\r\n"}
};

const client_replies_t client_replies[] =
{
    {REPUSER, "USER"},
    {REPPASS, "PASS"},
    {REPCWD, "CWD"},
    {REPCDUP, "CDUP"},
    {REPQUIT, "QUIT"},
    {REPQUIT2, "quit"},
    {REPDELE, "DELE"},
    {REPPWD, "PWD"},
    {REPPASV, "PASV"},
    {REPPORT, "PORT"},
    {REPHELP, "HELP"},
    {REPNOOP, "NOOP"},
    {REPRETR, "RETR"},
    {REPSTOR, "STOR"},
    {REPLIST, "LIST"}
};

char *get_server_reply(ServerReplies sr)
{
    for (size_t i = 0; ftp_replies[i].value; ++i) {
        if (ftp_replies[i].sr == sr)
            return (ftp_replies[i].value);
    }
    return ("ERROR");
}

char *get_client_reply(ClientReplies cr)
{
    for (size_t i = 0; client_replies[i].value; ++i) {
        if (client_replies[i].cr == cr)
            return (client_replies[i].value);
    }
    return ("ERROR");
}