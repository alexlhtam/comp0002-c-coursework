#include "graphics.h"
#include "robot.h"
#include "arena.h"

void initRobot(Robot* robot) {
    robot->x = 2;
    robot->y = 2;
    robot->dir = EAST;
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

int canMoveForward(Robot* robot) {
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
    if (canMoveForward(robot)) {
        if (robot->dir == NORTH) robot->y--;
        if (robot->dir == EAST)  robot->x++;
        if (robot->dir == SOUTH) robot->y++;
        if (robot->dir == WEST)  robot->x--;
    }
}

int atMarker(Robot* robot) {
    if (arena[robot->y][robot->x] == TILE_MARKER) {
        return 1;
    }
    return 0;
}