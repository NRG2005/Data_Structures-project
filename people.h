#include "rescue_list.h"

Person* createPerson(int id, char *name, int rescue_time)
{
	Person *new = (Person*)malloc(sizeof(Person));
	new->id = id;
    new->rescue_time = time;
    strcpy(new->name, name);
    return new;
}

Person* addPerson(Person* arr[], int priority, char* name, int rescue_time);
{
    Person* head=arr[priority];
    Person *new_person = createPerson(id,name,rescue_time);
    new_person->priority = priority;
    if(arr[priority]==NULL)
    {
        arr[priority]=new_person;
    }
    else
    {
        while(head->next!=NULL)
        {
            head=head->next;
        }
        head->next=new_person;
    }
}

void print_person(Person* arr[], int priority, int id, char *name, int rescue_time) 
{
    Person* head = arr[priority];
    for(int i=1; i<priority; i++)
    {
        while(head->next!=NULL)
        {
            printf("Person : ");
            printf("ID : %d ",head->id);
            printf("Name : %s ",head->name);
            printf("Rescue Time : %d ",head->rescue_time);
            printf("Priority : %d ",head->priority);
            head = head->next;
        }
    }
}

Person* searchPerson(Person** arr, int priority, int id, char* name, int rescue_time)
{
    int found = 0; 
    printf("People with priority %d :\n", priority);
    
    for (int i = 0; i < 6; i++) 
    {
        Person* head = arr[i];
        while(head->next!=NULL)
        {
            if (arr[i]->priority == priority) 
            {
                printf("ID: %d, Name: %s, Rescue Time: %d\n", arr[i]->id, arr[i]->name, arr[i]->time);
                found = 1;
            }
        }
    }
    
    if (found==0) 
    {
        printf("No people found with priority %d\n", priority);
    }
}