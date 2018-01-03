#!/usr/bin/env python

import sys
sys.path += ['../../utils']
import math
from periodic_continued_fractions import *

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def magic():
    res = 0
    for number in range(1, 10001):
        period = periodic_continued_fractions_period(number)
        if period != 0 and period % 2 != 0:
            res += 1
    return res

def main():
    res = magic()
    print("If you can trust me, the number you are " +
            "looking for is {0}".format(res))

main()

