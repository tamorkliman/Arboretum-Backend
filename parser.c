#include "parser.h"
#include <string.h>
#include <ctype.h>

//serial types
#define I2C "I2C"
#define UART "UART"
#define ONEWIRE "ONEWIRE"
#define RELAY "RELAY"

//name types
#define TEMPERATURE "TEMP_SENSOR"
#define HUMIDITY "HUMIDITY_SENSOR"
#define LIGHT_SENSOR "LIGHT_SENSOR"
#define TSMPPT "TSMPPT"
#define ACTUATOR "ACTUATOR"

//SENSOR TYPES
/*
HUMIDITY_SENSOR pin_count = 2
TSMPPT pin_count = 2
LIGHT_SENSOR pin_count = 2
TEMP_SENSOR pin_count = 1
ACTUATOR pin_count = 1
*/

char *name = "TEMPERATURE";
char *type = "ONEWIRE";
char **sensortypes;
char **sensornames;
static int numberoftypes = 0;
static int numberofnames = 0;


int search_sensor_name(char *nametofind){
  int returnNum = 0;
  for(int i = 0; i < numberofnames; i++){
    if(strcmp(nametofind,sensornames[i]) == 0){
        returnNum = 1;
        printf("found name\n");
        break;
    }
  }
  return returnNum;
}

int search_sensor_type(char *nametofind){
  int returnNum = 0;
  for(int i = 0; i < numberoftypes; i++){
    if(strcmp(nametofind,sensortypes[i]) == 0){
        returnNum = 1;
        printf("found type\n");
        break;
    }
  }
  return returnNum;
}

  // returns a Parser object with relevant information
  // If there is an erroneous input, cmd will be set to the null character
  Parser *parse_sensor_info(char *input_str) {
    //TO DO: get type names from database
    //make a create "type" function
    
    sensornames = calloc(100,sizeof(char *));
    for(int i = 0; i < 100; i++){
      sensornames[i] = calloc(100,sizeof(char));
    }
    sensornames[0] = "TEMP_SENSOR";
    numberofnames++;
    sensornames[1] = "HUMIDITY_SENSOR";
    numberofnames++;
    sensornames[2] = "LIGHT_SENSOR";
    numberofnames++;
    sensornames[3] = "TSMPPT";
    numberofnames++;
    sensornames[4] = "ACTUATOR";
    numberofnames++;

    sensortypes = calloc(100,sizeof(char *));
    for(int i = 0; i < 100; i++){
      sensortypes[i] = calloc(100,sizeof(char));
    }
    sensortypes[0] = "I2C";
    numberoftypes++;
    sensortypes[1] = "UART";
    numberoftypes++;
    sensortypes[2] = "ONEWIRE";
    numberoftypes++;
    sensortypes[3] = "RELAY";
    numberoftypes++;

    Parser *p = calloc(1,sizeof(Parser));
    p->name = calloc(100, sizeof(char));
    p->type = calloc(100, sizeof(char));
    //p->reading = calloc(100, sizeof(float));
<<<<<<< HEAD
    int numtokens = 0;
    int index = 0;
    for(index = 0; index < strlen(input_str); index++){
      if(input_str[index] == ' ') numtokens++;
    }
    
    if(index > 0){
      if(numtokens == 0){
        p->numtokens = 1;
      } else {
        p->numtokens = numtokens + 1; //to pass the num of tokens to main.c
        numtokens += 1; //just to keep track of num tokens
      }
    } else {
      p->numtokens = 0;
    }
    

    if(p->numtokens != 3){
      printf("in != 3\n");
      p->name = '\0';
      p->type = '\0';
      p->reading = 0.0;
      return p;
    }
    const char *token = strtok(input_str, " ");
    if (!token) { // no tokens
      printf("in !tokens\n");
=======

    const char *token = strtok(input_str, " ");
    if (!token) { // no tokens
>>>>>>> b928890d4b2e4b9cfea5a4e986082324300610db
      p->name = '\0';
      p->type = '\0';
      p->reading = 0.0;
      return p;
    }

      //first token is Name
      //second token is Type
      //third token is Reading
    //char *currentstring = &token;
    if(search_sensor_name((char *)token) == 1){
      strcpy(p->name,token);
      printf("name: %s\n", p->name);
    } else {
      printf("sensor name doesn't exist or message format is wrong message format: (NAME, TYPE, READING)\n");
      p->name = '\0';
    }

    token = strtok(NULL, " ");
    if(search_sensor_type((char *)token) == 1){
      strcpy(p->type,token);
      printf("type: %s\n", p->type);
    } else {
      printf("sensor type doesn't exist or message format is wrong message format: (NAME, TYPE, READING)\n");
      p->type = '\0';
    }

    token = strtok(NULL, " ");
    // if(strstr(token,"-") != '\0'){
    //   token = &token[1];
    //   float i = -atof(token);
    //   p->reading = &i;
    //   printf("reading: %f\n", p->reading);
    // } else if(atof(token) != 0.0){ 
    if(isdigit(token[0])){
      float i = atof(token);
      p->reading = i;
      printf("reading: %f\n", p->reading);

    } else {
      p->reading = 0;
    }
    // } else {
    //   p.reading = '\0';
    //   printf("sensor reading is bad. message format is wrong message format: (NAME, TYPE, READING)\n");
    // }

    return p;
}

    // switch(token) {
    //   case I2C:
    //     strcpy(p.type,token);
    //     break;
    //   case UART:
    //     break;
    //   case ONEWIRE:
    //     break;
    //   case RELAY: 
    //     break;
    //   default:
    //     p.name = '\0';
    //     p.type = '\0';
    //     p.reading = '\0';
    //     break;
    // }

//   switch(token[0]) {
//     case CHAR_CREATE:
//       {
//         uint8_t add_ind[8];
//         uint8_t reg_bit[8];
//         p.address_index = (const uint8_t *) add_ind;
//         p.reg_bit = (const uint8_t *) reg_bit;
//         p.pin_count = 0;
//         token = strtok(NULL, delimit);
//         if (!token) { // no arguments
//           p.cmd = '\0';
//           return p;
//         }
//         p.ret_str = token; // ret_str is now type_str
//         token = strtok(NULL, delimit);
//         if (token == NULL) { // no mention of onboard pin location
//           p.cmd = '\0';
//           return p;
//         }
//         if (!parse_pin(token, add_ind,
//               reg_bit, p.pin_count)) {
//           p.cmd = '\0';
//           return p;
//         }
//         p.pin_count++;
//         while (((token = strtok(NULL, delimit)) != NULL)) {
//           if (p.pin_count == 8) { //don't try to have more than 8 pins
//             p.cmd = '\0';
//             break;
//           }
//           if (!parse_pin(token, add_ind,
//                 reg_bit, p.pin_count)) break;
//           p.pin_count++;
//         }
//       }
//       break;
//     case CHAR_INIT:
//       if (!isdigit(token[1])) { // this isn't a number (but it should be)
//         p.cmd = '\0';
//         return p;
//       }
//       device_index = (uint8_t) atoi(token + 1); // index is second character
//       p.device_index = device_index;
//       break;
//     case CHAR_READ:
//       if (!isdigit(token[1])) { // this isn't a number (but it should be)
//         p.cmd = '\0';
//         return p;
//       }
//       device_index = (uint8_t) atoi(token + 1); // index is second character
//       p.device_index = device_index;
//       break;
//     case CHAR_WRITE:
//       if (!isdigit(token[1])) { // this isn't a number (but it should be)
//         p.cmd = '\0';
//         return p;
//       }
//       device_index = (uint8_t) atoi(token + 1); // index is second character
//       p.device_index = device_index;
//       char ndelimit[3] = "\r\n"; // custom one so that spaces are included
//       token = strtok(NULL, ndelimit);
//       if (!token) { // no string to write
//         p.cmd = '\0';
//         return p;
//       }
//       p.ret_str = token; // ret_str is string to write
//       break;
//     case CHAR_DESTROY:
//       if (!isdigit(token[1])) { // this isn't a number (but it should be)
//         p.cmd = '\0';
//         return p;
//       }
//       device_index = (uint8_t) atoi(token + 1); // index is second character
//       p.device_index = device_index;
//       break;
//     case CHAR_KILL:
//       if (!isdigit(token[1])) { // this isn't a number (but it should be)
//         p.cmd = '\0';
//         return p;
//       }
//       device_index = (uint8_t) atoi(token + 1); // index is second character
//       p.device_index = device_index;
//       break;
//     case CHAR_MAP:
//       // nothing to do
//       break;
// 	  case SELF_ID:
// 	  // nothing to do
// 		break;
//     default:
//       p.cmd = '\0'; // invalid command
//       break;
//   }
//   return p;
// }
