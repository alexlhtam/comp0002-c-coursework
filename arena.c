#include "graphics.h"
#include "arena.h"
#include <stdlib.h>

int arena[ARENA_HEIGHT][ARENA_WIDTH];

void initArena(void) {
    for (int y = 0; y < ARENA_HEIGHT; y++) {
        for (int x = 0; x < ARENA_WIDTH; x++) {
            if (y == 0 || y == ARENA_HEIGHT - 1 || x == 0 || x == ARENA_WIDTH - 1) {
                arena[y][x] = TILE_WALL;
            } else {
                arena[y][x] = TILE_EMPTY;
            }
        }
    }

    int marker_x, marker_y;
    int wallSide = rand() % 4; // 0=top, 1=right, 2=bottom, 3=left

    if (wallSide == 0) { // Top wall
        marker_x = (rand() % (ARENA_WIDTH - 2)) + 1; 
        marker_y = 1; 
    } else if (wallSide == 1) {
        marker_x = ARENA_WIDTH - 2;
        marker_y = (rand() % (ARENA_HEIGHT - 2)) + 1;
    } else if (wallSide == 2) {
        marker_x = (rand() % (ARENA_WIDTH - 2)) + 1;
        marker_y = ARENA_HEIGHT - 2;
    } else {
        marker_x = 1;
        marker_y = (rand() % (ARENA_HEIGHT - 2)) + 1;
    }

    arena[marker_y][marker_x] = TILE_MARKER;
}

void drawArena(void) {
    background();

    for (int y = 0; y < ARENA_HEIGHT; y++) {
        for (int x = 0; x < ARENA_WIDTH; x++) {
            int pixel_x = x * TILE_SIZE;
            int pixel_y = y * TILE_SIZE;

            if (arena[y][x] == TILE_WALL) {
                setColour(red);
                fillRect(pixel_x, pixel_y, TILE_SIZE, TILE_SIZE);
            } else if (arena[y][x] == TILE_MARKER) {
                setColour(gray);
                fillOval(pixel_x + 5, pixel_y + 5, TILE_SIZE - 5, TILE_SIZE - 10);
            }
        }
    }

    setColour(lightgray);
    setLineWidth(1);
    for (int i = 0; i <= ARENA_WIDTH; i++) {
        drawLine(i * TILE_SIZE, 0, i * TILE_SIZE, ARENA_HEIGHT * TILE_SIZE);
    }
    for (int i = 0; i <= ARENA_HEIGHT; i++) {
        drawLine(0, i * TILE_SIZE, ARENA_WIDTH * TILE_SIZE, i * TILE_SIZE);
    }

    foreground();
}