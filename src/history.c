#include <stdio.h>
#include <stdlib.h>
#include "history.h"


// Initialize LL
List* init_history(){
  // points to a structure "list" that will have an item
  // that item has value id, string, and pointer to next item
  List *history = malloc(sizeof(List));
  if(history == NULL){
    printf("failed to allocate history LL");
    return NULL;
  }
  history->root = NULL;
  return history;
}

// Add a history item at end of list
// List *list = the linked list
// char* str = the string to store
void add_history(List *list, char *str){

  Item *newItem = malloc(sizeof(Item));
  if(newItem == NULL){
    printf("failed to allocate new item strucutre");
    return;
  }
  // get length of str
  int len = 0;
  while(str[len] != '\0')
    len++;
  // allocate space for copy of str
  newItem->str = malloc(len+1);
  // default check malloc
  if(newItem->str == NULL){
    printf("failed to allocate memory for string");
    free(newItem);
    return;
  }
  // copy str content to items str
  for(int i = 0; i < len; i++)
    newItem->str[i] = str[i];
  newItem->str[len] = '\0';   // terminate items str
  newItem->next = NULL; //newItem is ready to be added into list
  
  // if list is empty
  if(list->root == NULL){
    // first id starts at 1
    newItem->id = 1;
    list->root = newItem; // set head of LL to new item
  } else {
    // if list is not empty
    Item *temp = list->root;
    // find end of list
    while(temp->next != NULL){
      temp = temp->next;
    }
    // add item to end of list and increment id
    newItem->id = temp->id + 1;
    temp->next = newItem;
  }
}

// retrive string stored in node where item->id == id
char *get_history(List *list, int id){

  Item *temp = list->root;
  // edgecase for id request
  if(id < 1){
    printf("id is not within bounds\n");
    return NULL;
  }
  // find item with requested id
  while(temp!=NULL && temp->id != id)
    temp = temp->next;

  // if no items with requested id is in list
  if(temp==NULL){
    printf("No item with that id found\n");
    return NULL;
  }
  // return the string the item with requested id has
  char *string = temp->str;
  return string;

}

// print entire content of linkedlist
void print_history(List *list){
  if(list == NULL){
    printf("List is empty");
    return;
  }
  Item *current = list->root;
  // iterate through every item within list
  while(current != NULL){
    printf("%d %s\n", current->id, current->str);
    current = current->next;
  }
 
  
}
// Freee history list and the strings it referecenes
void free_history(List *list){
  if(list == NULL)return;
  Item *current = list->root;
  // iterate through every item within list
  while (current != NULL){
    Item *currentPointer = current;   // point towards current item
    current = current->next;   // change current to next item
    free(currentPointer->str);   // free the current item
    free(currentPointer);   // free the current pointer as its going to change
  }
  free(list);   // after all string pointers are freed, free the actual list 
}
  
