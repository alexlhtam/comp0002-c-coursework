#ifndef ARENA_H
#define ARENA_H

#define ARENA_WIDTH 15
#define ARENA_HEIGHT 15

#define TILE_SIZE 40

#define TILE_EMPTY 0
#define TILE_WALL 1
#define TILE_MARKER 2

extern int arena[ARENA_HEIGHT][ARENA_WIDTH];

void initArena(void);

void drawArena(void);

#endif