#ifndef NUMBER_H
#define NUMBER_H

#include <list>

class Number{
private:
    int _digits[10];
    unsigned _reps;
    unsigned long long _num;
public:
    Number(unsigned long long num);
    bool operator < (const Number& right) const;
    bool operator == (const Number& number) const;
    bool incrementRep();
    unsigned getReps();
    unsigned long long getNum() const;
};

#endif  /* end of include guard for NUMBER_H */
