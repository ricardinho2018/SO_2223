#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    if (argc == 2 && strcmp(argv[1], "status") == 0) {
        // Enviar pedido para o servidor
        char buffer[BUFSIZ];
        sprintf(buffer, "status");
        if (send(sock, buffer, strlen(buffer), 0) == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }

        // Receber resposta do servidor
        memset(buffer, 0, BUFSIZ);
        if (recv(sock, buffer, BUFSIZ, 0) == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        // Exibir informações na tela
        printf("PID\tNome\tTempo de execucao (ms)\n");
        char *token = strtok(buffer, "\n");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, "\n");
        }
    } else {
        printf("Comando invalido.\n");
    }

    close(sock);
    return 0;
}
