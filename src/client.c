#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUFSZ 1024

void logexit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    char *address = argv[2];
    
    int sock = socket(AF_INET, SOCK_STREAM, 50);
    if (sock == -1) {
        logexit("socket");
    }

    if (connect(sock, address, sizeof(address)) != 0) {
        logexit("connect");
    }

    char buffer[BUFSZ];
    memset(buffer, 0, BUFSZ);
    fgets(buffer, BUFSZ-1, stdin);
    int count = send(sock, buffer, strlen(buffer)+1, 0);
    if (count != strlen(buffer)+1) {
        logexit("send");
    }

    memset(buffer, 0, BUFSZ);
    unsigned total = 0;
    while (1) {
        count = recv(sock, buffer + total, BUFSZ - total, 0);
        if (count == 0) {
            break;
        }
        total += count;
    }

    close(sock);

    return 0;
}