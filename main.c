#include <stdio.h>
#include "graphics.h"
#include "arena.h"
#include "robot.h"

#define WINDOW_WIDTH (ARENA_WIDTH * TILE_SIZE)
#define WINDOW_HEIGHT (ARENA_HEIGHT * TILE_SIZE)

int main(int argc, char **argv) {
    Robot myRobot;

    (void)argc;
    (void)argv;

    initArena();
    initRobot(&myRobot);
    setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    drawArena();

    while(!atMarker(&myRobot)) {
        // if (canMoveForward(&myRobot)) {
        //     forward(&myRobot);
        // } else {
        //     right(&myRobot);
        // }

        clear();

        drawRobot(&myRobot);
        sleep(200);

        /**
         * wall-follower algorithm
         */
        if (canMoveForward(&myRobot)) {
            forward(&myRobot);
        } else {
            left(&myRobot);

            if (canMoveForward(&myRobot)) {
                forward(&myRobot);
            } else {
                left(&myRobot);
            }
            
        }
    }

    clear();
    drawRobot(&myRobot);

    return 0;
}


