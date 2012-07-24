OBJS=main.o
CFLAGS=-Wall -g -O
CC=gcc
main:$(OBJS)
	$(CC) $(OBJS) -o main
$(OBJS):%o:%c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -fr *.o *.~ main
