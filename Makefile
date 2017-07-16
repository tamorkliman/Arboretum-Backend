

run: compile
	./Arboretum_Backend 7777

compile:
	gcc -c -Wall -Werror -Wpedantic -std=c99 *.c
	gcc -o Arboretum_Backend *.o

clean:
	rm -f *.o

spotless: clean
	rm -f Arboretum_Backend
