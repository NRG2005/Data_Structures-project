#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>


#define MAX_ZONES 100
#define MAX_SUPPLIES 100

typedef struct zone{
    int zone_id;
    int priority;
    int people_count;
    int supplies_needed;
    int time_required;
} Zone;


typedef struct zonequeue{
    Zone *zones[MAX_ZONES];
    int size;
} ZoneQ;

typedef struct supply{
    int items[MAX_SUPPLIES];
    int top;
} Supply;


typedef struct Person {
    int id;
    char name[50];
    int rescue_time;
    int priority;
    struct Person *next;
} Person;



// Functions for Zones
ZoneQ *init_zone();

void zone_info(ZoneQ*);

void edit_zone(ZoneQ* );

ZoneQ *update_zone(ZoneQ* );

Zone *new_zone(void);

ZoneQ* finZone(ZoneQ *, Supply* , Person **);

void arrange_queue(ZoneQ*);

void free_zone_queue(ZoneQ*);

// Functions for supllies

Supply *init_supplies(void);

void push(Supply* , int);

void pop(Supply* , int );



//Functions for people
Person* createPerson(int, char *, int);

Person* addPerson(Person**, int, char*, int);

Person* searchPerson(Person**, int , int , char, int);

void printPerson(Person**, int);

bool Excess(Supply* , int);