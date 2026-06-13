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
		prev->next = current->next;
		free(current);
	}
}

int search_node(struct Node *head, int value)
{
	if (head == NULL) {
		return 0;
	}
	while (head != NULL && head->data != value) {
		head = head->next;
	}
	if (head != NULL) {
		return 1;
	}
	return 0;
}

void insert_at_a_specific_position(struct Node **head, struct Node *new_node,
				   int position)
{
	if (position != 0 && *head == NULL) {
		return;
	} else if (position == 0) {
		insert_at_beginning(head, new_node);
	} else {
		int counter = 0;
		struct Node *temp = *head;
		while (counter != position - 1) {
			if (temp->next == NULL) {
				break;
			}
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
	printf("After deleting Node with value: 2\n");
	delete_a_node(&head, 2);
	print_list(head);
	printf("Is node with value: 0 exists: %d\n", search_node(head, 0));
	printf("After inserting at position: 0 aka head with value: 11\n");
	insert_at_a_specific_position(&head, create_node(11), 0);
	print_list(head);
	printf("After inserting at position: 2 with value: 22\n");
	insert_at_a_specific_position(&head, create_node(22), 2);
	print_list(head);
	free_list(head);
}
