#ifndef UTILS_H
#define UTILS_H

/**   Returns whether or not this unsigned char cast to int value is, or not,
 *  a letter. (a <= letter <= z) || (A <= letter <= Z).
 */
int is_letter(int letter);

/**   Returns the unsigned char cast to int representation of the lower case
 *  unsigned char cast to int value passed as an argument.
 */
int to_lowercase(int letter);

#endif
