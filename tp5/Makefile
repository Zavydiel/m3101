CFLAGS = -Wall -Werror -pedantic -g -ansi

main: main.o tag.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
