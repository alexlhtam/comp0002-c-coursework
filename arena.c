#include "graphics.h"
#include "arena.h"
#include <stdlib.h>



void initArena(int height, int width, int arena[height][width]) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                arena[y][x] = TILE_WALL;
            } else {
                arena[y][x] = TILE_EMPTY;
            }
        }
    }

    int marker_x = (rand() % (width - 2)) + 1;
    int marker_y = (rand() % (height - 2)) + 1;

    arena[marker_y][marker_x] = TILE_MARKER;
}

void drawArena(int height, int width, int arena[height][width]) {
    background();

    setColour(white);
    fillRect(0, 0, width * TILE_SIZE, height * TILE_SIZE);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
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
    for (int i = 0; i <= width; i++) {
        drawLine(i * TILE_SIZE, 0, i * TILE_SIZE, height * TILE_SIZE);
    }
    for (int i = 0; i <= height; i++) {
        drawLine(0, i * TILE_SIZE, width * TILE_SIZE, i * TILE_SIZE);
    }

    foreground();
}