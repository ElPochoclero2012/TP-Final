#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_JUEGOS 100

//struct juego.
//estado: 0 activo 1 inactivo
typedef struct{
    int fechaSalida;
    int precio;
    char nombre[40];
    int id;
    int estado;
    int stock;
}Juego;

///PROTOTIPOS====================================================================================================================
Juego cargarJuego();
void mostrarJuego(Juego auxJuego);

void cargarArchivoJuegos(char nombre[]);
void mostrarArchivoJuegos(char nombre[]);

int buscarJuegoPorId(char nombre[], int idABuscar);
int buscarJuegoPorNombre(char nombre[], char nombreABuscar[]);

void ordenarArchivoJuegosPorSeleccion(char nombre[]);
void ordenarArchivoJuegosPorPrecio(char nombre[]);

int pasarArchivoAArreglo(char nombre[], Juego lista[]);
void pasarArregloAArchivo(char nombre[], Juego lista[], int validos);

void ordenamientoSeleccion(Juego lista[], int validos);
void ordenamientoSeleccionPorPrecio(Juego lista[], int validos);

void mockJuegos(char nombre[]);
int bajaLogica(char nombre[],int idBuscado);

int modificarJuego(char nombre[],int idAModificar);
void cargarJuegoModificado(Juego *aux);

void filtroPorStock(char nombre[]);
void menu();

///VALIDACIONES
int validarNombre(char nombre[]);
int validarPrecio(int precio);
int validarAnio(int anio);
int validarId(int id);

int main()
{
    menu();

    return 0;
}
///=======================================================FUNCIONES===============================================================
///menu, me harté del quilombo del main
void menu()
{
    int opcion;
    char control = 's';

    do{
    system("cls");
    printf("===================MENU DE FUNCIONES DISPONIBLES===================\n");
    printf("1. Cargar un archivo de videojuegos\n");
    printf("2. Mostrar un archivo de videojuegos\n");
    printf("3. Buscar videojuego por ID\n");
    printf("4. Buscar videojuego por nombre\n");
    printf("5. Ordenamiento alfabeticamente\n");
    printf("6. Ordenamiento por precio\n");
    printf("7. Mock de Juegos\n");
    printf("8. Baja logica de juegos\n");
    printf("9. Modificacion de videojuegos\n");
    printf("10. Filtrar por stock\n");
    printf("Ingrese el nro de la funcion que desea ejecutar: \n");
    scanf("%d",&opcion);
    getchar();

    switch(opcion){
        case 1:
        ///CARGAR UN ARCHIVO "LISTA" DE VIDEOJUEGOS
        cargarArchivoJuegos("juegos.bin");
        break;

        case 2:
        printf("============LISTA DE JUEGOS============\n");
        mostrarArchivoJuegos("juegos.bin");

        break;

        case 3: {
    ///BUSCAR POR ID
        int idABuscar;

        printf("Ingrese el ID a buscar: \n");
        scanf("%d",&idABuscar);

        int res = buscarJuegoPorId("juegos.bin", idABuscar);

        if(res == 0){
            printf("ID inexistente en la lista.\n");
    }
}
        break;

        case 4: {
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
}
        break;

        case 5:
        ///ORDENAMIENTO ALFABETICAMENTE
        ordenarArchivoJuegosPorSeleccion("juegos.bin");
        //ARCHIVO ORDENADO ALFABETICAMENTE
        printf("=======================JUEGOS ORDENADOS ALFABETICAMENTE=======================\n");
        mostrarArchivoJuegos("juegos.bin");
        break;

        case 6:
        ///ORDENAMIENTO POR PRECIO
        ordenarArchivoJuegosPorPrecio("juegos.bin");
        //ARCHIVO ORDENADO POR PRECIO
        printf("=======================JUEGOS ORDENADOS POR PRECIO=======================\n");
        mostrarArchivoJuegos("juegos.bin");
        break;

        case 7:
        ///MOCK DE JUEGOS (DATOS DE 'PRUEBA')
        printf("DATOS DE PRUEBA: \n");
        mockJuegos("juegos.bin");

        break;

        case 8:{
    ///BAJA LÓGICA DE JUEGOS
        int idBuscado;
        printf("Ingrese el ID para dar de baja logica\n");
        scanf("%d",&idBuscado);

        int baja = bajaLogica("juegos.bin",idBuscado);
        if(baja == 1){
            printf("Juego dado de baja correctamente.\n");
        } else {
            printf("No se encontro el ID del juego en la lista.\n");
        }
}
        break;

        case 9:{
        ///MODIFICACIÓN DE JUEGOS
        int idAModificar;
        printf("Ingrese el ID del juego que desea modificar: \n");
        scanf("%d",&idAModificar);

        int modificado = modificarJuego("juegos.bin",idAModificar);
        if(modificado == 1){
            printf("%d",modificado);
        } else {
            printf("No se encontro el ID del juego en la lista\n");
        }
}
        break;

        case 10:
        ///FILTRAR POR STOCK
        filtroPorStock("juegos.bin");
        break;

        default:
            printf("Opcion invalida\n");
        break;


      }
        printf("Desea continuar ejecutando funciones del menu Juegos? s/n\n");
        scanf(" %c",&control);
    }while(control == 's');

}
///función cargarJuego modularizada. Validaciones incluidas
Juego cargarJuego()
{
    Juego aux;

    do{
        printf("Ingrese el nombre del juego: \n");
        fgets(aux.nombre,40,stdin);
        aux.nombre[strcspn(aux.nombre,"\n")] = 0;
    }while(!validarNombre(aux.nombre));

    do{
        printf("Ingrese el precio del juego: \n");
        scanf("%d",&aux.precio);
    }while(!validarPrecio(aux.precio));

    do{
        printf("Ingrese el anio de salida: \n");
        scanf("%d",&aux.fechaSalida);
    }while(!validarAnio(aux.fechaSalida));

    do{
        printf("Ingrese el ID del juego: \n");
        scanf("%d",&aux.id);
    }while(!validarId(aux.id));


    do{
        printf("Ingrese la cantidad de stock: \n");
        scanf("%d",&aux.stock);
    }while(aux.stock < 0);
    getchar();

    aux.estado = 0;

    return aux;
}
///función para cargar un archivo "lista" de videojuegos utilizando la función anterior hasta que el usuario lo decida
///es la Alta de Juegos
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
    printf("El precio del juego es: %d dolares\n",auxJuego.precio);
    printf("El anio de salida fue: %d\n",auxJuego.fechaSalida);
    printf("El ID del juego es: %d\n",auxJuego.id);
    printf("Cantidad en stock: %d\n",auxJuego.stock);
    printf("\n========================\n");
}
///funcion para mostrar una lista de juegos
void mostrarArchivoJuegos(char nombre[])
{
    FILE *buf = fopen(nombre,"rb");
    Juego aux;
    if(buf){
    while(fread(&aux,sizeof(Juego),1,buf) > 0){
            if(aux.estado == 0){
            mostrarJuego(aux);
            }
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
            if(idABuscar == aux.id && aux.estado == 0){
                mostrarJuego(aux);
                flag = 1;
                break;
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

            if(strcmpi(nombreABuscar, aux.nombre) == 0 && aux.estado == 0){

                mostrarJuego(aux);
                flag = 1;
                break;
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
///funcion para validar nombre
int validarNombre(char nombre[])
{
    int i = 0;

    while(nombre[i] != '\0'){

        if(!isspace(nombre[i])){
            return 1;
        }

        i++;
    }

    return 0;
}
///funcion para validar precio
int validarPrecio(int precio)
{
    return precio > 0;
}
///validar anio
int validarAnio(int anio)
{
    return anio >= 1950 && anio <= 2026;
}
///validar ID
int validarId(int id)
{
    return id > 0;
}
///mocks de juego
void mockJuegos(char nombre[])
{
    FILE *buf = fopen(nombre, "wb");

    Juego lista[] = {
        {2020,60,"Minecraft",1,0,15},
        {2018,45,"Fortnite",2,0,50},
        {2023,70,"Elden Ring",3,0,20},
        {2015,30,"Undertale",4,0,15},
        {2011,40,"Skyrim",5,0,5}
    };

    if(buf){
        fwrite(lista, sizeof(Juego), 5, buf);
        fclose(buf);
    } else{
        printf("No se pudo abrir el archivo");
    }
}
///BAJA LOGICA DE JUEGOS
int bajaLogica(char nombre[],int idBuscado)
{
    FILE*buf = fopen(nombre,"r+b");
    Juego aux;
    int flag = 0;

    if(buf){
        while(fread(&aux,sizeof(Juego),1,buf) > 0){
            if(aux.id == idBuscado){
                aux.estado = 1;

                fseek(buf,-sizeof(Juego),SEEK_CUR);

                fwrite(&aux,sizeof(Juego),1,buf);

                flag = 1;
                break;
            }
        }

    fclose(buf);
    }else {
        printf("No se pudo abrir el archivo\n");
    }
    return flag;
}
void cargarJuegoModificado(Juego *aux)
{
    getchar();

    do{
        printf("Ingrese el nuevo nombre del juego:\n");
        fgets((*aux).nombre, 40, stdin);
        (*aux).nombre[strcspn((*aux).nombre, "\n")] = 0;
    }while(!validarNombre((*aux).nombre));

    do{
        printf("Ingrese el nuevo precio:\n");
        scanf("%d", &aux->precio);
    }while(!validarPrecio((*aux).precio));

    do{
        printf("Ingrese el nuevo anio de salida:\n");
        scanf("%d", &aux->fechaSalida);
    }while(!validarAnio((*aux).fechaSalida));

    do{
        printf("Ingrese el nuevo stock:\n");
        scanf("%d", &aux->stock);
    }while((*aux).stock < 0);
}
///modificar juego
int modificarJuego(char nombre[],int idAModificar)
{
    FILE * buf = fopen(nombre,"r+b");
    Juego aux;
    int flag = 0;

    if(buf){
        while(fread(&aux,sizeof(Juego),1,buf) == 1){
            if(aux.id == idAModificar){
                flag = 1;

                printf("Ingrese los nuevos datos: \n");

                cargarJuegoModificado(&aux);

                fseek(buf,-sizeof(Juego),SEEK_CUR);

                fwrite(&aux,sizeof(Juego),1,buf);

                printf("Datos de juego modificado correctamente\n");
                break;
            }
        }

    fclose(buf);
    } else {
        printf("No se pudo abrir el archivo.\n");
    }
    return flag;
}
///filtrar por stock
void filtroPorStock(char nombre[])
{
    FILE*buf = fopen(nombre,"rb");
    Juego aux;

    if(buf){
        while(fread(&aux,sizeof(Juego),1,buf) == 1){
            if(aux.stock > 0 && aux.estado == 0){
                mostrarJuego(aux);
            }
        }

    fclose(buf);
    }else {
        printf("No se abrio el archivo\n");
    }
}
