<<<<<<< HEAD
SRC=Arboretum_Backend.c parser.h Sensor_List.h Ping_Sensors.h 
OBJ=$(SRC:%.c=%.o)
EXE=Arboretum_Backend

CFLAGS=-g -Wall -Werror -Wpedantic
CFLAGS+=`mysql_config --cflags`
LFLAGS=`mysql_config --libs`

#run: compile
#	./$(EXE) 1234

compile:
	gcc $(SRC) -c $(CFLAGS)
	gcc $(OBJ) -o $(EXE) $(LFLAGS)
	#gcc $(SRC) -o $(EXE) $(CFLAGS) $(LFLAGS)

clean:
	rm -f *.o

spotless: clean
	rm -f Arboretum_Backend

cn: cn
	netstat -tulpn
=======
CC = gcc
CFLAGS=-Wall -std=c99

main: main.o Sensor_List.o
	$(CC) -o main Arboretum-Backend.c.o Sensor_List.o Ping_Sensors.o parser.o $(CFLAGS)

clean:
	rm *.o testsensorlist
>>>>>>> b928890d4b2e4b9cfea5a4e986082324300610db
