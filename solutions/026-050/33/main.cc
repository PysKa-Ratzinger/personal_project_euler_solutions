#include <stdio.h>
#include <list>

class Fraction{
private:
    int _numerator;
    int _denominator;
public:
    Fraction(int a, int b);
    int getNumerator() const;
    int getDenominator() const;
    bool isMagic() const;
    void reduce();
    void operator *= (const Fraction& right);
    bool operator == (const Fraction& right);
};

Fraction::Fraction(int a, int b) : _numerator(a), _denominator(b) {}

int Fraction::getNumerator() const
{
    return _numerator;
}

int Fraction::getDenominator() const
{
    return _denominator;
}

bool Fraction::isMagic() const
{
    int digs[2][2]{{_numerator / 10, _numerator % 10}, {_denominator / 10, _denominator % 10}};
    if(digs[0][1] == digs[1][1] && digs[1][1] == 0)
        return false;
    
    Fraction tmp(_numerator, _denominator);
    tmp.reduce();
    
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(digs[0][i] == digs[1][j]){
                Fraction tmp2(digs[0][1-i], digs[1][1-j]);
                tmp2.reduce();
                if(tmp == tmp2) return true;
            }
        }
    }
    
    return false;
}

void Fraction::reduce()
{
    for(int i=2; i<=_numerator && i<=_denominator; i++){
        while(_numerator % i == 0 && _denominator % i == 0){
            _numerator /= i;
            _denominator /= i;
        }
    }
}

void Fraction::operator*=(const Fraction& right)
{
    _numerator *= right.getNumerator();
    _denominator *= right.getDenominator();
}

bool Fraction::operator==(const Fraction& right)
{
    return _numerator == right.getNumerator() && _denominator == right.getDenominator();
}

int main(){
    std::list<Fraction> my_list;
    for(int i=10; i<100; i++){
        for(int j=i+1; j<100; j++){
            Fraction *f = new Fraction(i, j);
            if(f->isMagic()){
                printf("%d/%d is magic\n", f->getNumerator(), f->getDenominator());
                my_list.push_front(*f);
            }else{
                delete f;
            }
        }
    }
    
    Fraction res(1, 1);
    for(Fraction f : my_list){
        res *= f;
    }
    res.reduce();
    
    printf("If you can trust me, the number you are looking for is %d.\n", res.getDenominator());
    return 0;
}
