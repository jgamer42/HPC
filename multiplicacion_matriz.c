#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int user_input(){
    int size=0;
    printf("Ingrese el tamaño de las matricez: ");
    scanf("%d",&size);
    return size;
}

int main(void) {
    int size = user_input();
    int matrizA[size][size]; 
    int matrizB[size][size];
    int producto[size][size];
    int col,row = 0;
    memset(matrizA,0,sizeof(matrizA));
    while(row < size){
        col = 0;
        while(col < size){
            matrizA[col][row] = rand()%100;
            col ++;
        }
        row ++;
    }

    memset(matrizB,0,sizeof(matrizB));
    row = 0;
    col = 0;
    while(row < size){
        col = 0;
        while(col < size){
            matrizB[col][row] = rand()%100;
            col ++;
        }
        row ++;
    }
    memset(producto,0,sizeof(producto));

    for (int a = 0; a < size; a++) {
        for (int i = 0; i < size; i++) {
            int suma = 0;
            for (int j = 0; j < size; j++) {
                suma += matrizA[i][j] * matrizB[j][a];
            }
            producto[i][a] = suma;
        }
    }
    printf("Imprimiendo producto\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", producto[i][j]);
        }
        printf("\n");
    }
}