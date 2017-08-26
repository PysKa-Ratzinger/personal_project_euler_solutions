#include <stdio.h>

int res = 0;

const int coins[]{200, 100, 50, 20, 10, 5, 2, 1};
const int coins_size = 8;

void magic(int target, int last_coin){
    if(target == 0){
        res++;
        return;
    }

    int i=0;
    for(; i<coins_size; i++){
        if(coins[i] <= last_coin)
            break;
    }
    for(; i<coins_size; i++){
        int new_coin = coins[i];
        int new_target = target - new_coin;
        if(new_target < 0)
            continue;
        magic(new_target, new_coin);
    }
}

int main(){
    magic(200, 200);
    
    printf("If you can trust me, the number you are looking for is %d.\n", res);
    return 0;
}
