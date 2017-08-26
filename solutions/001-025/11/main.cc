#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SZ 512
#define ROWS 20
#define COLS 20

bool isNumber(int character){
    return character >= '0' && character <= '9';
}

unsigned long magic2(int grid[ROWS][COLS]){
   unsigned long res = 0;

    unsigned long temp;
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(j<COLS-4){
                temp = grid[i][j] * grid[i][j+1] * grid[i][j+2] * grid[i][j+3];
                if(temp > res) res = temp;
            }
            if(i<ROWS-4){
                temp = grid[i][j] * grid[i+1][j] * grid[i+2][j] * grid[i+3][j];
                if(temp > res) res = temp;
            }
            if(i<ROWS-4 && j<COLS-4){
                temp = grid[i][j] * grid[i+1][j+1] *
                        grid[i+2][j+2] * grid[i+3][j+4];
                if(temp > res) res = temp;
            }
            if(i>3 && j<COLS-4){
                temp = grid[i][j] * grid[i-1][j+1] *
                        grid[i-2][j+2] * grid[i-3][j+3];
                if(temp > res) res = temp;
            }
        }
    }

   return res;
}

unsigned long magic(FILE* input_file){
    int grid[ROWS][COLS];

    bool wasNumber = false;
    int input;
    int number = 0;
    int row_idx = 0;
    int col_idx = 0;
    while((input = getc(input_file)) != EOF){
        if(isNumber(input)){
            number *= 10;
            number += input - '0';
            wasNumber = true;
        }else if(wasNumber){
            grid[row_idx][col_idx] = number;
            number = 0;
            wasNumber = false;
            col_idx++;
            if(col_idx == COLS){
                col_idx = 0;
                row_idx++;
            }
        }
    }

    return magic2(grid);
}

int main(){
    unsigned long res = 0;
    char buffer[BUFFER_SZ];

    printf("Insert the name of the input file: ");
    fgets(buffer, BUFFER_SZ, stdin);
    buffer[strlen(buffer)-1] = '\0';

    FILE* input_file = fopen(buffer, "r");
    if(input_file == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }else{
        printf("File opened successfully.\n");
    }

    res = magic(input_file);

    fclose(input_file);
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    return 0;
}

