#include <stdio.h>
#include <stdlib.h>
#define N 9


//lê os valores da matriz de entrada
void lerMatriz(unsigned char matriz[N][N]){
  
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%hhd", &matriz[i][j]);
        }
    }

    printf("\n");
  
}


//imprime a matriz organizada 
void imprimirMatriz(unsigned char matriz[][N]){

  printf("    ");
  for(int i=0; i<N; i++) {
    if(i==3|| i==6) {
      printf("   ");
    }
    printf("%d ",i);
  }

  printf("\n");
  
  for(int i=0; i<N+1; i++) {
    printf("  -");
  }
  
  printf("\n");
  
  for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++) {
            if(j==0) {
                printf("%d | ",i);
            }
            if(matriz[i][j]==0) {
                printf("- ");
            } else {
                //para imprimir os números inseridos pelo usuário
                if(matriz[i][j]>=10) {
                    printf("%d ",matriz[i][j]-9);
                } else {
                    printf("%d ",matriz[i][j]);
                }
            }

            if((j+1)%3==0) {
                printf(" | ");
            }
        }
    
        printf("\n");
    
        if(i==2 || i==5 || i==8) {
            for(int i=0; i<N+1; i++) {
                printf("  -");
            }
            printf("\n");
    }
  }
  
}


//elimina as células aleatoriamente
void eliminarCelulas(unsigned char matriz[][N], unsigned char numCelulasEliminadas, unsigned seed) {

    printf("\n");
    srand(seed);
    int linha, coluna;
  
    for(int i=0; i<numCelulasEliminadas; i++) {
    
        linha = rand() % 10;
        coluna = rand() % 10;

        matriz[linha][coluna]=0;
    
    }

    imprimirMatriz(matriz);
  
}


//preenche as células sem valor
char preencherCelula(unsigned char matriz[][N], unsigned char x, unsigned char y, unsigned char valor) {

    if(valor>0) {
        matriz[x][y]=valor;
        return 1;
    } else {
        return 0;
    }

}

//verifica se o número se repete pela linha
char verificarLinha(unsigned char matriz[][N], unsigned char x, unsigned char y){
  
  int acum=0;
  
  for(int i=0;i<N;i++){
        if(matriz[x][i] == matriz[x][y]) {
            acum++;
        }
    }

    if(acum>1) {
        return 0;
    } else {
        return 1;
    }
  
}


//verifica se o número se repete pela coluna
char verificarColuna(unsigned char matriz[][N], unsigned char x, unsigned char y){
  
  int acum=0;
  
    for(int i=0;i<N;i++){
        if(matriz[i][y]==matriz[x][y]){
            acum++;
        }
    }

    if(acum>1) {
        return 0;
    } else {
        return 1;
    }
  
}


//verifica se há números repetidos por bloco
char verificaBloco(unsigned char matriz[][N], unsigned char x, unsigned char y){

    int linhaBloco, colunaBloco;
    int acum=0;

    linhaBloco = (x+ ( 3- (x % 3))) -3;
    colunaBloco = (y+ ( 3- (y % 3))) -3;

    for(int i=linhaBloco; i<(linhaBloco+3); i++) {
        for(int j=colunaBloco; j<(colunaBloco+3); j++) {
            if(matriz[i][j]==matriz[x][y]) {
                acum++;
            }
        
        }
    }

    if(acum>1) {
        return 0;
    } else {
        return 1;
    }
  
}

//para conferir se é uma jogada válida
char jogadaInvalida(unsigned char matriz[][N], unsigned char x, unsigned char y){

    if(matriz[x][y]!=0 || x>8 || x<0 || y>8 || x<0) {
        return 0;
    } else {
        return 1;
    }
   
}


char ganhouJogo(unsigned char matriz[N][N]){
 
  int numOk = 0;
  int numEntradas = 0;

  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(matriz[i][j]>=10) {
            numEntradas++;
            matriz[i][j]=matriz[i][j]-9;
            if(verificarLinha(matriz,i,j)==1 && verificarColuna(matriz,i,j)==1 &&  verificaBloco(matriz,i,j)==1) {
                numOk++;
            }
        } 
    }
  }

    if(numEntradas==numOk) {
        return 1;
    } else {
        return 0;
    }

}

//Verificar se todas as células da matriz foram preenchidas
int checkJogo(unsigned char matriz[][N]) {

    int verifica = 0;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(matriz[i][j]!=0) {
                verifica++;
            }
        }
    }

    if(verifica == 81) {
        return 1;
    } else {
        return 0;
    }
  
}


int main(void) {
  
    unsigned char m[N][N];
    unsigned char seed, celElim, x, y, valor;
    int resultado;

    //lê os elementos da matriz gabarito
    printf("Entre com uma matriz 9x9 com o gabarito do jogo: \n");
    lerMatriz(m);

    //entradas do seed e o número de células que o usuário deseja eliminar
    printf("Digite o seed e o número de células eliminadas: \n");
    scanf("%hhd %hhd",&seed,&celElim);

    //manda eliminar o número de células que o usuário deseja 
    eliminarCelulas(m, celElim, seed);

    //entradas sucessivas
    while(checkJogo(m)!=1) {

        printf("Digite uma coordenada (x y) e um valor para atribuir a essa coordenada: \n");

        //lendo as coordenadas
        scanf("%hhd %hhd %hhd",&x,&y,&valor);
        
        if(jogadaInvalida(m,x,y)==1 && valor>0 && valor<10){
            valor=valor+9;
            preencherCelula(m,x,y,valor);
            printf("\n");
            imprimirMatriz(m);
        } else {
            printf("\nJogada inválida\n\n");
            imprimirMatriz(m);
        }
        
    }

    resultado = ganhouJogo(m);

    if(resultado == 1) {
        printf("Parabéns você ganhou!!"); 
    } else {
        printf("Você não ganhou");
    }
        
    return 0;
}