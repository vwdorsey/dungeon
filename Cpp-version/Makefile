CC=g++
CFLAGS= -std=c++11 -g -lncurses
LDFLAGS= -std=c++11 -g -lncurses

SOURCES=dungeon.cpp libs/map.cpp libs/pqueue.cpp libs/dijkstra.cpp libs/display.cpp libs/game.cpp libs/parser.cpp
OBJECTS=dungeon.o map.o pqueue.o dijkstra.o display.o game.o parser.o
EXECUTABLE=dungeon

define compcom
	$(CC) $(CFLAGS) -c $<
endef

all: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(compcom)

%.o: libs/%.cpp 
	$(compcom)
    
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) fc
