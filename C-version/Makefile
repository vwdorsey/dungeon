dungeon: dungeon-main.o generation.o tile.o room.o fileio.o path.o queue.o game.o display.o 
	gcc dungeon-main.o generation.o tile.o room.o fileio.o path.o queue.o game.o display.o -g -o dungeon -lncurses

dungeon-main.o: dungeon-main.c libs/generation.h libs/tile.h libs/room.h libs/fileio.h libs/path.h
	gcc -Wall dungeon-main.c -g -c

generation.o: libs/generation.h libs/generation.c libs/tile.h libs/room.h
	gcc -Wall -Werror libs/generation.c -g -c

tile.o: libs/tile.h libs/tile.c
	gcc -Wall -Werror libs/tile.c -g -c
	
room.o: libs/room.h libs/room.c
	gcc -Wall -Werror libs/room.c -g -c
	
fileio.o: libs/fileio.c libs/fileio.h libs/tile.h libs/room.h
	gcc -Wall -Werror libs/fileio.c -g -c
	
path.o: libs/path.c libs/path.h libs/queue.h libs/tile.h
	gcc -Wall libs/path.c -g -c

queue.o: libs/queue.c libs/queue.h
	gcc -Wall -Werror libs/queue.c -g -c
	
game.o: libs/game.c libs/queue.h libs/game.h libs/tile.h
	gcc -Wall -Werror libs/game.c -g -c
	
display.o: libs/display.c libs/display.h libs/defs.h
	gcc -Wall -Werror libs/display.c -g -c -lncurses
	
clean:
	rm -f *.o dungeon fc
