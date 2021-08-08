* main.c
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

* initializeConstraint.c
```c
void printString(char* str){
    int i = 0;
    while(str[i]){
        write(1, &str[i], 1);
        i++;
    }
}

int errorHandler(){
    printString("Error\n");
    return 0;
}

int initializeConstraint(char* input, char constraint[4][4]){
    int i = 0;
    // loop through all the characters
    for(; input[i]; i++){
        // if it is the second character,
        if(i % 2 == 1){
            // report error if it is not space.
            if(input[i] != ' '){
                return errorHandler();
            }
        }
        // if it is the first character.
        else {
            if('1' <= input[i] && input[i] <= '4'){
                constraint[i / 8][i % 8 / 2] = input[i];
            }
            // report error if the character is not within 1 and 4.
            else {
                return errorHandler();
            }
        }
    }
    // if the length of the string is too long or too short for a 4 x 4 grid.
    if(i != 31){
        // then report the error.
        return errorHandler();
    }
    // return 1 as success flag if there is no error found.
    return 1;
}
```

* solver.c
```c
typedef struct Value {
    char height;
} Slot;

typedef struct View {
    char tallest;
    int viewable;
} View;

// record the tallest tower ever met and count the viewable tower from the view.
void checkIsTaller(View views[4], char currTowerHeight, int currentView){
    if(views[currentView].tallest < currTowerHeight){
        views[currentView].tallest = currTowerHeight;
        views[currentView].viewable++;
    }
}

int isSolution(Slot arr[4][4], char constraint[4][4]){
    // outer for loop will check one row/column for each iteration.
    for(int i = 0; i < 4; i++){
        View views[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
        // this for loop check the one row/column for each view.
        for(int j = 0; j < 4; j++){
            checkIsTaller(views, arr[j][i].height, 0);
            checkIsTaller(views, arr[3 - j][i].height, 1);
            checkIsTaller(views, arr[i][j].height, 2);
            checkIsTaller(views, arr[i][3 - j].height, 3);
        }
        // this loop is for four views.
        for(int a = 0; a < 4; a++){
            // if the number of viewable tower is not the same as the constraint
            if(constraint[a][i] - '0' != views[a].viewable){
                // then we return 0 as fail flag.
                return 0;
            }
        }
    }
    // success if no conflict.
    return 1;
}

int notRepeated(int row, int col, int val, Slot arr[4][4]){
    // check whether current value had been existed in current row.
    for(int j = 0; j < 4; j++){
        if(arr[row][j].height == val){
            return 0;
        }
    }
    // check whether current value had been existed in current column.
    for(int i = 0; i < 4; i++){
        if(arr[i][col].height == val){
            return 0;
        }
    }
    return 1;
}

int backtracking(Slot arr[4][4], char constraint[4][4]){
    // the two outer for loop will go through all the slots of the grid.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            // if the current slot had been filled, then we go to the next slot.
            if(arr[i][j].height != 0){
                continue;
            }
            // try for different possible numbers.
            for(char k = '1'; k <= '4'; k++){
                // if the number has not been repeated in the row and column.
                if(notRepeated(i, j, k, arr)){
                    // then we assign the number to the slot.
                    arr[i][j].height = k;
                    // and go to the next slot by passing the board filled with the number into the recursive function.
                    if(backtracking(arr, constraint)) return 1;
                    // will reach this statement if we could not find a solution with the assigned number,
                    // so we remove it by assigning 0 to the slot, and try next number at next for loop iteration.
                    arr[i][j].height = 0;
                }
            }
            return 0;
        }
    }
    // return 1 as success flag if there is solution.
    if(isSolution(arr, constraint)){
        return 1;
    }
    else {
        return 0;
    }
}
```

* printBoard.c
```c
typedef struct Value {
    char height;
} Slot;

// print the board using two for loop.
void printBoard(Slot arr[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(j == 3){
                write(1, &(arr[i][j].height), 1);
            }
            else {
                write(1, &(arr[i][j].height), 1);
                write(1, " ", 1);
            }
        }
        write(1, "\n", 1);
    }
}
```
