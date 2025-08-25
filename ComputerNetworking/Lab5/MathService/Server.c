#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUF_SIZE], response[BUF_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Math Server running on port %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        int a, b;
        char op;
        double result = 0;
        char msg[BUF_SIZE];

        if (sscanf(buffer, "%d %c %d", &a, &op, &b) == 3) {
            switch (op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        snprintf(msg, sizeof(msg), "Error: Division by zero");
                        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
                        continue;
                    }
                    result = (double)a / b;
                    break;
                default:
                    snprintf(msg, sizeof(msg), "Error: Invalid operator");
                    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
                    continue;
            }
            snprintf(msg, sizeof(msg), "Result: %.2f", result);
        } else {
            snprintf(msg, sizeof(msg), "Error: Invalid format. Use: <int> <op> <int>");
        }

        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
        printf("Processed: %s → %s\n", buffer, msg);
    }

    close(sockfd);
    return 0;
}
