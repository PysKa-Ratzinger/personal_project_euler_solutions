#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SZ 512
#define TEMP_MAX 512

int temp[TEMP_MAX];
int temp_sz = 0;

int triangle_number(int index){
    if(index >= temp_sz){
        for(;temp_sz <= index; temp_sz++){
            if(temp_sz >= TEMP_MAX){
                printf("WARNING!!! Temporary triangle number buffer exceeded!\n");
                exit(1);
            }
            temp[temp_sz] = ((temp_sz+1) * (temp_sz+2)) / 2;
        }
    }
    return temp[index];
}

bool is_triangle_number(int number){
    for(int i=0; i<TEMP_MAX; i++){
        int temp = triangle_number(i);
        if(temp > number) return false;
        if(temp == number) return true;
    }
    return false;
}

int name_score(char *buffer){
    char c = *buffer;
    int res = 0;
    while(c){
        res += c - 'A' + 1;
        
        buffer++;
        c = *buffer;
    }
    return res;
}

void remove_newline(char *buffer){
    while(*buffer != '\n'){
        buffer++;
    }
    *buffer = '\0';
}

int main(){
    temp[0] = 1;
    temp_sz = 1;
    int res = 0;
    
    char buffer[BUFFER_SZ];
    
    FILE *fp = fopen("input", "r");
    while(fgets(buffer, BUFFER_SZ, fp) != NULL){
        remove_newline(buffer);
        int score = name_score(buffer);
        if(is_triangle_number(score)){
            res++;
        }
    }
    fclose(fp);
    
    printf("If you can trust me, the number you are looking for is %d\n", res);

    return 0;
}
