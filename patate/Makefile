CFLAGS = -Wall -Werror -g
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

patate: $(OBJ)
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
