dungeon: dungeon.o map.o pqueue.o dijkstra.o
	g++ dungeon.o map.o pqueue.o dijkstra.o -std=c++11 -g -o dungeon
	
dungeon.o: dungeon.cpp libs/map.hpp
	g++ dungeon.cpp -std=c++11 -g -c
	
map.o: libs/map.cpp libs/structs.hpp
	g++ libs/map.cpp -std=c++11 -g -c

pqueue.o: libs/pqueue.cpp
	g++ libs/pqueue.cpp -std=c++11 -g -c

dijkstra.o: libs/dijkstra.cpp
	g++ libs/dijkstra.cpp -std=c++11 -g -c
	
clean:
	rm -f *.o dungeon fc
