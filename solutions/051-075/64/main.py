#!/usr/bin/env python

import math
import sys

ONE_OVER_MILLION = 1E-6
MULTIPLIER = 2

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def square(number):
    min = 1
    max = 2
    while max**2 <= number:
        max <<= 1
    min = max >> 1
    handler = False
    while min < max:
        handler = not handler
        mid = (min + max + handler) >> 1
        square = mid**2
        if square < number:     min = mid
        elif square > number:   max = mid - 1
        else:                   return mid
    return min

def periodic_continued_fractions_period(number):
    global step_buffer
    squareNumber = square(number)
    if squareNumber**2 == number: return 0
    index = 0
    res = 0

    step_buffer = [{'value': squareNumber,
                    'numerator': 1,
                    'denominator': -squareNumber}]
    step = step_buffer[0]
    running = True

    index -= 1
    while running:
        index += 1
        if index == len(step_buffer):
            step_buffer += [{} for i in range(20)]
        prev = step
        step = step_buffer[index]
        temp_mul = prev['numerator']
        temp1 = -prev['denominator']
        temp_denominator = number - (temp1**2)

        if (temp_denominator % temp_mul != 0):
            eprint("Well, something went wrong with number {0}".format(number))
            sys.exit()

        temp_denominator /= temp_mul
        temp_value = 0
        while temp1 - temp_denominator >= -squareNumber:
            temp1 -= temp_denominator
            temp_value += 1

        step['value'] = temp_value
        step['numerator'] = temp_denominator
        step['denominator'] = temp1

        chk_index = index - 1
        while chk_index > 0:
            if step == step_buffer[chk_index]:
                running = False
                res = index - chk_index
                break
            chk_index -= 1
    return res

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

