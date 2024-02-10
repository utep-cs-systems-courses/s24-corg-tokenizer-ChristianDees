#include <stdio.h>
#include "history.h"
#include "tokenizer.h"
int main(){

  char input[101];
  List *history = init_history();
  while(1){
    printf("> ");
    scanf(" %[^\n]", input);
    int len = 0;
    while(input[len] != '\0')
      len++;
    if(len > 100){
      printf("Input is too large\n");
      break;
    }
    int i;
    for(i = 0; input[i] != '\0' && input[i] == "quit"[i];i++);
    if(input[i] == '\0' && "quit"[i] == '\0')break;
    char **token_array = tokenize(input);
    add_history(history, input);
    if(token_array == NULL){
      printf("Failed to tokenize input string");
      break;
    }
    print_tokens(token_array);
  }
  print_history(history);
 
  
  
  return 0;
}
