#include <stdio.h>
#include <stdlib.h>

struct singly_linked_int_list{
	int value;
	struct singly_linked_int_list * next;
};

int list_append(struct singly_linked_int_list ** head_ref, int new_value){
	struct singly_linked_int_list * new_node = malloc(sizeof(struct singly_linked_int_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(*head_ref == NULL){
			*head_ref = new_node;
		}else{
			struct singly_linked_int_list * current_node = *head_ref;
			while(current_node->next != NULL){
				current_node = current_node->next;
			}
			current_node->next = new_node;
		}
		return 1;
	}
};

int list_detach(struct singly_linked_int_list ** head_ref, int * detached_value_ref){
	if(*head_ref == NULL){
		return 0;
	}else if((*head_ref)->next == NULL){
		*detached_value_ref = (*head_ref)->value;
		free(*head_ref);
		*head_ref = NULL;
		return 1;
	}else{
		struct singly_linked_int_list * current_node = *head_ref;
		while(current_node->next->next != NULL){
			current_node = current_node->next;
		}
		*detached_value_ref = current_node->next->value;
		free(current_node->next);
		current_node->next = NULL;
		return 1;
	}
};

int list_push(struct singly_linked_int_list ** head_ref, int new_value){
	struct singly_linked_int_list * new_node = malloc(sizeof(struct singly_linked_int_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(*head_ref == NULL){
			*head_ref = new_node;
		}else{
			new_node->next = *head_ref;
			*head_ref = new_node;
		}
		return 1;
	}
};

int list_pop(struct singly_linked_int_list ** head_ref, int * popped_value_ref){
	if(*head_ref == NULL){
		return 0;
	}else{
		*popped_value_ref = (*head_ref)->value;
		struct singly_linked_int_list * temp = *head_ref;
		*head_ref = (*head_ref)->next;
		free(temp);
		return 1;
	}
};

int list_insert(struct singly_linked_int_list ** head_ref, struct singly_linked_int_list * previous_node, int new_value){
	struct singly_linked_int_list * new_node = malloc(sizeof(struct singly_linked_int_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(previous_node == NULL){
			new_node->next = *head_ref;
			*head_ref = new_node;
		}else{
			new_node->next = previous_node->next;
			previous_node->next = new_node;
		}
		return 1;
	}
};

int list_delete(struct singly_linked_int_list ** head_ref, int value_to_del){
	if(*head_ref == NULL){
		return 0;
	}else{
		if((*head_ref)->value == value_to_del){
			struct singly_linked_int_list * temp = *head_ref;
			*head_ref = (*head_ref)->next;
			free(temp);
			return 1;
		}else{
			struct singly_linked_int_list * current_node = *head_ref;
			while(current_node->next != NULL){
				if(current_node->next->value == value_to_del){
					struct singly_linked_int_list * temp = current_node->next;
					current_node->next = current_node->next->next;
					free(temp);
					return 1;
				}
				current_node = current_node->next;
			}
			return 0;
		}
	}
};

void list_clear(struct singly_linked_int_list ** head_ref){
	struct singly_linked_int_list * current_node = *head_ref;
	while(current_node != NULL){
		struct singly_linked_int_list * temp = current_node;
		current_node = current_node->next;
		free(temp);
	}
	*head_ref = NULL;
	return;
};

void list_print(struct singly_linked_int_list * head_ref){
	struct singly_linked_int_list * current_node = head_ref;
	while(current_node != NULL){
		printf("%d ", current_node->value);
		current_node = current_node->next;
	}
	printf("\n");
	return;
};

void find_prev(struct singly_linked_int_list * head_node, struct singly_linked_int_list ** previous_ref, int new_value){
	struct singly_linked_int_list * current_node = head_node;
	*previous_ref = NULL;
	while(current_node != NULL){
		if(current_node->value < new_value){
			*previous_ref = current_node;
			current_node = current_node->next;
			continue;
		}
		break;
	}
	return;
};

int main(){
	struct singly_linked_int_list * head_of_list = NULL;

	printf("1: Append\n");
	printf("2: Detach\n");
	printf("3: Push\n");
	printf("4: Pop\n");
	printf("5: Insert\n");
	printf("6: Delete\n");
	printf("7: Clear\n");
	printf("8: See the list\n");
	printf("9: See all options\n");
	printf("0: Quit\n");

	while(1){
		printf("> ");
		int option;
		scanf("%d", &option);
		if(option == 1){
			int value_to_append;
			printf("The integer to append?: ");
			scanf("%d", &value_to_append);
			if(list_append(&head_of_list, value_to_append)){
				printf("%d appended.\n", value_to_append);
			}else{
				printf("Memory allocation failed while appending node.\n");
				return 0;
			}
		}else if(option == 2){
			int detached_value;
			if(list_detach(&head_of_list, &detached_value)){
				printf("%d detached.\n", detached_value);
			}else{
				printf("There's nothing to detach.\n");
			}
		}else if(option == 3){
			int value_to_push;
			printf("The integer to push?: ");
			scanf("%d", &value_to_push);
			if(list_push(&head_of_list, value_to_push)){
				printf("%d pushed.\n", value_to_push);
			}else{
				printf("Memory allocation failed while pushing node.\n");
				return 0;
			}
		}else if(option == 4){
			int popped_value;
			if(list_pop(&head_of_list, &popped_value)){
				printf("%d popped.\n", popped_value);
			}else{
				printf("There's nothing to pop.\n");
			}
		}else if(option == 5){
			struct singly_linked_int_list * previous_of_new = NULL;
			int value_to_insert;
			printf("The integer to insert?: ");
			scanf("%d", &value_to_insert);
			find_prev(head_of_list, &previous_of_new, value_to_insert);
			if(list_insert(&head_of_list, previous_of_new, value_to_insert)){
				printf("%d inserted before the first greater integer.\n", value_to_insert);
			}else{
				printf("Memory allocation failed while inserting node.\n");
				return 0;
			}
		}else if(option == 6){
			int value_to_delete;
			printf("The integer to delete?: ");
			scanf("%d", &value_to_delete);
			if(list_delete(&head_of_list, value_to_delete)){
				printf("The first %d deleted.\n", value_to_delete);
			}else{
				printf("There's nothing to delete.\n");
			}
		}else if(option == 7){
			list_clear(&head_of_list);
			printf("List cleared.\n");
		}else if(option == 8){
			list_print(head_of_list);
		}else if(option == 9){
			printf("1: Append\n");
			printf("2: Detach\n");
			printf("3: Push\n");
			printf("4: Pop\n");
			printf("5: Insert\n");
			printf("6: Delete\n");
			printf("7: Clear\n");
			printf("8: See the list\n");
			printf("9: See all options\n");
			printf("0: Quit\n");
		}else if(option == 0){
			list_clear(&head_of_list);
			return 0;
		}else{
			printf("Invalid option.\n");
		}
	}
};