CFLAGS = -Wall -Werror -pedantic -g -ansi

hello.exe: hello.o main.o
	gcc -o hello.exe hello.o main.o

hello.o: hello.c
	gcc -c hello.c

main.o: hello.c main.c
	gcc -c main.c

clean:
	rm -f *.o
