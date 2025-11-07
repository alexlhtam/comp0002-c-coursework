#include "graphics.h"
#include "robot.h"
#include "arena.h"
#include <stdlib.h>

void initRobot(Robot* robot, int height, int width, int arena[height][width]) {
    int isNextToWall;

    do {
        robot->x = (rand() % (width - 2)) + 1;
        robot->y = (rand() % (height - 2)) + 1;
    
        isNextToWall = 0; // Assume it's not
        if (arena[robot->y - 1][robot->x] == TILE_WALL) isNextToWall = 1;
        if (arena[robot->y + 1][robot->x] == TILE_WALL) isNextToWall = 1;
        if (arena[robot->y][robot->x - 1] == TILE_WALL) isNextToWall = 1;
        if (arena[robot->y][robot->x + 1] == TILE_WALL) isNextToWall = 1;

        // don't let robot start on marker
        if (arena[robot->y][robot->x] == TILE_MARKER) isNextToWall = 1;

    } while (isNextToWall);

    robot->dir = rand() % 4;
    robot->markersCarried = 0;
}

void drawRobot(Robot* robot) {
    int center_x = robot->x * TILE_SIZE + TILE_SIZE / 2;
    int center_y = robot->y * TILE_SIZE + TILE_SIZE / 2;

    int x_coords[3];
    int y_coords[3];

    if (robot->dir == NORTH) {
        x_coords[0] = center_x;      y_coords[0] = center_y - 12; // tip
        x_coords[1] = center_x - 8;  y_coords[1] = center_y + 8;  // b-left
        x_coords[2] = center_x + 8;  y_coords[2] = center_y + 8;  // b-right
    } else if (robot->dir == EAST) {
        x_coords[0] = center_x + 12; y_coords[0] = center_y;      // tip
        x_coords[1] = center_x - 8;  y_coords[1] = center_y - 8;  // t-left
        x_coords[2] = center_x - 8;  y_coords[2] = center_y + 8;  // b-left
    } else if (robot->dir == SOUTH) {
        x_coords[0] = center_x;      y_coords[0] = center_y + 12; // tip
        x_coords[1] = center_x - 8;  y_coords[1] = center_y - 8;  // t-left
        x_coords[2] = center_x + 8;  y_coords[2] = center_y - 8;  // t-right
    } else { 
        x_coords[0] = center_x - 12; y_coords[0] = center_y;      // tip
        x_coords[1] = center_x + 8;  y_coords[1] = center_y - 8;  // t-right
        x_coords[2] = center_x + 8;  y_coords[2] = center_y + 8;  // b-right
    }

    setColour(blue);
    fillPolygon(3, x_coords, y_coords);
}

void left(Robot* robot) {
    switch (robot->dir) { // c is weird with negatives???
        case NORTH: robot->dir = WEST;   break;
        case WEST:  robot->dir = SOUTH;  break;
        case SOUTH: robot->dir = EAST;   break;
        case EAST:  robot->dir = NORTH;  break;
    }
}

void right(Robot* robot) {
    robot->dir = (robot->dir + 1) % 4;
}

int canMoveForward(Robot* robot, int height, int width, int arena[height][width]) {
    int next_x = robot->x;
    int next_y = robot->y;

    if (robot->dir == NORTH)  next_y--;
    if (robot->dir == EAST)   next_x++;
    if (robot->dir == SOUTH)  next_y++;
    if (robot->dir == WEST)   next_x--;

    if (arena[next_y][next_x] == TILE_WALL) {
        return 0;
    }

    // check for other obstacles in the future

    return 1;
}

void forward(Robot* robot) {
    if (robot->dir == NORTH) robot->y--;
    if (robot->dir == EAST)  robot->x++;
    if (robot->dir == SOUTH) robot->y++;
    if (robot->dir == WEST)  robot->x--;
}

int atMarker(Robot* robot, int height, int width, int arena[height][width]) {
    (void)height;
    (void)width;
    if (arena[robot->y][robot->x] == TILE_MARKER) {
        return 1;
    }
    return 0;
}

void drawTile(int x, int y) {
    background();

    setColour(white);
    fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    setColour(lightgray);
    setLineWidth(1);
    drawRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    foreground();
}

void pickUpMarker(Robot* robot, int height, int width, int arena[height][width]) {
    (void)height;
    (void)width;

    if (arena[robot->y][robot->x] == TILE_MARKER) {
        arena[robot->y][robot->x] = TILE_EMPTY;
        robot->markersCarried++;
        drawTile(robot->x, robot->y);
    }
}

void dropMarker(Robot* robot, int height, int width, int arena[height][width]) {
    (void)height;
    (void)width;
    if (robot->markersCarried > 0) {
        arena[robot->y][robot->x] = TILE_MARKER;
        robot->markersCarried--;

        background();
        setColour(gray);
        fillOval(robot->x * TILE_SIZE + 5, robot->y * TILE_SIZE + 5, TILE_SIZE - 10, TILE_SIZE - 10);
        foreground();
    }
}

int isAtCorner(Robot* robot, int height, int width) {
    // top left
    if (robot->x == 1 && robot->y == 1) return 1;
    // top right
    if (robot->x == width - 2 && robot->y == 1) return 1;
    // bottom left
    if (robot->x == 1 && robot->y == height - 2) return 1;
    // bottom right
    if (robot->x == width - 2 && robot->y == height - 2) return 1;

    return 0;
}