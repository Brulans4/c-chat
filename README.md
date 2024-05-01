# C Chat Application

Welcome to the C Chat Application! This project provides a simple chat system implemented in C programming language, allowing users to send and receive messages in real-time.

## Features

- **Server-Client Architecture**: The application follows a client-server architecture where clients connect to a central server to exchange messages.
- **Parent-Child Process Communication**: The server and client utilize parent-child process communication to handle sending and receiving messages concurrently.
- **Efficient Event Handling**: The server employs the `poll()` system call to efficiently manage multiple client connections and handle incoming messages.

## Requirements

- **C Compiler**: This project is implemented in C programming language and requires a compatible C compiler (e.g., GCC).
- **Unix-like Operating System**: The application is developed for Unix-like operating systems (e.g., Linux, macOS).

## Getting Started

1. **Clone the Repository**: Clone this repository to your local machine using the following command:

    ```
    git clone <repository_url>
    ```

2. **Compile the Code**: Navigate to the project directory and compile the server and client programs using the provided Makefile:

    ```
    cd c-chat/src
    make all
    ```

3. **Run the Server**: Start the server by executing the following command:

    ```
    ./server
    ```

4. **Run the Client**: Start one or more client instances by executing the following command:

    ```
    ./client
    ```

5. **Chat Away!**: You can now send and receive messages between the clients connected to the server.

## Configuration

- **IP Address and Port**: You can configure the IP address and port number used by the server and clients by modifying the `config.h` file.
- **Maximum Number of Users**: Adjust the maximum number of users allowed to connect to the server by changing the `USERS` constant in the `config.h` file.