#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "arena.h"
#include "robot.h"


int main(int argc, char **argv) {
    srand(time(NULL));
    
    (void)argc;
    (void)argv;

    int arena_height = (rand() % 10) + 10;
    int arena_width = (rand() % 10) + 10;
    int arena[arena_height][arena_width];

    Robot myRobot;

    initArena(arena_height, arena_width, arena);
    initRobot(&myRobot, arena_height, arena_width, arena);

    setWindowSize(arena_width * TILE_SIZE, arena_height * TILE_SIZE);
    
    drawArena(arena_height, arena_width, arena);

    while(!atMarker(&myRobot, arena_height, arena_width, arena)) {
        // if (canMoveForward(&myRobot)) {
        //     forward(&myRobot);
        // } else {
        //     right(&myRobot);
        // }

        /**
         * wall-follower algorithm
         */
        if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
            forward(&myRobot);
        } else {
            left(&myRobot);
            
            if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                forward(&myRobot);
            } else {
                left(&myRobot);
            }
        }

        clear();
        drawRobot(&myRobot);
        sleep(200);
    }

    pickUpMarker(&myRobot, arena_height, arena_width, arena);
    
    clear();
    drawRobot(&myRobot);
    sleep(500);

    while(!isAtCorner(&myRobot, arena_height, arena_width)) {
        if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
            forward(&myRobot);
        } else {
            left(&myRobot);

            if (canMoveForward(&myRobot,arena_height, arena_width, arena)) {
                forward(&myRobot);
            } else {
                left(&myRobot);
            }
        }

        clear();
        drawRobot(&myRobot);
        sleep(200);
    }

    dropMarker(&myRobot, arena_height, arena_width, arena);

    clear();
    drawRobot(&myRobot);

    return 0;
}


