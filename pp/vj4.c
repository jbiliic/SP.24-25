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
void createAndSort(Pointer,int,int);


int main(){

    element head;


    return 0;
}

void readFromFile(Pointer P){
    FILE *f;
    f=fopen("FileZa4Zad.txt","r");
    int e=0,c=0;

    if(!f){
        printf("Greska pri otvaranju datoteke");
    }

    while (foef(f)==0)
    {
       if(fscanf(f," %d %d ", &c,&e)==2){
        createAndSort(P,c,e);
       }
    }
    

}

void createAndSort(Pointer P, int c, int e){

}