CFLAGS = -Wall -Werror -pedantic -g -ansi

string: main.o string.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
