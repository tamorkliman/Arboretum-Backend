//Ping_Frequnecy.h
#ifndef _PING_TIMING_H_
#define _PING_TIMING_H_

typedef struct SensorPingTiming{
	char *NameOfSensor;
	int hours;
	int minutes;
	int days;
	int months;
	int seconds;
}SensorPingTiming;

typedef struct SensorPingList{
	int numsensors;
	char *SensorNodeLocation;
	SensorPingTiming *List;
}SensorPingList;

typedef struct SensorNodePingList{
	int numsensornodes;
	SensorPingList *List;
}SensorNodePingList;


SensorPingList create_sensor_ping_list(char *nodelocation);




SensorNodePingList create_sensornode_ping_list(void);

void add_sensornode_to_pinglist(SensorNodePingList *masterlist, char *nodelocation);

void set_a_sensornodes_ping_frequencies(SensorPingList *pinglist, int seconds, int minutes, int hours,  int days, int months);

void set_all_sensornodes_ping_frequencies(SensorNodePingList *masterlist, int seconds, int minutes, int hours,  int days, int months);

int ping_all_sensornodes(void);

void print_sensornode_pinglist(SensorNodePingList *masterlist);




SensorPingTiming create_sensor_ping(char *name, int seconds, int minutes, int hours, int days, int months);

void add_new_sensor_ping_timing(SensorPingList *pinglist, char *name, int seconds, int minutes, int hours,  int days, int months);

int sensor_ping_exists(SensorPingList *pinglist, char *sensornodelocation);

void print_sensor_pingtiming(SensorPingList *pinglist);





// TODO
// void remove_sensornode_from_pinglist(SensorNodePingList *masterlist, char *SensorNodeLocation);


#endif