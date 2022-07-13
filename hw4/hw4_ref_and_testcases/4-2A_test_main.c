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
        switch(tcase) {
            case 1: // NewGame
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(g != NULL);
                OJ_ASSERT(g->columns == 10 && g->rows == 8);
                OJ_ASSERT(g->foodCount == 0 && g->score == 0);
                for (int i = 0; i < 8; i++)
                    OJ_ASSERT(g->grid[i] != NULL);
                EndGame(g);
                break;
            }
            case 2: // Add walls
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddWall(g, 1, 1) == true);
                OJ_ASSERT(AddWall(g, 1, 1) == false);
                OJ_ASSERT(g->grid[1][1] == '#');
                OJ_ASSERT(AddWall(g, 11, 11) == false);
                for (int i = 0; i < 5; i++)
                    AddWall(g, 0, i);
                for (int i = 0; i < 5; i++)
                    OJ_ASSERT(g->grid[0][i] == '#');
                EndGame(g);
                break;
            }
            case 3: // Add food
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddWall(g, 1, 1) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(AddFood(g, 3, 5) == false);
                OJ_ASSERT(g->grid[3][5] == '.');
                OJ_ASSERT(AddFood(g, 1, 1) == false);
                OJ_ASSERT(AddFood(g, 11, 11) == false);
                EndGame(g);
                break;
            }
            case 4: // Add pacman(s)
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddFood(g, 3, 5) == true);
                OJ_ASSERT(g->grid[3][5] == '.');
                OJ_ASSERT(AddPacman(g, 3, 5) == false);

                OJ_ASSERT(AddWall(g, 1, 1) == true);
                OJ_ASSERT(AddPacman(g, 1, 1) == false);
                OJ_ASSERT(AddPacman(g, 11, 11) == false);

                OJ_ASSERT(AddPacman(g, 4, 6) == true);
                OJ_ASSERT(AddPacman(g, 4, 4) == false);
                OJ_ASSERT(g->grid[4][6] == 'C' && g->grid[4][4] != 'C');
                EndGame(g);
                break;
            }
            case 5: // Move legally
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddPacman(g, 5, 5) == true);
                OJ_ASSERT(g->grid[5][5] == 'C');
                
                MovePacman(g, up);
                OJ_ASSERT(g->grid[5][5] == ' ' && g->grid[4][5] == 'C');
                MovePacman(g, down);
                OJ_ASSERT(g->grid[4][5] == ' ' && g->grid[5][5] == 'C');
                MovePacman(g, left);
                OJ_ASSERT(g->grid[5][5] == ' ' && g->grid[5][4] == 'C');
                MovePacman(g, right);
                OJ_ASSERT(g->grid[5][4] == ' ' && g->grid[5][5] == 'C');
                MovePacman(g, idle);
                OJ_ASSERT(g->grid[5][5] == 'C');
                EndGame(g);
                break;
            }
            case 6: // Move to walls & boundary
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                OJ_ASSERT(g->grid[0][0] == 'C');
                OJ_ASSERT(AddWall(g, 1, 0) == true);
                OJ_ASSERT(AddWall(g, 0, 1) == true);

                MovePacman(g, up);
                OJ_ASSERT(g->grid[0][0] == 'C');
                MovePacman(g, down);
                OJ_ASSERT(g->grid[0][0] == 'C');
                MovePacman(g, left);
                OJ_ASSERT(g->grid[0][0] == 'C');
                MovePacman(g, right);
                OJ_ASSERT(g->grid[0][0] == 'C');
                MovePacman(g, idle);
                OJ_ASSERT(g->grid[0][0] == 'C');
                EndGame(g);
                break;
            }
            case 7: // Eat food
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                OJ_ASSERT(g->grid[0][0] == 'C');
                OJ_ASSERT(AddFood(g, 0, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 2) == true);
                OJ_ASSERT(g->grid[0][0] == 'C' && g->grid[0][1] == '.' && g->grid[0][2] == '.');
                MovePacman(g, right);
                MovePacman(g, right);
                OJ_ASSERT(g->grid[0][0] == ' ' && g->grid[0][1] == ' ' && g->grid[0][2] == 'C');
                EndGame(g);
                break;
            }
            case 8: // Score
            {
                Game* g = NewGame(8, 10);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                OJ_ASSERT(g->grid[0][0] == 'C');
                OJ_ASSERT(AddFood(g, 0, 1) == true);
                OJ_ASSERT(AddFood(g, 0, 2) == true);
                OJ_ASSERT(AddWall(g, 0, 3) == true);
                OJ_ASSERT(g->grid[0][0] == 'C' && g->grid[0][1] == '.' && g->grid[0][2] == '.');
                MovePacman(g, right);
                OJ_ASSERT(g->score == 9);
                MovePacman(g, right);
                OJ_ASSERT(g->grid[0][0] == ' ' && g->grid[0][1] == ' ' && g->grid[0][2] == 'C');
                OJ_ASSERT(g->score == 18);
                MovePacman(g, right);
                OJ_ASSERT(g->score == 17);
                MovePacman(g, idle);
                OJ_ASSERT(g->score == 16);
                MovePacman(g, down);
                OJ_ASSERT(g->grid[1][2] == 'C' && g->score == 15);
                EndGame(g);
                break;
            }
            case 9: // Everything
            {
                Game* g = NewGame(8, 10);
                for (int i = 0; i < 10; i++)
                    OJ_ASSERT(AddWall(g, 2, i) == true);
                for (int i = 1; i < 10; i++)
                {
                    OJ_ASSERT(AddFood(g, 1, i) == true);
                    OJ_ASSERT(AddFood(g, 0, i) == true);
                }
                OJ_ASSERT(g->foodCount == 18);
                OJ_ASSERT(g->score == 0);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                OJ_ASSERT(AddPacman(g, 0, 1) == false);
                OJ_ASSERT(AddPacman(g, 0, 0) == false);
                OJ_ASSERT(AddPacman(g, 2, 2) == false);
                for (int i = 0; i < 9; i++)
                    MovePacman(g, right);
                OJ_ASSERT(g->score == 81);
                OJ_ASSERT(g->foodCount == 9);
                EndGame(g);
                break;
            }
            case 10: // Everything
            {
                Game* g = NewGame(8, 10);
                for (int i = 0; i < 10; i++)
                    OJ_ASSERT(AddWall(g, 2, i) == true);
                for (int i = 1; i < 10; i++)
                {
                    OJ_ASSERT(AddFood(g, 1, i) == true);
                    OJ_ASSERT(AddFood(g, 0, i) == true);
                }
                OJ_ASSERT(g->foodCount == 18);
                OJ_ASSERT(g->score == 0);
                OJ_ASSERT(AddPacman(g, 0, 0) == true);
                MovePacman(g, down);
                MovePacman(g, down);
                OJ_ASSERT(g->grid[1][0] == 'C');
                for (int i = 0; i < 9; i++)
                    MovePacman(g, right);
                OJ_ASSERT(g->score == 79);
                OJ_ASSERT(g->foodCount == 9);
                
                for (int i = 0; i < 10; i++)
                    MovePacman(g, idle);
                OJ_ASSERT(g->score == 69);
                EndGame(g);
                break;
            }
            default: return 1;
        }
        printf(GREEN("Testcase %d passed.\n"), tcase);
    }
    return 0;
}