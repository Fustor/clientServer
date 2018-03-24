// A simple server in the internet domain using TCP
// The port nu1mber is passed as an argument

// Please note this is a C program
// It compiles without warnings with gcc

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

int main() {
    int sockfd, newsockfd, clilen;
    char buffer[256];
    struct sockaddr_in servaddr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);











    return 0;

}

