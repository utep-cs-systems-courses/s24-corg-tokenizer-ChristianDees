#include <stdio.h>
#include "history.h"
#include "tokenizer.h"

// returns 1 if two pointers are of same characters, 0 if not
int wordsMatch(char *a, char *b){
  int i = 0;
  // iterates through both pointers
  while(a[i] != '\0' || b[i] != '\0'){
    // return 0 once a character does not match
    if(a[i] != b[i])return 0;
    i++;
  }
  // return 0 if strings differ in length
  return(a[i] != '\0' || b[i] != '\0')?0:1;
  
}



int main(){
  
  // maximum size for user input including '\0'
  char input[101];
  List *history = init_history();
  char *h_command = "history";
  char *quit = "quit";
  // continuously ask for input until user quits
 start:
  while(1){
    printf("> ");
    scanf(" %[^\n]", input);
    int len = 0;
    // check user input size to prevent buffer overflow
    while(input[len] != '\0')
      len++;
    if(len > 100){
      printf("Input is too large\n");
      goto quit;
    }
    // tokenize input
    char **token_array = tokenize(input);
    // malloc check
    if(token_array == NULL){
      printf("Failed to tokenize input string");
      goto quit;
    }
    // add input to history as long as it is not a call to a history id
    if(input[0] != '!')add_history(history, input);
    // case user calls a string from history
    if(input[0] == '!'){
      int id = 0;
      for(int i = 1; i < len; i++)
	id = id * 10 + (input[i] - 48);
      // return string with provided id from history
      char *id_string = get_history(history, id);
      if(id_string != NULL){
	printf("%s\n", id_string);
	// if string was history command, perform the command again
	if(wordsMatch(id_string, h_command))goto p_history;
      }
      // if user enters history command, perform the command
    } else if (wordsMatch(input,h_command)){
      goto p_history; 
    }else if (wordsMatch(input, quit)){
      // if user enters quit command, exit the program while freeing the token_array memory
      free_tokens(token_array);
      goto quit;
    } else {
      // print tokens
      print_tokens(token_array);
    }
    // free the toke_array memory
    free_tokens(token_array);
  }

  // history command to print all content of the history
 p_history:
  print_history(history);
  goto start;
  // quit command to exit the program
 quit:
  free_history(history);
  return 0;
}
