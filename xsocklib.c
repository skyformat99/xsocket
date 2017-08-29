#include "xsocklib.h"

ssize_t xreadn(int fd, void *buff, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = buff;
    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) {
                nread = 0;
            }
            else {
                return -1;
            }
        }

        nleft -= nread;
        ptr += nread;
    }

    return n - nleft;
}

ssize_t xwriten(int fd, const void *buff, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = buff;
    nleft = n;

    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR) {
                nwritten = 0;
            }
            else {
                return -1;
            }
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}

ssize_t xreadline(int fd, void *buff, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = buff;
    for (n = 1; n < maxlen; n++) {
again:
        if ((rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n') {
                break;
            }
        } 
        else if (rc == 0) {
            *ptr = 0;
            return n - 1;
        }
        else {
            if (errno == EINTR) {
                goto again;
            }

            return -1;
        }
    }

    *ptr = 0;
    return n;
}


int xsocket(int family, int type, int protocol)
{
    int sockfd;
    if ((sockfd = socket(family, type, protocol) < 0)) {
        xerr_sys("socker error");
        return -1;
    }

    return sockfd;
}

int xconnect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
    if (connect(sockfd, servaddr, addrlen) < 0) {
        xerr_ret("connect error");
        return -1;
    }
    return 0;
}

int xbind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
    int ret;
    if ((ret = bind(sockfd, myaddr, addrlen)) == -1) {
        xerr_sys("bind error");
        return -1;
    }

    return 0;
}

int xlisten(int sockfd, int backlog)
{
    char *ptr;
    if ((ptr = getenv("LISTENQ")) != NULL) {
        backlog = atoi(ptr);
    }

    if (listen(sockfd, backlog) < 0) {
        xerr_sys("listen error");
        return -1;
    }

    return 0;
}

int xaccept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{

    int connfd;
    if ((connfd = accept(sockfd, cliaddr, addrlen)) < 0) {
        xerr_sys("accept error");
        return -1;
    }

    return connfd;
}


pid_t xfork(void)
{
    int pid;
    if ((pid = fork()) < 0) {
        xerr_quit("fork error");
        return -1;
    }

    return pid;
}


int xclose(int sockfd)
{
    if (close(sockfd) < 0) {
        xerr_sys("close error");
        return -1;
    }

    return 0;
}
