#include <stdlib.h>
#include <stdio.h>

struct Node {
	unsigned int data;
	struct Node *next;
};

struct Node *create_node(unsigned int n);
void print_list(struct Node *head);
void insert_at_beginning(struct Node **head, struct Node *new_node);
void insert_at_end(struct Node **head, struct Node *new_node);
void delete_a_node(struct Node **head, unsigned int value);
struct Node *search_node(struct Node *head, unsigned int data);
void insert_at_a_specific_position(struct Node **head, struct Node *new_node,
				   int position);
void reverse_list(struct Node **head);
void free_list(struct Node *head);

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
	printf("Node:\n");
	print_list(head);
	struct Node *third_node = create_node(3);
	if (third_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_beginning(&head, third_node);
	printf("\nAfter inserting at beginning with value: %d\n",
	       third_node->data);
	print_list(head);
	struct Node *forth_node = create_node(4);
	if (forth_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_end(&head, forth_node);
	printf("\nAfter inserting at the end with value: %d\n",
	       forth_node->data);
	print_list(head);
	delete_a_node(&head, 2);
	printf("\nAfter deleting Node with value: 2\n");
	print_list(head);
	struct Node *searched_node = search_node(head, 0);
	if (searched_node != NULL) {
		printf("\nSearched node:\n");
		printf("Data: %d, Next: %p\n", searched_node->data,
		       (void *)searched_node->next);
	}
	struct Node *node_with_value_eleven = create_node(11);
	if (node_with_value_eleven == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_a_specific_position(&head, node_with_value_eleven, 0);
	printf("\nAfter inserting at position: 0 aka head with value: 11\n");
	print_list(head);
	struct Node *node_with_value_twenty_two = create_node(22);
	if (node_with_value_twenty_two == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_a_specific_position(&head, node_with_value_twenty_two, 2);
	printf("\nAfter inserting at position: 2 with value: 22\n");
	print_list(head);
	reverse_list(&head);
	printf("\nAfter reversing the list\n");
	print_list(head);
	free_list(head);
}

struct Node *create_node(unsigned int n)
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

void delete_a_node(struct Node **head, unsigned int value)
{
	if (*head == NULL) {
		return;
	} else if (value == (*head)->data) {
		struct Node *temp = *head;
		*head = temp->next;
		free(temp);
	} else {
		struct Node *prev = *head;
		struct Node *current = (*head)->next;
		while (current != NULL && current->data != value) {
			prev = current;
			current = current->next;
		}
		if (current == NULL) {
			return;
		}
		prev->next = current->next;
		free(current);
	}
}

struct Node *search_node(struct Node *head, unsigned int data)
{
	if (head == NULL) {
		return NULL;
	}
	while (head->data != data) {
		if (head->next == NULL) {
			return NULL;
		}
		head = head->next;
	}
	return head;
}

void insert_at_a_specific_position(struct Node **head, struct Node *new_node,
				   int position)
{
	if (position < 0) {
		return;
	} else if (position != 0 && *head == NULL) {
		return;
	} else if (position == 0) {
		insert_at_beginning(head, new_node);
	} else {
		int counter = 0;
		struct Node *temp = *head;
		while (counter != position - 1 && temp->next != NULL) {
			counter++;
			temp = temp->next;
		}
		if (position - 1 > counter) {
			return;
		}
		new_node->next = temp->next;
		temp->next = new_node;
	}
}

void reverse_list(struct Node **head)
{
	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	struct Node *current = *head;
	struct Node *prev = NULL;
	while (current != NULL) {
		struct Node *temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	*head = prev;
}

void free_list(struct Node *head)
{
	while (head != NULL) {
		struct Node *temp = head->next;
		free(head);
		head = temp;
	}
}
