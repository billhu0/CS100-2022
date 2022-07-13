#include <stdio.h>

void add(int a, int b){
    // YOUR CODE HERE
}

void subtract(int a, int b){
    // YOUR CODE HERE
}

void multiply(int a, int b){
    // YOUR CODE HERE
}

int main(){
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}