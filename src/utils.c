#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>

#include "utils.h"

#define BUF_LEN 256


void *smalloc(size_t size)
{
  void *res = malloc(size);
  checkCond(size != 0 && res == NULL, "ERROR MALLOC");
  return res;
}

void checkCond(bool cond, char *msg)
{
  if (cond)
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
}

void checkNeg(int res, char *msg)
{
  checkCond(res < 0, msg);
}

void checkNull(void *res, char *msg)
{
  checkCond(res == NULL, msg);
}

int sclose(int fd)
{
  int resv = close(fd);
  checkNeg(resv, "Error CLOSE");
  return resv;
}

ssize_t sread(int fd, void *buf, size_t count)
{
  ssize_t r = read(fd, buf, count);
  checkNeg(r, "Error READ");
  return r;
}

ssize_t swrite(int fd, const void *buf, size_t count)
{
  ssize_t r = write(fd, buf, count);
  checkNeg(r, "Error WRITE");
  return r;
}

pid_t sfork()
{
  int childId = fork();
  checkCond(childId == -1, "Fork failed");
  return childId;
}

pid_t fork_and_run0(void (*run)(void))
{
  int childId = fork();
  checkNeg(childId, "Fork failded");

  if (childId == 0)
  {
    (*run)();
    exit(EXIT_SUCCESS);
  }

  return childId;
}

int ssocket()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  checkNeg(sockfd, "socket client creation error");
  return sockfd;
}

int sconnect(char *serverIP, int serverPort, int sockfd)
{
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr)); /* en System V */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(serverPort);
  inet_aton(serverIP, &addr.sin_addr);
  int ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  checkNeg(ret, "connect client error");
  return ret;
}

int sbind(int port, int sockfd)
{
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  checkNeg(ret, "server bind error");
  return ret;
}

int slisten(int sockfd, int backlog)
{
  int ret = listen(sockfd, backlog);
  checkNeg(ret, "listen error error");
  return ret;
}

int saccept(int sockfd)
{
  int newsockfd = accept(sockfd, NULL, NULL);
  checkNeg(newsockfd, "accept failure");

  return newsockfd;
}

int spoll(struct pollfd *fds, nfds_t nfds, int timeout)
{
  int ret = poll(fds, nfds, timeout);
  checkNeg(ret, "poll failure");

  return ret;
}
