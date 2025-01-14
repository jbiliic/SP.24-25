#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct Drzava;
struct Grad;

typedef struct Drzava* dPos;
typedef struct Grad* gPos;


typedef struct Drzava{

    char ime[20];
    gPos gradovi;
    dPos next;


}drzava;

typedef struct Grad{

    char ime[20];
    int brS;
    gPos r;
    gPos l;
}grad;

void readFile(char[], dPos);
dPos makeC(char[],char[]);
gPos makeCity(char[],gPos);
gPos addG(gPos,gPos);
void addC(dPos,dPos);
void ispisDrz(dPos);
void ispisGrad(gPos);

void provjeriDrz(dPos,int,char[]);
void provjeriGrad(gPos,int);

int main(){

    drzava head={'\0',NULL,NULL};
    int s;
    char ime[22];

    readFile("C:/Users/jopab/OneDrive/Dokumenti/SP.24-25/pp/drzave.txt",&head);

    ispisDrz(&head);
    printf("Unesite broj stanovnika");
    scanf("%d" , &s);
    printf("\n Unesit eime");
    scanf("%s" , ime);
    provjeriDrz(&head,s,ime);

    return 0;
}

void readFile(char file[],dPos head){

    FILE *f;
    char iDrz[20],fGrad[100];

    f=fopen(file,"r");
    if(!f){
        puts("Greska");
    }

    while(feof(f)==0){

        fscanf(f," %s %s " , iDrz,fGrad);

       dPos newC= makeC(iDrz,fGrad);
       addC(head,newC);
    }
}

void addC(dPos head, dPos newC){

    if(head->next==NULL){
        head->next=newC;
        return;
    }

    dPos temp=head;

    while(temp->next!=NULL && strcmp(temp->next->ime,newC->ime)<0){
        temp=temp->next;
    }

    if(temp->next==NULL){
        temp->next=newC;
        return;
    }else if(strcmp(temp->next->ime,newC->ime)>0) {

        newC->next=temp->next;

        temp->next=newC;
        return;
    }
}

dPos makeC(char iD[],char fileN[]){

    dPos newC=NULL;
    newC=malloc(sizeof(drzava));
    strcpy(newC->ime,iD);
    newC->next=NULL;

    gPos headG=malloc(sizeof(grad));
    headG->l=NULL;
    headG->r=NULL;

    headG=makeCity(fileN,headG);

    newC->gradovi=headG;

    return newC;
}

gPos makeCity(char fileName[],gPos head){

    FILE *f;
    char name[20];
    int num;
    f=fopen(fileName,"r");

    while(feof(f)==0){
        fscanf(f," %s %d " , name ,&num);

        gPos newG=malloc(sizeof(grad));
        newG->brS=num;
        newG->l=NULL;
        newG->r=NULL;
        strcpy(newG->ime,name);

        head->r=addG(head->r,newG);
    }

    return head;
}

gPos addG(gPos head, gPos newG){

    if(head==NULL){
        return newG;
    }

    if(head->brS<newG->brS){
        head->r=addG(head->r,newG);
    }
    else if(head->brS>newG->brS){
        head->l=addG(head->l,newG);
    }
}

void ispisDrz(dPos head){
    dPos temp=head->next;

    while(temp!=NULL){
        printf(" \nDrzava : %s \n Gradovi inorder: " , temp->ime);
        ispisGrad(temp->gradovi->r);
        temp=temp->next;
    }
}

void ispisGrad(gPos head){
    if(head==NULL)
    return;

    ispisGrad(head->l);
    printf(" %s br st: %d," , head->ime,head->brS);
     ispisGrad(head->r);

}

void provjeriDrz(dPos head,int x,char ime[]){
    dPos temp=head->next;

    while(temp!=NULL && strcmp(temp->ime,ime)!=0){
        temp=temp->next;
    }
    if(temp==NULL)
    return;

    if(strcmp(temp->ime,ime)==0){
    printf(" \nDrzava : %s \n Gradovi s vise od %d stanovnika " , temp->ime,x);
    provjeriGrad(temp->gradovi->r,x);}else puts("te drzave nema");
}

void provjeriGrad(gPos head,int x){
    if(head==NULL)
    return;

    provjeriGrad(head->l,x);
    if(head->brS>x)
    printf(" %s br st: %d>%d," , head->ime,head->brS,x);
    provjeriGrad(head->r,x);

}