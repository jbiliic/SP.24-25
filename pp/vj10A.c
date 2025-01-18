#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct City;
struct State;

typedef struct City* cityPos;
typedef struct State * statePos;

typedef struct State{

    char name[20];
    cityPos cityList;
    statePos l;
    statePos r;
}state;

typedef struct City{

    char name[20];
    int residents;
    cityPos next;
}city;

int readFile(char[],statePos);
statePos makeState(char[],char[]);
cityPos makeCityList(char[]);
statePos addState(statePos,statePos);
void printState(statePos);
void printCity(cityPos);
void stateIterator(statePos,char[],int);
void cityIterator(cityPos,int);
void freeAll(statePos);


int main(){

    state root={"\n",NULL,NULL,NULL};
    char pickName[20];
    int pickResidents;

    readFile("C:/Users/jopab/OneDrive/Dokumenti/SP.24-25/pp/drzave.txt",&root);
    printState(root.r);
    puts("\nUnesite ime drzave");
    scanf(" %s" ,pickName);
    puts("\n Unesite br stanovnika");
    scanf("%d" , &pickResidents);
    stateIterator(root.r,pickName,pickResidents);
    freeAll(root.r);

    puts("\n");



    return 0;
}

int readFile(char fileNmae[],statePos root){
    FILE *f=NULL;
    char stateName[20],cityFileNmae[100];
    f=fopen(fileNmae,"r");

    if(!f){
        puts("Greska pri otvaranju glavnog file-a");
        return -1;
    }

    while(feof(f)==0){

        fscanf(f," %19s %99s " , stateName,cityFileNmae);

        statePos newState=NULL;
        newState=makeState(stateName,cityFileNmae);
        root->r=addState(root->r,newState);
    }
    fclose(f);
    return 1;
}

statePos makeState(char stateName[],char cityFileName[]){
    statePos newState=NULL;
    cityPos cityList=NULL;

    newState=malloc(sizeof(state));
    if(!newState){
        puts("Greska pri alociranju memorije za drzavu");
        return NULL;
    }
    cityList=makeCityList(cityFileName);
    newState->cityList=cityList;
    newState->l=NULL;
    newState->r=NULL;
    strcpy(newState->name,stateName);


    return newState;
}

cityPos makeCityList(char fileName[]){
    cityPos cityList=NULL;
    FILE *f=NULL;

    f=fopen(fileName,"r");
    if(!f){
        puts("Greskia pri otvaranju fila gradova");
        return NULL;
    }
    
    cityList=malloc(sizeof(city));
    if(!cityList){
            puts("greska pri alociranju memorije za grad");
            return NULL;
    }
    strcpy(cityList->name,"\0");
    cityList->residents=0;
    cityList->next=NULL;

    while(feof(f)==0){
        cityPos newCity=NULL;
        cityPos temp=cityList;
        char cityName[20];
        int population=0;

        fscanf(f," %19s %d " ,cityName,&population );

        newCity=malloc(sizeof(city));
        if(!newCity){
            puts("greska pri alociranju memorije za grad");
            return NULL;
        }
        newCity->residents=population;
        strcpy(newCity->name,cityName);
        newCity->next=NULL;

        while(temp->next!=NULL && temp->next->residents<newCity->residents){
            temp=temp->next;
        }

        if(temp->next==NULL){
            newCity->next=temp->next;
            temp->next=newCity;
            continue;
        }

        if(temp->next->residents==newCity->residents){
            while(temp->next->residents==newCity->residents && strcmp(temp->next->name,newCity->name)<0){
                temp=temp->next;
            }
            newCity->next=temp->next;
            temp->next=newCity;
            continue;
        }

        newCity->next=temp->next;
        temp->next=newCity;
    }
    fclose(f);

    return cityList;
}

statePos addState(statePos root,statePos newState){

    if(root==NULL){
       return newState; 

    }else if(strcmp(root->name,newState->name)<0){
        root->r=addState(root->r,newState);

    }else if(strcmp(root->name,newState->name)>0){
        root->l=addState(root->l,newState);

    }else return NULL;
}

void printState(statePos root){
    if(root==NULL){
        return;
    }

    printState(root->l);
    printf(" Drzava : %s \n sadrzani gradovi : ",root->name);
    printCity(root->cityList);
    printState(root->r);
}

void printCity(cityPos head){
    if(head->next==NULL){
        puts("Nema gradova u ovoj drzavi");
    }

    cityPos temp=head->next;

    while (temp!=NULL)
    {
        printf(" ,%s Br stanovnika: %d" , temp->name,temp->residents);
        temp=temp->next;
    } 
    puts("\n");
}

void stateIterator(statePos root,char name[],int x){
    if(root==NULL){
        return;
    }

    if(strcmp(root->name,name)==0){
        cityIterator(root->cityList,x);
    }

    stateIterator(root->l,name,x);
    stateIterator(root->r,name,x);
}

void cityIterator(cityPos head,int x){
    if(head->next==NULL){
        puts("Nema gradova u ovoj drzavi");
    }

    cityPos temp=head->next;

    while (temp!=NULL)
    {
        if(temp->residents>x){
            printf(" ,%s Br stanovnika: %d" , temp->name,temp->residents);
            }

        temp=temp->next;
    } 
    puts("\n");
}

void freeAll(statePos root){
    if(root==NULL){
        return;
    }

    cityPos iterator=root->cityList->next;
    cityPos temp;
    

    while(iterator !=NULL){
        temp=iterator->next;
        free(iterator);
        iterator=temp;
    }
    freeAll(root->l);
    freeAll(root->r);
    free(root);

}