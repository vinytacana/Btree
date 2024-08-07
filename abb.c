#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "abb.h"

No* createNo(int leaf){
    No* newNo= (No*)malloc(sizeof(No));
    newNo->n=0;
    newNo->leaf=leaf;
    for(int i=0;i<max_keys;i++){
        newNo->fiho[i]=NULL;
    }
    return newNo;
}
btree* createTree(){
    btree *newTree=(btree*)malloc(sizeof(btree));
    newTree->root=createNo(1);
    return newTree;
}

No* busca(No *no, char *key){
    int i=0;
    while(i<no->n && strcmp(key,no->keys[i])>0){
        i++;
    }
    if(i<no->n && strcmp(key,no->keys[i])==0){
        return no;
    }
    if(no->leaf){
        return NULL;
    }
    return busca(no->fiho[i],key);
}

void split(No *parent, int i, No *child){
    No* newNo= createNo(child->leaf);
    newNo->n=min_keys;

    for(int j=0;j<min_keys;j++){
        strcpy(newNo->keys[j],child->keys[j+min_keys+1]);
    }

    if(!child->leaf){
        for(int j=0;j<min_keys+1;j++){
            newNo->fiho[j]=child->fiho[j+min_keys+1];
        }
    }
    child->n=min_keys;
    for(int j=parent->n;j>=i+1;j--){
        parent->fiho[j+1]=parent->fiho[j];
    }
    parent->fiho[i+1]=newNo;

    for(int j=parent->n-1;j>=i;j--){
        strcpy(parent->keys[j+1], parent->keys[j]);
    }
    strcpy(parent->keys[i], child->keys[min_keys]);
    parent->n+=1;
}

void insertNonFull(No* no, char *key){
    int i= no->n-1;

    if(no->leaf){
        while(i>=0 && strcmp(key, no->keys[i])<0){
            strcpy(no->keys[i+1],no->keys[i]);
            i--;
        }
        strcpy(no->keys[i+1],key);
        no->n+=1;
    }else{
        while(i>=0 && strcmp(key,no->keys[i])<0){
            i--;
        }
        i++;
        if(no->fiho[i]->n==max_keys){
            split(no,i,no->fiho[i]);
            if(strcmp(key,no->keys[i]>0)){
                i++;
            }
        }

        insertNonFull(no->fiho[i],key);
    }
}

void insert(btree *tree, char *key){
    No*root= tree->root;
    if(root->n== max_keys){
        No* newRoot = createNo(0);
        newRoot->fiho[0]= root;
        split(newRoot, 0, root);
        insertNonFull(newRoot, key);
        tree->root=newRoot;
    }else{
        insertNonFull(root, key);
    }
}

void display(No* no, int level){
    if(no){
        int i;
        for(i=0;i<no->n;i++){
            if(!no->leaf){
                display(no->fiho[i], level+1);
            }
            printf("Nivel: %d, chave: %d\n",level, no->keys[i]);
        }
        if(!no->leaf){
            display(no->fiho[i], level+1);
        }
    }
}

void destroy(No *no){
    if(no){
        if(!no->leaf){
            for(int i=0;i<=no->n;i++){
                destroy(no->fiho[i]);
            }
        }
        free(no);
    }
}
