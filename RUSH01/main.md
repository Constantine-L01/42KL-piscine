# main.c

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct Value {
    char height;
} Slot;
typedef struct View {
    char tallest;
    int viewable;
} View;

int initializeConstraint(char* input, char constraint[4][4]);
int errorHandler();
int backtracking(Slot arr[4][4], char constraint[4][4]);
void printBoard(Slot arr[4][4]);

int main()
{
    char input[] = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
    char constraint[4][4];

    if(!initializeConstraint(input, constraint)){
        return 0;
    };
    // board
    Slot arr[4][4];
    // initialise all the slots into 0.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            Slot v = {0};
            arr[i][j] = v;
        }
    }
    int ret = backtracking(arr, constraint);
    // print board if there is solution.
    if(ret == 1){
        printBoard(arr);
    }
    else {
        return errorHandler();
    }
}
```
