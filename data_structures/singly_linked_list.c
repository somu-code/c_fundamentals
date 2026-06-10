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
	insert_at_beginning(&head, forth_node);
	print_list(head);
	free(head);
	free(second_node);
	free(third_node);
}
