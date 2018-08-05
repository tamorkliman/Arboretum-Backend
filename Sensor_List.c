#include "Sensor_List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENSORNODES 256
#define MAX_SENSORS 256
#define MAX_SENSORNODENAME_SIZE 256 //characters
#define MAX_SENSORNAME_SIZE 256
#define MAX_SENSORTYPE_SIZE 256

SensorNodeList create_sensornode_list(void){
	printf("heree1\n");
	SensorNodeList newSensorNodeList;
	newSensorNodeList.NumSensorNodes = 0;
	for(int i = 0; i < MAX_SENSORNODES; i++){
		newSensorNodeList.List = calloc(MAX_SENSORNODES,sizeof(SensorList));
	}
	return newSensorNodeList;
}

void add_sensornode(SensorNodeList *nodelist, char *nodelocation){
	printf("heree2\n");
	int numNodes = nodelist->NumSensorNodes;
	nodelist->List[numNodes] = create_sensor_list(nodelocation);
	nodelist->NumSensorNodes++;
}

SensorList create_sensor_list(char *nodelocation){
	printf("heree3\n");
	SensorList newSensorList;
	newSensorList.NumSensors = 0;
	newSensorList.SensorNodeLocation = malloc(MAX_SENSORNODENAME_SIZE*sizeof(char));
	newSensorList.SensorNodeLocation = nodelocation;
	for(int i = 0; i < MAX_SENSORS; i++){
		newSensorList.List = calloc(MAX_SENSORS,sizeof(Sensor));
	}
	return newSensorList;
}

int sensornode_exists(SensorNodeList *nodelist, char *sensornodename){
  printf("heree4\n");
  int foundsensornode = 0;
  for(int i = 0; i < nodelist->NumSensorNodes; i++){
    if(strcmp(sensornodename,nodelist->List[i].SensorNodeLocation) == 0){
        foundsensornode = 1;
        printf("found name of sensor node: %s\n", sensornodename);
        break;
    }
  }
  return foundsensornode;
}

Sensor create_sensor(char name[], char type[], float sensorreading){
	printf("heree5\n");
	Sensor newSensor;
	newSensor.NameOfSensor = malloc(sizeof(char)*MAX_SENSORNAME_SIZE);
	newSensor.SensorType = malloc(sizeof(char)*MAX_SENSORTYPE_SIZE);
	newSensor.NameOfSensor = name;
	newSensor.SensorType = type;
	newSensor.SensorReading = sensorreading;
	return newSensor;
}

void add_sensor(SensorList *sensorlist, char name[], char type[], float sensorreading){
	printf("heree6\n");
	//int num = sensorlist->NumSensors;
	//printf("heree61");
	sensorlist->List[0] = create_sensor(name, type, sensorreading);
	printf("heree62");
	sensorlist->NumSensors += 1;
}

int sensor_exists(SensorList *sensorlist, char name[]){
	printf("heree7\n");
	int foundSensorIndex = 0;
	for(int i = 0; i < sensorlist->NumSensors; i++){
		//if(sensorlist->List[i].NameOfSensor == '\0') break; //protect from segfault
		if(strcmp(sensorlist->List[i].NameOfSensor, name) == 0){
			foundSensorIndex = 1;
			break;
		}
	}
	return foundSensorIndex;
}

// int find_sensor_index(SensorList *sensorlist, char name[]){
// 	int foundSensorIndex = 0;
// 	for(int i = 0; i < sensorlist->NumSensors; i++){
// 		if(sensorlist->List[i].NameOfSensor == '\0') break; //protect from segfault
// 		if(strcmp(sensorlist->List[i].NameOfSensor, name) == 0){
// 			foundSensorIndex = 1;
// 			break;
// 		}
// 	}
// 	return foundSensorIndex;
// }

int find_sensornode_index(SensorNodeList *nodelist, char *sensornodename){
  printf("heree8\n");
  int nodeindex = 0;
  for(int i = 0; i < nodelist->NumSensorNodes; i++){
    if(strcmp(sensornodename,nodelist->List[i].SensorNodeLocation) == 0){
        nodeindex = 1;
        break;
    }
  }
  return nodeindex;
}

int find_sensor_index(SensorList *sensorlist, char name[]){
	printf("heree9\n");
	int foundSensorIndex = 0;
	for(int i = 0; i < MAX_SENSORS; i++){
		//if(sensorlist->List[i].NameOfSensor == '\0') break; //protect from segfault
		if(strcmp(sensorlist->List[i].NameOfSensor, name) == 0){
			foundSensorIndex = i;
			break;
		}
	}
	return foundSensorIndex;
}

//has not been tested for memory leaks or usage
void remove_sensor(SensorList *sensorlist, char name[]){
	printf("heree10\n");
	if(sensor_exists(sensorlist, name) == 0) return; //check that it exists because list starts from zero (aka returning zero can signify an index or doesnt exist)
	int sensorLocation = find_sensor_index(sensorlist, name);
	int sensorAmount = sensorlist->NumSensors;
	//free(sensorlist->List[sensorLocation].NameOfSensor);
	//free(sensorlist->List[sensorLocation].SensorType);
	for(int i = sensorLocation; i < sensorAmount ; i++){ //iterate until you found the sensor and then delete it
		if( i + 1 == sensorAmount){
		//TODO: add a free memory function or implementation
			free(sensorlist->List[i].SensorType);
			free(sensorlist->List[i].NameOfSensor);
			//this line below is probably wrong
			//sensorlist->List[i] = sensorlist->List[i + 1]; //delete sensor from list
			break;
		}
	}
	sensorlist->NumSensors -= 1;
}
void update_sensor_reading(SensorList *sensorlist, char name[], float sensorreading){
	printf("heree11\n");
	if(sensor_exists(sensorlist, name) == 0) return; //check that it exists because list starts from zero
	int index = find_sensor_index(sensorlist,name);
	sensorlist->List[index].SensorReading = sensorreading;
}
void print_sensor_list(SensorList *sensorlist){
	printf("heree12\n");
	printf("\n%s Sensor List\n", sensorlist->SensorNodeLocation);
	for(int i = 0; i < sensorlist->NumSensors; i++){
		printf("--- Sensor %d ---\n", i + 1);
		printf("Name: %s\n",sensorlist->List[i].NameOfSensor);
		printf("Type: %s\n",sensorlist->List[i].SensorType);
		printf("Reading: %f\n",sensorlist->List[i].SensorReading);
		printf("\n");
	}
}

void print_sensornode_list(SensorNodeList *nodelist){
	printf("heree13\n");
	for(int i = 0; i < nodelist->NumSensorNodes; i++){
		printf("****** SensorNode %d *****\n", i + 1);
		print_sensor_list(&nodelist->List[i]);
	}
}
