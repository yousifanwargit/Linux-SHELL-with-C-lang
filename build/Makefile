CC=gcc
CFLAGS=-c
LDFLAGS=-o
EXECUTABLE=myshell
OBJECTS=femto-shell.o functions.o neofetch.o
SOURCES=../femto-shell.c ../functions/functions.c ../neofetch/neofetch.c

$(EXECUTABLE): femto-shell.o functions.o neofetch.o
	$(CC) $^ $(LDFLAGS) $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $^


clean:
	rm $(OBJECTS)

install:
	cp $(EXECUTABLE) /usr/bin

uninstall: 
	rm /usr/bin/$(EXECUTABLE)