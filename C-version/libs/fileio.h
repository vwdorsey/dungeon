#ifndef FILEIO_H
#define FILEIO_H

#include "tile.h"
#include "room.h"

typedef struct tile t_tile;

void write_save_file(t_tile *map, roominfo *rooms);
void read_load_file(t_tile *loaded_map, roominfo *rooms);

#endif
