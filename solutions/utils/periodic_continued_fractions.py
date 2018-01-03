#!/usr/bin/env python

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

def periodic_continued_fractions(number):
    squareNumber = square(number)
    if squareNumber**2 == number:
        return {'values': None, 'period': 0}
    index = 0
    res = 0

    step_buffer = [{'value': squareNumber,
                    'numerator': 1,
                    'denominator': -squareNumber}]
    step = step_buffer[0]
    running = True

    while running:
        index += 1
        step_buffer += [{}]
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

    step_buffer = step_buffer[:-1]
    return {'values': step_buffer, 'period': res}

def periodic_continued_fractions_period(number):
    res = periodic_continued_fractions(number)
    return res['period']

class PCFValues:
    index = 0
    indexes = [0]
    fractions = []
    currNumerator = 0
    currDenominator = 0

    def __init__(self, fractions):
        self.fractions = fractions
        self.currNumerator = fractions['values'][0]['value']
        self.currDenominator = 1
        self.index = 0
        self.indexes = [0]

    def incrementIndex(self):
        self.index += 1
        if self.index >= len(self.fractions['values']):
            self.index -= self.fractions['period']
        self.indexes += [self.index]

    def getCurrentValue(self):
        return [self.currNumerator, self.currDenominator]

    def getNextValue(self):
        self.incrementIndex()
        a = 1
        b = 0
        for i in range(len(self.indexes)):
            val = self.fractions['values'][self.indexes[-i-1]]['value']
            temp = a
            a = b
            b = temp
            a += val * b
        self.currNumerator = a
        self.currDenominator = b
        return [a, b]

