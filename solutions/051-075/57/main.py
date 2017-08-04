#!/usr/bin/env python

def main():
    res = 0
    a = 3
    b = 2
    digsA = 1
    digsB = 1
    ceilA = 10
    ceilB = 10
    it = 1

    while(it < 1000):
        it += 1
        b += a;
        a += 2*(b-a)
        if(a > ceilA):
            digsA += 1
            ceilA *= 10
        if(b > ceilB):
            digsB += 1
            ceilB *= 10
        if(digsA > digsB):
            res += 1

    print("If you can trust me, the number you are looking for is " + str(res))

main()

