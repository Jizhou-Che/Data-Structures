#include <stdio.h>
#include <stdlib.h>

struct singly_linked_int_list{
	int value;
	struct singly_linked_int_list * next;
};

struct int_stack{
	struct singly_linked_int_list * stack_list;
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
}

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
}

void list_clear(struct singly_linked_int_list ** head_ref){
	struct singly_linked_int_list * current_node = *head_ref;
	while(current_node != NULL){
		struct singly_linked_int_list * temp = current_node;
		current_node = current_node->next;
		free(temp);
	}
	*head_ref = NULL;
	return;
}

void list_print(struct singly_linked_int_list * head_ref){
	struct singly_linked_int_list * current_node = head_ref;
	while(current_node != NULL){
		printf("%d ", current_node->value);
		current_node = current_node->next;
	}
	printf("\n");
	return;
}

void stack_create(struct int_stack * stack_ref){
	stack_ref->stack_list = NULL;
	return;
}

int stack_push(struct int_stack * stack_ref, int new_value){
	return list_push(&(stack_ref->stack_list), new_value);
}

int stack_pop(struct int_stack * stack_ref, int * popped_value_ref){
	return list_pop(&(stack_ref->stack_list), popped_value_ref);
}

void stack_clear(struct int_stack * stack_ref){
	list_clear(&(stack_ref->stack_list));
	return;
}

void stack_print(struct int_stack * stack_ref){
	list_print(stack_ref->stack_list);
	return;
}

int main(){
	struct int_stack stack;
	stack_create(&stack);

	printf("1: Push\n");
	printf("2: Pop\n");
	printf("3: Clear the stack\n");
	printf("4: See the stack\n");
	printf("5: See all options\n");
	printf("0: Quit\n");

	while(1){
		printf("> ");
		int option;
		scanf("%d", &option);
		if(option == 1){
			int value_to_push;
			printf("The integer to push?: ");
			scanf("%d", &value_to_push);
			if(stack_push(&stack, value_to_push)){
				printf("%d pushed.\n", value_to_push);
			}else{
				printf("Memory allocation failed while pushing node.\n");
				stack_clear(&stack);
				return 0;
			}
		}else if(option == 2){
			int popped_value;
			if(stack_pop(&stack, &popped_value)){
				printf("%d popped.\n", popped_value);
			}else{
				printf("There's nothing to pop.\n");
			}
		}else if(option == 3){
			stack_clear(&stack);
			printf("Stack cleared.\n");
		}else if(option == 4){
			stack_print(&stack);
		}else if(option == 5){
			printf("1: Push\n");
			printf("2: Pop\n");
			printf("3: Clear the stack\n");
			printf("4: See the stack\n");
			printf("5: See all options\n");
			printf("0: Quit\n");
		}else if(option == 0){
			stack_clear(&stack);
			return 0;
		}else{
			printf("Invalid option.\n");
		}
	}
}
