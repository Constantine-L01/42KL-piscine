# solver.c

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
