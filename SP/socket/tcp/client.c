
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sock;
    char buffer[1024];

    struct sockaddr_in server_addr;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket failed");
        return 1;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "10.42.0.102",
              &server_addr.sin_addr);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server!\n");

    // Continuous chat
    while (1)
    {
        // Send client message
        printf("client: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            perror("Send failed");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            printf("Chat ended.\n");
            break;
        }

        // Receive server response
        memset(buffer, 0, sizeof(buffer));

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        buffer[n] = '\0';

        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("Server ended the chat.\n");
            break;
        }
    }

    close(sock);

    return 0;
}

