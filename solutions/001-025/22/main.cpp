#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../utils/bst.h"

#define STR_LEN 512

int min(int a, int b){
  return a < b ? a : b;
}

int name_score(std::string str, int depth){
  int res = 0;
  printf("%d-%s:\t", depth, str.c_str());
  for(unsigned int i=0; i<str.length(); i++){
    res += str.at(i) - 'A' + 1;
    printf("%d", str.at(i) - 'A' + 1);
    if(i != str.length()-1){
      printf(" + ");
    }
  }
  printf(" = %d * %d = ", res, depth);
  res *= depth;
  printf("%d\n", res);
  return res;
}

unsigned long long get_total_score(Node<std::string>* node, int *depth){
  unsigned long long res = 0;
  if(node->_left_child)
    res += get_total_score(node->_left_child, depth);

  int temp = name_score(*node->_elem, *depth);
  *depth = *depth + 1;
  if(res + temp < res){
    printf("DANGER: OVERFLOW!!!\n");
  }
  res += temp;

  if(node->_right_child)
    res += get_total_score(node->_right_child, depth);

  return res;
}

char* read_string(char *s, int size, FILE *stream){
  int c;
  int state = 0;
  int sz = 0;

  while(sz < size){
    c = fgetc(stream);
    if(c == EOF)
      return NULL;

    switch(state){
      case 0:
        if(c == '"'){
          state = 1;
        }
        break;

      case 1:
        if(c == '"'){
          s[sz++] = '\0';
          return s;
        }else{
          s[sz++] = c;
        }
        break;
    }
  }
  return NULL;
}

void remove_newline(char *s){
  while(*s != '\n'){
    s++;
  }
  *s = '\0';
}

int main(int argc, char *argv[]){
  char buffer[STR_LEN];

  if(argc != 2){
    printf("This is not how you use the program...\n");
    return 1;
  }

  FILE* fd = fopen(argv[1], "r");

  if(fd == NULL){
    perror("fopen");
    return 1;
  }

  BST<std::string> *bst = new BST<std::string>();

  // Insert all elements
  while(read_string(buffer, STR_LEN, fd)){
    std::string *str = new std::string(buffer);
    bst->insert(str);
  }

  int depth = 1;
  unsigned long long res = get_total_score(bst->_head_node, &depth);
  printf("If you can trust me, the total score you are looking for is %llu\n", res);

  delete bst;

  fclose(fd);
  return 0;
}
