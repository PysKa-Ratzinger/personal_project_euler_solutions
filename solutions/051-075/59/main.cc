#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/dictionary.hpp"
#include "../../utils/utils.h"

#define BUFFER_SZ 4096
#define INPUT_FILE_NAME "input.txt"
#define DICTIONARY_FILE_NAME "dict2.txt"

struct message{
    size_t length;
    size_t size;
    unsigned char* content;
};

int ask_input_file(FILE** input_file){
    char buffer[BUFFER_SZ];
    FILE* temp;

    printf("File name: ");
    fgets(buffer, BUFFER_SZ, stdin);
    buffer[strlen(buffer)-1] = '\0';
    temp = fopen(buffer, "r");

    if(temp == NULL){
        perror("fopen");
        return 1;
    }

    *input_file = temp;
    return 0;
}

struct message* create_message(){
    struct message* res = (struct message*)malloc(sizeof(struct message));
    if(res == NULL) return NULL;
    res->length = BUFFER_SZ;
    res->size = 0;
    res->content = (unsigned char*)malloc(sizeof(unsigned char)*BUFFER_SZ);
    if(res->content == NULL){
        free(res);
        return NULL;
    }
    return res;
}

void free_message(struct message* msg){
    free(msg->content);
    free(msg);
}

int read_message_from_file(struct message* msg, FILE* input_file){
    int c;
    char curr_value = 0;
    bool read_char = false;
    while((c = getc(input_file)) != EOF){
        if(c >= '0' && c <= '9'){
            curr_value *= 10;
            curr_value += c - '0';
            read_char = true;
        }else if(read_char){
            msg->content[msg->size++] = curr_value;
            if(msg->size == msg->length){
                return 1;
            }
            curr_value = 0;
            read_char = false;
        }
    }
    if(read_char == true){
        msg->content[msg->size++] = curr_value;
    }
    msg->content[msg->size] = '\0';
    return 0;
}

unsigned long crack_message(struct message* msg, struct dictionary* dict){
    unsigned char key[3]{'a', 'a', 'a'};
    unsigned char definitive_key[3] = {0};
    unsigned num_occurrences = 0;
    unsigned char* content = msg->content;
    size_t size = msg->size;
    while(key[0] <= 'z'){
        for(size_t i=0; i<size; i++){
            content[i] ^= key[i%3];
        }

        unsigned temp = 0;
        bool prevLetter = false;
        struct dictionary_search_status* status = init_search(dict, content[0]);
        for(unsigned i=1; i<size; i++){
            unsigned char c = content[i];
            if(is_letter(c)){
                if(prevLetter){
                    feed_search(status, c);
                }else{
                    reset_search(status, c);
                    prevLetter = true;
                }
            }else if(c == ' '){
                if(prevLetter && is_search_over(status)){
                    temp++;
                }
                prevLetter = false;
            }
        }
        if(prevLetter && is_search_over(status)){
            temp++;
        }
        clean_dictionary_search_status(status);

        if(temp > num_occurrences){
            for(int i=0; i<3; i++){
                definitive_key[i] = key[i];
                num_occurrences = temp;
            }
        }

        for(size_t i=0; i<size; i++){
            content[i] ^= key[i%3];
        }

        for(int i=2; i>=0; i--){
            key[i]++;
            if(key[i] > 'z'){
                if(i == 0) break;
                key[i] = 'a';
            }else{
                break;
            }
        }
    }

    unsigned long answer = 0;

    // printf("---------------------* %c%c%c *---------------------\n",
    //         definitive_key[0], definitive_key[1], definitive_key[2]);
    for(size_t i=0; i<size; i++){
        answer += content[i] ^ definitive_key[i%3];
        // printf("%c", content[i] ^ definitive_key[i%3]);
    }
    // printf("\n");

    return answer;
}

int main(){
    FILE* input_file;
    FILE* dict_file;
    struct message* msg;
    struct dictionary* dictionary;
    unsigned long answer = 0;
    int err;
    int res = EXIT_FAILURE;

    // printf("What is the name of the input file?\n");
    // if((err = ask_input_file(&input_file)) != 0)
    //     return err;
    input_file = fopen(INPUT_FILE_NAME, "r");
    if(input_file == NULL)
        return EXIT_FAILURE;

    msg = create_message();
    if(msg != NULL){
        err = read_message_from_file(msg, input_file);
        if(err == 0){
            // printf("What is the name of the dictionary to use to solve this?\n");
            // err = ask_input_file(&dict_file);
            // if(err == 0){
            dict_file = fopen(DICTIONARY_FILE_NAME, "r");
            if(dict_file != NULL){
                dictionary = create_dictionary(dict_file);
                if(dictionary != NULL){
                    answer = crack_message(msg, dictionary);
                    res = EXIT_SUCCESS;
                    free_dictionary(dictionary);
                }
                fclose(dict_file);
            }
        }
        free_message(msg);
    }
    fclose(input_file);

    if(res == EXIT_SUCCESS){
        printf("If you can trust me, the number you are "
                "looking for is %lu\n", answer);
    }

    return res;
}
