#!/usr/bin/env python

def digitalSum(n):
    res = 0
    while(n):
        res += n % 10
        n //= 10
    return res

def main():
    res = 0
    for a in range (1, 100):
        for b in range(1, 100):
            temp = digitalSum(a ** b)
            if(temp > res):
                res = temp

    print("If you can trust me, the number you are looking for is", res)

main()
