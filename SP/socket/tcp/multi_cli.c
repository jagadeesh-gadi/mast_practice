
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>

int client_fd;

void *receive_msg(void *arg)
{
    char buffer[1024];

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
        {
            printf("\nServer disconnected\n");
            exit(0);
        }

        buffer[n] = '\0';

        printf("\nServer: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            exit(0);
    }

    return NULL;
}

int main()
{
    struct sockaddr_in addr;
    pthread_t thread;
    char buffer[1024];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "10.42.0.102", &addr.sin_addr);

    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Connection failed");
        close(client_fd);
        return 1;
    }

    printf("Connected to server\n");

    pthread_create(&thread, NULL, receive_msg, NULL);

    while (1)
    {
        printf("Client: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        send(client_fd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(client_fd);
    return 0;
}

