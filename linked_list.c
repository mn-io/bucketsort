#include "linked_list.h"

#define PRINT_LINEBREAK 40

List *list_create() {
	List *new_list = (List *)malloc(sizeof(List));

	if(new_list == NULL) {
		fprintf(stderr, "Couldn't create List.\n");
		exit(EXIT_FAILURE);
	}

	new_list->size = 0;
	new_list->head = NULL;
	new_list->last = NULL;

	return new_list;
}

Element *list_create_element(int *ptr) {
	Element *new_element = (Element *)malloc(sizeof(Element));

	if(new_element == NULL) {
		fprintf(stderr, "Couldn't create List element.\n");
		exit(EXIT_FAILURE);
	}

	new_element->ptr = ptr;
	new_element->next = NULL;
	return new_element;
}

void list_append(List *list, Element *element) {
	if(list->head == NULL) {
		list->head = element;
	}

	if(list->last != NULL) {
		list->last->next = element;
	}

	list->last = element;
	list->size++;
}

void list_destroy(List *list) {
	Element *current = list->head;
	Element *element = NULL;

	while(current != NULL) {
		element = current;
		current = current->next;
		free(element);
	}

	list->size = 0;
	memset(list, 0, sizeof(List));
	free(list);
	list = NULL;
}

void list_to_array(List *list, int values[]) {
	Element *current = list->head;

	int i = 0;
	while(current != NULL) {
		values[i] = *(current->ptr);
		current = current->next;
		i++;
	}
}

void list_print(List *list) {
	Element *current = list->head;
	int i = 0;
	while(current != NULL) {
		printf("%i", *(current->ptr));
		current = current->next;
		if(current != NULL) {
			printf(" -> ");
		}
		if(0 == i+1 % PRINT_LINEBREAK) {
			printf("\n");
		}
		i++;
	}
	printf("\n");
}
