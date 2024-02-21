#include "stdio.h"
#include "stdlib.h"
#include "tokenizer.h"



// returns true if character is a space/tab
int space_char(char c){
  return(c == ' ' | c == '\t')?1:0;
}

// returns true if character is not a space/tab
int non_space_char(char c){
  return !space_char(c);
}

// returns pointer to the next token
char *token_start(char *str){
  // continue through spaces until reached character or end of string
  while(*str != '\0' && space_char(*str))
    str++;
  if(*str == '\0')return NULL;
  return str;
}

// returns the terminator of a token
char *token_terminator(char *token){
  // continue through entire token until reached a delimiter
  while(*token != '\0' && non_space_char(*token))
    token++;
  return token;
}

// return total tokens within a string
int count_tokens(char *str){
  int count = 0;
  while(*str != '\0'){   //continue through entire token
    while(*str != '\0' && space_char(*str))  // skip over leading spaces
      str++;
    if(*str == '\0')break; // leave once reached end of str
    count++;
    while(*str != '\0' && non_space_char(*str)) // iterate over token until it ends
      str++;
  }
  return count;
}

// return copy of a string
char *copy_str(char *inStr, short len){
  char *copy_of_word = malloc(sizeof(char)*(len+1)); //allocate memory to hold size of inStr
  if(copy_of_word == NULL){   // default check case for when allocating memory
    printf("Failed to allocate memory");
    return NULL;
  }
  for(int i = 0; i < len; i++)   // copy each letter within origial string to the copy
    copy_of_word[i] = inStr[i];
  copy_of_word[len] = '\0';   // zero terminate copy
  return copy_of_word;
}


char **tokenize(char* str){

  int total_tokens = count_tokens(str);   // total amount of tokens within str
  // intialize array of char pointers pointing to each token
  // defualt memory allocation check
  char **token_array = malloc(sizeof(char*)*(total_tokens + 1));   
  if(token_array == NULL){
    printf("Failed to allocate token_array memmory");
    return NULL;
  } 
  for(int i = 0; i < total_tokens; i++){   // iterate through each token
    str = token_start(str);   // set pointer to next token available
    char *term = token_terminator(str); 
    int len = term - str;  // length of current token
    token_array[i] = malloc(sizeof(char)*(len+1)); // set index to a size of specific token
    if(token_array[i] == NULL){   // free every allocated memory if this allocation fails
      printf("Failed to allocate memory for token"); 
      for(int x = 0; x < i; x++)
	free(token_array[x]);
      free(token_array);
      return NULL;
    }
    char *copy = copy_str(str,len);  // copy of current token
    for(int x = 0; x < len; x++) // copies content from current token to a pointers pointer
      token_array[i][x] = copy[x];
    free(copy); // free allocated memory as it is going to change for the next token
    token_array[i][len] = '\0'; // end pointers pointer with a zero-terminator
    str = token_start(term); // set str to point to the next token
  }
  token_array[total_tokens] = NULL;
  return token_array;
  
}

// print each token
void print_tokens(char **tokens){

  int index = 0;
  while(tokens[index] != NULL){   // go through entire pointer of pointers
    printf("%s\n", tokens[index]);   // print current pointer that is being pointed to
    index++;
  }
}

// free every pointer
void free_tokens(char **tokens){

  int index = 0;
  while(tokens[index] != NULL){   // go through entire pointer of pointers
    free(tokens[index]);   // free allocated memory for each pointer 
    index++;
  }
  free(tokens);   // free the overall pointer
}

