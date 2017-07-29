#!/usr/bin/env python

def main():
    fileName = input('Input file name: ')
    f = open(fileName, 'r')
    res = 0
    for number in f:
        res += int(number)
    print("If you can trust me, the number you are looking for is " \
            + str(res)[:10])

main()

