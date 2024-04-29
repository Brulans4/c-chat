#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <stdbool.h>

#include "server.h"
#include "utils.h"
#include "config.h"

int main()
{
  int sockfd = initServer(PORT, USERS);

  struct pollfd *fds = initPollfd(sockfd, USERS);

  runServer(sockfd, fds, USERS);
}

int initServer(int port, int maxSize)
{
  int sockfd = ssocket();

  sbind(port, sockfd);
  slisten(sockfd, maxSize);

  return sockfd;
}

struct pollfd *initPollfd(int sockfd, int maxSize)
{
  struct pollfd *fds = smalloc(sizeof(struct pollfd) * maxSize);

  for (int i = 0; i < maxSize; i++)
  {
    fds[i].fd = saccept(sockfd);
    fds[i].events = POLLIN;
    fds[i].revents = 0;

    printf("Client %d connected\n", i + 1);
  }
  return fds;
}

void runServer(int sockfd, struct pollfd *fds, int maxSize)
{
  while (true)
  {
    spoll(fds, maxSize, -1);
    char *buffer = smalloc(sizeof(char) * MAX_LINE_LENGTH);

    for (int i = 0; i < maxSize; i++)
    {
      if (fds[i].revents & POLLIN)
      {
        int sizeRead = sread(fds[i].fd, buffer, sizeof(buffer));
        if (sizeRead == 0)
        {
          sclose(sockfd);

          free(buffer);
          free(fds);

          exit(EXIT_SUCCESS);
        }
        for (int j = 0; j < sizeRead; j++)
        {
          if (buffer[j] == '\n')
          {
            buffer[j] = '\0';
          }
        }

        for (int j = 0; j < maxSize; j++)
        {
          if (i != j)
          {
            swrite(fds[j].fd, buffer, sizeof(buffer));
          }
        }
      }
    }
    free(buffer);
  }
}