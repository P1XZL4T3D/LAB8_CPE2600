	CC = gcc
CFLAGS = -Wall
SOURCES = main.c vectorcalc.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = vectorcalc

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)