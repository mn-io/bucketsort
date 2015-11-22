#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element_ {
  int *ptr;
  struct element_ *next;
} Element;

typedef struct list_ {
  int size;
  struct element_ *head;
  struct element_ *last;
} List;

List *list_create();

Element *list_create_element(int *ptr);

void list_append(List *list, Element *element);

void list_destroy(List *list);

void list_to_array(List *list, int values[]);

void list_print(List *list);
