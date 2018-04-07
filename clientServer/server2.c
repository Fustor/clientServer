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


void error(char *msg)
{
    perror(msg);
    exit(1);
}
struct job {
    char title[256];
    char avgPay[256];
    char midPay[256];

} ;
///////////look up fscanf
int main()
{
     struct job jobs[512];
     FILE *file;
     file = fopen("Salaries.txt", "r");


        while(!feof(file))
        {
            //printf("scanning \n");
            for(int i = 0;i<512;i++) {
                fscanf( file, "%[^\t]\t%[^\t]\t%[^\n]\n", jobs[i].title, jobs[i].avgPay, jobs[i].midPay );
                //printf( "%s\t%s\t%s\n",                    jobs[i].title, jobs[i].avgPay, jobs[i].midPay );
            }

            //printf("next \n");
       /* jobs[i].title = string1;
        jobs[i].avgPay = string2;
        jobs[i].midPay = string3;
        */
        }




     printf("Enter server port number: \n");
     int portNum;
     scanf("%d",&portNum);

     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n = 2;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = portNum;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");

    while(1) {
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);


     for(int i = 0;i<512;i++) {
       // printf("%s \n", "checking");
        for(int j = 0;j<256;j++) {
            if(jobs[i].title[j] == '\0') {
                printf("%s%s%s \n", jobs[i].title,jobs[i].avgPay, jobs[i].midPay);
                i = 512;
                break;
            }
            else if(jobs[i].title[j] != buffer[j]) {

                break;
            }
        }

     }

     if (n < 0) error("ERROR reading from socket");
     printf("%d",n);
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);

     if (n < 0) error("ERROR writing to socket");
     }


     return 0;
}


