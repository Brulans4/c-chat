#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <stdbool.h>

#include "properties.h"
#include "client.h"
#include "utils.h"

int main()
{
    printf("Welcome to C Chat\n");

    int sockfd = ssocket();
    sconnect(LOCAL_HOST, PORT, sockfd);
    printf("You are now connected\n");

    int pid = sfork();
    if (pid == 0)
    {
        parentProcess(sockfd);
    }
    else
    {
        childProcess(sockfd);
    }
    exit(EXIT_SUCCESS);
}

void parentProcess(int sockfd)
{
    while (true)
    {
        char *buffer = smalloc(sizeof(char) * 255);

        int readsize = sread(0, buffer, sizeof(buffer));
        if (readsize == 0)
        {
            exit(EXIT_FAILURE);
        }
        swrite(sockfd, buffer, readsize);

        free(buffer);
    }
}

void childProcess(int sockfd)
{
    while (true)
    {
        char *buffer = smalloc(sizeof(char) * 255);

        int readsize = sread(sockfd, buffer, sizeof(buffer));
        if (readsize == 0)
        {
            exit(EXIT_FAILURE);
        }
        printf("Your friend has send \"%s\" \n", buffer);

        free(buffer);
    }
}