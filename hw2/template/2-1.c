#include <stdio.h>
#include <stdlib.h>

void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin){
    // YOUR CODE HERE
}

#define SIZE 8

int main(){
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}