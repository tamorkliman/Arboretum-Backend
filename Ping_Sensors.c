//these macros are also in SensorList.h, consider having a common file
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Ping_Sensors.h"

#define MAX_SENSORNODES 256 
#define MAX_SENSORS 256
#define MAX_SENSORNODENAME_SIZE 256 //characters
#define MAX_SENSORNAME_SIZE 256
#define MAX_SENSORTYPE_SIZE 256

void set_seconds(SensorPingTiming *sensor, int seconds){
	sensor->seconds = seconds;
}

void set_minutes(SensorPingTiming *sensor, int minutes){ 
	sensor->minutes = minutes;
}

void set_hours(SensorPingTiming *sensor, int hours){
	sensor->hours = hours;
}

void set_days(SensorPingTiming *sensor, int days){
	sensor->days = days;
}

void set_months(SensorPingTiming *sensor, int months){
	sensor->months = months;
}

void set_name(SensorPingTiming *sensor, char *name){
	sensor->NameOfSensor = name;
}

void set_a_sensor_ping_frequency(SensorPingTiming *sensor, int seconds, int minutes, int hours,  int days, int months){
	set_seconds(sensor, seconds);
	set_minutes(sensor, minutes);
	set_hours(sensor, hours);
	set_days(sensor, days);
	set_months(sensor, months);
}


void set_a_sensornodes_ping_frequencies(SensorPingList *pinglist, int seconds, int minutes, int hours,  int days, int months){
	for(int i = 0; i < pinglist->numsensors; i++){
		set_a_sensor_ping_frequency(&pinglist->List[i], seconds, minutes, hours, days, months);
	}
}

void set_all_sensornodes_ping_frequencies(SensorNodePingList *masterlist, int seconds, int minutes, int hours,  int days, int months){
	for(int i = 0; i < masterlist->numsensornodes; i++){
		set_a_sensornodes_ping_frequencies(&masterlist->List[i], seconds, minutes, hours, days, months);
	}
}

SensorNodePingList create_sensornode_ping_list(void){
	SensorNodePingList newSensorNodePingList;
	newSensorNodePingList.numsensornodes = 0;
	for(int i = 0; i < MAX_SENSORNODES; i++){
		newSensorNodePingList.List = calloc(MAX_SENSORNODES,sizeof(SensorNodePingList));
	}
	return newSensorNodePingList;
}

SensorPingList create_sensor_ping_list(char *nodelocation){
	SensorPingList newSensorPingList;
	newSensorPingList.numsensors = 0;
	newSensorPingList.SensorNodeLocation = malloc(MAX_SENSORNODENAME_SIZE*sizeof(char));
	newSensorPingList.SensorNodeLocation = nodelocation;
	for(int i = 0; i < MAX_SENSORS; i++){
		newSensorPingList.List = calloc(MAX_SENSORS,sizeof(SensorPingTiming));
	}
	return newSensorPingList;
}

SensorPingTiming create_sensor_ping(char *name, int seconds, int minutes, int hours, int days, int months){
	SensorPingTiming newSensorPingTiming;
	newSensorPingTiming.NameOfSensor = malloc(sizeof(char)*MAX_SENSORNAME_SIZE);
	newSensorPingTiming.NameOfSensor = name;
	newSensorPingTiming.seconds = seconds;
	newSensorPingTiming.minutes = minutes;
	newSensorPingTiming.hours = hours;
	newSensorPingTiming.days = days;
	newSensorPingTiming.months = months;
	return newSensorPingTiming;
}

void add_sensornode_to_pinglist(SensorNodePingList *masterlist, char *nodelocation){
	int numNodes = masterlist->numsensornodes;
	masterlist->List[numNodes] = create_sensor_ping_list(nodelocation);
	masterlist->numsensornodes += 1;
}

void add_new_sensor_ping_timing(SensorPingList *pinglist, char *name, int seconds, int minutes, int hours,  int days, int months){
	int num = pinglist->numsensors;
	pinglist->List[num] = create_sensor_ping(name, seconds, minutes, hours, days, months);
	pinglist->numsensors += 1;
}

int sensornode_ping_exists(SensorNodePingList *masterlist, char *sensornodelocation){
	int foundSensornodeIndex = 0;	
	for(int i = 0; i < masterlist->numsensornodes; i++){
		//if(masterlist->List[i].SensorNodeLocation == '\0') break; //protect from segfault
		if(strcmp(masterlist->List[i].SensorNodeLocation, sensornodelocation) == 0){
			foundSensornodeIndex = 1;
			break;
		}
	}
	return foundSensornodeIndex;
}

int find_sensornode_ping_index(SensorNodePingList *masterlist, char *sensornodelocation){
	int foundsensornodeindex = 0;
	for(int i = 0; i < masterlist->numsensornodes; i++){
		if(strcmp(masterlist->List[i].SensorNodeLocation, sensornodelocation) == 0){
			foundsensornodeindex = i;
		}
	}
	return foundsensornodeindex;
}

int sensor_ping_exists(SensorPingList *pinglist, char *name){
	int foundsensorpingindex = 0;
	for(int i = 0; i < pinglist->numsensors; i++){
		if(strcmp(pinglist->List[i].NameOfSensor, name) == 0){
			foundsensorpingindex = 1;
			break;
		}
	}
	return foundsensorpingindex;
}


void print_sensorlist_pingtiming(SensorPingList *pinglist){
	printf("\n%s Sensor Ping List\n", pinglist->SensorNodeLocation);
	for(int i = 0; i < pinglist->numsensors; i++){
		printf("--- Sensor %d: ---\n",i + 1);
		printf("Sensor Name: %s\n",pinglist->List[i].NameOfSensor);
		printf("Ping Seconds: %i\n",pinglist->List[i].seconds);
		printf("Ping Minutes: %i\n",pinglist->List[i].minutes);		
		printf("Ping Hours: %i\n",pinglist->List[i].hours);
		printf("Ping Days: %i\n",pinglist->List[i].days);
		printf("Ping Months: %i\n",pinglist->List[i].months);
		printf("\n");
	}
}

void print_sensornode_pinglist(SensorNodePingList *masterlist){
	for(int i = 0; i < masterlist->numsensornodes; i++){
		printf("****** SensorNode %d *****\n",i + 1);
		print_sensorlist_pingtiming(&masterlist->List[i]);
	}
}
