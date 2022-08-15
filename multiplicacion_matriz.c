#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int user_input(){
    int size=0;
    printf("Ingrese el tamaño de las matricez: ");
    scanf("%d",&size);
    printf("\n");
    return size;
}

void show_matrix(int size, int matrix[size][size], char name[]){
    printf("Showing %s \n",name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    int size = user_input();
    int matrix_a[size][size],matrix_b[size][size],result[size][size];
    
    memset(matrix_a,0,sizeof(matrix_a));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++){
            matrix_a[col][row] = rand()%100;
        }
    }
    show_matrix(size,matrix_a,"A");

    memset(matrix_b,0,sizeof(matrix_b));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++){
            matrix_b[col][row] = rand()%100;
        }
    }
    show_matrix(size,matrix_b,"B");

    memset(result,0,sizeof(result));
    for (int a = 0; a < size; a++) {
        for (int i = 0; i < size; i++) {
            int suma = 0;
            for (int j = 0; j < size; j++) {
                suma += matrix_a[i][j] * matrix_b[j][a];
            }
            result[i][a] = suma;
        }
    }
    show_matrix(size,result,"result");
}