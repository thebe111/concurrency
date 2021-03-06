#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "headers/servers.h"

void
blocking_sock_connection(int sockfd) {
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);

    int sockfd_new = accept(sockfd, (struct sockaddr*) &peer_addr, &peer_addr_len);

    if (sockfd_new == -1) {
        perror("blocking_sock_connection.c:10: error to accept connection");
        exit(1);
    }

    log_peer_connection(&peer_addr, peer_addr_len);

    while (1) {
        uint8_t buf[1024];

        printf("calling recv...\n");

        int len = recv(sockfd_new, buf, sizeof buf, 0);

        if (len == -1) {
            perror("blocking_sock_connection.c:28: error calling recv");
        } else if (len == 0) {
            printf("peer disconnected, i'm done\n");
            break;
        }

        printf("recv returned %d bytes\n", len);
    }

    close(sockfd_new);
    close(sockfd);
}
