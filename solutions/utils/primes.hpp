#pragma once

#include <vector>
#include <list>

/**
 * Gets the prime whose index is equal to the one passed as an argument
 * @param  index index of the prime to be returned
 * @return       the prime whose indes is equal to the one passed as an argument
 */
unsigned long getPrime(unsigned index);

/**
 * @brief Returns a list with every prime which is smaller than the given
 * 	number
 *
 * @param max The maximum value to be returned
 *
 * @return A list with the requested primes is returned
 */
std::list<unsigned long> getPrimesSmallerThan(unsigned long max);

/**
 * @brief Gets a list of divisors of a number
 *
 * @param number The number to get the divisions of
 *
 * @return Returns a vector with all the divisors of a number
 */
std::vector<unsigned long> getDivs(unsigned long number, bool withReps);

/**
 * Checks whether a number is a prime, or not
 * @param  number the number to be checked
 * @return        TRUE if it is prime, FALSE otherwise
 */
bool isPrime(unsigned long number);

