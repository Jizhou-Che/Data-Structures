#include <stdio.h>
#include <stdlib.h>

struct singly_linked_int_list{
	int value;
	struct singly_linked_int_list * next;
};

struct int_queue{
	struct singly_linked_int_list * queue_list_head;
	struct singly_linked_int_list * queue_list_tail;
};

int list_append(struct singly_linked_int_list ** head_ref, struct singly_linked_int_list ** tail_ref, int new_value){
	struct singly_linked_int_list * new_node = malloc(sizeof(struct singly_linked_int_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->value = new_value;
		new_node->next = NULL;
		if(*tail_ref == NULL){
			*head_ref = new_node;
			*tail_ref = new_node;
		}else{
			(*tail_ref)->next = new_node;
			*tail_ref = new_node;
		}
		return 1;
	}
};

int list_pop(struct singly_linked_int_list ** head_ref, struct singly_linked_int_list ** tail_ref, int * popped_value_ref){
	if(*head_ref == NULL){
		return 0;
	}else{
		*popped_value_ref = (*head_ref)->value;
		struct singly_linked_int_list * temp = *head_ref;
		*head_ref = (*head_ref)->next;
		free(temp);
		if(*head_ref == NULL){
			*tail_ref = NULL;
		}
		return 1;
	}
};

void list_clear(struct singly_linked_int_list ** head_ref, struct singly_linked_int_list ** tail_ref){
	struct singly_linked_int_list * current_node = *head_ref;
	while(current_node != NULL){
		struct singly_linked_int_list * temp = current_node;
		current_node = current_node->next;
		free(temp);
	}
	*head_ref = NULL;
	*tail_ref = NULL;
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

void queue_create(struct int_queue * queue_ref){
	queue_ref->queue_list_head = NULL;
	queue_ref->queue_list_tail = NULL;
	return;
};

int enqueue(struct int_queue * queue_ref, int new_value){
	return list_append(&(queue_ref->queue_list_head), &(queue_ref->queue_list_tail), new_value);
};

int dequeue(struct int_queue * queue_ref, int * dequeued_value_ref){
	return list_pop(&(queue_ref->queue_list_head), &(queue_ref->queue_list_tail), dequeued_value_ref);
};

void queue_clear(struct int_queue * queue_ref){
	list_clear(&(queue_ref->queue_list_head), &(queue_ref->queue_list_tail));
	return;
};

void queue_print(struct int_queue * queue_ref){
	list_print(queue_ref->queue_list_head);
	return;
};

int main(){
	struct int_queue queue;
	queue_create(&queue);

	printf("1: Enqueue\n");
	printf("2: Dequeue\n");
	printf("3: Clear the queue\n");
	printf("4: See the queue\n");
	printf("5: See all options\n");
	printf("0: Quit\n");

	while(1){
		printf("> ");
		int option;
		scanf("%d", &option);
		if(option == 1){
			int value_to_enqueue;
			printf("The integer to enqueue?: ");
			scanf("%d", &value_to_enqueue);
			if(enqueue(&queue, value_to_enqueue)){
				printf("%d enqueued.\n", value_to_enqueue);
			}else{
				printf("Memory allocation failed while enqueuing node.\n");
				return 0;
			}
		}else if(option == 2){
			int dequeued_value;
			if(dequeue(&queue, &dequeued_value)){
				printf("%d dequeued.\n", dequeued_value);
			}else{
				printf("There's nothing to dequeue.\n");
			}
		}else if(option == 3){
			queue_clear(&queue);
			printf("Queue cleared.\n");
		}else if(option == 4){
			queue_print(&queue);
		}else if(option == 5){
			printf("1: Enqueue\n");
			printf("2: Dequeue\n");
			printf("3: Clear the queue\n");
			printf("4: See the queue\n");
			printf("5: See all options\n");
			printf("0: Quit\n");
		}else if(option == 0){
			queue_clear(&queue);
			return 0;
		}else{
			printf("Invalid option.\n");
		}
	}
};