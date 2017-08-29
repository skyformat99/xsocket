
#include "xsocklib.h"
#include "xerror.h"

#define SERV_PORT 8899
#define LISTENQ 10
#define MAXLINE 4096

void str_echo(int sockfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = xsocket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    xbind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    xlisten(listenfd, LISTENQ);

    for (; ;) {
        clilen = sizeof(cliaddr);
        connfd = xaccept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        if ((childpid = xfork()) == 0) {
            xclose(listenfd);
            str_echo(connfd);
            exit(0);
        }

        xclose(connfd);
    }
}

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];
again:
    while ((n = read(sockfd, buf, MAXLINE)) > 0) {
        xwriten(sockfd, buf, n);
    }

    if (n < 0 && errno == EINTR) {
        goto again;
    }
    else if (n < 0) {
        xerr_sys("str_echo: read error");
    }
}


