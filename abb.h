#ifndef ABB_H
#define ABB_H
#define max_keys 4
#define min_keys (max_keys/2)
typedef struct No{
    int n;
    char keys[max_keys][21];
    struct No *fiho[max_keys+1];
    int leaf;
}No;

typedef struct btree{
    No *root;
}btree;

No* createNo(int leaf);
btree* createTree();
No* busca(No *no, char *key);
void split(No *parent, int i, No *child);
void insertNonFull(No* no, char *key);
void insert(btree *tree, char *key);
void display(No* no, int level);
void destroy(No *no);

#endif 