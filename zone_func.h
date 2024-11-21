#include "rescue_list.h"


#define MAX_ZONES 100
#define MAX_SUPPLIES 100



Zone *new_zone(){                                                       //New Zone Node

    Zone *new_Zone= (Zone*)malloc(sizeof(Zone));

    if(new_Zone==NULL){
        printf("Memory allocation failed");
        exit(0);
    }

    int zone_id, people_count, priority;
    printf("Enter Zone ID : ");
    scanf("%d", &zone_id);

    printf("Enter count of people : ");
    scanf("%d", &people_count);

    printf("Enter priority :");
    scanf("%d", &priority);

    srand(time(NULL));  
    float random_factor = (float)rand() / RAND_MAX;
    float time = 2 + (22 * (1.0 - (priority / 6.0)) * random_factor);
    

    new_Zone->zone_id= zone_id;
    new_Zone->priority= priority;
    new_Zone->people_count= people_count;
    new_Zone->supplies_needed= 6-priority;
    new_Zone->time_required= time;

    return new_Zone;
}



ZoneQ *init_zone() {
    int size;
    printf("Enter the number of zones : ");
    scanf("%d", &size);

    ZoneQ *root = (ZoneQ*)malloc(sizeof(ZoneQ));
    if (root == NULL) {
        printf("Memory allocation failed for ZoneQ\n");
        exit(1);
    }

    root->size = size;

    for (int i = 0; i < MAX_ZONES; i++) {
        root->zones[i] = NULL;
    }

    
    for (int i = 0; i < size; i++) {
        printf("Zone %d\n", i+1);
        root->zones[i] = new_zone();
    }

    return root;
}



void zone_info(ZoneQ *root) {
    printf("Printing all the zones in queue\n");

    for (int i = 0; i < root->size; i++) {
        if (root->zones[i] != NULL) {  // Good practice to check for NULL
            printf("Zone ID: %d\n", root->zones[i]->zone_id);
            printf("Priority: %d\n", root->zones[i]->priority);
            printf("People Count: %d\n", root->zones[i]->people_count);
            printf("Supplies needed: %d\n", root->zones[i]->supplies_needed);
            printf("Time Required: %d\n\n", root->zones[i]->time_required);
        }
    }
}




void edit_zone(ZoneQ *root){                                                       //Edits zone variables (like zone_id, priority)

    if(root==NULL){
        printf("Queue is not initialized\n");
        return;
    }

    int zone_id;
    printf("Enter Zone ID you want to edit :\n");
    scanf("%d", zone_id);

    int zone_id, people_count, priority;

    for(int i =0; i<root->size; i++){
        if(root->zones[i]->zone_id==zone_id){
            printf("Enter new zone details :-\n");

            
            printf("Enter Zone ID : ");
            scanf("%d", &zone_id);

            printf("Enter count of people : ");
            scanf("%d", &people_count);

            printf("Enter priority :");
            scanf("%d", &priority);

            srand(time(NULL));  
            float random_factor = (float)rand() / RAND_MAX;
            float time = 2 + (22 * (1.0 - (priority / 6.0)) * random_factor);
    

            root->zones[i]->zone_id= zone_id;
            root->zones[i]->priority= priority;
            root->zones[i]->people_count= people_count;
            root->zones[i]->supplies_needed= 6-priority;
            root->zones[i]->time_required= time;

            
        }
    }
    
    arrange_queue(root);
    return;

}



ZoneQ *update_zone(ZoneQ *root) {                                       //Updates queue
    if (root == NULL) {
        printf("Queue not initialized!\n");
        return ;
    }

    int choice;
    while (1) {
        printf("-+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+--+-+-+-");
        printf("\nZone Queue Update Menu:\n");
        printf("1. Add new zone\n");
        printf("2. Delete zone\n");
        printf("3. Display current zones\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:                                                     //Adds zone
                if (root->size >= MAX_ZONES) {
                    printf("Queue is full! Cannot add more zones.\n");
                    break;
                }
                printf("\nAdding new zone:\n");
                root->zones[root->size] = new_zone();
                root->size++;
                arrange_queue(root);
                printf("Zone added and queue rearranged by priority.\n");
                break;

            case 2:                                                     // Delete zone
                if (root->size <= 0) {
                    printf("Queue is empty! Nothing to delete.\n");
                    break;
                }
                int zone_id;
                printf("Enter Zone ID to delete: ");
                scanf("%d", &zone_id);
                
                
                int found = -1;
                for (int i = 0; i < root->size; i++) {
                    if (root->zones[i]->zone_id == zone_id) {
                        found = i;
                        break;
                    }
                }
                
                if (found != -1) {
                    
                    free(root->zones[found]);
                    
                    
                    for (int i = found; i < root->size - 1; i++) {
                        root->zones[i] = root->zones[i + 1];
                    }
                    root->size--;
                    root->zones[root->size] = NULL;
                    arrange_queue(root);
                    printf("Zone deleted and queue rearranged by priority.\n");
                } else {
                    printf("Zone with ID %d not found!\n", zone_id);
                }
                break;

            case 3:                                                     // Display zones
                if (root->size <= 0) {
                    printf("Queue is empty!\n");
                } else {
                    zone_info(root);
                }
                break;

            case 4: // Exit
                printf("Exiting zone update menu.\n");
                return root;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return root;
}







ZoneQ *finZone(ZoneQ* root, Supply *supplies, Person* personArr[]) {
    if (Excess(supplies, root->zones[0]->supplies_needed)) {
        Person* head = personArr[root->zones[0]->priority];
        while (head != NULL) {
            Person* temp = head;
            head = head->next;
            free(temp);
        }
        personArr[root->zones[0]->priority] = NULL;

        root->size--;
        Zone* temp = root->zones[0];
        for (int i = 0; root->zones[i] == NULL; i++) {
            root->zones[i] = root->zones[i + 1];
        }
        pop(supplies, temp->supplies_needed);
        free(temp);
    }

    return root;
}



void arrange_queue(ZoneQ *root) {
    for (int i = 0; i < root->size - 1; i++) {
        for (int j = 0; j < root->size - i - 1; j++) {
            if (root->zones[j]->priority > root->zones[j + 1]->priority) {
                Zone *temp = root->zones[j];
                root->zones[j] = root->zones[j + 1];
                root->zones[j + 1] = temp;
            }
        }
    }
}


void free_zone_queue(ZoneQ *root) {
    if (root != NULL) {
        for (int i = 0; i < root->size; i++) {
            if (root->zones[i] != NULL) {
                free(root->zones[i]);
            }
        }
        free(root);
    }
}