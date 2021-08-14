/**
 * Assignment Title: Grocery Store Database
 * A menu-driven program that processes data structures and text files. Adds new items, deletes items,
 * checks and updates items in inventory, as well as displays and stores inventory items in a text file.
 *
 * @author: Harini Manikandan
 * @date: 16/12/2020
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct item					//creating a structure
{
	int id;
	char name[20];
	double cost;
	char category;
	struct item *next;
}Item;

//function prototypes
void AddNewItem(Item * head);
void DeleteItem(Item **head);		//Menu2
Item* search(Item *head);
Item* DeleteLast(Item * head);
void ChangeCost(Item * head);	//Menu 3
void Find(Item*head);	

void sort(Item **head, int option, int order);
Item* selection_sort(Item *head, int option, int order);
void swap(Item **head, Item *tmp_head,Item *min,Item *before);
		
void DisplayList(Item * head);	

int save_flag=0;	//global variable save flag set to False(0). Will later be set to True(1) if any changes are made.

int main()
{
	FILE *fptr;
	
	char fname[100];
	int choice;
	struct item *p=NULL, *temp=NULL, *head=NULL;
	
	printf("Welcome to the grocery store!\n");
	printf("Please enter the file name of the file you wish to load into stock:\n");
	scanf("%s",fname);
	fptr=fopen(fname,"r+");
	if(fptr==NULL)
    {
      printf("Error in opening file!");
      exit(1);		//unsuccessful termination
    }
    else
    {
    	printf("\nThe file %s successfully loaded!\n\n",fname);
	}
	
	//to read the txt file and store in linked list
   	while(!feof(fptr))		//loop till reach end of file
   	{
   		temp = (Item*)malloc(sizeof(Item));
   		if(fscanf(fptr,"%d %s %lf %c",&temp->id, &temp->name, &temp->cost, &temp->category) == 4)	//if 4 inputs taken in then add to linked list
   		{
   			temp->next = NULL;
	   		if(head==NULL)		//if list is currently empty,then set temp node as the head node.
			{
				head=temp;
			}
			else
			{
				p=head;
				while(p->next !=NULL)
				{
					p=p->next;
				}
				p->next = temp;
			}
		}//end of if
   		
	}//end of while
   	
   	fclose(fptr);		//closing the file
   	
   	//printing the linked list
   	p = head;
	while(p!=NULL)
	{
		printf("%d %s %.2lf %c\n",p->id, p->name, p->cost, p->category);
		p = p->next;
	}
	
   	//menu
   	int flag = 0;	//not save flag, but a the flag to run the loop
   	char cond;
   	int opt;
    while(flag == 0)
    {
    	printf("---------------Menu-------------------\n");
    	printf("1. Add new item\n");
    	printf("2. Delete item\n");
    	printf("3. Change the cost of an item\n");
    	printf("4. Search for item\n");
    	printf("5. Display inventory details\n");
    	printf("6. Quit\n");
    	printf("--------------------------------------\n");
    	printf("Please choose one of the following selections:");
    	scanf("%d",&choice);
    	switch(choice)
    	{
    		case 1:
    			//Adding new item
    			AddNewItem(head);		//function declaration
    			printf("\n***********new list********\n");
    			DisplayList(head);
    			break;
    		case 2:
    			//Deleting Item
    			DeleteItem(&head);		//Menu2 just for deleting the item
    			printf("\n***********new list********\n");
    			DisplayList(head);
    			break;
    		case 3:
    			//Updating the Item's Cost
    			ChangeCost(head);
    			printf("\n***********new list********\n");
    			DisplayList(head);
    			break;
    		case 4:
    			//Finding a specific item
    			Find(head);
    			break;
    		case 5:
    			//Sorting the List
    			printf("Would like to have a sorted list? (y/n)\n");
    			scanf("\n%c",&cond);
    			if(cond == 'n' || cond == 'N')
    			{
    				printf("*******NON-SORTED LIST*******\n");
					DisplayList(head);
				}
    			else if(cond=='y' || cond=='Y')
    			{
    				printf("Ascending(A) or Descending order(D)?\n");
    				scanf("\n%c",&cond);
    				if(cond == 'a' || cond == 'A')
    				{
						printf("1. ID num\n");
						printf("2. Item Name\n");
						printf("3. Item Cost\n");
						printf("4. Product Category\n");
						printf("Based on which of these categories would you like to sort(1-4)?\n");
						scanf("%d",&opt);
						//sort func
						if(opt==1)
							sort(&head,1,1);
						else if(opt==2)
							sort(&head,2,1);
						else if(opt==3)
							sort(&head,3,1);
						else if(opt==4)
							sort(&head,4,1);
						
					}
    				else if(cond == 'd' || cond == 'D')
    				{
    					printf("1. ID num\n");
						printf("2. Item Name\n");
						printf("3. Item Cost\n");
						printf("4. Product Category\n");
						printf("Based on which of these categories would you like to sort(1-4)?\n");
						scanf("%d",&opt);
						//sort func
						if(opt==1)
							sort(&head,1,2);
						else if(opt==2)
							sort(&head,2,2);
						else if(opt==3)
							sort(&head,3,2);
						else if(opt==4)
							sort(&head,4,2);
						
					}
					printf("*******SORTED LIST*******\n");
					DisplayList(head);
				}//end of else
    			break;
    		case 6:
    			if(save_flag != 0)	//only if save_flag has been set to 1, meaning changes have been made to the database
    			{
    				FILE *fpointer;
					char c;
					char filename[100];
					struct item *p =head;
					printf("Would you like to save the changes made?(y/n)\n");
					scanf("\n%c",&c);
					if(c=='y' || c=='Y')
					{
						printf("Great! What is the name of the file you would like to save into?\n");
						scanf("%s",filename);
						if(strcmp(filename,fname) == 0)		//compares the new filename entered by user with file used to access the data
						{
							printf("Sorry you cannot store into this file!\n");
							return 1;	//exit the program
						}
						else
						{
							fpointer=fopen(filename,"w+");
				            p=head;
				            // Writes each node of the linked list into the file.
				            while (p != NULL) {
				            fprintf(fpointer, "%d %s %.2lf %c\n",p->id, p->name, p->cost, p->category);	//writing in the file
				            p=p->next;	//traverse through the list to access subsequent nodes and print them out into the file.
				            }
				   			printf("\n The file %s created successfully...!!\n\n",filename);
						}
					}
					else if(c=='n' || c=='N')	//when user does not want to save the changes made
					{
						printf("Ok, See You Next Time!\n");
					}
					fclose(fpointer);//closing new file pointer
				}//end of if
    			flag = 1;	//changing the flag to terminate the loop
    			break;
    		default:
    			printf("Illegal Choice Entered! Please try again!\n");//error message when user did NOT enter a num from 1-6
		}
	}
   	
	
	return 0;
}//end of main

void AddNewItem(Item * head)		//function definition for Menu1
{
	
	//creating a new node of type struct item and size struct item
	struct item *new_node = (struct item*)malloc(sizeof(struct item));
	printf("\nWhat is the ID number of the item to add?\n");
	scanf("%d",&new_node->id);		//storing the values into the new node
	printf("What is the name of the item to be added?\n");
	scanf("%s",&new_node->name);
	printf("What is the cost of the item to be added?\n");
	scanf("%lf",&new_node->cost);
	printf("What is the product category of the item to be added?\n");
	scanf("\n%c",&new_node->category);
	
	int check;
	struct item *p = head;
	struct item *prev=NULL;
	while(p != NULL)
	{
		//if ID is same and NAME means DUPLICATE ITEM
		int i=strcmp(new_node->name, p->name);		//comparing the 2 strings, is same should return 0
		if(((new_node->id) == (p->id)) || (i==0))
		{
			printf("\nThis item WAS NOT ADDED as it is already in stock!\n");
			check = 1;
			break;	
		}
		prev=p;
		p = p->next;
		check=0;
	}//end of while
	if(check!=1)
	{
		prev->next = new_node;
		new_node->next = NULL;
		save_flag=1;	//changing the save flag to True as changes made
	}
	
	return;
}//end of function  

void DeleteItem(Item **head)		//Menu2
{
	int num;
	struct item *p, *q;
	q= *head;
	p= q->next;
	printf("What is the ID number of the product you wish to delete?\n");
	scanf("%d",&num);
	if(q->id == num)	//if starting node
	{
		*head=p;			//assigning p as the new head
		free(q);		//deleting the node
		save_flag=1;	//changing save_flag to true a change has occured, item deleted
	}
	else
	{
		while(p->id != num)		//while id not found,
		{						//continue traversing through the node
			p=p->next;
			q=q->next;
		}
		if(p->next == NULL)		//if Last Node
		{
			q->next = NULL;
			free(p);
			save_flag=1;	//changing save_flag to true a change has occured, item deleted
		}
		else				//if some other Middle node
		{
			q->next = p->next;
			free(p);
			save_flag=1;	//changing save_flag to true a change has occured, item deleted
		}
	}//end of big else
	
}//end of function DeleteItem


void ChangeCost(Item * head)		//Menu 3
{
	
	double newcost;
	int idnum;
	int x=0;
	printf("What is the ID number of the item in question?\n");
	scanf("%d",&idnum);
	struct item *p = head;
	while(p!=NULL)
	{
		if(p->id == idnum)		//if id entered by user found in database, update it's cost
		{
			printf("What is the new price for %s?\n",p->name);
			scanf("%lf",&newcost);
			p->cost = newcost;		//updating the new cost of the product into the database
			x=1;
			save_flag=1;	//changing the save flag to True as changes made
		}
		p=p->next;
	}
	if(x!=1)
	{
		printf("This item was NOT FOUND in the database\n");	//error message when id entered by user not found in database
	}
			
}

void Find(Item*head)		//Menu 4
{
	char n[20];
	int x=0;
	printf("What is the NAME of the item would you like to search for?\n");
	scanf("%s", &n);
	struct item *p = head;
	while(p!=NULL)
	{
		if((strcmp(n,p->name)) == 0)	//compare the string the user entered with the database
		{
			x=1;
			break;	//if found the Node, break from the loop
		}
		p = p->next;	
	}
	if(x!=0)
	{
		printf("%d %s %.2lf %c\n",p->id, p->name, p->cost, p->category); //printing the contents of the specific Node.
	}
	else
	{
		printf("This Item was not Found in the Database!\n");	//error message when user entered item name not found in the database
	}
		
}//end of function for Menu4

void swap(Item **head, Item *tmp_head,Item *min,Item *prev)	//function for swapping nodes, double pointer for 1st arg as taking address of pointer head
{
	//swapping the pointers, not data
	*head = min;				//assigning the min node as the head node
	prev->next = tmp_head;
	Item *temp = min->next;		//temp: stores the next link of the min node
	min->next = tmp_head->next;
	tmp_head->next = temp; 
}	

Item* selection_sort(Item *head,int option, int order)
{
	if(head->next == NULL)	//if head is the single node present in the linked list, then return head itself
	{
		return head;
	}
	struct item *min = head;	//setting the min node as the head
	struct item *prev_min;		//the previous node of min
	struct item *p = head;
	if(order==1)					//Ascending order
	{
		while(p->next != NULL)	//traversing through the list
		{
			if((option == 1) && (p->next->id < min->id))		//sorting based on id num
			{							//if next node's id num is lesser than the current node's id num, 
				min = p->next;		//then assign the next node as min.
				prev_min = p;			//p->next's previous node would be p itself, hence prev_min is p.
			}
			if((option == 2))		//sorting based on item name
			{
				if(strcmp(p->next->name , min->name)<0)
				{							//if next node's name is alphabetically prior to the current node's name,
					min = p->next;		//assign next node to min
					prev_min = p;			//p is min's previous node
				}
			}
			if((option == 3) && (p->next->cost < min->cost))		//sorting based on item cost
			{						//if next node's cost is smaller than the current node's cost,
				min = p->next;	//then assign the next node as min.
				prev_min = p;		//previous node of min = p
			}
			if((option == 4) && (p->next->category < min->category))	//sorting based on category
			{						//if next node's category comes alphabetically earlier than the current node's category letter,
				min = p->next;	//then assign the next node as the min
				prev_min = p;		//previous node of min = p
			}
			p = p->next;		//traversing through the list, to find the smallest
		}//end of while
	}//end of big if
	else							//Descending Order
	{
		while(p->next != NULL)
		{
			if((option == 1) && (p->next->id > min->id))		//sorting based on id num
			{								//if next node's id num is greater than current node's id num,
				min = p->next;			//then assign into min the next node. Storing the max value into node min
				prev_min = p;				//min's previous node would be p
			}
			if((option == 2))		//sorting based on item name
			{
				if(strcmp(p->next->name , min->name)>0)
				{
					min = p->next;
					prev_min = p;
				}
			}
			if((option == 3) && (p->next->cost > min->cost))		//sorting based on item cost
			{
				min = p->next;
				prev_min = p;
			}
			if((option == 4) && (p->next->category > min->category))	//sorting based on category
			{
				min = p->next;
				prev_min = p;
			}
			p = p->next;
		}//end of while
	}
	
	if(min != head)		//if min is NOT the head node, then swap nodes.
	{
		swap(&head,head,min,prev_min);
	}
	head->next = selection_sort((head->next), option, order);	//recursive function! repeat the same process for the next node
	
	return head;
}

void sort(Item **head, int option, int order)
{
	if(*head == NULL)
	{
		return;
	}
	*head=selection_sort(*head, option, order);
}


void DisplayList(Item * head)		//function to display the linked list
{
	Item *p = head;
	printf("\n");
	while(p != NULL)
	{
		printf("%d %s %.2lf %c\n",p->id, p->name, p->cost, p->category);
		p=p->next;
	}
}
