/*
 *Written by
 *Isaak Cherdak and Talmor Kliman
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
#include <time.h>


#include "Sensor_List.c"
#include "Ping_Sensors.h"
#include "parser.c"

#define IPPROTO_DEFAULT 0
#define MAX_CONNECTIONS 1
#define NUM_SENSORS 6
#define TIMEOUT_NOPACKET 6

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
  // for(int i = 0; i < NUM_SENSORS; i++){
  //   sendstr[i] = calloc(100,sizeof(char));
  // }
  char command[100];
  memset(command,'\0',100);
  // char *commandS = calloc(100,sizeof(char));
  // char *commandM = calloc(100,sizeof(char));
  // char *commandR = calloc(100,sizeof(char));

  // commandS = "s1\r";
  // commandM = "m1\r";
  // commandR = "r1\r";

  sendstr[0] = "s1\r";
  sendstr[1] = "m2\r";
  sendstr[2] = "r1\r";
  sendstr[3] = "r2\r";
  sendstr[4] = "r5\r";
  sendstr[5] = "r6\r";
  //Start Talmor Stuff
  Parser *p;
  int NumSensorsOnDevice = 0;
  int sensorIndex = 1;
  int firstdigit = 1;
  int seconddigit = 0;
  SensorNodeList sensorNodeList = create_sensornode_list();
  // int firstdigit = 1;
  // int seconddigit = 0;
  //char readcommand[100];
  //memset(readcommand, '\0',100);
  //End Talmor Stuff
  char DeviceLocation[100];
  memset(DeviceLocation, '\0',100);
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
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  //char timestr[32];
  static int startsec = 0;
  static int startmin = 0;
  static int starthour = 0;
  static int startday = 0;
  static int startmonth = 0;

  static int endsec = 0;
  static int endmin = 0;
  static int endhour = 0;
  static int endday = 0;
  static int endmonth = 0;

  startsec = tm.tm_sec;
  startmin = tm.tm_min;
  starthour = tm.tm_hour;
  startday = tm.tm_mday;
  startmonth = tm.tm_mon + 1;
  printf("sec: %d\n,min: %d\n,hour: %d\n,day: %d\n,month: %d\n",startsec,startmin,starthour,startday,startmonth);
//------------------ TEST CODE FOR PING QUERY ----------------------
   static MYSQL *conn;

  char *server = "db-01.soe.ucsc.edu";
  char *user = "arboretum_data";
  char *password = "icherdak_backend";
  char *database = "arboretum_data";
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server,
          user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "Failed to insert to DB: %s\n", mysql_error(conn));
     //continue;
    }
    char pingtimingquerystr[256];
    pingtimingquerystr[1056] = '\0';
    sprintf(pingtimingquerystr, "SELECT * FROM pingtiming where id=(select max(id) from pingtiming)");
    if (mysql_query(conn, pingtimingquerystr)) {
      //stderror((char *) mysql_error(conn));
      fprintf(stderr, "Failed to Get Ping Timing from DB: %s\n", mysql_error(conn));
      //exit(1);
    } else {
      printf("DB Get Ping Timing Successful\n");
    }
    printf("here\n");
    MYSQL_RES *result = mysql_store_result(conn);
   // result = mysql_store_result(conn);
    printf("here\n");
   int num_fields = mysql_num_fields(result);
   printf("numfields: %d\n", num_fields);
   int num_rows = mysql_num_rows(result);
   printf("numrows: %d\n", num_rows);

char webuserpingtimingNAME[100];
char webuserpingtimingSEC[100];
char webuserpingtimingMIN[100];
char webuserpingtimingHOUR[100];
char webuserpingtimingDAY[100];
char webuserpingtimingMONTH[100];
int rowindex = 0;
MYSQL_ROW row = mysql_fetch_row(result);

  printf("here\n");
    for(int i = 0; i < num_fields; i++) 
    { 
      if(row){
        
        if(rowindex == 1) sprintf(webuserpingtimingNAME,"%s",row[i]);
        if(rowindex == 2) sprintf(webuserpingtimingSEC,"%s",row[i]);
        if(rowindex == 3) sprintf(webuserpingtimingMIN,"%s",row[i]);
        if(rowindex == 4) sprintf(webuserpingtimingHOUR,"%s",row[i]);
        if(rowindex == 5) sprintf(webuserpingtimingDAY,"%s",row[i]);
        if(rowindex == 6) sprintf(webuserpingtimingMONTH,"%s",row[i]);
        rowindex++;
        printf("%s ", row[i]);
      }
    }
      printf("\n");

      printf("WebNAME: %s\n",webuserpingtimingNAME);
      printf("WebSEC: %s\n",webuserpingtimingSEC);
      printf("WebMIN: %s\n", webuserpingtimingMIN);
      printf("WebHOUR: %s\n", webuserpingtimingHOUR);
      printf("WebDAY: %s\n", webuserpingtimingDAY);
      printf("WebMONTH: %s\n", webuserpingtimingMONTH);
      mysql_close(conn);

      // if()
  endsec = startsec + atoi(webuserpingtimingSEC);
  endmin = tm.tm_min + atoi(webuserpingtimingMIN);
  endhour = tm.tm_hour + atoi(webuserpingtimingHOUR);
  endday = tm.tm_mday + atoi(webuserpingtimingDAY);
  endmonth = tm.tm_mon + 1 + atoi(webuserpingtimingMONTH);
  //int monthindex = 0;
  
  printf("sec: %d\n,min: %d\n,hour: %d\n,day: %d\n,month: %d\n",endsec,endmin,endhour,endday,endmonth);
  // MYSQL *conn;

  // char *server = "db-01.soe.ucsc.edu";
  // char *user = "arboretum_data";
  // char *password = "icherdak_backend";
  // char *database = "arboretum_data";

  for (;;) {
    //Start Talmor Stuff
    
    
    //End Talmor Stuffls


    int8_t no_receive_count = 0;
    client_addr_len = sizeof(client_addr);
    int clientfd = -1;
    while (clientfd == -1) {
      clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
      if (clientfd == -1) {
        printf("Couldn't accept connection, retrying...\n");
      }
    }
    printf("Started new connection with client\n");
    int sendcount = 0;
    int attemptsend = 1;
    NumSensorsOnDevice = 0;
              //printf("sec %d, min %d, hour %d, day %d, month %d\n",sec,min,hour,day,month);
              //sprintf(timestr, "%04d%02d%02d::%02d%02d%02d", tm.tm_year + 1900,
              // tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec
    while (1) {
      printf("sendcount = %d\n",sendcount);
      // if(sendcount == 0){
      //     if (attemptsend && send(clientfd, sendstr[sendcount], strlen(sendstr[sendcount]), 0) != strlen(sendstr[sendcount])) {
      //       printf("Connection error\n");
      //       break;
      //     }
      // } else if (sendcount == 1){
      //     if (attemptsend && send(clientfd, sendstr[sendcount], strlen(sendstr[sendcount]), 0) != strlen(sendstr[sendcount])) {
      //       printf("Connection error\n");
      //       break;
      //     }
      // } else if (sendcount >= 2){
      //     if (attemptsend && send(clientfd, sendstr[sendcount], strlen(sendstr[sendcount]), 0) != strlen(sendstr[sendcount])) {
      //       printf("Connection error\n");
      //       break;
      //     }
      // }
      if(sendcount == 0) strcpy(command, "s1\r");
      // if(sendcount == 1) strcpy(command, "m1\r");
      // if(sendcount == 2) strcpy(command, "r1\r");

      if (attemptsend && send(clientfd, command, strlen(command), 0) != strlen(command)) {
          printf("Connection error\n");
          break;
      }
      attemptsend = 0;
      char recvstr[101];

      sleep(2);

      int recvstatus = recv(clientfd, recvstr, 100, MSG_DONTWAIT);
      printf("recvstatus: %d\n", recvstatus);
      if (recvstatus == -1 && errno != EWOULDBLOCK) { //non-blocking
        stderror("Couldn't receive packet");
      } else if (recvstatus != -1 && recvstatus != 0) {
        recvstr[recvstatus] = '\0'; // theoretically shouldn't do anything
        printf("Received Packet: %s\n", recvstr);
        attemptsend = 1; // send next packet
        no_receive_count = -1;
        if(sendcount == 0) { //get the identification from device (SensorNode)
            printf("hereeeeee1\n");
            //if(search_client_names(token)){ //check that the client exists
              strcpy(DeviceLocation,recvstr);
              printf("DeviceLocation: %s\n", DeviceLocation);
              strcpy(command, "m1\r"); //next command
              sendcount++;
            //}
        } else if(sendcount == 1) { //get the amount of sensors created on device (SensorNode)
              printf("hereeeeee2\n");
              //if(atoi(recvstr) < 100 && atoi(recvstr) > 0){ //check that the number is within 1 to 100
                NumSensorsOnDevice = recvstr[0] - '0'; //convert char to int
                printf("NumSensorsOnDevice: %d\n", NumSensorsOnDevice);
                sendcount++;
                strcpy(command, "r1\r");
                sensorIndex++;
              //}
        } else if(sendcount >= 2){ //get sensor readings
              int o = sensornode_exists(&sensorNodeList, DeviceLocation);
              printf("\n sensornode exists %d\n",o);
              if(sendcount == 2) add_sensornode(&sensorNodeList, DeviceLocation);
              p = parse_sensor_info(recvstr);
              add_sensor(0,p->name, p->type, p->reading);
              print_sensornode_list(&sensorNodeList);
              printf("hereeeeee3\n");
              if(sensorIndex < 10){
                 sprintf(command,"r%c\r\n",(uint8_t)(sensorIndex) + '0');  //next command 
              } else if(sensorIndex >= 10 && sensorIndex < 100){
                if(sensorIndex - 10 >= 0 && sensorIndex < 20) {
                    firstdigit = 1;
                    seconddigit = 0;
                    while((sensorIndex - 10) - seconddigit != 0){
                      seconddigit++;
                    }
                    sprintf(command,"r%c%c\r\n", firstdigit + '0', seconddigit + '0');  //next command 
                } else if (sensorIndex - 20 > 10 && sensorIndex < 30){
                    firstdigit = 2;
                    seconddigit = 0;
                    while((sensorIndex - 20) - seconddigit != 0){
                      seconddigit++;
                    }
                   sprintf(command,"r%c%c\r\n", firstdigit + '0', seconddigit + '0');  //next command 
                } else if (sensorIndex - 30 > 20 && sensorIndex < 40){
                    firstdigit = 3;
                    seconddigit = 0;
                    while((sensorIndex - 30) - seconddigit != 0){
                      seconddigit++;
                    }
                    sprintf(command,"r%c%c\r\n", firstdigit + '0', seconddigit + '0');  //next command 
                }
              }
          // p = parse_sensor_info(recvstr);
          printf("here motherfucker\n");
          //printf("name: %s\ntype: %s\nreading: %f\n", p->name, p->type, p->reading);
          sendcount++;
          
            
            //int nodeindex = 0;
            // int o = sensornode_exists(&sensorNodeList, DeviceLocation);
            //   printf("\n sensornode exists %d\n",o);
            //   add_sensornode(&sensorNodeList, DeviceLocation);
            //   print_sensornode_list(&sensorNodeList);
              // if(sensornode_exists(&sensorNodeList, DeviceLocation)){
              //   printf("here1\n");
              //   nodeindex = find_sensornode_index(&sensorNodeList, DeviceLocation);
              //   printf("here2\n");
              //   if(sensor_exists(&sensorNodeList.List[nodeindex], p->name)){
              //     printf("here3\n");
              //     update_sensor_reading(&sensorNodeList.List[nodeindex], p->name, p->reading);
              //   } else {
              //     printf("here4\n");
              //     add_sensor(&sensorNodeList.List[nodeindex],p->name, p->type, p->reading);
              //   }
              // } else {
              //   printf("here5");
              //   add_sensornode(&sensorNodeList, DeviceLocation);
              //   nodeindex = find_sensornode_index(&sensorNodeList, DeviceLocation);
              //   add_sensor(&sensorNodeList.List[nodeindex],p->name, p->type, p->reading);
              // }
             // print_sensornode_list(&sensorNodeList);

          //sprintf(readcommand,"r%c\r\n",(uint8_t)(sensorIndex) + '0');
          
          //printf("readcommand: %s\n",readcommand);


          // sendcount = 0;
          // sensorIndex++;
          // if(sensorIndex < 10){
          //   sprintf(readcommand,"r%c\r\n",(int8_t)(sensorIndex) + '0');
          // } 
          //printf("before strcpy");
          //strcpy(sendstr[sendcount][0],readcommand);
          //printf("after strcpy");
          //       } else if (sensorIndex - 20 > 10 && sensorIndex < 30){
          //           firstdigit = 2;
          //           seconddigit = 0;
          //           while((sensorIndex - 20) - seconddigit != 0){
          //             seconddigit++;
          //           }
          //           sprintf(readcommand,"r%c%c\r\n",firstdigit + '0', seconddigit +'0');
          //       } else if (sensorIndex - 30 > 20 && sensorIndex < 40){
          //           firstdigit = 3;
          //           seconddigit = 0;
          //           while((sensorIndex - 30) - seconddigit != 0){
          //             seconddigit++;
          //           }
          //           sprintf(readcommand,"r%c%c\r\n",firstdigit + '0', seconddigit +'0');
          //       }
          //     }

          if(sensorIndex > NumSensorsOnDevice){ //once you get all sensor data from a single device restart
             //print_sensor_list(&sensorlist);
             sendcount = 0; //start the conversation over
             sensorIndex = 1;
             NumSensorsOnDevice = 0;
             //memset(readcommand, '\0',100);
             //strcpy(readcommand,"r1\r"); //restart the iteration through sensors
             memset(DeviceLocation, '\0',100);
          }
          printf("sensorIndex = %d\n",sensorIndex);
          sensorIndex++;
          //     sensorIndex += 1;
          // will become 0 at the end of the loop
        }
        // if(sendcount == 4){

        //if(sendcount == 4) sendcount = 0;

       

        //if (!strchr(recvstr, '=')) {
        //  printf("Invalid data syntax: skipping DB insert\n");
        //  continue;
        //}

        // conn = mysql_init(NULL);

        // // Connect to database
        // if (!mysql_real_connect(conn, server,
        //       user, password, database, 0, NULL, 0)) {
        //   fprintf(stderr, "Failed to insert to DB: %s\n", mysql_error(conn));
        //   continue;
        // }

        // // insert data into database
        // char query_str[256];
        // query_str[255] = '\0';
        // char *device_name = strtok(recvstr, "=\r\n");
        // time_t t = time(NULL);
        // struct tm tm = *localtime(&t);
        // char timestr[32];
        // sprintf(timestr, "%04d%02d%02d::%02d%02d%02d", tm.tm_year + 1900,
        //     tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        // if (device_name) {} // stop compiler from complaining
        // snprintf(query_str, 255, "%s ('%s', '%s', '%s')",
        //     "INSERT INTO device_data VALUES",
        //     "1",
        //     strtok(NULL, "\r\n"),
        //     timestr);
        // if (mysql_query(conn, query_str)) {
        //   //stderror((char *) mysql_error(conn));
        //   fprintf(stderr, "Failed to insert to DB: %s\n", mysql_error(conn));
        //   //exit(1);
        // } else {
        //   printf("DB insertion successful\n");
        // }

        // //disconnect from DB
        // mysql_close(conn);

      } else if (recvstatus != 0) {
        printf("No packet received\n");
      // } else if (recvstatus == 0){
      //   printf("Received empty packet\n");
      // } else {
      } else {
        break; // disconnected
      }
      fp = fopen("stop-arboretum", "r");
      if (fp != NULL) {
        fclose(fp);
        break;
      }
      if (no_receive_count++ > TIMEOUT_NOPACKET) {
        printf("Didn't receive packet\n");
        break;
      }
    }
    if (clientfd != -1) close(clientfd); //we don't do that because it's already closed
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
