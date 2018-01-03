#!/usr/bin/env python

import sys
sys.path += ['../../utils']
import math
from periodic_continued_fractions import *

def checkSolution(number, x, y):
    return x**2 - number * y**2 == 1

def solvePellEquation(number):
    pcf = periodic_continued_fractions(number)
    if not pcf['values']: return
    x = PCFValues(pcf)
    val = [x.currNumerator, x.currDenominator]
    while not checkSolution(number, val[0], val[1]):
        val = x.getNextValue()
    return val

def main():
    x = 2
    res = 0
    for i in range(2, 1001):
        val = solvePellEquation(i)
        if val:
            if val[0] > x:
                x = val[0]
                res = i
    print(x)
    print("If you can trust me, the solution you are "
            "looking for is {0}.".format(res))

main()

