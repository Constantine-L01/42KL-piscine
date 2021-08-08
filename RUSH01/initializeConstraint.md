# initializeConstraint.c

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
