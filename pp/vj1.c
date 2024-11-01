#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct {
    char ime[MAX];
    char prezime[MAX];
    int bodovi;
} student;

int main() {
   FILE *p;
   student *studenti=NULL;
   int i=0,brojstudenata=0;

   studenti=malloc(sizeof(student));
   if(studenti=NULL){
    printf("Greska pri alokaciji memoriije \n");
   }

   p=fopen("list.txt", "r");

   if(!p)
     printf("Greska pri otvaranju datoteke");
    
    while(feof(p)==0){
        studenti=realloc(studenti,sizeof(student)*(i+1));
        fscanf(p," %s %s %d", studenti[i].ime,studenti[i].prezime,&studenti[i].bodovi);
        i++;

    }

    brojstudenata=i;
    fclose(p);

    for(i=0 ; i<brojstudenata-1 ; i++){
        printf(" %d-student: %s %s bodovi:%d\n",i+1,studenti[i].ime,studenti[i].prezime,studenti[i].bodovi);
    }

free(studenti);

    return 0;
}
