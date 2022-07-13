#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200

typedef enum gameState{losing, onGoing, winning} GameState;
typedef enum direction{up, down, left, right, idle} Direction;


// This serves to let "Game" know that "Ghost" is a typename,
// so we can declare variables of type "Ghost" in the Game structure.
// In this way, the definition of Ghost structure can appear
// later than Game structure appears.
typedef struct ghost Ghost;

typedef struct game {
    char** grid;     // a 2-dimensional array of characters to display the game;
    int rows;        // number of rows of the grid;
    int columns;     // number of columns of the grid;
    int foodCount;   // number of remaining food in the game;
    int score;       // current score;
    GameState state; // the state of the game, one of losing, onGoing, or winning.

    int pacmanPosR;
    int pacmanPosC;

    Ghost* ghosts[MAX_GHOSTS];
    int numGhosts;

    int capsuleTime;       // the remaining duration of capsule;
    bool ghostsCannotMove; // if true, ghosts cannot move on this turn;
} Game;

struct ghost {
    int posR;
    int posC;
    char itemBelow;
    Direction moveDirection;
};


// void PrintGame(Game* game);
void PlayGame(Game* game);




/* Creates a new game, with given rows and columns.
 * The top-left corner is at row 0 and column 0.
 * Boundary is not included in either rows or columns.
 * You should dynamically allocate space for a Game pointer,
 * dynamically allocate a 2-dimensional char grid,
 * and initialize any other value in your Game structure.
 * Return that pointer to the game you created.
 */
Game* NewGame(int rows, int columns){ 
    Game* game = (Game*)malloc(sizeof(Game));
    game->columns = columns;
    game->rows = rows;
    game->grid = (char**)malloc(sizeof(char*) * rows);
    for(int i = 0; i < rows; i++){
        game->grid[i] = (char*)malloc(sizeof(char) * columns);
        memset(game->grid[i], ' ', columns);
    }

    game->foodCount = 0;
    game->score = 0;
    game->state = onGoing;
    game->pacmanPosR = -1;
    game->pacmanPosC = -1;

    game->numGhosts = 0;
    game->capsuleTime = 0;
    game->ghostsCannotMove = false;

    return game;
}

bool IsValidPos(Game* game, int r, int c){
    return (r >= 0 && r < game->rows && c >= 0 && c < game->columns);
}


/* Adds a wall to the game, at row = r, column = c.
 * Walls should be added only to an empty place.
 * After you successfully add a Pacman, return true.
 * Return false on failures.
 */
bool AddWall(Game* game, int r, int c){
    if(!IsValidPos(game, r, c)) return false;
    if(game->grid[r][c] != ' ') return false;
    game->grid[r][c] = '#';
    return true;
}

/* Adds a food to the game, at row = r, column = c.
 * Foods should be added only to an empty place.
 * After you successfully add a food, return true.
 * Return false on failures.
 */
bool AddFood(Game* game, int r, int c){
    if(!IsValidPos(game, r, c)) return false;
    if(game->grid[r][c] != ' ') return false;
    game->grid[r][c] = '.';
    game->foodCount++;
    return true;
}


/* Adds a Pacman to the game! At row = r, column = c.
 * If there is already a Pacman, return false.
 * Pacman should be added only to an empty place.
 * After you successfully add a Pacman, return true.
 * Return false on failures.
 */
bool AddPacman(Game* game, int r, int c){
    if(game->pacmanPosR != -1 || game->pacmanPosC != -1) return false;
    if(!IsValidPos(game, r, c)) return false;
    if(game->grid[r][c] != ' ') return false;
    game->grid[r][c] = 'C';
    game->pacmanPosR = r;
    game->pacmanPosC = c;
    return true;
}

/* Moves Pacman in the given direction.
 * The direction will always be valid.
 * Pacman should stay still if this move
 * will let him hit a wall or boundaries.
 * No matter what move is performed, the
 * game score should decrease by 1.
 *
 * FOR PART 2:
 * Pacman is allowed to move onto a grid
 * with a ghost. In that case, Pacman loses,
 * and will not be able to eat the food
 * under that ghost, if any. Score should
 * still decrease by 1.
 */
void MovePacman(Game* game, Direction direction){
    int nextR = game->pacmanPosR;
    int nextC = game->pacmanPosC;

    if(game->capsuleTime > 0){
        game->capsuleTime--;
    }

    game->score -= 1;

    switch(direction){
    case up:
        nextR--; break;
    case left:
        nextC--; break;
    case down:
        nextR++; break;
    case right:
        nextC++; break;
    case idle:
        return;
    default:
        return;
    }
    if(!IsValidPos(game, nextR, nextC) || game->grid[nextR][nextC] == '#') {
        return;
    }
    
    game->grid[game->pacmanPosR][game->pacmanPosC] = ' ';
    game->pacmanPosR = nextR;
    game->pacmanPosC = nextC;

    if(game->grid[nextR][nextC] == ' '){
        game->grid[nextR][nextC] = 'C';
        return;
    }
    if(game->grid[nextR][nextC] == '.'){
        game->score += FOOD_SCORE;
        game->foodCount--;
        if(game->foodCount == 0) {
            game->state = winning;
        }
        game->grid[nextR][nextC] = 'C';
        return;
    }
    if(game->grid[nextR][nextC] == 'o'){
        game->score += CAPSULE_SCORE;
        game->capsuleTime = CAPSULE_DURATION;
        game->foodCount--;
        if(game->foodCount == 0) {
            game->state = winning;
        }
        game->grid[nextR][nextC] = 'C';
        return;
    }
    if(game->grid[nextR][nextC] == '@'){
        game->state = losing;
        return;
    }

    // Eats a scared ghost.
    if(game->grid[nextR][nextC] == 'X'){
        game->score += GHOST_SCORE;

        // Note: This loop of finding the target ghost is unavoidable 
        //       due to the simple design of storing ghosts in an array.
        //       With different designs, you may come up with a more efficient method.
        int targetGhostIndex = 0;
        for(targetGhostIndex = 0; targetGhostIndex < game->numGhosts; targetGhostIndex++){
            Ghost* currGhost = game->ghosts[targetGhostIndex];
            if(currGhost->posR == nextR && currGhost->posC == nextC){
                // That ghost is found. Remember eating anything under it.
                if(currGhost->itemBelow == '.'){            
                    game->score += FOOD_SCORE;
                    game->foodCount--;
                    if(game->foodCount == 0) game->state = winning;
                }
                if(currGhost->itemBelow == 'o'){            
                    game->score += CAPSULE_SCORE;
                    game->capsuleTime = CAPSULE_DURATION;
                    game->foodCount--;
                    if(game->foodCount == 0) game->state = winning;
                }
                break;
            }
        }

        // Deletes that ghost.
        free(game->ghosts[targetGhostIndex]);
        game->numGhosts--;
        for(int i = targetGhostIndex; i < game->numGhosts; i++){
            game->ghosts[i] = game->ghosts[i + 1];
        }

        game->grid[nextR][nextC] = 'C';

        return;
    }

    return;
}

/* Adds a ghost to the game,
 * at row = r, column = c, with given initial direction.
 * Ghosts can be added to an empty place or on a food.
 * For the latter case, the ghost will cover that food on display,
 * represented also by an '@', but that food should still exist,
 * and that grid should display '.' when the ghost leaves.
 */
bool AddGhost(Game* game, int r, int c, Direction direction){
    if(!IsValidPos(game, r, c)) return false;
    if(game->grid[r][c] == ' '){
        Ghost* ghost = (Ghost*)malloc(sizeof(Ghost));
        ghost->posR = r;
        ghost->posC = c;
        ghost->itemBelow = ' ';
        ghost->moveDirection = direction;
        game->ghosts[game->numGhosts++] = ghost;
        game->grid[r][c] = '@';
        return true;
    } else if(game->grid[r][c] == '.'){
        Ghost* ghost = (Ghost*)malloc(sizeof(Ghost));
        ghost->posR = r;
        ghost->posC = c;
        ghost->itemBelow = '.';
        ghost->moveDirection = direction;
        game->ghosts[game->numGhosts++] = ghost;
        game->grid[r][c] = '@';
        return true;
    } else if(game->grid[r][c] == 'o'){
        Ghost* ghost = (Ghost*)malloc(sizeof(Ghost));
        ghost->posR = r;
        ghost->posC = c;
        ghost->itemBelow = 'o';
        ghost->moveDirection = direction;
        game->ghosts[game->numGhosts++] = ghost;
        game->grid[r][c] = '@';
        return true;
    } else {
        return false;
    }
}

/* Moves all ghosts in their own directions.
 * Ghosts should be moved in the order they were added.
 * If a ghost would move onto a cell with food or a capsule,
 * it will cover the food or capsule in display.
 * If a ghost would bump into a wall, another ghost, or a boundary,
 * Its direction will reverse, and it will try to move
 * in the new direction immediately this turn.
 * If it will bump into another wall/ghost/boundary,
 * it won't move for this turn, with its direction reversed.
 */
void MoveGhosts(Game* game){
    // Determines whether ghosts should be represented by '@' or 'X' first.
    char ghostIcon = '@';
    if(game->capsuleTime > 0){
        // When Pacman has superpower, the ghost should move every other turn.
        // Note that directly judging by "capsuleTime % 2" fails,
        // because the duration might have refreshed by eating another capsule.
        if(game->ghostsCannotMove){
            game->ghostsCannotMove = false;
            return;
        } else {
            game->ghostsCannotMove = true;
            ghostIcon = 'X';
        }
    } else {
        game->ghostsCannotMove = false;
        ghostIcon = '@';
    }

    for(int i = 0; i < game->numGhosts; i++){
        Ghost* currGhost = game->ghosts[i];

        // Determines the next location.
        int nextR = currGhost->posR;
        int nextC = currGhost->posC;
        switch(currGhost->moveDirection){
        case up:
            nextR--; break;
        case left:
            nextC--; break;
        case down:
            nextR++; break;
        case right:
            nextC++; break;
        default:
            return;
        }

        // Fails to move
        if(!IsValidPos(game, nextR, nextC) || game->grid[nextR][nextC] == '#' || game->grid[nextR][nextC] == '@' || game->grid[nextR][nextC] == 'X'){
            switch(currGhost->moveDirection){
            case up:
                currGhost->moveDirection = down;
                nextR+=2; 
                break;
            case left:
                currGhost->moveDirection = right;
                nextC+=2; 
                break;
            case down:
                currGhost->moveDirection = up;
                nextR-=2; 
                break;
            case right:
                currGhost->moveDirection = left;
                nextC-=2; 
                break;
            default:
                return;
            }
        }
        
        // Fails to move again
        if(!IsValidPos(game, nextR, nextC) || game->grid[nextR][nextC] == '#' || game->grid[nextR][nextC] == '@' || game->grid[nextR][nextC] == 'X') {
            // Note: directly writing "continue;" will lead to '@' not updated to 'X', 
            //       potentially failing test case 10. 
            game->grid[currGhost->posR][currGhost->posC] = ghostIcon;
            continue;
        } 

        // Restores the item below this ghost.
        game->grid[currGhost->posR][currGhost->posC] = currGhost->itemBelow;

        currGhost->posR = nextR;
        currGhost->posC = nextC;

        // Bumps into Pacman
        if(game->grid[nextR][nextC] == 'C'){
            if(ghostIcon == '@'){
                currGhost->itemBelow = ' ';
                game->state = losing;
            } else {
                currGhost->itemBelow = ' ';
                game->score += GHOST_SCORE;

                // Deleting this ghost. 
                free(currGhost);
                game->numGhosts--;
                for(int j = i; j < game->numGhosts; j++){
                    game->ghosts[j] = game->ghosts[j + 1];
                }
                i--; // A bad way of writing code! The simple idea of storing ghosts in an array should be blamed.
                continue;
            }
        } else {
            currGhost->itemBelow = game->grid[nextR][nextC];
        }

        // Finally, updates the ghost display.
        game->grid[currGhost->posR][currGhost->posC] = ghostIcon;
    }

}

/* Adds a capsule to the game, at row = r, column = c.
 * Capsules should be added only to an empty place,
 * or added to a cell with food to upgrade that food.
 * After you successfully add a capsule, return true.
 * Return false on failures.
 *
 * Capsules will grant Pacman CAPSULE_SCORE = 50 and
 * CAPSULE_DURATION = 10 turns of superpower when eaten.
 * 
 * When with superpower, scared ghosts will be displayed in 'x',
 * and will be unable to move every other turn. 
 * (they can move on the turn when Pacman eats a capsule.)
 * When Pacman eats a scared ghost, it earns GHOST_SCORE = 200.
 * 
 * Pacman's superpower activates immediately when it eats a 
 * capsule, and counts down immediately after Pacman's turn,
 * starting from its next turn. In other words, Pacman's superpower
 * ends after 10 turns at the same moment of eating a capsule.
 */
bool AddCapsule(Game *game, int r, int c){
    if(!IsValidPos(game, r, c)) return false;
    if(game->grid[r][c] == ' '){
        game->grid[r][c] = 'o';
        game->foodCount++;
        return true;
    } else if(game->grid[r][c] == '.'){
        game->grid[r][c] = 'o';
        return true;
    } else {
        return false;
    }
}

void EndGame(Game* game){
    if(!game) return;

    if(game->grid){
        for(int i = 0; i < game->rows; i++){
            free(game->grid[i]);
        }
        free(game->grid);
    }  

    if(game->numGhosts > 0){
        for(int i = 0; i < game->numGhosts; i++){
            free(game->ghosts[i]);
        }
    }
    free(game);
}

int main(){
    // This is the same game as in 4-2B test case 10.
    Game* g = NewGame(6, 6);
    AddWall(g, 0, 4);
    AddWall(g, 1, 5);
    AddGhost(g, 0, 5, right);

    AddGhost(g, 5, 3, right);
    AddGhost(g, 3, 4, right);
    AddGhost(g, 5, 4, up);
    AddWall(g, 3, 3);

    AddFood(g, 3, 1);
    AddFood(g, 3, 5);
    AddFood(g, 4, 1);
    AddFood(g, 5, 1);
    AddFood(g, 0, 0);

    AddFood(g, 2, 0);
    AddFood(g, 2, 1);
    AddCapsule(g, 2, 0);
    AddGhost(g, 2, 2, right);
    AddGhost(g, 4, 1, down);
    AddWall(g, 2, 3);

    AddCapsule(g, 5, 0);

    AddPacman(g, 2, 2);
    AddPacman(g, 3, 1);
    AddPacman(g, 3, 0);
    AddPacman(g, 4, 0);

    // To test on your own, play it by moving in this order:
    // d a s a s d d d d a a a w w w 
    PlayGame(g);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */

#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game* game){
    if(!game || !game->grid) return;

// If Windows,  clear console.
#ifdef _WIN32 
    system("cls");
#else

// Clears terminal screen
#ifndef _ONLINE_JUDGE
    fflush(stdout);
    system("clear");
#endif

#endif
    
    // The game grid
    printf(" ");
    for(int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for(int i = 0; i < game->rows; i++){
        printf("|");
        for(int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for(int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch(game->state){
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

void PlayGame(Game* game){
    
    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while(true){
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf("%[^\n]", input);
        // Handles the '\n'.""
        getchar();
        Direction direction;
        switch(input[0]){
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if(game->state != onGoing){
            break;
        }
        
        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman.
        if(game->state != onGoing){
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}