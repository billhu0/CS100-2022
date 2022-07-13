#include "stdio.h"
#include "stdlib.h"

int** MagicSquare(int n){
    // YOUR CODE HERE
}

void FreeMagicSquare(int** magicSquare, int n){
    // YOUR CODE HERE 
}

int main(){
    int n;
    scanf("%d", &n); // Please input a positive odd number.
    int** magicSquare = MagicSquare(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}
