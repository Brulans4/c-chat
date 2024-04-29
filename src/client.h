#ifndef _CLIENT_H_
#define _CLIENT_H_

/**
 * @brief Parent process logic for sending messages.
 * @param sockfd The socket file descriptor.
 */
void parentProcess(int sockfd);

/**
 * @brief Child process logic for receiving messages.
 * @param sockfd The socket file descriptor.
 */
void childProcess(int sockfd);

#endif // _CLIENT_H_