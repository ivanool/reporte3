#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



struct producto{
    char nombre[20];
    char descripcion[100];
    int precio;
    int cantidad;
    int id;
};


void leer_archivo_csv(char *archivo, struct producto *productos, int *num_productos) {
    FILE *fp;
    char buffer[1024];
    int i = 0;

    fp = fopen(archivo, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo %s\n", archivo);
        exit(1);
    }


    fgets(buffer, 1024, fp);


    while (fgets(buffer, 1024, fp)) {

        char *nombre = strtok(buffer, ",");
        char *descripcion = strtok(NULL, ",");
        char *precio_str = strtok(NULL, ",");
        char *cantidad_str = strtok(NULL, ",");
        char *id_str = strtok(NULL, ",");

        int precio = atoi(precio_str);
        int cantidad = atoi(cantidad_str);
        int id = atoi(id_str);

        strcpy(productos[i].nombre, nombre);
        strcpy(productos[i].descripcion, descripcion);
        productos[i].precio = precio;
        productos[i].cantidad = cantidad;
        productos[i].id = id;

        i++;
    }

    *num_productos = i;

    fclose(fp);
}


void *mostrar_productos(struct producto *productos){
    
    for(int i = 0; i < 5; i++){

        printf("Nombre: %s\n", productos[i].nombre);
        printf("Descripcion %s\n", productos[i].descripcion);
        printf("Precio: %d\n", productos[i].precio);
        printf("Cantidad disponible: %d\n", productos[i].cantidad);
        printf("Id: %d\n", productos[i].id);
    }
}

int *agregar_producto(struct producto *productos, int *carrito[6][2]){
    printf("¿Digite el id del producto que desea agregar");
    int id;
    scanf("%d", &id);
    printf("¿Cuantos productos desea agregar?");
    int cantidad = 0;
    scanf("%d", &cantidad);
    if (cantidad > productos[id].cantidad){
        printf("No hay suficientes productos");
        return 0;
    }
    productos[id].cantidad -= cantidad;
    carrito[id][1] += cantidad;
    return 1;
}

int *eliminar_producto(struct producto *productos, int *carrito[6][2]){
    printf("¿Digite el id del producto que desea eliminar");
    int id;
    scanf("%d", &id);
    printf("¿Cuántos productos desea eliminar?");
    int cantidad;
    scanf("%d", &cantidad);
    if (cantidad > carrito[id][1]){
        printf("No hay suficientes productos en el carrito");
        return 0;
    }
    productos[id].cantidad += cantidad;
    carrito[id][1] -= cantidad;
    return 1;
}

int *mostrar_carrito(struct producto *productos, int *carrito[6][2]){
    int total = 0;
    for(int i = 0; i < 6; i++){
        if (carrito[i][1] != 0){
            printf("Nombre: %s \n", productos[i].nombre);
            int temporal = 0;
            temporal = carrito[i][1];
            printf("Costo: %d \n", (productos[i].precio*temporal)/4);
            printf("\n %d", temporal);
        }
    }
    return 0;

}

void comprar_productos(struct producto *productos, int *carrito[6][2]){
    FILE *fp;
    fp = fopen("recibo.txt", "w");
    fprintf(fp, "Factura de compra\n");
    for(int i = 0; i < 6; i++){
        if (carrito[i][1] != 0){
            fprintf(fp, "Nombre: %s", productos[i].nombre);
            int temporal = 0;
            temporal = carrito[i][1];
            int temporal2 = 0;
            temporal2 = (productos[i].precio * temporal)/4;
            fprintf(fp, "Costo: %d",temporal2);
            printf("\n");
        }
    }

    float costo_total = 0;

    for(int i = 0; i < 6; i++){
        if (carrito[i][1] != 0){
            int temporal = 0;
            temporal = carrito[i][1];
            costo_total += productos[i].precio*temporal;
        }
    }

    fprintf(fp, "\nCosto total: %f", costo_total/4);
    fclose(fp);


    for(int i = 0; i < 6; i++){
        carrito[i][1] = 0;
    }

}

void salir(struct producto *productos, int *carrito[6][2]){
    if (carrito[1][1] != 0 || carrito[2][1] != 0 || carrito[3][1] != 0 || carrito[4][1] != 0 || carrito[5][1] != 0 || carrito[6][1] != 0){
        printf("¿Desea comprar los productos en el carrito? (s/n)");
        char respuesta;
        scanf("%c", &respuesta);
        if (respuesta == 's'){
            comprar_productos(&productos, &carrito);
        }
        else{
            exit(0);

        }
    }
    else{
        exit(0);
    }

}

void menu(){

    
    int costo_total = 0;
    int a = -1;

    int *carrito[6][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};

    struct producto productos[5];
    int num_productos = 0;
    leer_archivo_csv("prueba.csv", productos, &num_productos);

    printf("Se leyeron %d productos del archivo:\n", num_productos);
    for (int i = 0; i < num_productos; i++) {
        printf("%s, %s, %d, %d, %d\n", productos[i].nombre, productos[i].descripcion, productos[i].precio, productos[i].cantidad, productos[i].id);
    }

    while(1){

        int opcion;
        printf("Buenos dias ¿Que desea hacer? \n");

        printf("¿Que desea hacer? \n");
        printf("1. Mostrar productos\n");
        printf("2. Agregar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar carrito\n");
        printf("5. Comprar productos\n");
        printf("6. Salir\n");

        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                mostrar_productos(&productos);
                break;
            case 2:
                a = agregar_producto(&productos, &carrito);
                if (a == 0){
                    printf("No se pudo agregar el producto");
                }
                else{
                    printf("Producto agregado");
                }
                break;
            case 3:
                a = eliminar_producto(&productos, &carrito);
                if (a == 0){
                    printf("No se pudo eliminar el producto");
                }
                else{
                    printf("Producto eliminado");
                }
                break;
            case 4:
                mostrar_carrito(&productos, &carrito);
                break;
            case 5:
                comprar_productos(&productos, &carrito);
                break;
            case 6:
                salir(&productos, &carrito);
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }
}

int main(){
    menu();
}
