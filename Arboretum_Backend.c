/*
 *Written by
 *Isaak Cherdak
 *
 *Credit for general lessons to:
 *http://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IPPROTO_DEFAULT 0
#define MAX_CONNECTIONS 1

typedef struct sockaddr_in sockaddr_in_s;

void stderror(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) {
  sockaddr_in_s server_addr;
  sockaddr_in_s client_addr;
  socklen_t client_addr_len;
  char sendstr[101] = "WHATSUP!!!\r\n";

  if (argc != 2) {
    fprintf(stderr, "Usage: argv[0] port");
  }

  int port = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_DEFAULT);
  if (sockfd == -1) {
    stderror("Couldn't create socket");
  }

  // NOTE: htons converts port to a network format
  int bindstatus = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(sockaddr_in_s));
  if (bindstatus == -1) {
    stderror("Bind unsuccessful");
  }

  int listenstatus = listen(sockfd, MAX_CONNECTIONS);
  if (listenstatus == -1) {
    stderror("Couldn't listen on socket");
  }

  for (;;) {
    client_addr_len = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
    if (clientfd == -1) {
      stderror("Couldn't accept connection");
    }
    while (1) {
      if (send(clientfd, sendstr, strlen(sendstr), 0) != strlen(sendstr)) {
        stderror("Couldn't send packet");
      }
      sleep(2);
    }
  }

  int closestatus = close(sockfd);
  if (closestatus == -1) {
    stderror("Couldn't close socket");
  }
  printf("It's beautiful\n");
  return 0;
}
