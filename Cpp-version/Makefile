CC=g++
CFLAGS= -std=c++11 -g -c -lncurses
LDFLAGS= -std=c++11 -g -lncurses
SOURCES=dungeon.cpp libs/map.cpp libs/pqueue.cpp libs/dijkstra.cpp libs/display.cpp libs/game.cpp libs/parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dungeon.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< $@
    
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) fc