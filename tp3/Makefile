CFLAGS = -Wall -Werror -pedantic -g -ansi

main: main.o fct.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
