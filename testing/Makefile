SRC=Arboretum_Backend.c
OBJ=$(SRC:%.c=%.o)
EXE=Arboretum_Backend

run: compile
	./$(EXE) 1234

compile:
	gcc -c -Wall -Werror -Wpedantic -std=c99 $(SRC)
	gcc -o $(EXE) $(OBJ)

clean:
	rm -f *.o

spotless: clean
	rm -f Arboretum_Backend
