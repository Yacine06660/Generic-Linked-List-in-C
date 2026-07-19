#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include "lists.h"


int main(int argc, char const *argv[])
{
	
	node *head1 = CreateList();
	int ch = 0, stat = 0;
	size_t count = 0, temp;
	TYPE type;
	void *val = NULL;
	FILE *saved, *count_track, *list;

	count_track = fopen("count.track", "r+");

	list = fopen("list.dat", "ab+");

	if (count_track == NULL)
	{
		count_track = fopen("count.track", "w+");
		fprintf(count_track, "%zu", 0);
		rewind(count_track);
	}
	
	stat = fscanf(count_track, "%zu", &temp);
	rewind(count_track);
	if(stat == 1) 
	{
		fscanf(count_track, "%zu", &count);
	}
	else
	{
		return -1;
	}
	 
	saved = fopen("saved.txt", "a");
	fprintf(saved, "%zu. ", count);

	rewind(count_track);

	int fd = fileno(count_track);
	ftruncate(fd, 0);
	rewind(count_track);

	fprintf(count_track, "%zu", ++count);

	fclose(count_track);

	do
	{
		DisplayMenu();
		scanf("%d", &ch);

		switch (ch)
		{
			case 1:
				val = GetInput(&type);

				printf("chose a position to insert the element (position 1 is the first element) : ");
				int pos;
				scanf("%d", &pos);

				write_to_file(saved, val, type);

				head1 = Insert(head1, pos, val, type);
				break;

			case 2:
				displayList(head1);
				break;

			case 3:
				head1 = DeleteList(head1);
				break;

			case 4:
				head1 = LoadList(head1, list);
				break;

			default:

				fprintf(saved, "\n");
				fclose(saved);

				SaveList(list, head1);
				fclose(list);
				break;
		}
	} while (ch != 0);
	
	return 0;
}
