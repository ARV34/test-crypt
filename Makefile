# Arestov Roman <arv34@mail.ru>

CC = gcc
CFLAGS += -c -Wall -O2
LFLAGS += -lcrypto -lssl

all: crypt

crypt: main.o user_interface.o file_io.o cryption.o
	$(CC) main.o user_interface.o file_io.o cryption.o -o crypt $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

user_interface.o: user_interface.c
	$(CC) $(CFLAGS) user_interface.c

file_io.o: file_io.c
	$(CC) $(CFLAGS) file_io.c
	
cryption.o: cryption.c
	$(CC) $(CFLAGS) cryption.c

clean:
	rm -rf *.o crypt
