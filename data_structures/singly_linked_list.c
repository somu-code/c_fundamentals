#include <stdlib.h>
#include <stdio.h>

struct Node {
	int data;
	struct Node *next;
};

struct Node *create_node(int n)
{
	struct Node *temp = malloc(sizeof(struct Node));
	if (temp == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}
	temp->data = n;
	temp->next = NULL;
	return temp;
}

void print_list(struct Node *head)
{
	while (head != NULL) {
		printf("Data: %d, Next: %p\n", head->data, (void *)head->next);
		head = head->next;
	}
}

void insert_at_beginning(struct Node **head, struct Node *new_node)
{
	new_node->next = *head;
	*head = new_node;
}

void insert_at_end(struct Node **head, struct Node *new_node)
{
	if (*head != NULL) {
		struct Node *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
	} else {
		*head = new_node;
	}
}

void delete_a_node(struct Node **head, int value)
{
	if (*head == NULL) {
		return;
	}
	if (value == (*head)->data && (*head)->next == NULL) {
		*head = NULL;
		return;
	}
	while ((*head)->next != NULL) {
		if ((*head)->data == value) {
			printf("%d\n", (*head)->data);
		}
		*head = (*head)->next;
	}
}

// search for a value
// insert at a specific position
// reverse a list

void free_list(struct Node *head)
{
	while (head != NULL) {
		struct Node *temp = head->next;
		free(head);
		head = temp;
	}
}

int main(void)
{
	struct Node *head = NULL;
	head = create_node(0);
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	struct Node *second_node = create_node(2);
	if (second_node == NULL) {
		return EXIT_FAILURE;
	}
	head->next = second_node;
	struct Node *third_node = create_node(3);
	if (third_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_beginning(&head, third_node);
	struct Node *forth_node = create_node(4);
	if (forth_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_end(&head, forth_node);
	print_list(head);
	printf("After delete node\n");
	delete_a_node(&head, 2);
	print_list(head);
	free_list(head);
}
