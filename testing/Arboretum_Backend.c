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
#include <mysql/mysql.h>

#define IPPROTO_DEFAULT 0
#define MAX_CONNECTIONS 1
#define NUM_SENSORS 6

typedef struct sockaddr_in sockaddr_in_s;

void stderror(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char **argv) {
  FILE *fp = NULL;
  sockaddr_in_s server_addr;
  sockaddr_in_s client_addr;
  socklen_t client_addr_len;
  char **sendstr = calloc(NUM_SENSORS, sizeof(char *));
  sendstr[0] = "r1\r";
  sendstr[1] = "r2\r";
  sendstr[2] = "r3\r";
  sendstr[3] = "r4\r";
  sendstr[4] = "r5\r";
  sendstr[5] = "r6\r";


  if (argc != 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
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

    /* // mysql example

       MYSQL *conn;
       MYSQL_RES *res;
       MYSQL_ROW row;

       char *server = "localhost";
       char *user = "root";
       char *password = "PASSWORD";
       char *database = "mysql";

       conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
    user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }

    // send SQL query
    if (mysql_query(conn, "show tables")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }

    res = mysql_use_result(conn);

    // output table name
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s \n", row[0]);

    // close connection
    mysql_free_result(res);
    mysql_close(conn);
    */ // end unused mysql example

    client_addr_len = sizeof(client_addr);
    int clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
    if (clientfd == -1) {
      stderror("Couldn't accept connection");
    }
    printf("Started new connection with client\n");
    int sendcount = 0;
    int attemptsend = 1;
    while (1) {
      if (attemptsend && send(clientfd, sendstr[sendcount], strlen(sendstr[sendcount]), 0) != strlen(sendstr[sendcount])) {
        stderror("Couldn't send packet");
      }
      attemptsend = 0;
      char recvstr[101];

      sleep(2);

      int recvstatus = recv(clientfd, recvstr, 100, MSG_DONTWAIT);
      if (recvstatus == -1 && errno != EWOULDBLOCK) { //non-blocking
        stderror("Couldn't receive packet");
      } else if (recvstatus != -1 && recvstatus != 0) {
        recvstr[recvstatus] = '\0'; // theoretically shouldn't do anything
        printf("Received Packet: %s\n", recvstr);
        attemptsend = 1; // send next packet
        // FIXME: change back to NUMSENSORS
        //sendcount = (sendcount + 1) % NUM_SENSORS; // select next packet to send
        sendcount = (sendcount + 1) % 2; // select next packet to send
        if (0 && send(clientfd, recvstr, strlen(recvstr), 0) != strlen(recvstr)) {
          stderror("Couldn't echo packet");
        }
      } else if (recvstatus != 0) {
        printf("No packet received\n");
      } else {
        break; // disconnected
      }
      fp = fopen("stop-arboretum", "r");
      if (fp != NULL) {
        fclose(fp);
        break;
      }
    }
    close(clientfd); //we don't do that because it's already closed
    printf("Disconnected from client\n");
    fp = fopen("stop-arboretum", "r");
    if (fp != NULL) {
      fclose(fp);
      break;
    }
  }

  int closestatus = close(sockfd);
  if (closestatus == -1) {
    stderror("Couldn't close socket");
  }
  free(sendstr);
  printf("Server Closed\n");
  return 0;
}
