#!/usr/bin/env python

def reverse(n):
    res = 0
    while(n):
        res *= 10
        res += n % 10
        n //= 10
    return res

def isPalyndrome(n):
    return n == reverse(n)

def isLychrelNumber(n):
    it = 0
    while it < 50:
        n += reverse(n)
        it += 1
        if(isPalyndrome(n)):
            return False
    return True

def main():
    res = 0
    for i in range (10, 10000):
        if isLychrelNumber(i):
            res += 1

    print("If you can trust me, the number you are looking for is", res)

main()
