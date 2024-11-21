#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "rescue_list.h"


#define MAX_PRIORITIES 5

int main() {
    int choice;
    Supply *supplies = init_supplies();
    ZoneQ *zoneQueue = NULL;
    Person* personArr[MAX_PRIORITIES] = { NULL };

    printf("Hello! Welcome to the rescue operation.\n");
    while (1) {
        printf("--------------------------------------------------------------------------------\n");
        printf("Menu\n");
        printf("1. Create Zones\n");
        printf("2. View Zone information\n");
        printf("3. Edit Zone\n");
        printf("4. Update Zone\n");
        printf("5. Finishing Zone\n");
        printf("6. Add Person\n");
        printf("7. View Person information\n");
        printf("8. Exiting\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                zoneQueue = init_zone();
                break;
            case 2:
                if (zoneQueue != NULL) {
                    zone_info(zoneQueue);
                } else {
                    printf("Zone queue is not initialized.\n");
                }
                break;
            case 3:
                if (zoneQueue != NULL) {
                    edit_zone(zoneQueue);
                } else {
                    printf("Zone queue is not initialized.\n");
                }
                break;
            case 4:
                if (zoneQueue != NULL) {
                    zoneQueue = update_zone(zoneQueue);
                } else {
                    printf("Zone queue is not initialized.\n");
                }
                break;
            case 5:
                if (zoneQueue != NULL) {
                    finZone(zoneQueue, supplies,personArr);
                    arrange_queue(zoneQueue);
                } else {
                    printf("Zone queue is not initialized.\n");
                }
                break;
            case 6:
            {
                int priority;
                char name[50];
                int time;
                printf("Enter person priority: ");
                scanf("%d", &priority);
                printf("Enter person name: ");
                scanf("%s", name);
                printf("Enter person rescue time: ");
                scanf("%d", &time);
                addPerson(personArr, priority, name, time);
                break;
            }
            case 7:
                printPerson(personArr, MAX_PRIORITIES);
                break;
            case 8:
                printf("Exiting the program\n");
                free_zone_queue(zoneQueue);
                free(supplies);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}