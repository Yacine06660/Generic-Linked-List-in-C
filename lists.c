#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

void DisplayMenu()
{
	printf("_____________ MENU _____________\n");
	printf("0. Save and EXIT\n1. Insert a new element in the list\n2. Display the list\n3. DeleteList\n4. load list file\n");
}

void *GetInput(TYPE *type)
{
	int choice;
	void *new = NULL;
	int c;


	printf("What is the type of the element you want to insert ?\n0 -> int; 1 -> size_t; 2 -> long; 3 ->float; 4 -> double; 5 -> char; 6 -> string\n");
	scanf("%d", &choice);

	printf("Enter the vlaue of this element: ");

	switch (choice)
	{
		int c;
		case INT:
			new = malloc(sizeof(int));
			scanf("%d", (int *)new);
			break;

		case SIZET:
			new = malloc(sizeof(size_t));
			scanf("%zu", (size_t *)new);
			break;

		case LONG:
			new = malloc(sizeof(long));
			scanf("%ld", (long *)new);
			break;

		case FLOAT:
			new = malloc(sizeof(float));
			scanf("%f", (float *)new);
			break;

		case DOUBLE:
			new = malloc(sizeof(double));
			scanf("%lf", (double *)new);
			break;

		case CHAR:
			new = malloc(sizeof(char));

			while (c = getchar() != '\n' && c != EOF);

			scanf("%c", (char *)new);
			break;

		case STRING:
			new = malloc(1000);
	
			while (c = getchar() != '\n' && c != EOF);
			
			fgets((char *)new, 1000, stdin);
			*((char *)new + strcspn((char *)new, "\n")) = '\0';
			break;
	
		default:
			break;
	}

	*type = choice;
	return new;

}

void *CreateList(void)
{
	return NULL;
}

node *CreateNode(void *ptr, TYPE type)
{
	node *new = malloc(sizeof(node));
	new->data = ptr;
	new->next = NULL;
	new->type = type;

	return new;
}


node *Insert(node *head, int pos, void *ptr, TYPE type)
{
	int i = 1;
	node *new, *temp = head, *pre = NULL;

	new = CreateNode(ptr, type);

	if (pos <= 0) pos = 1;
	
	while (temp != NULL && i < pos)
	{
		pre = temp;
		temp = temp->next;
		i++;
	}
	
	new->next = temp;
	
	if (head == NULL || pos == 1)
	{
		head = new;
	}

	if (pre != NULL)
	{
		pre->next = new; 
	}

	
	return head;
}

void displayList(node *head)
{
	if (head == NULL) {
		printf("The list is empty !\n");
		return;
	}

	node *t = head;

	while (t != NULL)
	{
		void *valptr = t->data;
		switch (t->type)
		{
		case INT:
			printf("%d", *((int *)valptr));
			break;
		case SIZET:
			printf("%zu", *((size_t *)valptr));
			break;
		case LONG:
			printf("%ld", *((long *)valptr));
			break;
		case FLOAT:
			printf("%f", *((float *)valptr));
			break;
		case DOUBLE:
			printf("%lf", *((double *)valptr));
			break;
		case CHAR:
			printf("%c", *((char *)valptr));
			break;
		case STRING:
			printf("%s", (char *)valptr);
			break;

		default:
			break;
		}
		printf(" - ");
		
		t = t->next;
	}

	printf("\n");
	
}

node *DeleteNode(node *n)
{
	if (n != NULL) 
	{
		free(n->data);
		free(n);
	}

	return NULL;
}

node *DeleteList(node *head)
{
	node *current = head;
	node *next;

	while (current != NULL)
	{
		next = current->next;
		current = DeleteNode(current);
		current = next;
	}
	
	return NULL;
}

void write_to_file(FILE *file, void *valptr, TYPE type)
{
	switch (type)
		{
		case INT:
			fprintf(file, "%d", *((int *)valptr));
			break;
		case SIZET:
			fprintf(file, "%zu", *((size_t *)valptr));
			break;
		case LONG:
			fprintf(file, "%ld", *((long *)valptr));
			break;
		case FLOAT:
			fprintf(file, "%f", *((float *)valptr));
			break;
		case DOUBLE:
			fprintf(file, "%lf", *((double *)valptr));
			break;
		case CHAR:
			fprintf(file, "%c", *((char *)valptr));
			break;
		case STRING:
			fprintf(file, "%s", (char *)valptr);
			break;

		default:
			break;
		}
		fprintf(file ," - ");
}

void SaveList(FILE* file, node* head)
{
	int size = 0;

	while(head != NULL)
	{
		fwrite(&(head->type), sizeof(int), 1, file);
		
		switch (head->type)
		{
		case 0:
			fwrite(head->data, sizeof(int), 1, file);
			break;
		case 1:
			fwrite(head->data, sizeof(size_t), 1, file);
			break;
		case 2:
			fwrite(head->data, sizeof(long), 1, file);
			break;
		case 3:
			fwrite(head->data, sizeof(float), 1, file);
			break;
		case 4:
			fwrite(head->data, sizeof(double), 1, file);
			break;
		case 5:
			fwrite(head->data, sizeof(char), 1, file);
			break;
		case 6:
			fwrite(head->data, strlen((char*)head->data) + 1, 1, file);
			break;
		default:
			fputc(0, file);
			break;
		}
		
		head = head->next;
		
	}
}

node* LoadList(node* head, FILE* file)
{
	file = fopen("list.dat", "rb");
	if(file == NULL)
	{
		printf("Failed to open file!!\n");
		return NULL;
	}

	head = NULL;

	TYPE type;
	int pos = 1;
	void *dat = NULL;

	while (fread(&type, sizeof(TYPE), 1, file) == 1)
	{
		int size = 0;
		switch (type)
		{
		case INT:
			size = sizeof(int);
			break;

		case SIZET:
			size = sizeof(size_t);
			break;

		case FLOAT:
			size = sizeof(float);
			break;

		case LONG:
			size = sizeof(long);
			break;

		case DOUBLE:
			size = sizeof(double);
			break;

		case CHAR:
			size = sizeof(char);
			break;

		case STRING:
			size = -1;
			break;
		
		default:
			size = -2;
			break;
		}

		switch (size)
		{
		case -1:
			long cur = ftell(file);

			int c, len = 0;
			while ((c = fgetc(file)) !=  EOF && c != '\0')
			{
				len++;
			}

			if (c == EOF)
			{
				break;
			}

			dat = malloc(len + 1);

			fseek(file, cur, SEEK_SET);
			fread(dat, len + 1, 1,file);
			
			break;

		case -2:
			//to be done later (maybe)
			break;
		
		default:
			dat = malloc(size);
			fread(dat, size, 1, file);
			break;
		}

		head = Insert(head, pos, dat, type);
		pos++;
	}
	fclose(file);

	return head;
	
}