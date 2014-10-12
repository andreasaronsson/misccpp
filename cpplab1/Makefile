CC = g++
CFLAGS = -g -W -Wall -pedantic -Wpointer-arith -std=gnu99

EXEC = run

OBJS := song.o
OBJS += rfile.o
OBJS += queries.o
OBJS += compare.o
OBJS += albums.o
OBJS += album.o

all:	$(EXEC)

$(EXEC):	$(OBJS)
			@echo "Linking" $@
			$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

