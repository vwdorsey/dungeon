CC=g++
CFLAGS= -std=c++11 -ggdb -lncurses
LDFLAGS= -std=c++11 -ggdb -lncurses

OBJECTS=dungeon.o map.o pqueue.o dijkstra.o display.o game.o parser.o dice.o character.o object.o char_template.o obj_template.o
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
