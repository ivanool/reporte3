#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definimos la estructura
struct myStruct {
    int* array1;
    int* array2;
};

// Función que llena un array con números aleatorios
void fillArrayWithRandomNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100; // Generamos un número aleatorio entre 0 y 99
    }
}

int main() {
    srand(time(NULL)); // Inicializamos la semilla para generar números aleatorios
    
    // Creamos una instancia de la estructura
    struct myStruct myInstance;
    
    // Reservamos memoria para los dos arrays
    myInstance.array1 = malloc(10 * sizeof(int));
    myInstance.array2 = malloc(5 * sizeof(int));
    
    // Llenamos los arrays con números aleatorios
    fillArrayWithRandomNumbers(myInstance.array1, 10);
    fillArrayWithRandomNumbers(myInstance.array2, 5);
    
    // Imprimimos los arrays por pantalla
    printf("Array 1: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", myInstance.array1[i]);
    }
    printf("\n");
    
    printf("Array 2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", myInstance.array2[i]);
    }
    printf("\n");
    
    // Liberamos la memoria reservada para los arrays
    free(myInstance.array1);
    free(myInstance.array2);
    
    return 0;
}
