#include "utils.h"

int is_letter(int letter){
  return (letter >= 'a' && letter <= 'z') ||
          (letter >= 'A' && letter <= 'Z');
}

int to_lowercase(int letter){
  if(letter >= 'A' && letter <= 'Z'){
    return letter - 'A' + 'a';
  }else{
    return letter;
  }
}
