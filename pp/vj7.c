#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct _cvor;
typedef struct _cvor* pos;
typedef struct _cvor{

    char name[50];
    pos next;
    pos child;
}cvor;

struct _stack;
typedef struct _stack* next;
typedef struct _stack{

    pos cvor;
    next next;
}stack;

pos create(char[]);
int addDir(pos,char[]);
pos cdDir(next,pos,char[]);
int push(next,pos);
pos pop(next);
int printStack(next st,pos current){
    printf(" %s/" , st->cvor->name);

    while(st->next!=NULL){
        printf(" %s/" , st->next->cvor->name);
        st=st->next;
    }

    printf("%s>" , current->name);
}

int main(){

    stack x={.cvor=NULL,.next=NULL};
    cvor root={.child=NULL,.next=NULL};
    next st=malloc(sizeof(stack));
    st->cvor=NULL;
    st->next=NULL;
    x.next=st;
    pos current=malloc(sizeof(cvor));
    current->child=NULL;
    current->next=NULL;
    strcpy(current->name, "c:");
    push(x.next,current);
    root.child=current;

    int m;
    char b[50];

    while(m!=5){

        puts("1-md \n 2-cd \n 3-cd.. \n 5-exit \n");
        scanf("%d" , &m)
;        

        switch (m)
        {
        case 1:
            puts("Unesite ime: ");
            scanf("%s" , b);
            addDir(current,b);
            printStack(x.next,current);
            break;

            case 2:
            puts("Unesite ime: ");
            scanf("%s" , b);
            current=cdDir(x.next,current,b);
            printStack(x.next,current);
            break;

            case 3:
            current=pop(x.next);
            printStack(x.next,current);
            break;

        default:
        puts("Pokusaj ponovo");
            break;
        }
    }


    return 0;
}

pos create(char name[]){
    pos newEl=NULL;

    newEl=malloc(sizeof(cvor));

    newEl->child=NULL;
    newEl->next=NULL;
    strcpy(newEl->name,name);

    return newEl;
}

int addDir(pos current,char name[]){

    pos new=NULL,temp=NULL;
    new=create(name);

    temp=current->child;

    if(temp==NULL){
        current->child=new;
        return 1;
    }
    

    while(temp->next!=NULL)
    temp=temp->next;

    temp->next=new;
    return 1;
}

pos cdDir(next stack,pos current, char name[]){

    pos temp=NULL;
    temp=current->child;

    while(temp!=NULL || strcmp(temp->name,name)!=0)
    temp=temp->next;

    if(temp==NULL)
    return NULL;

    push(stack,current);

    return temp;
}

int push(next _stack,pos current){
    
    if(_stack==NULL){
        _stack=malloc(sizeof(stack));
        _stack->cvor=current;
        _stack->next=NULL;
    }
    next temp=NULL;

    while(temp!=NULL)
    temp=temp->next;

    temp=malloc(sizeof(stack));
    temp->cvor=current;
    temp->next=NULL;

    return 1;
}

pos pop(next _stack){

    if(_stack->next==NULL){
        puts("Stack prazan");
        return NULL;
    }

    next temp=_stack->next;
    pos saver;

    while(temp->next!=NULL)
    temp=temp->next;

    saver=temp->cvor;
    free(temp);
    return saver;
}



