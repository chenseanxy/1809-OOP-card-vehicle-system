#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int Status;

typedef struct Tnode{
    string word;
    int count;
    Tnode* left;
    Tnode* right;
}Tnode, *Tree;

Status newnode(Tree T, bool L, string word){
    Tnode* node=(Tnode*)malloc(sizeof(Tnode));
    if(node==NULL){return -1;}

    if(L){
        T->left=node;
    }
    else{
        T->right=node;
    }
    T->count++;
    node->word=word;
    node->left=NULL;
    node->right=NULL;
    node->count=0;
}

Status printTree(Tree T){
    while(true){
        if(T->left!=NULL){
            printTree(T->left);
        }
        if(T->right!=NULL){
            printTree(T->right);
        }
        cout << T->word << endl;
    }
}

int main(){

    system("pause");
    return 0;
}