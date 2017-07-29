#ifndef NUMBER_H
#define NUMBER_H

#include <list>

class Number{
private:
    std::list<int> _my_set;
    int _num;
    int _reps;
public:
    Number(int num, int reps);
    bool operator < (const Number& right) const;
    int getNum();
    int getReps();
};

#endif  /* end of include guard for NUMBER_H */
