dungeon: dungeon.o map.o pqueue.o dijkstra.o display.o game.o parser.o
	g++ dungeon.o map.o pqueue.o dijkstra.o display.o game.o parser.o -std=c++11 -lncurses -g -o dungeon
	
dungeon.o: dungeon.cpp
	g++ dungeon.cpp -std=c++11 -g -c
	
map.o: libs/map.cpp
	g++ libs/map.cpp -std=c++11 -g -c

pqueue.o: libs/pqueue.cpp
	g++ libs/pqueue.cpp -std=c++11 -g -c

dijkstra.o: libs/dijkstra.cpp
	g++ libs/dijkstra.cpp -std=c++11 -g -c
	
display.o: libs/display.cpp
	g++ libs/display.cpp -std=c++11 -lncurses -g -c
	
game.o: libs/game.cpp
	g++ libs/game.cpp -std=c++11 -g -c 
	
parser.o: libs/parser.cpp
	g++ libs/parser.cpp -std=c++11 -g -c 
	
clean:
	rm -f *.o dungeon fc
