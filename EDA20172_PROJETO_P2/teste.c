#include <stdio.h>
#include <stdlib.h>

typedef struct arv {
    int info;
    struct arv *esq;
    struct arv *dir;
}arv;

#define espaco 5

int capacidade_usada = 0;

void calcula_capacidade_usada(arv *p){
    if(p){
        capacidade_usada++;
        calcula_capacidade_usada(p->dir);
        calcula_capacidade_usada(p->esq);
    }
}

void desenha_arvore_horiz(arv *arvore, int depth, char *path, int dir){
    int i, j;

    if (arvore== NULL)
        return;

    depth++;

    desenha_arvore_horiz(arvore->dir, depth, path, 1);

    path[depth-2] = 0;

    if(dir)
        path[depth-2] = 1;

    if(arvore->esq)
        path[depth-1] = 1;

    printf("\n");

    for(i=0; i<depth-1; i++){
      if(i == depth-2)
          printf("+");
      else if(path[i])
          printf("|");
      else
          printf(" ");

      for(j=1; j<espaco; j++)
        if(i < depth-2)
            printf(" ");
        else
          printf("-");
    }

    printf("%d\n", arvore->info);

    for(i=0; i<depth; i++){
      if(path[i])
          printf("|");
      else
          printf(" ");

      for(j=1; j<espaco; j++)
          printf(" ");
    }

    desenha_arvore_horiz(arvore->esq, depth, path, 0);
}

void draw_arvore_hor(arv *arvore){
    char path[255] = {};
    desenha_arvore_horiz(arvore, 0, path, 0);
}

arv * rot_dir(arv *p){
    arv *q, *temp;
    q = p->esq;
    temp = q->dir;
    q->dir = p;
    p->esq = temp;
    p = q;

    return p;
}

arv * rot_esq(arv *p){
    arv *q, *temp;
    q = p->dir;
    temp = q->esq;
    q->esq = p;
    p->dir = temp;
    p = q;

    return p;
}

arv * rot_esq_dir(arv *p){
    p = rot_esq(p->esq);
    p = rot_dir(p);

    return p;
}

arv * rot_dir_esq(arv *p){
    p = rot_dir(p->dir);
    p = rot_esq(p);

    return p;
}

arv * novo_no(int valor){
    arv *novo = (arv*)malloc(sizeof(arv));

    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

int calcula_nivel(arv *r) {
   if (r == NULL)
      return -1; // altura da árvore vazia
   else {
      int he = calcula_nivel(r->esq);
      int hd = calcula_nivel(r->dir);
      if (he < hd) return hd + 1;
      else return he + 1;
   }
}

int fat_bal(arv *p){
    int fat;

    if(p){
        fat = ((calcula_nivel(p->dir) + 1) - (calcula_nivel(p->esq) + 1));
        return fat;
    }

    return -1;
}

arv * balanceia_arv(arv *p){
    arv *temp;

    if(p){
        if(fat_bal(p) < -1){
            if(fat_bal(p->esq) < 0)
                p = rot_dir(p);
            else
                p = rot_esq_dir(p);
        }
        else if(fat_bal(p) > 1){
            if(fat_bal(p->dir) > 0)
                p = rot_esq(p);
            else
                p = rot_dir_esq(p);
        }
    }

    return p;
}

arv * inserir(arv *p, arv *elemento){
    if(!p)
        return elemento;
    else{
        if(elemento->info > p->info){
          p->dir = inserir(p->dir, elemento);
          p = balanceia_arv(p);
        }
        else{
          p->esq = inserir(p->esq, elemento);
          p = balanceia_arv(p);
        }
    }

    return p;
}

void imprime(arv *p){
    if(p){
        printf("\n%d\n", p->info);
        imprime(p->esq);
        imprime(p->dir);
    }
}

int main(){
    arv *raiz = NULL;
    int qtd, i, valor;
    int nivel = 0;

    scanf("%d", &qtd);

    for(i = 0; i < qtd; i++){
        scanf("%d", &valor);
        raiz = inserir(raiz, novo_no(valor));
    }

    calcula_capacidade_usada(raiz);

    printf("\nUsado: %d\n", capacidade_usada);
    draw_arvore_hor(raiz);
    printf("\n");

    return 0;
}
