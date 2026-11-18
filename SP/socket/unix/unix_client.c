
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    int client_fd;
    struct sockaddr_un addr;
    char buffer[100];

    // Create UNIX socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (client_fd < 0)
    {
        perror("Socket failed");
        return 1;
    }

    // Configure server address
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/socket");

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&addr,
                sizeof(addr)) < 0)
    {
        perror("Connection failed");
        close(client_fd);
        return 1;
    }

    printf("Connected to server\n");

    while (1)
    {
        printf("Client :: ");

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Send client message
        send(client_fd, buffer, strlen(buffer) + 1, 0);

        if (strcmp(buffer, "exit") == 0)
            break;

        // Receive server reply
        memset(buffer, 0, sizeof(buffer));

        int n = recv(client_fd, buffer, sizeof(buffer)-1, 0);

        if (n <= 0)
        {
            printf("Server disconnected\n");
            break;
        }

        buffer[n] = '\0';

        printf("Server :: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(client_fd);

    printf("Chat ended\n");

    return 0;
}

