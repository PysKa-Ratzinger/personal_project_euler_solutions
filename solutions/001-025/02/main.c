#include <stdio.h>
#include "asm.h"

int main(){
    unsigned int res = magic();

    printf("If you can trust me, the number you are "
            "looking for is %u\n", res);
    return 0;
}

