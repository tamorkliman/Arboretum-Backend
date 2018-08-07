#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Parser{
	char *name;
	char *type;
	float reading;
	int hours;
	int minutes;
	int days;
	int months;
<<<<<<< HEAD
	int seconds;
	int numtokens;	
=======
	int seconds;	
>>>>>>> b928890d4b2e4b9cfea5a4e986082324300610db
} Parser;

Parser *parse_sensor_info(char *);

#endif /* _PARSER_H_ */
