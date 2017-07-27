#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SZ   512
#define SEQUENCE_SZ 13

int main(){
    unsigned long long res = 0;
    char buffer[BUFFER_SZ];

    printf("Enter the name of the input file: ");
    if(fgets(buffer, BUFFER_SZ, stdin) == NULL){
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    buffer[strlen(buffer)-1] = '\0';

    FILE* input_file = fopen(buffer, "r");
    if(input_file == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    unsigned long long temp = 1;
    int digits[SEQUENCE_SZ];
    int digits_size = 0;
    int index = 0;
    int input;

    while((input = getc(input_file)) != EOF){
        if(input < '0' || input > '9'){
            continue;
        }

        int digit = input - '0';

        if(digit == 0){
            digits_size = 0;
            index = 0;
            temp = 1;
        }else{
            if(digits_size < SEQUENCE_SZ){
                digits[digits_size++] = digit;
                temp *= digit;
                if(digits_size == SEQUENCE_SZ && temp > res){
                    res = temp;
                }
            }else{
                temp /= digits[index];
                temp *= digit;
                digits[index] = digit;
                index = (index + 1) % SEQUENCE_SZ;
                if(temp > res){
                    res = temp;
                }
            }
        }
    }

    fclose(input_file);
    printf("If you can trust me, the number you "
            "are looking for is %llu\n", res);
    return 0;
}

