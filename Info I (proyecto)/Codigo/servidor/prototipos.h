#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXDATASIZE 20
#define MYPORT 3493
#define BACKLOG 10

void sigchld_handler (int);
void seleccionar (int, FILE**);
void fscandir (char*);
