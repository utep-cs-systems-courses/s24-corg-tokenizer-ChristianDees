#ifndef _HISTORY_
#define _HISTORY_

typedef struct s_Item {
  int id;
  char *str;
  struct s_Item *next;
}Item;
typedef struct s_List {
  struct s_Item *root;
}List;
List* init_history();
void add_history(List *list, char *str);
char *get_history (List *list, int id);
void print_history(List *list);
void free_history(List *list);

#endif
