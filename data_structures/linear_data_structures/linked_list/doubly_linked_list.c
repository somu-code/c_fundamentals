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
void insert_at_end(struct Node **head, struct Node **tail,
		   struct Node *new_node);
void insert_at_specific_position(struct Node **head, struct Node **tail,
				 struct Node *new_node, int position);
void delete_a_node();
int search_node();
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
	struct Node *third_node = create_node(3);
	if (third_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_beginning(&head, &tail, third_node);
	printf("\nAfter inserting a node at begining with value: 3\n");
	print_list(head);
	struct Node *forth_node = create_node(4);
	if (forth_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_end(&head, &tail, forth_node);
	printf("\nAfter inserting a node at end with value: 4\n");
	print_list(head);
	struct Node *fifth_node = create_node(5);
	if (fifth_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_specific_position(&head, &tail, fifth_node, 0);
	printf("\nAfter inserting a node at position 0 aka head with value: 5\n");
	print_list(head);
	struct Node *sixth_node = create_node(6);
	if (sixth_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_specific_position(&head, &tail, sixth_node, 2);
	printf("\nAfter inserting a node at position 2 with value: 6\n");
	print_list(head);
	struct Node *seventh_node = create_node(7);
	if (seventh_node == NULL) {
		return EXIT_FAILURE;
	}
	insert_at_specific_position(&head, &tail, seventh_node, 5);
	printf("\nAfter inserting a node at position 5, with value: 7\n");
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

void insert_at_end(struct Node **head, struct Node **tail,
		   struct Node *new_node)
{
	if (*head == NULL) {
		*head = new_node;
		*tail = *head;
	} else {
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
}

void insert_at_specific_position(struct Node **head, struct Node **tail,
				 struct Node *new_node, int position)
{
	if (*head == NULL && position != 0) {
		return;
	} else {
		int counter = 0;
		struct Node *temp = *head;
		while (counter != position && temp->next != NULL) {
			temp = temp->next;
			counter++;
		}
		if (counter < position) {
			return;
		}
		if (temp->prev != NULL) {
			struct Node *temp2 = temp->prev;
			temp2->next = new_node;
			new_node->prev = temp2;
		}
		new_node->next = temp;
		temp->prev = new_node;
		if (counter == 0) {
			*head = new_node;
		}
		if (new_node->next == NULL) {
			*tail = new_node;
		}
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
