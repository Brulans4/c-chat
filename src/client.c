#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <poll.h>
#include <stdbool.h>

#include "client.h"
#include "utils.h"
#include "config.h" 

/**
 * @brief Entry point of the C Chat program.
 */
int main()
{
    printf("Welcome to C Chat\n");

    int sockfd = ssocket();
    sconnect(IP, PORT, sockfd);
    printf("You are now connected\n");
    int pid = sfork();
    if (pid == 0)
    {
        childProcess(sockfd);
    }
    else
    {
        parentProcess(sockfd);
    }
    sclose(sockfd);

    exit(EXIT_SUCCESS);
}

void parentProcess(int sockfd)
{
    while (true)
    {
        char *buffer = smalloc(sizeof(char) * MAX_LINE_LENGTH);

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
        char *buffer = smalloc(sizeof(char) * MAX_LINE_LENGTH);

        int readsize = sread(sockfd, buffer, sizeof(buffer));
        if (readsize == 0)
        {
            exit(EXIT_FAILURE);
        }
        printf("Your friend has send \"%s\" \n", buffer);

        free(buffer);
    }
}