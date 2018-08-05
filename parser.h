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
	int seconds;	
} Parser;

Parser *parse_sensor_info(char *);

#endif /* _PARSER_H_ */
