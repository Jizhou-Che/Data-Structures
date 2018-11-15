#include <stdio.h>
#include <stdlib.h>

struct linked_list{
	int value;
	struct linked_list * next;
};

int append(struct linked_list ** head_ref, int new_value){
	struct linked_list * new_node = malloc(sizeof(struct linked_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(*head_ref == NULL){
			*head_ref = new_node;
			return 1;
		}else{
			struct linked_list * current_node = *head_ref;
			while(current_node->next != NULL){
				current_node = current_node->next;
			}
			current_node->next = new_node;
			return 1;
		}
	}
};

int detach(struct linked_list ** head_ref, int * detached_value_ref){
	if(*head_ref == NULL){
		return 0;
	}else if((*head_ref)->next == NULL){
		*detached_value_ref = (*head_ref)->value;
		free(*head_ref);
		*head_ref = NULL;
		return 1;
	}else{
		struct linked_list * current_node = *head_ref;
		while(current_node->next->next != NULL){
			current_node = current_node->next;
		}
		*detached_value_ref = current_node->next->value;
		free(current_node->next);
		current_node->next = NULL;
		return 1;
	}
};

int push(struct linked_list ** head_ref, int new_value){
	struct linked_list * new_node = malloc(sizeof(struct linked_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(*head_ref == NULL){
			*head_ref = new_node;
			return 1;
		}else{
			new_node->next = *head_ref;
			*head_ref = new_node;
			return 1;
		}
	}
};

int pop(struct linked_list ** head_ref, int * popped_value_ref){
	if(*head_ref == NULL){
		return 0;
	}else{
		*popped_value_ref = (*head_ref)->value;
		struct linked_list * temp = *head_ref;
		*head_ref = (*head_ref)->next;
		free(temp);
		return 1;
	}
};

int insert(struct linked_list ** head_ref, struct linked_list * previous_node, int new_value){
	struct linked_list * new_node = malloc(sizeof(struct linked_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(previous_node == NULL){
			new_node->next = *head_ref;
			*head_ref = new_node;
			return 1;
		}else{
			new_node->next = previous_node->next;
			previous_node->next = new_node;
			return 1;
		}
	}
};

int delete(struct linked_list ** head_ref, int value_to_del){
	if(*head_ref == NULL){
		return 0;
	}else{
		if((*head_ref)->value == value_to_del){
			struct linked_list * temp = *head_ref;
			*head_ref = (*head_ref)->next;
			free(temp);
			return 1;
		}else{
			struct linked_list * current_node = *head_ref;
			while(current_node->next != NULL){
				if(current_node->next->value == value_to_del){
					struct linked_list * temp = current_node->next;
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

void find_prev(struct linked_list * head_node, struct linked_list ** previous_ref, int new_value){
	struct linked_list * current_node = head_node;
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
	struct linked_list * head_of_list = NULL;
	struct linked_list * current_of_list = NULL;

	if(!append(&head_of_list, 1)){
		printf("Memory allocation failed while appending node.\n");
		return 0;
	}
	if(!append(&head_of_list, 2)){
		printf("Memory allocation failed while appending node.\n");
		return 0;
	}
	if(!append(&head_of_list, 3)){
		printf("Memory allocation failed while appending node.\n");
		return 0;
	}

	if(!push(&head_of_list, -1)){
		printf("Memory allocation failed while pushing node.\n");
		return 0;
	}
	if(!push(&head_of_list, -2)){
		printf("Memory allocation failed while pushing node.\n");
		return 0;
	}
	if(!push(&head_of_list, -3)){
		printf("Memory allocation failed while pushing node.\n");
		return 0;
	}

	struct linked_list * previous_of_new = NULL;
	int value_to_insert;
	value_to_insert = -4;
	find_prev(head_of_list, &previous_of_new, value_to_insert);
	if(!insert(&head_of_list, previous_of_new, value_to_insert)){
		printf("Memory allocation failed while inserting node.\n");
	}

	value_to_insert = 0;
	find_prev(head_of_list, &previous_of_new, value_to_insert);
	if(!insert(&head_of_list, previous_of_new, value_to_insert)){
		printf("Memory allocation failed while inserting node.\n");
	}

	value_to_insert = 4;
	find_prev(head_of_list, &previous_of_new, value_to_insert);
	if(!insert(&head_of_list, previous_of_new, value_to_insert)){
		printf("Memory allocation failed while inserting node.\n");
	}

	current_of_list = head_of_list;
	while(current_of_list != NULL){
		printf("%d ", current_of_list->value);
		current_of_list = current_of_list->next;
	}
	printf("\n");

	int popped_value;
	if(pop(&head_of_list, &popped_value)){
		printf("%d popped.\n", popped_value);
	}else{
		printf("There's nothing to pop. ");
	}

	int detached_value;
	if(detach(&head_of_list, &detached_value)){
		printf("%d detached.\n", detached_value);
	}else{
		printf("There's nothing to detach. ");
	}

	int value_to_delete;
	value_to_delete = -3;
	if(!delete(&head_of_list, value_to_delete)){
		printf("There's nothing to delete.\n");
	}
	value_to_delete = 0;
	if(!delete(&head_of_list, value_to_delete)){
		printf("There's nothing to delete.\n");
	}
	value_to_delete = 3;
	if(!delete(&head_of_list, value_to_delete)){
		printf("There's nothing to delete.\n");
	}

	current_of_list = head_of_list;
	while(current_of_list != NULL){
		printf("%d ", current_of_list->value);
		current_of_list = current_of_list->next;
	}
	printf("\n");

	current_of_list = head_of_list;
	while(current_of_list != NULL){
		struct linked_list * temp = current_of_list;
		current_of_list = current_of_list->next;
		free(temp);
	}

	return 0;
};