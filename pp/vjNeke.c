#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node;
struct Queue;

typedef struct Node* pos;
typedef struct Queue* qPos;
typedef struct Node{
    int el;
    pos l;
    pos r;
}node;
typedef struct Queue{
    pos el;
    qPos next;

}queue;

pos addEl(int,pos);
pos makeEl(int);
void ispisInorder(pos);
void ispisPostorder(pos);
void ispisPreorder(pos);
void levelOrder(qPos);
pos pop(qPos);
void push(qPos,pos tree);
bool find(int,pos);
pos delete(int,pos);
pos findMin(pos);


int main(){

    node root={0,NULL,NULL};
    queue q={NULL,NULL};

    root.r=addEl(5,root.r);
    root.r=addEl(2,root.r);
    root.r=addEl(4,root.r);
    root.r=addEl(56,root.r);
    root.r=addEl(21,root.r);
    root.r=addEl(100,root.r);
    root.r=addEl(0,root.r);

    printf("Preorder ispis : ");
    ispisPreorder(root.r);
    puts("\n");

    printf("inorder ispis : ");
    ispisInorder(root.r);
    puts("\n");

    printf("Postorder ispis : ");
    ispisPostorder(root.r);
    puts("\n");

    push(&q,root.r);

    printf("LevelOrder : ");
    levelOrder(&q);
    puts("\n");

    if(find(7,root.r)){
        printf("Element se nalazi u stablu. \n");
    }else{
        printf("Element se ne nalazi u stablu");
    }

    root.r=delete(0,root.r);
    puts("\n");

    ispisPreorder(root.r);


    
    
    return 0;
}

pos makeEl(int x){

    pos newEl = malloc(sizeof(node));
    newEl->el=x;
    newEl->l=NULL;
    newEl->r=NULL;
    return newEl;
}

pos addEl(int newEl,pos pointer){

    if(pointer == NULL){
        pos new=makeEl(newEl);
        return new;
    }

    if(pointer->el > newEl){
        pointer->l=addEl(newEl,pointer->l);
        return;
    }

    if(pointer->el < newEl){
        pointer->r=addEl(newEl,pointer->r);
        return;
    }
}

void ispisInorder(pos currentEl){

    if(currentEl==NULL)
        return;

    ispisInorder(currentEl->l);
    printf("%d " , currentEl->el);
    ispisInorder(currentEl->r);
}

void ispisPostorder(pos currentEl){

    if(currentEl==NULL)
        return;

    ispisPostorder(currentEl->l);
    ispisPostorder(currentEl->r);
    printf("%d " , currentEl->el);
}

void ispisPreorder(pos currentEl){

    if(currentEl==NULL)
        return;
    
    printf("%d " , currentEl->el);
    ispisPreorder(currentEl->l);
    ispisPreorder(currentEl->r);
}

void levelOrder(qPos q){

    pos toPrint=pop(q);

    if(toPrint==NULL)
    return;

    printf("%d " , toPrint->el);
    push(q,toPrint->l);
    push(q,toPrint->r);
    levelOrder(q);
}

void push(qPos q,pos tree){

    if(tree==NULL)
    return;

    qPos newQ;
    newQ = malloc(sizeof(queue));
    newQ->el=tree;
    newQ->next=q->next;
    q->next=newQ;
}

pos pop(qPos q){
    if(q->next==NULL){
        return NULL;
    }

    qPos temp=q->next;

    while(temp->next!=NULL){
        q=temp;
        temp=temp->next;
    }

    pos toReturn=temp->el;
    q->next=NULL;
    free(temp);

    return toReturn;
}

bool find(int x,pos root){

    if(root==NULL)
    return false;

    if(root->el<x){
        find(x,root->r);
    }else{
        if(root->el>x){
            find(x,root->l);
        }else{
            if(root->el==x){
                return true;
            }
        }
    }
}

pos delete(int value, pos root) {
	if(root==NULL)
		return root;

	else if(root->el>value)
		root->l=delete(value, root->l);
	else if (root->el < value)
		root->r=delete(value, root->r);
	else {
		if (root->r == NULL && root->l ==NULL) {
			free(root);
			return NULL;
		}
		else if (root->r == NULL) {
			pos temp = root;
			root = root->l;
			free(temp);
			return root;
		}
		else if (root->l == NULL) {
			pos temp = root;
			root = root->r;
			free(temp);
			return root;	
		}
		else {
			pos temp = findMin(root->r);
			root->el = temp->el;
			root->r = delete(temp->el, root->r);
			return root;
		}
	}

	return root;
}

pos findMin(pos root) {
	if (root == NULL)
		return NULL;
	while (root->l != NULL)
		root = root->l;
	return root;
}