#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define main __student_main_function_
#define _ONLINE_JUDGE

///////////// INSERT YOUR CODE BELOW /////////////

///////////// INSERT YOUR CODE ABOVE /////////////

#include "hw4_utils.h"

#undef main

int main() {
    for(int tcase = 1; tcase <= 10; tcase++) {
        switch (tcase) {
            case 1: // Add ghosts
            {
                // Ghost on empty cells
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddGhost(g, 3, 5, left) == true);
                OJ_ASSERT(AddGhost(g, 2, 1, up) == true);
                OJ_ASSERT(g->grid[2][1] == '@');
                OJ_ASSERT(g->grid[3][5] == '@');
                OJ_ASSERT(AddFood(g, 3, 5) == false);
                EndGame(g);
    
                // Ghost at invalid places
                g = NewGame(8, 10);
                OJ_ASSERT(AddGhost(g, 8, 10, left) == false);
                OJ_ASSERT(AddWall(g, 2, 1) == true);
                OJ_ASSERT(AddGhost(g, 2, 1, up) == false);
                OJ_ASSERT(AddPacman(g, 3, 5) == true);
                OJ_ASSERT(AddGhost(g, 3, 5, down) == false);
                OJ_ASSERT(g->grid[2][1] != '@');
                OJ_ASSERT(g->grid[3][5] != '@');
                EndGame(g);
                
                // Ghost on foods 
                g = NewGame(8, 10);
                OJ_ASSERT(AddGhost(g, 3, 5, left) == true);
                OJ_ASSERT(AddFood(g, 2, 1) == true);
                for(int i = 0; i < 10; i++){
                    OJ_ASSERT(AddFood(g, 4, i) == true);
                }
                OJ_ASSERT(g->foodCount == 11);
                OJ_ASSERT(AddGhost(g, 2, 1, up) == true);
                OJ_ASSERT(g->grid[2][1] == '@');
                OJ_ASSERT(g->foodCount == 11);
                OJ_ASSERT(g->grid[3][5] == '@');
                OJ_ASSERT(AddFood(g, 3, 5) == false);
                EndGame(g);
                break;
            }
            case 2: // Move ghosts on an empty board
            {
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 2, left) == true);
                MoveGhosts(g);
                OJ_ASSERT(g->grid[3][5] == '@');
                OJ_ASSERT(g->grid[4][1] == '@');
                OJ_ASSERT(g->grid[3][4] != '@');
                OJ_ASSERT(g->grid[4][2] != '@');
    
                MoveGhosts(g);
                OJ_ASSERT(g->grid[3][4] == '@');
                OJ_ASSERT(g->grid[4][0] == '@');
                OJ_ASSERT(g->grid[3][5] != '@');
                OJ_ASSERT(g->grid[4][1] != '@');
    
                MoveGhosts(g);
                OJ_ASSERT(g->grid[3][3] == '@');
                OJ_ASSERT(g->grid[4][1] == '@');
                OJ_ASSERT(g->grid[3][4] != '@');
                OJ_ASSERT(g->grid[3][5] != '@');
                OJ_ASSERT(g->grid[4][0] != '@');
                OJ_ASSERT(g->grid[4][2] != '@');
                EndGame(g);
    
                break;
            }
            case 3: // Losing the game
            {
                // Pacman bumps into a ghost
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 2, left) == true);
                OJ_ASSERT(AddPacman(g, 2, 4) == true);
                MovePacman(g, down);
                OJ_ASSERT(g->grid[3][4] == '@');
                OJ_ASSERT(g->state == losing);
                EndGame(g);
    
                // Ghost kills Pacman
                g = NewGame(6, 6);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 2, left) == true);
                OJ_ASSERT(AddPacman(g, 3, 5) == true);
                MovePacman(g, idle);
                OJ_ASSERT(g->state != losing);
                MoveGhosts(g);
                OJ_ASSERT(g->grid[3][5] == '@');
                OJ_ASSERT(g->state == losing);
                EndGame(g);
    
                // They move towards a same grid
                g = NewGame(6, 6);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                OJ_ASSERT(AddGhost(g, 3, 5, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 2, left) == true);
                OJ_ASSERT(AddPacman(g, 2, 4) == true);
                MovePacman(g, down);
                OJ_ASSERT(g->state != losing);
                MoveGhosts(g);
                OJ_ASSERT(g->grid[3][4] == '@');
                OJ_ASSERT(g->state == losing);
    			EndGame(g);
                break;
            }
            case 4: // Ghosts with foods, and Pacman.
            {
                // Ghost moving on foods
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddFood(g, 3, 1) == true);
                OJ_ASSERT(AddFood(g, 3, 3) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(AddFood(g, 4, 1) == true);
                OJ_ASSERT(AddFood(g, 5, 1) == true);
                OJ_ASSERT(AddGhost(g, 4, 1, down) == true);
                OJ_ASSERT(g->foodCount == 5);
                /* ______
                  |      |
                  |      |
                  |      |
                  | . .@.|
                  | @    |
                  | .    |
                  \------/
                */
    
                MoveGhosts(g);
                /* ______
                  |      |
                  |      |
                  |      |
                  | . . @|
                  | .    |
                  | @    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][5] == '@' && g->grid[5][1] == '@');
                OJ_ASSERT(g->grid[3][4] == ' ' && g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[3][1] == '.' && g->grid[3][3] == '.');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  |      |
                  |      |
                  | . .@.|
                  | @    |
                  | .    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][4] == '@' && g->grid[4][1] == '@');
                OJ_ASSERT(g->grid[3][5] == '.' && g->grid[5][1] == '.');
                OJ_ASSERT(g->grid[3][1] == '.' && g->grid[3][3] == '.');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  |      |
                  |      |
                  | @ @ .|
                  | .    |
                  | .    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][3] == '@' && g->grid[3][1] == '@');
                OJ_ASSERT(g->grid[3][4] == ' ' && g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[5][1] == '.' && g->grid[3][5] == '.');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  |      |
                  | @    |
                  | .@. .|
                  | .    |
                  | .    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][2] == '@' && g->grid[2][1] == '@');
                OJ_ASSERT(g->grid[3][3] == '.' && g->grid[3][1] == '.');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  | @    |
                  |      |
                  | @ . .|
                  | .    |
                  | .    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][1] == '@' && g->grid[1][1] == '@');
                OJ_ASSERT(g->grid[3][2] == ' ' && g->grid[2][1] == ' ');
                EndGame(g);
    
                // Eat food along ghost trail
                g = NewGame(8, 10);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                OJ_ASSERT(AddFood(g, 0, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 2) == true);
                OJ_ASSERT(AddGhost(g, 0, 3, left) == true);
                OJ_ASSERT(AddWall(g, 0, 4) == true);
                OJ_ASSERT(g->foodCount == 2);
                /* ______
                  |C..@# |
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
    
                MovePacman(g, down);
                MoveGhosts(g);
                /* ______
                  | .@ # |
                  |C     |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->grid[1][0] == 'C' && g->grid[0][1] == '.' && g->grid[0][2] == '@' && g->grid[0][3] == ' ');
    
                MovePacman(g, idle);
                MoveGhosts(g);
                /* ______
                  | @. # |
                  |C     |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->grid[1][0] == 'C' && g->grid[0][1] == '@' && g->grid[0][2] == '.' && g->grid[0][3] == ' ');
                
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                /* ______
                  | @. # |
                  |C     |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->grid[1][0] == 'C' && g->grid[0][1] == '@' && g->grid[0][2] == '.' && g->grid[0][3] == ' ');
                            
                MovePacman(g, up);
                MoveGhosts(g);            
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  | C.@# |
                  |      |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 1);
                OJ_ASSERT(g->grid[0][0] == ' ' && g->grid[0][1] == 'C' && g->grid[0][2] == '.' && g->grid[0][3] == '@');
                            
                MovePacman(g, down);
                MoveGhosts(g);            
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  | @. # |
                  |  C   |
                  |      |
                  |      |
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 1);
                OJ_ASSERT(g->grid[1][2] == 'C' && g->grid[0][1] == '@' && g->grid[0][2] == '.' && g->grid[0][3] == ' ');
    
                MovePacman(g, up);
                OJ_ASSERT(g->foodCount == 0);
                OJ_ASSERT(g->state == winning);
    
                EndGame(g);
                break;
    
    
            }
            case 5: // Ghost hitting walls and ghosts
            {
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 5, 4, up) == true);
                OJ_ASSERT(AddWall(g, 3, 3) == true);
    
                OJ_ASSERT(AddFood(g, 3, 1) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(AddFood(g, 4, 1) == true);
                OJ_ASSERT(AddFood(g, 5, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                
                OJ_ASSERT(AddGhost(g, 2, 2, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 1, down) == true);
                OJ_ASSERT(AddWall(g, 2, 3) == true)
                OJ_ASSERT(g->foodCount == 5);
                /* ______
                  |.     |
                  |      |
                  |  @#  |
                  | . #@.|
                  | @    |
                  | .  @ |
                  \------/
                */
    
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  | @ #  |
                  | . # @|
                  | .  @ |
                  | @    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][5] == '@' && g->grid[5][1] == '@' && g->grid[4][4] == '@' && g->grid[2][1] == '@');
    
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  |@  #  |
                  | . #@.|
                  | @    |
                  | .  @ |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->grid[3][4] == '@' && g->grid[4][1] == '@' && g->grid[5][4] == '@' && g->grid[2][0] == '@');
                OJ_ASSERT(g->grid[3][5] == '.' && g->grid[5][1] == '.');
    
                MoveGhosts(g);
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  | @@#  |
                  | . #@.|
                  | .    |
                  | .  @ |
                  \------/
                */
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[2][2] == '@' && g->grid[2][0] != '@');
    
                MoveGhosts(g);
                /* ______
                  |.     |
                  | @    |
                  |  @#  |
                  | . # @|
                  | .  @ |
                  | .    |
                  \------/
                */
                OJ_ASSERT(g->grid[1][1] == '@' && g->grid[2][2] == '@' && g->grid[2][1] != '@');
                MoveGhosts(g);
                /* ______
                  |.@    |
                  |      |
                  | @ #  |
                  | . #@.|
                  | .    |
                  | .  @ |
                  \------/
                */
                OJ_ASSERT(g->grid[0][1] == '@' && g->grid[2][1] == '@');
                EndGame(g);
    
                // multiple collisions         
                g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 3, 2, right) == true);
                OJ_ASSERT(AddGhost(g, 3, 1, up) == true);
                OJ_ASSERT(AddWall(g, 3, 3) == true);
                OJ_ASSERT(AddWall(g, 4, 1) == true);
                OJ_ASSERT(AddWall(g, 1, 1) == true);
                /* ______
                  |      |
                  | #    |
                  |      |
                  | @@#  |
                  | #    |
                  |      |
                  \------/
                */
    
                MoveGhosts(g);
                /* ______
                  |      |
                  | #    |
                  | @    |
                  |  @#  |
                  | #    |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[3][2] == '@' && g->grid[3][1] == ' ');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  | #    |
                  | @    |
                  | @ #  |
                  | #    |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[3][1] == '@');
    
                MoveGhosts(g);
                /* ______
                  |      |
                  | #    |
                  |      |
                  |@@ #  |
                  | #    |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->grid[3][1] == '@' && g->grid[3][0] == '@');
                
                MoveGhosts(g);
                /* ______
                  |      |
                  | #    |
                  | @    |
                  |@  #  |
                  | #    |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[3][0] == '@' && g->grid[3][1] == ' ');
                EndGame(g);
                break;
                
            }
            case 6: // Add capsules
            {
                // Add capsules on empty cells
                Game* g = NewGame(6, 6);
                for(int i = 0; i < 6; i++){
                    OJ_ASSERT(AddFood(g, 2, i) == true);
                }
                OJ_ASSERT(g->foodCount == 6);
                OJ_ASSERT(AddCapsule(g, 1, 1) == true);
                OJ_ASSERT(AddCapsule(g, 1, 1) == false);
                OJ_ASSERT(g->foodCount == 7);
    
                // Add capsules on invalid places
                OJ_ASSERT(AddCapsule(g, 6, 6) == false);
                OJ_ASSERT(AddWall(g, 3, 1) == true);
                OJ_ASSERT(AddCapsule(g, 3, 1) == false);
                OJ_ASSERT(AddGhost(g, 3, 3, left) == true);
                OJ_ASSERT(AddCapsule(g, 3, 3) == false);
                OJ_ASSERT(AddPacman(g, 3, 5) == true);
                OJ_ASSERT(AddCapsule(g, 3, 5) == false);
                OJ_ASSERT(g->foodCount == 7)
                OJ_ASSERT(g->grid[3][1] == '#');
                OJ_ASSERT(g->grid[3][3] == '@');
                OJ_ASSERT(g->grid[3][5] == 'C');
    
                // Upgrade foods to capsules
                OJ_ASSERT(AddCapsule(g, 2, 3) == true);
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->grid[2][2] == '.');
                OJ_ASSERT(g->grid[2][3] == 'o');
                OJ_ASSERT(AddCapsule(g, 2, 3) == false);
    
                // Add ghosts on capsules
                OJ_ASSERT(AddGhost(g, 2, 3, left) == true);
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->grid[2][3] == '@');
    
                EndGame(g);
                break;
            }
            case 7: // Earning score for capsules and ghosts
            {
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 5, 3, right) == true);
                OJ_ASSERT(AddFood(g, 5, 4) == true);
                OJ_ASSERT(AddFood(g, 5, 5) == true);
                OJ_ASSERT(AddFood(g, 5, 0) == true);
                OJ_ASSERT(AddCapsule(g, 5, 0) == true);
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(AddPacman(g, 4, 1) == true);

                // To test on your own by playing, create your game to be
                // the same as above, and play it by moving in this order:
                // s a d d s s d d d 

                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    | C    |
                    |o  @..|
                    \------/
                */
    
                MovePacman(g, down);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |oC  @.|
                    \------/
                */
                MovePacman(g, left);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |C   .X|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 48);
                OJ_ASSERT(g->grid[5][0] == 'C');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == 'X');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    | C  .X|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 47);
                OJ_ASSERT(g->grid[5][1] == 'C');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == 'X');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |  C X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 46);
                OJ_ASSERT(g->grid[5][2] == 'C');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                MovePacman(g, down);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |  C X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 45);
                OJ_ASSERT(g->grid[5][2] == 'C');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                MovePacman(g, down);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |  CX..|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 44);
                OJ_ASSERT(g->grid[5][2] == 'C');
                OJ_ASSERT(g->grid[5][3] == 'X');
                OJ_ASSERT(g->grid[5][4] == '.');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |   C..|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 243);
                OJ_ASSERT(g->grid[5][3] == 'C');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->state == onGoing);
    
                
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, right);
                
                OJ_ASSERT(g->foodCount == 0);
                OJ_ASSERT(g->score == 261);
                OJ_ASSERT(g->grid[5][5] == 'C');
                OJ_ASSERT(g->state == winning);
    
                EndGame(g);
    
                break;
            }
            case 8: // Eating foods/capsules under ghosts, extending capsule durations 
            {
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddWall(g, 5, 3) == true);
                OJ_ASSERT(AddFood(g, 5, 4) == true);
                OJ_ASSERT(AddFood(g, 5, 5) == true);
                OJ_ASSERT(AddFood(g, 5, 0) == true);
                OJ_ASSERT(AddGhost(g, 5, 4, right) == true);
                OJ_ASSERT(AddCapsule(g, 5, 0) == true);
                OJ_ASSERT(AddCapsule(g, 5, 2) == true);
                OJ_ASSERT(AddCapsule(g, 4, 5) == true);
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(AddGhost(g, 3, 0, down) == true);
                OJ_ASSERT(AddGhost(g, 2, 2, down) == true);
                OJ_ASSERT(AddPacman(g, 4, 1) == true);

                // To test on your own by playing, create your game to be
                // the same as above, and play it by moving in this order:
                // s a a d d w d d i i i i i i i d s a 

                /*   ______
                    |      |
                    |      |
                    |  @   |
                    |@     |
                    | C   o|
                    |o o#@.|
                    \------/
                */
    
                MovePacman(g, down);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |  @   |
                    |@    o|
                    |oCo#.@|
                    \------/
                */
                OJ_ASSERT(g->grid[4][0] == '@');
                OJ_ASSERT(g->grid[3][2] == '@');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == '@');
    
                MovePacman(g, left);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |  X  o|
                    |C o#X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->score == 248);
                OJ_ASSERT(g->grid[4][0] == ' ');
                OJ_ASSERT(g->grid[5][0] == 'C');
                OJ_ASSERT(g->grid[3][2] == ' ');
                OJ_ASSERT(g->grid[4][2] == 'X');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                MovePacman(g, left);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |  X  o|
                    |C o#X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->score == 247);
                OJ_ASSERT(g->grid[4][0] == ' ');
                OJ_ASSERT(g->grid[5][0] == 'C');
                OJ_ASSERT(g->grid[3][2] == ' ');
                OJ_ASSERT(g->grid[4][2] == 'X');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
                
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |     o|
                    | CX#.X|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->score == 246);
                OJ_ASSERT(g->grid[5][0] == ' ');
                OJ_ASSERT(g->grid[5][1] == 'C');
                OJ_ASSERT(g->grid[4][2] == ' ');
                OJ_ASSERT(g->grid[5][2] == 'X');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == 'X');
                
                // Eats a capsule under ghost.
                // Refreshes superpower duration.
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |     o|
                    |  C#.X|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 495);
                OJ_ASSERT(g->grid[4][2] == ' ');
                OJ_ASSERT(g->grid[5][2] == 'C');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == 'X');
    
                MovePacman(g, up);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |  C  o|
                    |   #X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 494);
                OJ_ASSERT(g->grid[4][2] == 'C');
                OJ_ASSERT(g->grid[5][2] == ' ');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |   C o|
                    |   #X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 493);
                OJ_ASSERT(g->grid[4][3] == 'C');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                // killing time...
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
    
                MovePacman(g, idle);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |    Co|
                    |   #X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 486);
                OJ_ASSERT(g->grid[4][4] == 'C');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
    
                // Expires, but ghost moved last turn.
                MovePacman(g, idle);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |    Co|
                    |   #.@|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 485);
                OJ_ASSERT(g->grid[4][4] == 'C');
                OJ_ASSERT(g->grid[5][4] == '.');
                OJ_ASSERT(g->grid[5][5] == '@');
                
                MovePacman(g, right);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |     C|
                    |   #X.|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 534);
                OJ_ASSERT(g->grid[4][5] == 'C');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == '.');
                
                MovePacman(g, down);
                MoveGhosts(g);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |   #XC|
                    \------/
                */
                OJ_ASSERT(g->foodCount == 1);
                OJ_ASSERT(g->score == 543);
                OJ_ASSERT(g->grid[4][5] == ' ');
                OJ_ASSERT(g->grid[5][4] == 'X');
                OJ_ASSERT(g->grid[5][5] == 'C');
                OJ_ASSERT(g->state == onGoing);
    
                MovePacman(g, left);
                /*   ______
                    |      |
                    |      |
                    |      |
                    |      |
                    |      |
                    |   #C |
                    \------/
                */
                OJ_ASSERT(g->foodCount == 0);
                OJ_ASSERT(g->score == 752);
                OJ_ASSERT(g->grid[4][5] == ' ');
                OJ_ASSERT(g->grid[5][4] == 'C');
                OJ_ASSERT(g->grid[5][5] == ' ');
                OJ_ASSERT(g->state == winning);
    
                EndGame(g);
                break;
            }
    
            case 9: // Complex cases with ghosts!
            {            
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddGhost(g, 5, 3, right) == true);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 5, 4, up) == true);
                OJ_ASSERT(AddWall(g, 3, 3) == true);
    
                OJ_ASSERT(AddFood(g, 3, 1) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(AddFood(g, 4, 1) == true);
                OJ_ASSERT(AddFood(g, 5, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                
                OJ_ASSERT(AddGhost(g, 2, 2, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 1, down) == true);
                OJ_ASSERT(AddWall(g, 2, 3) == true);
                OJ_ASSERT(g->foodCount == 5);
    
                OJ_ASSERT(AddPacman(g, 2, 2) == false);
                OJ_ASSERT(AddPacman(g, 3, 0) == true);

                // To test on your own by playing, create your game to be
                // the same as above, and play it by moving in this order:
                // d d s a i i i s w d w w w d d d s s 

                /* ______
                  |.   #@|
                  |     #|
                  |  @#  |
                  |C. #@.|
                  | @    |
                  | . @@ |
                  \------/
                */
    
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  | @ #  |
                  | C # @|
                  | .  @ |
                  | @@   |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->grid[3][5] == '@' && g->grid[5][1] == '@' && g->grid[4][4] == '@' && g->grid[2][1] == '@' && g->grid[5][2] == '@');
                
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  |@  #  |
                  |  C#@.|
                  | @    |
                  | . @@ |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->grid[3][4] == '@' && g->grid[4][1] == '@' && g->grid[5][4] == '@' && g->grid[2][0] == '@');
                OJ_ASSERT(g->grid[3][5] == '.' && g->grid[5][1] == '.' && g->grid[3][2] == 'C');
    
                MovePacman(g, down);
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  | @ #  |
                  | @ # @|
                  | .C @ |
                  | .@   |
                  \------/
                */
                OJ_ASSERT(g->grid[5][2] == '@' && g->grid[5][1] == '.');
    
    
                MovePacman(g, left);
                MoveGhosts(g);
                /* ______
                  |.     |
                  |      |
                  | @@#  |
                  |   #@.|
                  | C    |
                  | @  @ |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 16);
                OJ_ASSERT(g->grid[5][1] == '@');
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[2][2] == '@' && g->grid[2][0] != '@');
    
    
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, idle);
                MoveGhosts(g);
                MovePacman(g, down);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                /* ______
                  |.     |
                  | @    |
                  |  @#  |
                  |   # @|
                  | C  @ |
                  |  @   |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 21);
                OJ_ASSERT(g->grid[5][2] == '@');
                OJ_ASSERT(g->grid[2][1] == ' ' && g->grid[2][2] == '@' && g->grid[1][1] == '@');
    
                
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                /* ______
                  |.     |
                  | @C   |
                  |  @#  |
                  |   # @|
                  |    @ |
                  |  @   |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 2);
                OJ_ASSERT(g->score == 17);
                OJ_ASSERT(g->grid[5][2] == '@');
                OJ_ASSERT(g->grid[2][1] == ' ' && g->grid[2][2] == '@' && g->grid[1][1] == '@');
    
                
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, down);
                MoveGhosts(g);
                /* ______
                  |.     |
                  | @    |
                  |  @# C|
                  |   # @|
                  |    @ |
                  |@     |
                  \------/
                */
    
                MovePacman(g, down);
                /* ______
                  |.     |
                  | @    |
                  |  @#  |
                  |   # @|
                  |    @ |
                  |@     |
                  \------/
                */
                OJ_ASSERT(g->score == 12);
                OJ_ASSERT(g->state == losing);
                OJ_ASSERT(g->grid[3][5] == '@' && g->grid[2][5] == ' ' && g->grid[1][1] == '@' && g->grid[5][0] == '@');
    
                EndGame(g);
                break;
            }
            case 10: // Ghosts, capsules, everything!
            {            
                Game* g = NewGame(6, 6);
                OJ_ASSERT(AddWall(g, 0, 4) == true);
                OJ_ASSERT(AddWall(g, 1, 5) == true);
                OJ_ASSERT(AddGhost(g, 0, 5, right) == true);
    
                OJ_ASSERT(AddGhost(g, 5, 3, right) == true);
                OJ_ASSERT(AddGhost(g, 3, 4, right) == true);
                OJ_ASSERT(AddGhost(g, 5, 4, up) == true);
                OJ_ASSERT(AddWall(g, 3, 3) == true);
    
                OJ_ASSERT(AddFood(g, 3, 1) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(AddFood(g, 4, 1) == true);
                OJ_ASSERT(AddFood(g, 5, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 0) == true);
                
                OJ_ASSERT(AddFood(g, 2, 0) == true);
                OJ_ASSERT(AddFood(g, 2, 1) == true);
                OJ_ASSERT(AddCapsule(g, 2, 0) == true);
                OJ_ASSERT(AddGhost(g, 2, 2, right) == true);
                OJ_ASSERT(AddGhost(g, 4, 1, down) == true);
                OJ_ASSERT(AddWall(g, 2, 3) == true);
    
                OJ_ASSERT(AddCapsule(g, 5, 0) == true);
                OJ_ASSERT(g->foodCount == 8);
    
                OJ_ASSERT(AddPacman(g, 2, 2) == false);
                OJ_ASSERT(AddPacman(g, 3, 1) == false);
                OJ_ASSERT(AddPacman(g, 3, 0) == true);
                OJ_ASSERT(AddPacman(g, 4, 0) == false);

                // To test on your own by playing, create your game to be
                // the same as above, and play it by moving in this order:
                // d a s a s d d d d a a a w w w 



                /* ______
                  |.   #@|
                  |     #|
                  |o.@#  |
                  |C. #@.|
                  | @    |
                  |o. @@ |
                  \------/
                */
    
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.   #@|
                  |     #|
                  |o@ #  |
                  | C # @|
                  | .  @ |
                  |o@@   |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->grid[3][5] == '@' && g->grid[5][1] == '@' && g->grid[4][4] == '@' && g->grid[2][1] == '@' && g->grid[5][2] == '@');
                OJ_ASSERT(g->grid[2][0] == 'o');
                
                MovePacman(g, left);
                MoveGhosts(g);
                /* ______
                  |.   #@|
                  |     #|
                  |@. #  |
                  |C  #@.|
                  | @    |
                  |o. @@ |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->grid[3][4] == '@' && g->grid[4][1] == '@' && g->grid[5][4] == '@' && g->grid[2][0] == '@');
                OJ_ASSERT(g->grid[3][5] == '.' && g->grid[5][1] == '.' && g->grid[3][0] == 'C');
                OJ_ASSERT(g->grid[2][1] == '.');
    
                MovePacman(g, down);
                MoveGhosts(g);
                /* ______
                  |.   #@|
                  |     #|
                  |o@ #  |
                  | @ # @|
                  |C.  @ |
                  |o.@   |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->grid[5][2] == '@' && g->grid[3][5] == '@');
                OJ_ASSERT(g->grid[4][1] == '.' && g->grid[5][1] == '.' && g->grid[2][0] == 'o');
    
    
                MovePacman(g, left);
                MoveGhosts(g);
                /* ______
                  |.   #@|
                  |     #|
                  |o@@#  |
                  |   #@.|
                  |C.    |
                  |o@  @ |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 7);
                OJ_ASSERT(g->score == 6);
                OJ_ASSERT(g->grid[5][1] == '@');
                OJ_ASSERT(g->grid[2][1] == '@' && g->grid[2][2] == '@' && g->grid[2][0] == 'o');
    
    
                MovePacman(g, down);
                MoveGhosts(g);
                /* ______
                  |.   #X|
                  | X   #|
                  |o.X#  |
                  |   # X|
                  | .  X |
                  |C.    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 6);
                OJ_ASSERT(g->score == 255);
                OJ_ASSERT(g->grid[5][0] == 'C');
                OJ_ASSERT(g->grid[2][0] == 'o' && g->grid[2][1] == '.' && g->grid[2][2] == 'X');
                OJ_ASSERT(g->grid[5][1] == '.' && g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[3][5] == 'X' && g->grid[4][4] == 'X');
                OJ_ASSERT(g->grid[0][5] == 'X');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.   #X|
                  | X   #|
                  |o.X#  |
                  |   # X|
                  | .  X |
                  | C    |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->score == 264);
                OJ_ASSERT(g->grid[5][1] == 'C');
                OJ_ASSERT(g->grid[2][0] == 'o' && g->grid[2][1] == '.' && g->grid[2][2] == 'X');
                OJ_ASSERT(g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[3][5] == 'X' && g->grid[4][4] == 'X');
                OJ_ASSERT(g->grid[0][5] == 'X');
    
                MovePacman(g, right);
                MoveGhosts(g);
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.X  #X|
                  |     #|
                  |oX #  |
                  |   #X.|
                  | .    |
                  |   CX |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->score == 262);
                OJ_ASSERT(g->grid[5][3] == 'C');
                OJ_ASSERT(g->grid[2][0] == 'o' && g->grid[2][1] == 'X' && g->grid[2][2] == ' ');
                OJ_ASSERT(g->grid[0][1] == 'X');
                OJ_ASSERT(g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[3][4] == 'X' && g->grid[3][5] == '.');
                OJ_ASSERT(g->grid[0][5] == 'X');
    
                MovePacman(g, right);
                MoveGhosts(g);
                /* ______
                  |.   #X|
                  | X   #|
                  |X. #  |
                  |   # X|
                  | .    |
                  |    C |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 5);
                OJ_ASSERT(g->score == 461);
                OJ_ASSERT(g->grid[5][4] == 'C');
                OJ_ASSERT(g->grid[2][0] == 'X' && g->grid[2][1] == '.' && g->grid[2][2] == ' ');
                OJ_ASSERT(g->grid[1][1] == 'X');
                OJ_ASSERT(g->grid[4][1] == '.');
                OJ_ASSERT(g->grid[3][4] == ' ' && g->grid[3][5] == 'X');
                OJ_ASSERT(g->grid[0][5] == 'X');
    
                MovePacman(g, left);
                MoveGhosts(g);
                MovePacman(g, left);
                MoveGhosts(g);
                MovePacman(g, left);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                /* ______
                  |.   #X|
                  | X   #|
                  |o.X#  |
                  |   # X|
                  | C    |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 4);
                OJ_ASSERT(g->score == 467);
                OJ_ASSERT(g->grid[4][1] == 'C');
                OJ_ASSERT(g->grid[2][0] == 'o' && g->grid[2][1] == '.' && g->grid[2][2] == 'X');
                OJ_ASSERT(g->grid[1][1] == 'X');
                OJ_ASSERT(g->grid[3][4] == ' ' && g->grid[3][5] == 'X');
                OJ_ASSERT(g->grid[0][5] == 'X');
                OJ_ASSERT(g->state == onGoing);
    
    
                MovePacman(g, up);
                MoveGhosts(g);
                MovePacman(g, up);
                MoveGhosts(g);
                /* ______
                  |.@  #@|
                  |     #|
                  |o@ #  |
                  |   #@.|
                  |      |
                  |      |
                  \------/
                */
                OJ_ASSERT(g->foodCount == 3);
                OJ_ASSERT(g->score == 475);
                OJ_ASSERT(g->grid[3][2] == ' ');
                OJ_ASSERT(g->grid[2][0] == 'o' && g->grid[2][1] == '@' && g->grid[2][2] == ' ');
                OJ_ASSERT(g->grid[0][1] == '@');
                OJ_ASSERT(g->grid[3][4] == '@' && g->grid[3][5] == '.');
                OJ_ASSERT(g->grid[0][5] == '@');
                OJ_ASSERT(g->state == losing);
    
                EndGame(g);
                break;
            }
            default: return 1;
        }
        printf(GREEN("Testcase %d passed.\n"), tcase);
    }
    return 0;
}