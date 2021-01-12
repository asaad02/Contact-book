CC = gcc
CFLAGS = -Wall -ansi -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)contactList.o $(BINDIR)contactHelper.o
	$(CC) $(BINDIR)contactList.o $(BINDIR)contactHelper.o -o $@

$(BINDIR)contactList.o: $(SRCDIR)contactList.c
	$(CC) $(CFLAGS) -c $(SRCDIR)contactList.c -o $@
	
$(BINDIR)contactHelper.o: $(SRCDIR)contactHelper.c
	$(CC) $(CFLAGS) -c $(SRCDIR)contactHelper.c -o $@
	
run:
	$(BINDIR)contactList
	
clean: 
	rm ./bin/*.o ./contactList $(BINDIR)*.db
