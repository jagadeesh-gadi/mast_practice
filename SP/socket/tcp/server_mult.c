
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void *handle_client(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);

    char buffer[1024];

    printf("Client connected! FD: %d\n", client_fd);

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
        {
            printf("Client FD %d disconnected\n", client_fd);
            break;
        }

        buffer[n] = '\0';

        printf("Client %d says: %s\n", client_fd, buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            printf("Client %d ended chat\n", client_fd);
            break;
        }

        // Send response to this client
        char response[] = "Message received by server";

        send(client_fd, response, strlen(response), MSG_NOSIGNAL);
    }

    close(client_fd);

    return NULL;
}

int main()
{
    int server_fd, client_fd;
    int opt = 1;

    struct sockaddr_in server_addr;

    pthread_t thread;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket failed");
        return 1;
    }

    // Allow address reuse
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    // Configure address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen
    if (listen(server_fd, 10) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server waiting for multiple clients...\n");

    // Accept multiple clients
    while (1)
    {
        client_fd = accept(server_fd, NULL, NULL);

        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        int *new_fd = malloc(sizeof(int));

        if (new_fd == NULL)
        {
            perror("Malloc failed");
            close(client_fd);
            continue;
        }

        *new_fd = client_fd;

        // Create separate thread for each client
        if (pthread_create(&thread, NULL,
                           handle_client, new_fd) != 0)
        {
            perror("Thread creation failed");
            close(client_fd);
            free(new_fd);
            continue;
        }

        pthread_detach(thread);
    }

    close(server_fd);

    return 0;
}

