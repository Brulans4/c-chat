#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/ipc.h>
#include <poll.h>

/**
 * Allocates memory for the given size.
 * 
 * This function allocates memory for the given size and checks if the
 *    allocation was successful. If the allocation was not successful, the
 *   function will print an error message and exit the program.
 * 
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory.
*/
void *smalloc(size_t size);

/**
 * Checks the given condition.
 * 
 * This function checks the given condition and prints the given message if the
 *    condition is true. If the condition is true, the function will exit the
 *    program.
 * 
 * @param cond The condition to check.
 * @param msg The message to print if the condition is true.
*/
void checkCond(bool cond, char *msg);

/**
 * Checks if the given result is negative.
 * 
 * This function checks if the given result is negative and prints the given
 *    message if the result is negative. If the result is negative, the function
 *    will exit the program.
 * 
 * @param res The result to check.
 * @param msg The message to print if the result is negative.
*/
void checkNeg(int res, char *msg);

/**
 * Checks if the given result is null.
 * 
 * This function checks if the given result is null and prints the given message
 *    if the result is null. If the result is null, the function will exit the
 *    program.
 * 
 * @param res The result to check.
 * @param msg The message to print if the result is null.
*/
void checkNull(void *res, char *msg);

/**
 * Forks a new process.
 * 
 * This function forks a new process and checks if the fork was successful. If
 *    the fork was not successful, the function will print an error message and
 *    exit the program.
 * 
 * @return The process ID of the new process.
*/
pid_t sfork();

/**
 * Forks a new process and runs the given function.
 * 
 * This function forks a new process and runs the given function in the child
 *    process. The function will check if the fork was successful and print an
 *    error message if the fork was not successful.
 * 
 * @param run The function to run in the child process.
 * @return The process ID of the new process.
*/
int sclose(int fd);

/**
 * Reads from the given file descriptor.
 * 
 * This function reads from the given file descriptor and checks if the read was
 *    successful. If the read was not successful, the function will print an
 *    error message and exit the program.
 * 
 * @param fd The file descriptor to read from.
 * @param buf The buffer to read into.
 * @param count The number of bytes to read.
 * @return The number of bytes read.
*/
ssize_t sread(int fd, void *buf, size_t count);

/**
 * Writes to the given file descriptor.
 * 
 * This function writes to the given file descriptor and checks if the write was
 *    successful. If the write was not successful, the function will print an
 *    error message and exit the program.
 * 
 * @param fd The file descriptor to write to.
 * @param buf The buffer to write from.
 * @param count The number of bytes to write.
 * @return The number of bytes written.
*/
ssize_t swrite(int fd, const void *buf, size_t count);

/**
 * Forks a new process.
 * 
 * This function forks a new process and checks if the fork was successful. If
 *    the fork was not successful, the function will print an error message and
 *    exit the program.
 * 
 * @return The process ID of the new process.
*/
int ssocket();

/**
 * Connects to the given server.
 * 
 * This function connects to the given server and checks if the connection was
 *    successful. If the connection was not successful, the function will print
 *    an error message and exit the program.
 * 
 * @param serverIP The IP address of the server to connect to.
 * @param serverPort The port of the server to connect to.
 * @param sockfd The socket file descriptor.
 * @return An integer value indicating the success or failure of the connection.
*/
int sconnect(char *serverIP, int serverPort, int sockfd);

/**
 * Binds the given port to the given socket file descriptor.
 * 
 * This function binds the given port to the given socket file descriptor and
 *    checks if the binding was successful. If the binding was not successful,
 *    the function will print an error message and exit the program.
 * 
 * @param port The port to bind to the socket file descriptor.
 * @param sockfd The socket file descriptor.
 * @return An integer value indicating the success or failure of the binding.
*/
int sbind(int port, int sockfd);

/**
 * Listens for incoming connections on the given socket file descriptor.
 * 
 * This function listens for incoming connections on the given socket file
 *    descriptor and checks if the listening was successful. If the listening
 *    was not successful, the function will print an error message and exit the
 *    program.
 * 
 * @param sockfd The socket file descriptor.
 * @param backlog The maximum number of pending connections.
 * @return An integer value indicating the success or failure of the listening.
*/
int slisten(int sockfd, int backlog);

/**
 * Accepts an incoming connection on the given socket file descriptor.
 * 
 * This function accepts an incoming connection on the given socket file
 *    descriptor and checks if the acceptance was successful. If the acceptance
 *    was not successful, the function will print an error message and exit the
 *    program.
 * 
 * @param sockfd The socket file descriptor.
 * @return An integer value indicating the success or failure of the acceptance.
*/
int saccept(int sockfd);

/**
 * Polls the given file descriptors for events.
 * 
 * This function polls the given file descriptors for events and checks if the
 *    polling was successful. If the polling was not successful, the function
 *    will print an error message and exit the program.
 * 
 * @param fds The array of pollfd structures.
 * @param nfds The number of pollfd structures in the array.
 * @param timeout The timeout in milliseconds.
 * @return An integer value indicating the success or failure of the polling.
*/
int spoll(struct pollfd *fds, nfds_t nfds, int timeout);

#endif // _UTILS_H_
