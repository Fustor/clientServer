
// Please note this is a C program
// It compiles without warnings with gcc
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    printf("Enter host name: \n");
    char hostName[100];
    scanf("%s",hostName);
    printf("Enter port number: \n");
    int portNum;
    scanf("%d",&portNum);



    int sockfd, portno, n =2;
    portno = portNum;


    struct sockaddr_in serv_addr;
    struct hostent *server;
    while(1) {
    char buffer[512];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(hostName);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    int c;
    while((c = getchar()) != '\n' && c != EOF);//clears input stream, without fgets takes in \n

    printf("Enter a college major: ");
    bzero(buffer,512);
    fgets(buffer,511,stdin);

    int checkEmpty = 0;
    for(int i = 0;i<512;i++) {
        if(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t'&& buffer[i] != '\0') {
            //printf("%s%c\n", "not empty", buffer[i]);
            checkEmpty = 1;
            break;
        }
    }
    if(checkEmpty == 0) {
        //printf("%s\n", "empty");
        break;
    }
    char career[512];
    strcpy(career,buffer);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");
    bzero(buffer,512);
    n = read(sockfd,buffer,511);
    char *split;
    split = strtok(buffer, " ");
    printf("%s%s%s%s\n", "The average early career pay for a ", career, "major is $", split);
    split = strtok(NULL," ");
    printf("%s%s\n", "The corresponding mid career pay is $", split);
    //printf("%s\n",buffer);


    if (n < 0)
         error("ERROR reading from socket");
    //printf("%s\n",buffer);
    }

    return 0;
}

