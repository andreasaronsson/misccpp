CC = g++
CFLAGS = -g -W -Wall -pedantic -Wpointer-arith -std=gnu99

EXEC = run

OBJS := ett.o


all:	$(EXEC)

$(EXEC):	$(OBJS)
			@echo "Linking" $@
			$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

