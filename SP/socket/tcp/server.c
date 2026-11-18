
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int server_fd, client_fd;
    char buffer[1024];

    struct sockaddr_in server_addr;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server waiting for client...\n");

    // Accept client
    client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");

    // Continuous chat
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        // Receive client message
        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        buffer[n] = '\0';

        printf("\nClient: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("Client ended the chat.\n");
            break;
        }

        // Send server message
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(client_fd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0) {
            printf("Chat ended.\n");
            break;
        }
    }

    close(client_fd);
    close(server_fd);

    return 0;
}

