/******************************************************************************

CIS 2520 F22
Project: Assignment 2 part 2
Date: October 24th, 2022
Name: Rhiana Quarrington Craig
ID: 1106407

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

double calculateNum(double num0, double num1, char op);
void push();
int pop();
bool isFull();

// N will be the capacity of the Static Stack
#define N 1000

// Initializing the top of the stack to be -1
int top = -1;

// Initializing the stack using an array
int stack[N];

int main(int argc, char *argv[]) {
    
    char eqn[strlen(argv[2])];
    strncpy(eqn, argv[2], strlen(argv[2]));
    char nameExe[strlen(argv[1])];
    strncpy(nameExe, argv[1], strlen(argv[1]));
    int len = strlen(eqn);  
    int i, n = 0, p = 0, j = 0, k = 0;
    double num[4];
    char op;
    double result;
    
    while(len > j) {
        if (len > j) {
            if (eqn[j] >= 48 && eqn[j] <= 57) {
                if(!isFull()) {
                    //convert char to int and push integer onto stack
                    push(eqn[j] - 48);
                    j++;
                }
                else {
                    //stack ran out of space, print error and exit program
                    printf("Expression is too complex\n");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                if(len == j+1) {
                    printf("The answer is: %.2f", calculateNum(pop(), pop(), eqn[j]));
                    return 0;
                }
                push((int)calculateNum(pop(), pop(), eqn[j]));
                j++;
            }}
            
        }
    
    return 0;
}

double calculateNum(double num0, double num1, char op) {
    
    if(op == '+') {
        return num0 + num1;
    }
    
    if(op == '-') {
        return num0 - num1;
    }    
    
    if(op == '*') {
        return num0 * num1;
    }    
    
    if(op == '/') {
        return num0 / num1;
    }
}

void push(int x) {
    // Checking overflow state
    if(top == N-1)
        printf("Overflow State: can't add more elements into the stack\n");
    else{
        top+=1;
        stack[top] = x;
    }
}

int pop() {
    // Checking underflow state
    if(top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else{
        int x = stack[top];
        top-=1;
        return x;
    }
    return -1;
}

bool isFull() {
    if(top == N-1){
        printf("Stack is full: Overflow State\n");
        return true;
    }
    return false;
}
