#include "stdio.h"
#include "stdlib.h"
#include "tokenizer.h"



/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */

// returns true if character is a space/tab
int space_char(char c){
  return(c == ' ' | c == '\t')?1:0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */

// returns true if character is not a space/tab
int non_space_char(char c){
  return !space_char(c);
}

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */


// returns pointer to the next token
char *token_start(char *str){
  while(*str != '\0'){
    if(non_space_char(*str)){
      str++;
    }
    if(space_char(*str)){
      str++;
      return str;
    }
  }
  return NULL;
}

/* Returns a pointer terminator char following *token */

// returns the terminator of a token
char *token_terminator(char *token){
  // continue through entire token
  while(*token != '\0'){
    // if character is not empty space, continue iterating
    if(non_space_char(*token))
      token++;
    // return the terminator that ends the token
    if(space_char(*token))
      return token;
  }
  return token;
}

/* Counts the number of tokens in the string argument. */

// return total tokens within a string
int count_tokens(char *str){
  int count = 0;
  while(*str != '\0'){   //continue through entire token
    if(non_space_char(*str)){   // while there is another token, add 1, if not break
      count++;
      str = token_start(str);
      if (str == NULL)
	break;
    }
    str++;
  }
  
  return count;
}


/* Returns a freshly allocated new zero-terminated string 
   containing <len> chars from <inStr> */

// return copy of a string
char *copy_str(char *inStr, short len){
  char *copy_of_word = malloc(sizeof(char)*(len+1)); //allocate memory to hold size of inStr
  if(copy_of_word == NULL){   // default check case for when allocating memory
    printf("Failed to allocate memory");
    return NULL;
  }
  for(int i = 0; i < len; i++)   // copy each letter within origial string to the copy
    copy_of_word[i] = inStr[i];
  copy_of_word[len] = '\0';
  return copy_of_word;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/


char **tokenize(char* str){

  int total_tokens = count_tokens(str);   // total amount of tokens within str
  char **aoc = malloc(sizeof(char*)*(total_tokens + 1));   
  if(aoc == NULL){
    printf("Failed to allocate aoc memmory");
    return NULL;
  }

  for(int i = 0; i < total_tokens; i++){   // iterate through each token
    char *term = token_terminator(str);
    int len = term - str;  // length of current token
    aoc[i] = malloc(sizeof(char)*(len+1));
    if(aoc[i] == NULL){   // free every allocated memory if this allocation fails
      printf("Failed to allocate memory for token"); 
      for(int x = 0; x < i; x++)
	free(aoc[x]);
      free(aoc);
      return NULL;
    }
    char *copy = copy_str(str,len);  // copy of current token
    for(int x = 0; x < len; x++) // copies content from current token to a pointers pointer
      aoc[i][x] = copy[x];
    free(copy); // free allocated memory as it is going to change for the next token
    aoc[i][len] = '\0'; // end pointers pointer with a zero-terminator
    str = token_start(str); // set str to point to the next token
  }
  return aoc;
  
}

/* Prints all tokens. */

// print each token
void print_tokens(char **tokens){

  int index = 0;
  while(tokens[index] != NULL){   // go through entire pointer of pointers
    printf("%s\n", tokens[index]);   // print current pointer that is being pointed to
    index++;
  }
  free_tokens(tokens);   // free the allocated memory
}

/* Frees all tokens and the vector containing themx. */

// free every pointer
void free_tokens(char **tokens){

  int index = 0;
  while(tokens[index] != NULL){   // go through entire pointer of pointers
    free(tokens[index]);   // free allocated memory for each pointer 
    index++;
  }
  free(tokens);   // free the overall pointer
}

