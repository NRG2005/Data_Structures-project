#include "rescue_list.h"

Supply* init_supplies(){
    Supply* sup=malloc(sizeof(Supply));
    if(sup==NULL)
    {
        printf("NO memory for supplies");
        exit(0);
    }
    else
    {
        sup->top=-1;
        for(int i = 0 ; i<MAX_SUPPLIES ; i++)
        {
            sup->items[i]=1;
        }
    }
    return sup;
}
void push(Supply *supplies,int items){
    if(supplies->top==MAX_SUPPLIES-1){
        printf("Stack is alreaddy full\n");
        return;
    }
    supplies->items[++supplies->top] = items;
}

void pop(Supply *supplies, int items ){
    if (supplies->top >= 0) 
    {
        supplies->top--;
    }
}


bool Excess(Supply *supplies, int items) {
    if (items > supplies->top) {
        return false;
    }
    return true;
}






