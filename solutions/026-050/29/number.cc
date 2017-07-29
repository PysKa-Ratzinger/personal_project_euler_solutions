#include <stdio.h>

#include "number.h"

Number::Number(int num, int reps) : _num(num) , _reps(reps)
{
    for(int i=2; i<num; i++){
        if(num % i == 0){
            for(int j=0; j<reps; j++){
                _my_set.push_back(i);
            }
            num /= i;
            i--;
        }
    }
    if(num > 1){
        for(int j=0; j<reps; j++){
            _my_set.push_back(num);
        }
    }
}

bool Number::operator < (const Number& right) const
{
    if(_my_set.size() < right._my_set.size()){
        return true;
    }else if(_my_set.size() > right._my_set.size()){
        return false;
    }

    std::list<int>::const_iterator it1 = _my_set.begin();
    std::list<int>::const_iterator it2 = right._my_set.begin();
    
    while(it1 != _my_set.end() && it2 != right._my_set.end()){
        int num1 = *it1;
        int num2 = *it2;

        if(num1 != num2){
            if(num1 < num2){
                return true;
            }else{
                return false;
            }
        }
        
        it1++;
        it2++;
    }
    
    return false;
}

int Number::getNum()
{
    return _num;
}

int Number::getReps()
{
    return _reps;
}
