struct Node {
	struct Node *prev;
	int data;
	struct Node *next;
};

struct Node *create_node(int data);

int main(void)
{
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
