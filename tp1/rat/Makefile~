CFLAGS = -Wall -Werror -pedantic -g -ansi

tab: tableau.o main.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
gcc -c $(CFLAGS) $^

clean:
	rm -f *.o

ratdoto: rat.o 
