#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *prev;
	int data;
	struct Node *next;
};

struct Node *create_node(int data);
void print_list(struct Node *head);
void insert_at_beginning(struct Node **head, struct Node **tail,
			 struct Node *new_node);
void insert_at_end(struct Node *tail, struct Node *new_node);
void delete_a_node();
int search_node();
void insert_at_a_specific_position();
void reverse_list();
void free_list(struct Node *head);

int main(void)
{
	struct Node *head = NULL;
	struct Node *tail = NULL;
	head = create_node(0);
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	tail = head;
	struct Node *second_node = create_node(2);
	if (second_node == NULL) {
		return EXIT_FAILURE;
	}
	head->next = second_node;
	second_node->prev = head;
	tail = second_node;
	printf("Node list:\n");
	print_list(head);
	struct Node *third_node = create_node(100);
	if (third_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_beginning(&head, &tail, third_node);
	printf("\nAfter inserting a node at begining with value: 100\n");
	print_list(head);
	free_list(head);
}

struct Node *create_node(int data)
{
	struct Node *temp = malloc(sizeof(struct Node));
	if (temp == NULL) {
		perror("Failed to allocate memory for struct");
		return NULL;
	}
	temp->prev = NULL;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void print_list(struct Node *head)
{
	if (head == NULL) {
		return;
	} else if (head->next == NULL) {
		printf("prev: %p ", (void *)head->prev);
		printf("data: %d ", head->data);
		printf("next: %p\n", (void *)head->next);
	} else {
		while (head != NULL) {
			printf("prev: %p ", (void *)head->prev);
			printf("data: %d ", head->data);
			printf("next: %p\n", (void *)head->next);
			head = head->next;
		}
	}
}

void insert_at_beginning(struct Node **head, struct Node **tail,
			 struct Node *new_node)
{
	if (*head == NULL) {
		*head = new_node;
		*tail = *head;
	} else {
		new_node->next = *head;
		(*head)->prev = new_node;
		*head = new_node;
	}
}

void free_list(struct Node *head)
{
	if (head == NULL) {
		return;
	} else if (head->next == NULL) {
		free(head);
		return;
	} else {
		while (head->next != NULL) {
			struct Node *temp = head;
			head = head->next;
			free(temp);
		}
		free(head);
	}
}
