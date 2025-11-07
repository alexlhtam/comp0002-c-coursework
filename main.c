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

    while(myRobot.y != 1) {
        if (myRobot.dir == EAST) left(&myRobot);
        if (myRobot.dir == SOUTH) { left(&myRobot); left(&myRobot); }
        if (myRobot.dir == WEST) right(&myRobot);

        if (!canMoveForward(&myRobot, arena_height, arena_width, arena)) {
            right(&myRobot);
            if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                forward(&myRobot);
            }
            left(&myRobot);
        } else {
            forward(&myRobot);
        }

        clear();
        drawRobot(&myRobot);
        sleep(50);
    }

    while (myRobot.x != 1) {
        if (myRobot.dir == NORTH) left(&myRobot);
        if (myRobot.dir == EAST) { left(&myRobot); left(&myRobot); }
        if (myRobot.dir == SOUTH) right(&myRobot);

        if (!canMoveForward(&myRobot, arena_height, arena_width, arena)) {
             // sanity check
            right(&myRobot);
            if(canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                forward(&myRobot);
            }
            left(&myRobot);
        } else {
            forward(&myRobot);
        }
        
        clear();
        drawRobot(&myRobot);
        sleep(50);
    }

    int scanDirection = EAST; 
    
    while(!atMarker(&myRobot, arena_height, arena_width, arena)) {
        
        if (scanDirection == EAST) {
 
            while (myRobot.dir != EAST) {
                right(&myRobot); 
            }
            
            if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                forward(&myRobot);
            } else {
                // Hit the right wall, move down and reverse
                right(&myRobot);
                if(canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                   forward(&myRobot);
                }
                scanDirection = WEST;
            }

        } else if (scanDirection == WEST) {
            while (myRobot.dir != WEST) {
                left(&myRobot);
            } 

            if (canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                forward(&myRobot);
            } else {
                left(&myRobot);
                if(canMoveForward(&myRobot, arena_height, arena_width, arena)) {
                   forward(&myRobot);
                }
                scanDirection = EAST;
            }
        }

        clear();
        drawRobot(&myRobot);
        sleep(50);
    }

    pickUpMarker(&myRobot, arena_height, arena_width, arena);
    
    clear();
    drawRobot(&myRobot);
    sleep(50);

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
        sleep(50);
    }

    dropMarker(&myRobot, arena_height, arena_width, arena);
    clear();
    drawRobot(&myRobot);

    return 0;
}


