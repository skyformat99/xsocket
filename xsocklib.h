#ifndef X_SOCK_H
#define X_SOCK_H

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define MAXLINE 4096
#define SERV_PORT 8787
#define LISTENQ 10

ssize_t xreadn(int fd, void *buff, size_t nbytes);
ssize_t xwriten(int fd, const void *buff, size_t nbytes);
ssize_t xreadline(int fd, void *buff, size_t maclen);


// wrapper socket method
//

int xsocket(int family, int type, int protocol);
int xconnect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
int xbind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
int xlisten(int sockfd, int backlog);
int xaccept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
pid_t xfork(void);
int xclose(int sockfd);

#endif
