#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024

struct _element;
typedef struct _element * Pointer;
typedef struct _element{
    int koef;
    int exp;
    Pointer next;
}element;

void readFromFile(Pointer);
void readFromFile2(Pointer);
Pointer create(int,int);
void sort(Pointer,Pointer);
void insertAfter(Pointer,Pointer);
void print(Pointer);
Pointer addPolinom(Pointer,Pointer,Pointer);


int main(){

    element head,head2,headAdd,headTimes;
    head.next=NULL;
    head2.next=NULL;
    headAdd.next=NULL;
    headTimes.next=NULL;

    readFromFile(&head);
    readFromFile2(&head2);
    print(head.next);
    print(head2.next);

    addPolinom(&head,&head2,&headAdd);
    print(headAdd.next);



    return 0;
}

void readFromFile(Pointer P){
    FILE *f;
    f=fopen("FileZa4Zad.txt","r");
    Pointer newEl;
    int e=0,c=0;

    if(!f){
        printf("Greska pri otvaranju datoteke");
    }

    while (feof(f)==0)
    {
       if(fscanf(f," %d %d", &c,&e)==2){
        newEl=create(c,e);
        sort(P,newEl);
       }
    }
    fclose(f);
    

}

Pointer create(int c, int e){
    Pointer newEl;
    newEl=(Pointer)malloc(sizeof(element));

    if(!newEl){
        printf("Neuspjela alokacija memorije");
    }

    newEl->exp=e;
    newEl->koef=c;
    newEl->next=NULL;

    return newEl; 
}

void sort(Pointer P , Pointer newEl){
    Pointer temp=P;

    while (temp->next!=NULL && newEl->exp>temp->next->exp)
    {
        temp=temp->next;
    }

    if (temp->next != NULL && temp->next->exp == newEl->exp) {
        temp->next->koef += newEl->koef;
        free(newEl);
    } else {
        insertAfter(temp, newEl);
    }
    
}

void print(Pointer P){
    while(P!=NULL){
        printf("(%d * X^%d )+",P->koef,P->exp);
        P=P->next;
    }
}

void insertAfter(Pointer P, Pointer new){
    new->next=P->next;
    P->next=new;
}

void readFromFile2(Pointer P){
    FILE *f;
    f=fopen("FileZa4Zad2polinom.txt","r");
    Pointer newEl;
    int e=0,c=0;

    if(!f){
        printf("Greska pri otvaranju datoteke");
    }

    while (feof(f)==0)
    {
       if(fscanf(f," %d %d", &c,&e)==2){
        newEl=create(c,e);
        sort(P,newEl);
       }
    }
    fclose(f);
}

Pointer addPolinom(Pointer p1,Pointer p2, Pointer p){
    p=p1;
    Pointer temp=p;
    int counter=1;

    while(p1->next!=NULL){
        counter=1; 

        while(p->next!=NULL){
            if(p1->next->exp==p->next->exp){
                p->next->exp=p1->next->exp;
                counter=0;
            }
            p=p->next;
        }

        if(counter){
            sort(temp,p1->next);
        }

        p1=p1->next;
    }
    return p;
}