CFLAGS = -Wall -Werror -pedantic -g
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

musicsort: $(OBJ)
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
