#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8080
#define MAXLINE 1024

int main(void) {

  int sockfd;
  char buffer[MAXLINE];
  char tempType = ' ';

  struct sockaddr_in servaddr;
  struct hostent *server;

  FILE *readFile = fopen("desiredTemp.txt", 'r');
  FILE *writeFile = fopen("receivedTemp.txt", 'w');

  while (1 == 1) {
    
    // read file
    tempType = fgetc(readFile);
    // send number
    
    bzero((char *)&servaddr, sizeof(servaddr));

    if((server = gethostbyname("LAPTOP-KTCF7DB5\0")) == NULL) {
      printf("Error, host name not valid\n");
      exit(EXIT_FAILURE);
    }

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    bcopy((char *)server->h_addr_list[0], (char *)&servaddr.sin_addr.s_addr, server->h_length);

    int n, len;

    sendto(sockfd, &tempType, 1,
        0, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
            
    printf("Message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    // receive number
    
    // write file
    fprintf(writeFile, "%s", buffer);

  }

}
