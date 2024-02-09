#include <stdio.h>
#include "tokenizer.h"

int main(){

  char input[100];
  printf("> ");
  scanf(" %[^\n]",input);
  char **token_array = tokenize(input);
  if(token_array == NULL){
    printf("Failed to tokenize input string");
  }
  print_tokens(token_array);
  
  
  return 0;
}
