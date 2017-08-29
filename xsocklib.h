#ifndef X_SOCK_H
#define X_SOCK_H

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>

extern ssize_t xreadn(int fd, void *buff, size_t nbytes);
extern ssize_t xwriten(int fd, const void *buff, size_t nbytes);
extern ssize_t xreadline(int fd, void *buff, size_t maclen);


// wrapper socket method
//

extern int xsocket(int family, int type, int protocol);
extern int xconnect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
extern int xbind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
extern int xlisten(int sockfd, int backlog);
extern int xaccept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
extern pid_t xfork(void);
extern int xclose(int sockfd);

#endif
