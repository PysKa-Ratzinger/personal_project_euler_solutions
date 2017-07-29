#include <stdio.h>
#include <iostream>

#include "../utils/bst.h"
#include "number.h"

#define TARGET 100

int main(){
    BST<Number> bst;
    
    for(int a=2; a<=TARGET; a++){
        for(int b=2; b<=TARGET; b++){
            Number *num = new Number(a, b);
            if(!bst.insert(*num)){
                delete num;
            }
        }
    }
    
    printf("If you can trust me, the number you are looking for is %lu\n", bst.size());

    return 0;
}
