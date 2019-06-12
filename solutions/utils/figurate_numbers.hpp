#pragma once

/**
 * Calculates polygonal numbers based on the values of the arguments. If a
 * value of 3 is passed with 'sides', the function calculates triangular
 * numbers, and returns the whose whose index is equal to the one passed as
 * an argument. If the value is 4, square numbers. And so on.
 * @param  sides Number of sides of the polygonal number
 * @param  index Index of the number we want
 * @return       The polygonal number with sides and index equal to the ones
 *                   passed as an argument
 */
unsigned long polygonal_number(unsigned long sides, unsigned long index);

/**
 * Calculates whether a number is (or isn't) a polygonal number with sides
 * equal to the value of sides passed as an argument.
 * @param  number the number to be checked
 * @param  sides  the number of sides it should have
 * @return        Ff the number is a polygonal number with sides equal to
 *                   @{sides}, it's index is returned, else, -1 is returned.
 */
long long is_polygonal_number(unsigned long number, unsigned long sides);
