#ifndef LISTS
#define LISTS

typedef enum TYPE
{
	CUSTOM_STRUCT = -1,
	STATIC_DATA = -2,
	INT = 0,
	SIZET = 1,
	LONG = 2,
	FLOAT = 3,
	DOUBLE = 4,
	CHAR = 5,
	STRING = 6,
}TYPE;

typedef struct node
{
	TYPE type;
	void *data;
	struct node *next;
}node;

void DisplayMenu();
void *CreateList(void);
node *CreateNode(void *ptr, TYPE type);
node *Insert(node *head, int pos, void *ptr, TYPE type);
void displayList(node *head);
void *GetInput(TYPE *type);
node *DeleteNode(node *n);
node *DeleteList(node *head);
void write_to_file(FILE *file, void *valptr, TYPE type);
void SaveList(FILE* file, node* head);
node* LoadList(node* head, FILE* file);


#endif