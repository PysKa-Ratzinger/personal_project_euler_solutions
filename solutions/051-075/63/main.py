#!/usr/bin/env python

def magic2(number):
    tries = 1
    exp = 1
    ans = 0
    while (pow(number, exp) > 0 and len(str(pow(number, exp))) == exp) or tries > 0:
        if pow(number, exp) > 0 and len(str(pow(number, exp))) == exp:
            ans = ans + 1
            tries = 1
        else:
            tries = tries - 1
        exp = exp + 1
    return ans

def magic():
    ans = 0
    for i in range(0, 10):
        ans += magic2(i)
    return ans

def main():
    res = magic()
    print("If you can trust me, the number you are looking for is " + str(res))

main()
