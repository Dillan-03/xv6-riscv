#include <stdlib.h>
#include <stdio.h>

void create();
void display();
void insert_begin();
void insert_end();
void delete_pos();

struct node
{
        // Your struct here
	struct node* next;
	int data;
	
};
// Remainder of struct definition

struct node* head;
int main()
{
        int choice;
        while (1)
        {

                printf("\n               MENU                            \n");
                printf("1.Create     \n");
                printf("2.Display    \n");
                printf("3.Insert at the beginning    \n");
                printf("4.Insert at the end  \n");
                printf("5.Delete from specified position     \n");
                printf("9.Exit       \n");
                printf("--------------------------------------\n");
                printf("Enter your choice:\t");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                        create();
                        break;
                case 2:
                        display();
                        break;
                case 3:
                        insert_begin();
                        break;
                case 4:
                        insert_end();
                        break;
                case 5:
                        delete_pos();
                        break;

                case 9:
                        exit(0);
                        break;

                default:
                        printf("\n Wrong Choice:\n");
                        break;
                }
        }
        return 0;
}
void create()
{
        // your code here
	
	//intialise a four element list with the data field set 1,2,3,4 for those first four fields. 
	
	//struct node *head = NULL;
	struct node* one = NULL;
	struct node* two = NULL;
	struct node* three = NULL;
	struct node* fourth = NULL;
	
	one = (struct node*) malloc(sizeof(struct node));
	two= (struct node*) malloc(sizeof(struct node));
	three = (struct node*) malloc(sizeof(struct node));
	fourth = (struct node*) malloc(sizeof(struct node));

	/* Assign data values */
	one->data = 1;
	two->data = 2;
	three->data=3;
	fourth->data = 4;
	/* Connect nodes */
	one->next = two;
	two->next = three;
	three->next = fourth;
	fourth->next = NULL;

	/* Save address of first node in head */
	head = one;
}
void display()
{	//struct node*o head;
	struct node* pointer;
	pointer = head;
	if (pointer == NULL){
		printf("Error\n");
	}else{
	while (pointer!= NULL) {
        	printf(" %d ", pointer->data);
        	pointer = pointer->next;
   	}
	} 
}
void insert_begin()
{
        // your code here
}
void insert_end()
{
        // your code here
}
void delete_pos()
{
        // your code here
}
