#!/usr/bin/env python

import math

res = 0
for i in range(1, 1001):
    res += pow(i, i);
print("If you can trust me, the number you are looking for is {0}".format(res % 10000000000))

