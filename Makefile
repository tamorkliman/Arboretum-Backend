CC = gcc
CFLAGS=-Wall -std=c99

main: main.o Sensor_List.o
	$(CC) -o main Arboretum-Backend.c.o Sensor_List.o Ping_Sensors.o parser.o $(CFLAGS)

clean:
	rm *.o testsensorlist
