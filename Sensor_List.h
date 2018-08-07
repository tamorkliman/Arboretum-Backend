#ifndef _SENSOR_LIST_H_
#define _SENSOR_LIST_H_
//Library for all devices (sensor nodes (microcontrollers)) that exist
//Can remove or add devices
//Also a library for all sensors on each device
//EACH SENSOR NAME MUST BE UNIQUE
//EACH SENSORNODE NAME MUST BE UNIQUE
typedef struct Sensor {
	char *NameOfSensor;
	char *SensorType;
	float SensorReading;
} Sensor;

typedef struct SensorList {
	int NumSensors;
	char *SensorNodeLocation;
	Sensor *List;
} SensorList;

typedef struct SensorNodeList {
	int NumSensorNodes;
	SensorList *List;
} SensorNodeList;
//or make an array of SensorLists for each device :)

//#define DLNULL (SensorList)NULLF
//public const Device nil = NULL;
//#define DNULL ((Device*)NULL)
//add destroy device list

SensorNodeList create_sensornode_list(void);

SensorList create_sensor_list(char *SensorNodeLocation);

void add_sensornode(SensorNodeList *nodelist, char *nodelocation);

int sensor_exists(SensorList *sensorlist, char name[]);

int sensornode_exists(SensorNodeList *nodelist, char *sensornodename);

int find_sensornode_index(SensorNodeList *nodelist, char *sensornodename);

void add_sensor(SensorList *sensorlist, char name[], char type[], float sensorreading);

void update_sensor_reading(SensorList *sensorlist, char name[], float sensorreading);

void remove_sensor(SensorList *sensorlist, char name[]);

void print_sensor_list(SensorList *sensorlist);

void print_sensornode_list(SensorNodeList *nodelist);








//get sensor reading

//print sensor list

//print sensors in each device

//Sensor create_sensor(char name[], char type[]); possibly omit this function to be local to the source because add sensor uses it (make the API cleaner)

#endif