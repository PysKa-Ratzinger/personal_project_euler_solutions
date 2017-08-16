#include <stdio.h>

#include "number.h"

Number::Number(unsigned long long num) : _num(num)
{
    for(int i=0; i<10; i++){
        _digits[i] = 0;
    }
    while(num){
        _digits[num % 10]++;
        num /= 10;
    }
    _reps = 1;
}

bool Number::operator < (const Number& right) const
{
    for(int i=0; i<10; i++){
        if(_digits[i] < right._digits[i]){
            return true;
        }else if(_digits[i] > right._digits[i]){
            return false;
        }
    }
    return false;
}

bool Number::operator==(const Number &number) const{
    for(int i=0; i<10; i++){
        if(_digits[i] != number._digits[i]){
            return false;
        }
    }
    return true;
}

unsigned Number::getReps(){
    return _reps;
}

bool Number::incrementRep(){
    if(_reps + 1 < _reps){
        return false;
    }
    _reps++;
    return true;
}

unsigned long long Number::getNum() const{
    return _num;
}
