#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_JUEGOS 100

//struct juego
typedef struct{
    int fechaSalida;
    int precio;
    char nombre[40];
    int id;
}Juego;

///PROTOTIPOS====================================================================================================================
Juego cargarJuego();
void mostrarJuego(Juego auxJuego);

void cargarArchivoJuegos(char nombre[]);
void mostrarArchivoJuegos(char nombre[]);

int buscarJuegoPorId(char nombre[], int idABuscar);
int buscarJuegoPorNombre(char nombre[], char nombreABuscar);

void ordenarArchivoJuegosPorSeleccion(char nombre[]);
void ordenarArchivoJuegosPorPrecio(char nombre[]);

int pasarArchivoAArreglo(char nombre[], Juego lista[]);
void pasarArregloAArchivo(char nombre[], Juego lista[], int validos);

void ordenamientoSeleccion(Juego lista[], int validos);
void ordenamientoSeleccionPorPrecio(Juego lista[], int validos);


int main()
{
    ///CARGAR UN ARCHIVO "LISTA" DE VIDEOJUEGOS
    cargarArchivoJuegos("juegos.bin");

    system("cls");

    printf("============LISTA DE JUEGOS============\n");
    mostrarArchivoJuegos("juegos.bin");

    ///BUSCAR POR ID
    int idABuscar;

    printf("Ingrese el ID a buscar: \n");
    scanf("%d",&idABuscar);

    int res = buscarJuegoPorId("juegos.bin", idABuscar);

    if(res == 0){
        printf("ID inexistente en la lista.\n");
}
    ///BUSCAR POR NOMBRE
    char nombreABuscar[40];

    printf("Ingrese el nombre del juego a buscar: \n");

    getchar();

    fgets(nombreABuscar,40,stdin);

    nombreABuscar[strcspn(nombreABuscar,"\n")] = 0;

    if(buscarJuegoPorNombre("juegos.bin", nombreABuscar)){
        printf("Juego encontrado\n");
    } else {
        printf("Juego inexistente\n");
    }
    ///ORDENAMIENTO ALFABETICAMENTE
    ordenarArchivoJuegosPorSeleccion("juegos.bin");
    //ARCHIVO ORDENADO ALFABETICAMENTE
    mostrarArchivoJuegos("juegos.bin");

    ///ORDENAMIENTO POR PRECIO
    ordenarArchivoJuegosPorPrecio("juegos.bin");
    //ARCHIVO ORDENADO POR PRECIO
    mostrarArchivoJuegos("juegos.bin");

    return 0;
}

///función cargarJuego modularizada.
Juego cargarJuego()
{
    Juego aux;

    printf("Ingrese el nombre del juego: \n");
    fgets(aux.nombre,40,stdin);
    aux.nombre[strcspn(aux.nombre,"\n")] = 0;

    printf("Ingrese el precio del juego: \n");
    scanf("%d",&aux.precio);

    printf("Ingrese el anio de salida: \n");
    scanf("%d",&aux.fechaSalida);

    printf("Ingrese el ID del juego: \n");
    scanf("%d",&aux.id);

    getchar();

    return aux;
}
///función para cargar un archivo "lista" de videojuegos utilizando la función anterior hasta que el usuario lo decida
void cargarArchivoJuegos(char nombre[])
{
    FILE* buf = fopen(nombre,"ab");
    char control = 's';
    Juego aux;

    if(buf){
        while(control == 's'){
            aux = cargarJuego();
            fwrite(&aux,sizeof(Juego),1,buf);

            printf("Desea continuar cargando la informacion de mas juegos?: s/n\n");
            scanf(" %c",&control);
            getchar();
        }

    fclose(buf);
    }else {
        printf("No se pudo abrir el archivo\n");
    }
}

///función mostrarJuego de forma modularizada
void mostrarJuego(Juego auxJuego)
{
    printf("\n========================\n");
    printf("El nombre del juego es: %s\n",auxJuego.nombre);
    printf("El precio del juego es: %d\n",auxJuego.precio);
    printf("El anio de salida es: %d\n",auxJuego.fechaSalida);
    printf("El ID del juego es: %d\n",auxJuego.id);
    printf("\n========================\n");
}
///funcion para mostrar una lista de juegos
void mostrarArchivoJuegos(char nombre[])
{
    FILE *buf = fopen(nombre,"rb");
    Juego aux;
    if(buf){
    while(fread(&aux,sizeof(Juego),1,buf) > 0){
            mostrarJuego(aux);
          }
    fclose(buf);
    } else {
        printf("No se pudo abrir el archivo\n");
    }
}
///funcion para buscar un juego en la lista de juegos por ID
int buscarJuegoPorId(char nombre[], int idABuscar)
{
    FILE *buf = fopen(nombre,"rb");
    Juego aux;
    int flag = 0;

    if(buf){
        while(fread(&aux,sizeof(Juego),1,buf) > 0){
            if(idABuscar == aux.id){
                mostrarJuego(aux);
                flag = 1;
            }
        }
        fclose(buf);
    } else {
        printf("No fue posible abrir el archivo\n");
    }
    return flag;
}
///funcion modularizada para buscar un juego en la lista de juegos por nombre
int buscarJuegoPorNombre(char nombre[], char nombreABuscar[])
{
    FILE *buf = fopen(nombre, "rb");
    Juego aux;
    int flag = 0;

    if(buf){

        while(fread(&aux, sizeof(Juego), 1, buf) > 0){

            if(strcmpi(nombreABuscar, aux.nombre) == 0){

                mostrarJuego(aux);
                flag = 1;
            }
        }

        fclose(buf);
    }
    return flag;
}
///función principal que ordena el archivo de juegos utilizando el algoritmo de selección y como parámetro el alfabeto
///pasarArchivoAArreglo() copia los registros del archivo a un arreglo y retorna la cantidad de elementos cargados
///ordenamientoSeleccion() ordena un arreglo de juegos alfabéticamente utilizando el algoritmo de selección
///pasarArregloAArchivo() sobrescribe el archivo con el arreglo ya ordenado
void ordenarArchivoJuegosPorSeleccion(char nombre[])
{
    Juego lista[MAX_JUEGOS];

    int validos = pasarArchivoAArreglo(nombre, lista);

    ordenamientoSeleccion(lista, validos);

    pasarArregloAArchivo(nombre, lista, validos);
}
int pasarArchivoAArreglo(char nombre[], Juego lista[])
{
    FILE *buf = fopen(nombre, "rb");
    int validos = 0;

    if(buf){
        while(validos < MAX_JUEGOS && fread(&lista[validos], sizeof(Juego), 1, buf) > 0){
            validos++;
        }
        fclose(buf);
    }
    return validos;
}
void ordenamientoSeleccion(Juego lista[],int validos)
{
    Juego aux;
    int posMenor;

    for(int i = 0; i < validos - 1; i++){
            posMenor = i;

            for(int j = i + 1; j < validos; j++){

                if(strcmpi(lista[j].nombre, lista[posMenor].nombre) < 0){
                    posMenor = j;
                }
            }
            aux = lista[i];
            lista[i] = lista[posMenor];
            lista[posMenor] = aux;
        }
}
void pasarArregloAArchivo(char nombre[], Juego lista[], int validos)
{
    FILE *buf = fopen(nombre, "wb");

    if(buf){
        fwrite(lista, sizeof(Juego), validos, buf);
        fclose(buf);
    }
}
///ordena un arreglo de juegos por precio utilizando el algoritmo de selección
///función principal que ordena el archivo de juegos por precio
void ordenarArchivoJuegosPorPrecio(char nombre[])
{
    Juego lista[MAX_JUEGOS];

    int validos = pasarArchivoAArreglo(nombre, lista);

    ordenamientoSeleccionPorPrecio(lista, validos);

    pasarArregloAArchivo(nombre, lista, validos);
}
void ordenamientoSeleccionPorPrecio(Juego lista[], int validos)
{
    Juego aux;
    int posMenor;

    for(int i = 0; i < validos - 1; i++){

        posMenor = i;

        for(int j = i + 1; j < validos; j++){

            if(lista[j].precio < lista[posMenor].precio){

                posMenor = j;
            }
        }
        aux = lista[i];
        lista[i] = lista[posMenor];
        lista[posMenor] = aux;
    }
}

