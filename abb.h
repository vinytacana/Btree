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

#endif 