#include <stdio.h>
#include <stdlib.h>

struct node{
    int valor;
	struct node *dir;
	struct node *esq;
};

typedef struct node Node;
int contador=0, maior=0;

Node* criar_arv(int valor){
    Node *n = malloc(sizeof(Node));
    n->valor = valor;
    n->esq = NULL;
    n->dir = NULL;
    maior = valor;
    return n;
}

void inserir_arv(Node *n, int valor){
    if(valor< n->valor){
        if(n->esq==NULL){
            n->esq = criar_arv(valor);
        }else{
            inserir_arv(n->esq, valor);
        }
    }else{
        if(n->dir==NULL){
            n->dir = criar_arv(valor);
        }else{
            inserir_arv(n->dir, valor);
        }
    }
    
}

void imprimir_arv(Node *n){
    if(n==NULL)
        return;
        imprimir_arv(n->esq);
        printf("\n%d", n->valor);
        imprimir_arv(n->dir);
        if(n->valor >= maior){
          maior = n->valor;
        }
        contador++;
} 

void remover_arv(Node *n, int valor){

	Node *filho = n;
	Node *pai;

  if(maior == valor){
    maior=0;
  }

	do{
		pai = filho;
		if(valor < filho->valor)
			filho = filho->esq;
		else if(valor > filho->valor)
			filho = filho->dir;	
	}while(filho!=NULL && filho->valor != valor);

	if(filho != NULL){
		if(filho->esq == NULL && filho->dir == NULL){
			if(pai->esq == filho) pai->esq = NULL;
			if(pai->dir == filho) pai->dir = NULL;
		}
		if(filho->esq != NULL && filho->dir == NULL){
			if(pai->esq == filho) pai->esq = filho->esq;
			if(pai->dir == filho) pai->dir = filho->esq;
		}
		if(filho->esq == NULL && filho->dir != NULL){
			if(pai->esq == filho) pai->esq = filho->dir;
			if(pai->dir == filho) pai->dir = filho->dir;
		}
		if(filho->esq != NULL && filho->dir != NULL){
			if(filho->esq->dir==NULL){
				filho->valor = filho->esq->valor;
				filho->esq = NULL;
			}else{
				Node *p = filho->esq;
				Node *aux = p;
				while(p->dir != NULL){
					aux = p;
					p = p->dir;
				}
				aux->dir = NULL;
				filho->valor = p->valor;
			}
		}
	}
}

int altura_arv(Node *n){
   if(n == NULL){
     return -1;
   }else{
     int al_esq = altura_arv(n->esq);
     int al_dir = altura_arv(n->dir);
     if(al_esq > al_dir){
       return al_esq+1;
     }else{
       return al_dir+1;
     }

   }

}

void imprimir_maior(){
    printf("\n\nMaior: %d", maior);
}


void quantidade_nos(){
    printf("\n\nNós: %d", contador);
}

int main(void){

    Node *root = criar_arv(3);

    inserir_arv(root, 5);
    inserir_arv(root, 4);
    inserir_arv(root, 7);
    inserir_arv(root, 2);
    inserir_arv(root, 1);
    inserir_arv(root, 0);
    inserir_arv(root, 8);
    inserir_arv(root, 9);


    remover_arv(root, 9);
    remover_arv(root, 8);
    remover_arv(root, 4);

    imprimir_arv(root);

    quantidade_nos();
    printf("\n\nAltura: %d", altura_arv(root));
    imprimir_maior();

    return 0;
}