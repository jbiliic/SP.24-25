#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX 50

struct _Student;
typedef struct _Student* Pointer;
typedef struct _Student{

    char Name[MAX];
    char LastName[MAX];
    int Age;
    Pointer next;
}Student;

Pointer CreateNewPearson();
Pointer CreateNewPearson2(char[],char[],int);
Pointer Find(Pointer);
Pointer FindPrev(Pointer,Pointer);
void AddToFront(Pointer);
void AddToFront2(Pointer,Pointer);
void AddToEnd(Pointer);
void PrintList(Pointer);
void Delete(Pointer);
void Sort(Pointer);
void ReadFromFile(Pointer);

int main(){

    Student Head;
    Head.next=NULL;

    int i=0,NumberOfStudents=0;

   ReadFromFile(&Head);

    
    PrintList(Head.next);

   




    return 0;
}

Pointer CreateNewPearson(){
    Pointer NewPearson;
    char Name[MAX],LastName[MAX];
    int Age;

    NewPearson=malloc(sizeof(Student));
    if(!NewPearson)
        printf("Greska u alokaciji memorije");

    printf("Unesite ime osobe ");
    scanf("%s", Name);
    strcpy(NewPearson->Name,Name);

     printf("Unesite prezime osobe ");
    scanf("%s", LastName);
    strcpy(NewPearson->LastName,LastName);

     printf("Unesite godiste osobe ");
    scanf("%d", &Age);
    NewPearson->Age=Age;

    return NewPearson;
}

void AddToFront(Pointer Head){
    Pointer NewPearson;
    NewPearson=CreateNewPearson();

    NewPearson->next=Head->next;
    Head->next=NewPearson;
}

void PrintList(Pointer p){
    int i=0;
    printf("\t \t \t Name \t Lastname  Age \n");
    while(p!=NULL){
        printf("%d-ti element liste je %s \t %s \t %d \n",i+1,p->Name,p->LastName,p->Age);
        p=p->next;
        i++;
    }
}

void AddToEnd(Pointer Head){
    Pointer NewPearson;
    NewPearson=CreateNewPearson();

    while(Head->next!=NULL){
        Head=Head->next;
    }

    Head->next=NewPearson;
    NewPearson->next=NULL;
}

Pointer Find(Pointer p){
    char LastName[MAX];

    printf("Unesite prezime koje zelite pronaci");
    scanf("%s", LastName);

    while(p!=NULL){
        if(strcmp(LastName,p->LastName)==0){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

Pointer FindPrev(Pointer Head , Pointer Element){
    while(Head->next!=Element){
        Head=Head->next;
    }
    

    return Head;
}

void Delete(Pointer Head){
    Pointer Element;
    Element=Find(Head);
    if(Element==NULL){
        printf("Nema trazenog elementa");
    }
    Pointer PrevElement;
    PrevElement=FindPrev(Head,Element);

    PrevElement->next=Element->next;
    Element->next=NULL;

    free(Element);

}

void Sort(Pointer Head){
    Pointer End,El,ElPrev,Temp;
    End=NULL;
    while(Head->next!=End){
        ElPrev=Head;
        El=Head->next;

        while(El->next!=End){
            if(strcmp(El->LastName,El->next->LastName)<0){
                Temp=El->next;
                ElPrev->next=Temp;
                El->next=Temp->next;
                Temp->next=El->next;
                El=Temp;
            }
            ElPrev=El;
            El=El->next;
        }
        End=El;
    }
}

void ReadFromFile(Pointer p){
    char Name[MAX],LastName[MAX];
    int Age;
    FILE *f;
    f=fopen("list.txt","r");

    if(!f)
    printf("Neuspjelo otvaranje datoteke");

    while(feof(f)==0){
        fscanf(f," %s %s %d ", Name,LastName,&Age);
        AddToFront2(p,CreateNewPearson2(Name,LastName,Age));
    }
    fclose(f);

}

Pointer CreateNewPearson2(char Name[],char LastName[],int Age){
    Pointer NewPearson=malloc(sizeof(Student));
    strcpy(NewPearson->Name,Name);
    strcpy(NewPearson->LastName,LastName);
    NewPearson->Age=Age;

    return NewPearson;

}

void AddToFront2(Pointer Head,Pointer Element){
    Element->next=Head->next;
    Head->next=Element;

}