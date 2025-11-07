#ifndef ROBOT_H
#define ROBOT_H

#include "arena.h"

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef struct {
    int x;
    int y;
    Direction dir;
    int markersCarried;
} Robot;

void initRobot(Robot* robot, int height, int width, int arena[height][width]);

void drawRobot(Robot* robot);

void left(Robot* robot);

void right(Robot* robot);

void forward(Robot* robot);

int canMoveForward(Robot* robot, int height, int width ,int arena[height][width]);

int atMarker(Robot* robot, int height, int width, int arena[height][width]);

void pickUpMarker(Robot* robot, int height, int width, int arena[height][width]);

void dropMarker(Robot* robot, int height, int width, int arena[height][width]);

int isAtCorner(Robot* robot, int height, int width);

#endif