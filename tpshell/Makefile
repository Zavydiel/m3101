CFLAGS = -Wall -Werror -pedantic -g -ansi
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

main: $(OBJ) ligne_commande.o
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o
