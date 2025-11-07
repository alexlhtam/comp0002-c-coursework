#ifndef ARENA_H
#define ARENA_H

#define TILE_SIZE 40

#define TILE_EMPTY 0
#define TILE_WALL 1
#define TILE_MARKER 2


void initArena(int height, int width, int arena[height][width]);

void drawArena(int height, int width, int arena[height][width]);

#endif