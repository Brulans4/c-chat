#include <unistd.h>
#include <poll.h>

#ifndef _SERVER_H_
#define _SERVER_H_

/**
 * Initializes the server.
 *
 * This function initializes the server and performs any necessary setup
 * before the server can start accepting client connections.
 *
 * @return An integer value indicating the success or failure of the server
 *         initialization. A return value of 0 indicates success, while a
 *         non-zero value indicates failure.
 */
int initServer();

/**
 * Initializes a pollfd structure for the given socket file descriptor.
 *
 * @param sockfd The socket file descriptor.
 * @return A pointer to the initialized pollfd structure.
 */
struct pollfd *initPollfd(int sockfd);

/**
 * Runs the server to handle incoming messages.
 *
 * @param sockfd The socket file descriptor for the server.
 * @param fds The array of pollfd structures for polling events.
 */
void runServer(int sockfd, struct pollfd *fds);

#endif // _SERVER_H_