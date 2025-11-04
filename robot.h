#ifndef ROBOT_H
#define ROBOT_H

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

void initRobot(Robot* robot);

void drawRobot(Robot* robot);

void left(Robot* robot);

void right(Robot* robot);

void forward(Robot* robot);

int canMoveForward(Robot* robot);

int atMarker(Robot* robot);

#endif