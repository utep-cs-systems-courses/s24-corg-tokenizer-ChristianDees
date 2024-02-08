#ifndef _TOKENIZER_
#define _TOKENIZER_


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c){
  return(c == ' ' | c == '\t')?1:0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c){
  return(c!=' ' && c != '\t')?1:0;
}

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */
char *token_start(char *str){
  while(*str != '\0'){
    if(non_space_char(*str)){
      str++;
    } else {
      str++;
      return str;
    }
  }
}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token){
  while(*token != '\0'){
    if(non_space_char(*token))
      token++;
    if(space_char(*token))
      return token;
  }
  return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str){
  int count = 0;
  while(*str != '\0'){
    if(non_space_char(*str)){
      count++;
      str = token_start(str);
      if (str == NULL)
	break;
      str++;
    }
  }
  return count;
}


/* Returns a freshly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){
  char *copy_of_word = malloc(sizeof(char)*(len+1));
  if(copy_of_word == NULL){
    printf("Failed to allocate memory");
    break;
  }
  for(int i = 0; i < len; i++)
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
char **tokenize(char* str);

/* Prints all tokens. */
void print_tokens(char **tokens);

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens);

#endif
