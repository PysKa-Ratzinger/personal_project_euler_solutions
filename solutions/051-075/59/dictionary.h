#pragma once

#include <stdio.h>

/** DICTIONARY.H
 *
 *    A dictionary is represented as a tree of letter nodes. A word is made
 *  by following any path from the root node to an end node without going
 *  back. A ASCII representation of the tree is as follows:
 *
 *    Tree containing the words {dog; dogs; dopler; apple}
 *
 * :-+-D---O-+-G*--S*            // Words can share multiple nodes
 *   |       `-P---L---E---R*    // Asterisks represent end letters
 *   +-A---P---P---L---E*
 *
 *  Author: Ricardo Catalão
 */

/**   An atomic structure which can be used to access every word in the
 *  dictionary.
 */
struct dictionary{
  /** First starting letter of the dictionary. */
  struct letter_node *first_root;

  /** Last starting letter of the dictionary. */
  struct letter_node *last_root;
};

/**   Letter node inside the dictionary. It constitutes a building block for
 *  a word. Words are stored as a sequence of letter nodes inside a dictionary.
 */
struct letter_node{
  /** The character this node represents. */
  unsigned char letter;

  /** Whether or not a word can end in this node. */
  unsigned char is_final;

  /**   The next letter with the same preceding letters as this one
   */
  struct letter_node *next_letter;

  /**   Smaller dictionary containing words that start with the letters
   *  visited up to this node.
   */
  struct dictionary child_dict;
};

/** Single search unit data. Part of the dictionary_search_status structure
 */
struct dictionary_search_node_data{
  /** Last node analyzed. */
  struct letter_node *node;

  /** Next search unit data. */
  struct dictionary_search_node_data *next_data;
};

/**   Persistent data for the feed_search(), reset_search() and
 *  is_search_over() methods
 */
struct dictionary_search_status{
  /** The dictionary we are searching */
  struct dictionary *dict;

  /** First node of a linked list of data */
  struct dictionary_search_node_data *first_node;

  /** Whether or not the word was found in the dictionary */
  int is_found;
};

/**   Creates a dictionary from a text file. Every word must be separated
 *  by a new line (although CSV files work as well). Characters that are not
 *  within the range [a, z] or [A, Z] will not be considered parts of a word.
 *    Capitalization will be ignored.
 */
struct dictionary *create_dictionary(FILE* file);

/**   Prints a dictionary to stdout
 */
void print_dictionary(struct dictionary *dict, int level);

/**   Frees a previously created dictionary from the memory.
 */
void free_dictionary(struct dictionary *dictionary);

/** *** WORD SEARCHING METHODS *** */

/**   Initializes the search information to the default state. The first
 *  letter is set to the letter passed as an argument. The rest of the letters
 *  of the word must be fed using feed_search().
 */
struct dictionary_search_status *init_search(struct dictionary* dict,
                                              unsigned char letter);

/**   Feeds a letter to the search algorithm.
 */
void feed_search(struct dictionary_search_status *status, unsigned char letter);

/**   Resets the search to a search with the letter passed as an argument as
 *  the first letter of the word. (Same as init_search, except we don't need
 *  to recreate the status structure).
 */
void reset_search(struct dictionary_search_status *status, unsigned char letter);

/**   Returns whether or not a word was found
 */
int is_search_over(struct dictionary_search_status *status);

/**   Cleans all the memory allocated to the search status
 */
void clean_dictionary_search_status(struct dictionary_search_status *status);
