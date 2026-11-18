
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>

void *receive_msg(void *arg)
{
    int client_fd = *(int *)arg;
    char buffer[1024];

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("\nClient: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(client_fd);
    return NULL;
}

void *send_msg(void *arg)
{
    int client_fd = *(int *)arg;
    char buffer[1024];

    while (1)
    {
        printf("Server: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        send(client_fd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    return NULL;
}

void *client_handler(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);

    pthread_t t1, t2;

    printf("Client connected: %d\n", client_fd);

    pthread_create(&t1, NULL, receive_msg, &client_fd);
    pthread_create(&t2, NULL, send_msg, &client_fd);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    pthread_t thread;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket failed");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    listen(server_fd, 5);

    printf("Server waiting for clients...\n");

    while (1)
    {
        client_fd = accept(server_fd, NULL, NULL);

        if (client_fd < 0)
            continue;

        int *ptr = malloc(sizeof(int));

        if (ptr == NULL)
        {
            close(client_fd);
            continue;
        }

        *ptr = client_fd;

        if (pthread_create(&thread, NULL, client_handler, ptr) != 0)
        {
            close(client_fd);
            free(ptr);
            continue;
        }

        pthread_detach(thread);
    }

    close(server_fd);
    return 0;
}

