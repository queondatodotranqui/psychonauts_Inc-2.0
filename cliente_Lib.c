#include <stdio.h>
#include <stdlib.h>
#include "cliente_Lib.h"
#include "archivo_Clientes_Lib.h"
#include <conio.h>
#include <string.h>

#define ESC 27

stCliente CargaCliente(){
    stCliente c;

    // id cliente

    system("cls");
    c.id = BuscaUltimoId() + 1;

    printf("A continuacion ingrese los datos solicitados para Cargar el Cliente: \n");

    // numero de cliente

    do{
        printf("Numero de Cliente: \n");
        scanf("%d", &c.numCliente);
        if(ExisteNumCliente(c.numCliente) == 1){ // VERIFICA QUE EL NUMERO DE CLIENTE NO SE REPITA
            printf("El numero de Cliente seleccionado ya esta en uso \n");
        }
    }while(c.numCliente < 0 || c.numCliente > 9999 || ExisteNumCliente(c.numCliente) == 1);

    system("cls");

    // NOMBRE

    printf("Nombre del Cliente: \n");
    fflush(stdin);
    gets(c.nombre);
    system("cls");

    // APELLIDO

    printf("Apellido Cliente: \n");
    fflush(stdin);
    gets(c.apellido);

    // DNI

    do{
        system("cls");
        printf("DNI del Cliente: \n");
        scanf("%d", &c.dni);
        if (ExisteCliente(c.dni) == 1){ // VERIFICA QUE EL CLIENTE NO ESTE YA INGRESADO EN EL ARCHIVO
            printf("Error el Cliente ya esta creado en el archivo \n");
            system("pause");
        }
    }while(ExisteCliente(c.dni) == 1);

    // EMAIL

    do{
        system("cls");
        printf("e-mail del Cliente: \n");
        fflush(stdin);
        gets(c.email);
        if (ValidacionEmail(c.email) == 0){ // VERIFICA QUE EL EMAIL SEA VALIDO
            printf("Error el email no es valido \n");
            system("pause");
        }
    }while(ValidacionEmail(c.email) == 0);

    // DOMICILIO

    system("cls");
    printf("Domicilio del Cliente: \n");
    fflush(stdin);
    gets(c.domicilio);

    // TELEFONO

    system("cls");
    printf("Prefijo del Telefono del Cliente: \n");
    scanf("%d", &c.movilPre);

    system("cls");
    printf("Sufijo del Telefono del Cliente: \n");
    scanf("%d", &c.movilSu);


    // BAJA

    c.baja = 0; // 0 Es ACTIVO 1 es INACTIVO  ///////  LO CARGAMOS SIEMPRE ACTIVO

    return c;
}

int ValidacionEmail (char email[]){
    int v = strlen(email);
    int i = 0;
    int flag = 0;
    while(i<v && flag == 0){
        if(email[i] == 64){
            flag = 1;
        }
        i++;
    }
    return flag; // SI ENCUENTRA UN @ EN EL ARREGLO RETORNA 1
}

void MuestraCliente(stCliente c){
    printf("------------------------------------- \n");
    printf("Numero de Cliente: %d \n", c.numCliente);
    printf("Nombre: %s \n", c.nombre);
    printf("Apellido: %s \n", c.apellido);
    printf("DNI: %d \n", c.dni);
    printf("email: %s \n", c.email);
    printf("Domicilio: %s \n", c.domicilio);
    printf("Telefono: %d - %d \n", c.movilPre, c.movilSu);
    printf("------------------------------------- \n");
}

stCliente ModificacionCliente(stCliente c){
    int opc;
    int opc2;
    do{
        printf("Ingrese la opcion segun que desea Modificar: \n");
        printf("1- Nombre \n");
        printf("2- Apellido \n");
        printf("3- DNI \n");
        printf("4- Email \n");
        printf("5- Domicilio \n");
        printf("6- Telefono \n");
        opc = getch();
        switch(opc){
            case 49:
                system("cls");
                printf("Ingrese el Nuevo Nombre: \n");
                fflush(stdin);
                gets(c.nombre);
                break;
            case 50:
                system("cls");
                printf("Ingrese el Nuevo Apellido: \n");
                fflush(stdin);
                gets(c.apellido);
                break;
            case 51:
                system("cls");
                printf("Ingrese el Nuevo DNI: \n");
                scanf("%d", &c.dni);
                break;
            case 52:
                do{
                    system("cls");
                    printf("Ingrese el Nuevo Email: \n");
                    fflush(stdin);
                    gets(c.email);
                    if (ValidacionEmail(c.email) == 0){
                        printf("Error el email no es valido \n");
                    }
                    system("pause");
                } while(ValidacionEmail(c.email) == 0);
                break;
            case 53:
                system("cls");
                printf("Ingrese el Nuevo Domicilio: \n");
                fflush(stdin);
                gets(c.domicilio);
                break;
            case 54:
                system("cls");
                printf("Ingrese el Nuevo Prefijo del Telefono: \n");
                scanf("%d", &c.movilPre);

                system("cls");
                printf("Ingrese el Nuevo Sufijo del Telefono: \n");
                scanf("%d", &c.movilSu);
            default:
                system("cls");
                printf("La opcion es Invalida \n");
        }
        system("cls");
        printf("Presione ENTER para modificar otra informacion del cliente o ESC para Salir \n");
        opc2 = getch();
    } while(opc2 != ESC);
    return c;
}
