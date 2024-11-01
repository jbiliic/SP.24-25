#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct osoba * pok;
typedef struct osoba{
   
char ime[MAX];
char prezime[MAX];
int godina;
pok next;

}osob;
//test test
    void dodaj(pok);
    void ispis(pok);
    pok stvori();
    void dodajkraj(pok);
    pok pronadizadnjeg(pok);
    pok pronadi(pok);
    pok pronadiprethodnog(pok, pok);
    void brisi(pok);

int main(){

int i=0, n=0,j;
osob head;
head.next=NULL;

printf("koliko osoba zelite unjeti");
scanf("%d" , &n);

for(i=0; i<n ; i++){
    dodaj(&head);
    }

ispis(head.next);
dodajkraj(&head);
ispis(head.next);
pronadi(&head);
brisi(&head);
ispis(head.next);

return 0;
}

void dodaj(pok head){
    pok element;
    pok temp;

    element=stvori();


    temp=head->next;
    head->next=element;
    element->next=temp;
}

void ispis(pok p){
int i=1;
    while(p!=NULL){
        printf("\n%d-ti element liste je %s\t%s\t%d\n",i, p->ime,p->prezime,p->godina);
        p=p->next;
        i++;
    }
}

pok stvori(){
    pok p=malloc(sizeof(osob));
    char ime[MAX];
    char prezime[MAX];
    int godina;

    printf(" \t Unesite ime \n");
    scanf("%s" , ime);
    strcpy(p->ime, ime);
    printf(" \t Unesite prezime \n");
    scanf("%s" , prezime);
    strcpy(p->prezime, prezime);
    printf(" \t Unesite godinu \n");
    scanf("%d" , &godina);
    p->godina=godina;

        return p;
}

void dodajkraj(pok p){
    pok zadnji=malloc(sizeof(osob));
    zadnji=pronadizadnjeg(p);
    pok novi=malloc(sizeof(osob));
    novi=stvori();

    zadnji->next=novi;
    novi->next=NULL;

}

pok pronadizadnjeg(pok p){

    while(p->next!=NULL)
    p=p->next;

    return p;
}

pok pronadi(pok p){

    char pr[MAX];
    int i=0;

    printf(" \t unesite prezime koje trazite \n");
    scanf("%s" , pr);

    while(p!=NULL){
        if(strcmp(pr,p->prezime)==0){
        printf("Potraga uspijesna! Trazeni element nalazi se na poziciji broj %d" , i);
        return p;
        }
        i++;
        p=p->next;
    }
    printf("\n Trazenog elementa nema u listi");
    return NULL;
}
pok pronadiprethodnog(pok p, pok x){

    while(p->next!=x)
    p=p->next;

    return p->next;
}

void brisi(pok p ){

    pok x,prethodni;
    prethodni=malloc(sizeof(osob));

    printf("\nUnesite element za brisanje");
    x=pronadi(p);
    prethodni=pronadiprethodnog(p,x);


    prethodni->next=x->next;
    free(x);
}