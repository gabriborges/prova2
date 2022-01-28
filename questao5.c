#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char nome[50];
  int camisa;
	struct node *dir;
	struct node *esq;
};

typedef struct node Node;

int contador=1, camisatemporario=0;

Node* criar_jogador(int camisa){
  if(contador>11){
    printf("\n!!!!!--> Este jogador não pode ser adicionado, não pode haver mais de 11 jogadores titulares em um mesmo time <--!!!!"); 
    return 0;
  }else{ 

    Node *n = malloc(sizeof(Node));
    n->camisa = camisa;
    printf("\nNome do jogador de camisa %d? ", camisa);
    scanf("%s", n->nome);
    n->esq = NULL;
    n->dir = NULL;
    contador++;
    return n;

  }
}

void inserir_jogador(Node *n, int camisa){
    if(camisa < n->camisa){
        if(n->esq==NULL){
            n->esq = criar_jogador(camisa);
        }else{
            inserir_jogador(n->esq, camisa);
        }
    }else{
        if(n->dir==NULL){
            n->dir = criar_jogador(camisa);
        }else{
            inserir_jogador(n->dir, camisa);
        }
    }
    
}

void imprimirEmOrdem(Node *n){
    if(n==NULL)
        return;
        imprimirEmOrdem(n->esq);
        printf("\nCamisa %d: ", n->camisa);
        printf("%s", n->nome);
        imprimirEmOrdem(n->dir);
} 

void imprimirPosOrdem(Node *n){
  if(n != NULL){
    imprimirPosOrdem(n->esq);
    imprimirPosOrdem(n->dir);
    printf("\nCamisa %d: ", n->camisa);
    printf("%s", n->nome);
  }
}


void removerjogador(Node *n, int camisa){
  
  contador--;
	Node *filho = n;
	Node *pai;

	do{
		pai = filho;
		if(camisa < filho->camisa)
			filho = filho->esq;
		else if(camisa > filho->camisa)
			filho = filho->dir;	
	}while(filho!=NULL && filho->camisa != camisa);

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
				filho->camisa = filho->esq->camisa;
				filho->esq = NULL;
			}else{
				Node *p = filho->esq;
				Node *aux = p;
				while(p->dir != NULL){
					aux = p;
					p = p->dir;
				}
				aux->dir = NULL;
				filho->camisa = p->camisa;
			}
		}
	}

  printf("\n\n----- O jogador de camisa %d foi removido e precisa ser substituido -----\n", camisa);
  printf("\nNumero do jogador substituto? ");
  scanf("%d", &camisatemporario);
  inserir_jogador(n, camisatemporario);

}

int main(void){

    Node *root = criar_jogador(7);

    inserir_jogador(root, 4);
    inserir_jogador(root, 2);
    inserir_jogador(root, 1);
    inserir_jogador(root, 3);
    inserir_jogador(root, 5);
    inserir_jogador(root, 8);
    inserir_jogador(root, 10);

    removerjogador(root, 4);

    printf("\nPos-Ordem: ");
    imprimirPosOrdem(root);
    printf("\n");

    printf("\nEm-Ordem: ");
    imprimirEmOrdem(root);
    printf("\n");

    return 0;
}