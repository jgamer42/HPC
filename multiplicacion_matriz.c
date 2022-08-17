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

void show_matrix(int size, long **matrix, char name[]){
    printf("Showing %s \n",name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%ld\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void fill_matrix(int size, long **matrix){
  for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++){
            matrix[col][row] = rand()%100;
        }
    }  
}

void assign_memory_to_matrix(int size,long **matrix){
    for (int index=0;index<size;++index){
        matrix[index] = (long*)malloc(size * sizeof(long));
    }
}

int main(void) {
    int size = user_input();
    long **result,**matrix_a,**matrix_b;
    matrix_a = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,matrix_a);
    fill_matrix(size,matrix_a);
    matrix_b = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,matrix_b);
    fill_matrix(size,matrix_b);
    result = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,result);
    for (int a = 0; a < size; a++) {
        for (int i = 0; i < size; i++) {
            long suma = 0;
            for (int j = 0; j < size; j++) {
                suma += matrix_a[i][j] * matrix_b[j][a];
            }
            result[i][a] = suma;
        }
    }
    show_matrix(size,result,"result");
}