#include<stdio.h>
#include <stdlib.h>              
#include <string.h>              
#include <unistd.h>              
#include <arpa/inet.h>           
#include <sys/socket.h>          
#include <netinet/in.h>    
      
#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sockfd;
    char buffer [BUFFER_SIZE];
    struct sockaddr_in server_addr , client_addr;
    socklen_t addr_len = sizeof(client_addr);

    //CREATE SOCKET
    if((sockfd = socket(AF_INET , SOCK_DGRAM)) < 0 ){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}