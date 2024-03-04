#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <stdbool.h>

#include "properties.h"
#include "utils.h"

int main()
{
    int sockfd = ssocket();

    sbind(PORT, sockfd);
    slisten(sockfd, MAX_SIZE);

    struct pollfd *fds = smalloc(sizeof(struct pollfd) * MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        fds[i].fd = saccept(sockfd);
        fds[i].events = POLLIN;
        fds[i].revents = 0;
    }

    while (true)
    {
        spoll(fds, 2, -1);
        char *buffer = smalloc(sizeof(char) * 255);

        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                int sizeRead = sread(fds[i].fd, buffer, sizeof(buffer));
                if (sizeRead == 0)
                {
                    sclose(sockfd);
                    exit(EXIT_SUCCESS);
                }
                for (int j = 0; j < sizeRead; j++)
                {
                    if (buffer[j] == '\n')
                    {
                        buffer[j] = '\0';
                    }
                }

                for (int j = 0; j < MAX_SIZE; j++)
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