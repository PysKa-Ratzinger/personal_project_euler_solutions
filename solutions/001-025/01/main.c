#include <stdio.h>

/* Problem 1: Multiples of 3 and 5
 *
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
int main(){
    int res = 0;

    // Brute-forcing way... didn't want to waste too much time with this problem.
    for(int i=1; i<1000; i++){
        if(i%3==0 || i%5==0)
            res += i;
    }

    printf("If you can trust me, the number you are looking for is %d\n", res);
    return 0;
}

