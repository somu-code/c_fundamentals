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

int main(void)
{
	struct Node *head = NULL;
	head = create_node(0);
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	struct Node *second_node = create_node(1);
	if (second_node == NULL) {
		return EXIT_FAILURE;
	}
	head->next = second_node;
	free(head);
	free(second_node);
}
