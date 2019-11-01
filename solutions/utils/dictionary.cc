#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.hpp"
#include "utils.hpp"

struct dictionary *create_dictionary(FILE* file){
	int curr_letter;
	struct dictionary *result = NULL;
	struct letter_node *curr_node = NULL;

	result = (struct dictionary*) malloc(sizeof(struct dictionary));
	memset(result, 0, sizeof(struct dictionary));

	curr_letter = fgetc(file);
	while(curr_letter != EOF){
		if(!is_letter(curr_letter)){

			// Maybe we reached the end of a word
			if(curr_node){
				curr_node->is_final = 1;
				curr_node = NULL;
			}
		}else{
			curr_letter = to_lowercase(curr_letter);

			struct letter_node *next;
			if(!curr_node){
				next = result->first_root;
			}else{
				next = curr_node->child_dict.first_root;
			}

			while(next){
				if(next->letter == curr_letter){
					break;
				}
				next = next->next_letter;
			}

			if(next){ // The letter already exists
				curr_node = next;
				next = NULL;
			}else{  // The letter does not exist
				struct letter_node *temp = (struct letter_node*)
					malloc(sizeof(struct letter_node));
				memset(temp, 0, sizeof(struct letter_node));
				temp->letter = curr_letter;

				if(!curr_node){ // If this is the first letter

					if(result->last_root){  // If dictionary has elements
						result->last_root->next_letter = temp;
						result->last_root = temp;
					}else{
						result->first_root = temp;
						result->last_root = temp;
					}

				} else {  // If this is not the first letter
					if(curr_node->child_dict.last_root){  // If dictionary has elements
						// Adds letter to the end of the smaller dictionary
						curr_node->child_dict.last_root->next_letter = temp;
						curr_node->child_dict.last_root = temp;
					}else{
						curr_node->child_dict.first_root = temp;
						curr_node->child_dict.last_root = temp;
					}

				}
				curr_node = temp;
			}
		}

		curr_letter = fgetc(file);
	}

	//EOF found
	// Maybe we reached the end of a word without newline
	if(curr_node){
		curr_node->is_final = 1;
		curr_node = NULL;
	}

	return result;
}

void print_dictionary(struct dictionary *dict, int level){
	char buffer[250];
	memset(&buffer, 0, sizeof(char) * 250);
	int whitespace = level + 1;

	if(!dict)
		return;

	struct letter_node *curr = dict->first_root;
	while(curr){
		if(curr != dict->first_root || level == 0){
			int i;
			for(i=0; i<whitespace; i++){
				printf(" ");
			}
		}
		if(curr->is_final){
			printf("%c", curr->letter + 'A' - 'a');
		}else{
			printf("%c", curr->letter);
		}
		if(curr->child_dict.first_root){
			print_dictionary(&curr->child_dict, level+1);
		}else{
			printf("\n");
		}
		curr = curr->next_letter;
	}
}

void free_child_dictionary(struct dictionary *dictionary){
	if(!dictionary)
		return;

	struct letter_node *curr = dictionary->first_root;
	while(curr){
		free_child_dictionary(&curr->child_dict);
		struct letter_node *next = curr->next_letter;
		free(curr);
		curr = next;
	}
}

void free_dictionary(struct dictionary *dictionary){
	if(!dictionary)
		return;

	struct letter_node *curr = dictionary->first_root;
	while(curr){
		free_child_dictionary(&curr->child_dict);
		struct letter_node *next = curr->next_letter;
		free(curr);
		curr = next;
	}

	free(dictionary);
}

struct dictionary_search_status *init_search(struct dictionary *dict,
		unsigned char letter){
	struct dictionary_search_status *result;

	result = (struct dictionary_search_status*)
		malloc(sizeof(struct dictionary_search_status));
	memset(result, 0, sizeof(struct dictionary_search_status));
	result->dict = dict;

	struct letter_node *curr = dict->first_root;
	while(curr){
		if(curr->letter == letter){
			result->first_node = (struct dictionary_search_node_data*)
				malloc(sizeof(struct dictionary_search_node_data));
			memset(result->first_node, 0, sizeof(struct dictionary_search_node_data));
			result->first_node->node = curr;
			if(curr->is_final){
				result->is_found = 1;
			}
		}
		curr = curr->next_letter;
	}

	return result;
}

void feed_search(struct dictionary_search_status *status, unsigned char letter){
	struct dictionary_search_node_data *curr = status->first_node;
	struct dictionary_search_node_data *prev = NULL;
	status->is_found = 0;
	while(curr){
		struct letter_node *curr_letter = curr->node->child_dict.first_root;
		int found_letter = 0;
		while(curr_letter){
			if(curr_letter->letter == letter){
				found_letter = 1;
				curr->node = curr_letter;
				status->is_found = curr_letter->is_final;
				break;
			}
			curr_letter = curr_letter->next_letter;
		}
		if(!found_letter){
			struct dictionary_search_node_data *temp = curr->next_data;
			free(curr);
			curr = temp;
			if(prev){
				prev->next_data = curr;
			}else{
				status->first_node = curr;
			}
		}else{
			prev = curr;
			curr = curr->next_data;
		}
	}
}

void reset_search(struct dictionary_search_status *status, unsigned char letter){
	// Resets the search status
	struct dictionary_search_node_data *data = status->first_node;
	while(data){
		struct dictionary_search_node_data *temp = data->next_data;
		free(data);
		data = temp;
	}
	status->first_node = NULL;
	status->is_found = 0;

	// Sets the first letter
	struct dictionary *dict = status->dict;
	struct letter_node *curr = dict->first_root;
	while(curr){
		if(curr->letter == letter){
			status->first_node = (struct dictionary_search_node_data*)
				malloc(sizeof(struct dictionary_search_node_data));
			memset(status->first_node, 0, sizeof(struct dictionary_search_node_data));
			status->first_node->node = curr;
			if(curr->is_final){
				status->is_found = 1;
			}
		}
		curr = curr->next_letter;
	}
}

int is_search_over(struct dictionary_search_status *status){
	return status->is_found;
}

void clean_dictionary_search_status(struct dictionary_search_status *status){
	struct dictionary_search_node_data *curr = status->first_node;
	while(curr){
		struct dictionary_search_node_data *temp = curr->next_data;
		free(curr);
		curr = temp;
	}
	free(status);
}
