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
    add_history(history, input);
    char **token_array = tokenize(input);
    if(token_array == NULL){
      printf("Failed to tokenize input string");
      break;
    }
    if(input[0] == '!'){
      int id = 0;
      for(int i = 1; i < len; i++)
	id = id * 10 + (input[i] - 48);
      char *id_string = get_history(history, id);
      if(id_string != NULL)printf("ID: %d contains string %s\n",id,id_string);
    } else if (input[0] == 'h' && input[1] == 'i' && input[2] == 's' && input[3] == 't' && input[4]== 'o' && input[5] == 'r' && input[6] == 'y' && input[7] == '\0'){
      print_history(history);
    } else if(input[0] == 'q' && input[1] == 'u' && input[2] == 'i' && input[3] == 't' && input[4]== '\0') {
      break;
    } else {
      print_tokens(token_array);
    }
    free_tokens(token_array);
  }
  free_history(history);
  return 0;
}
