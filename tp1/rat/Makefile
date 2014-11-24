CFLAGS = -Wall -Werror -pedantic -g -ansi

rat: main.o rat.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
