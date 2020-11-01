#include <stdio.h>
#include <stdlib.h>
#include "menu_Lib.h"
#include "cliente_Lib.h"
#include "consumos_Lib.h"
#include "archivo_Clientes_Lib.h"
#include "archivo_Consumos_Lib.h"
#include "stats_Lib.h"

#include <conio.h>
#include <string.h>
#include "gotoxy.h"

#define arCliente "clientes.dat"
#define arConsumo "consumos.dat"
#define ESC 27
#define AnioMax 2020
#define AnioMin 2000

/*********************************************************//**
* \brief Menu principal del programa.
***********************************************************/
void MenuPrincipal(){
    int opc;
    int opc2;
    do{
        system("cls");
        color(10);
        printf("------------------------------------------ Psychonauts Inc ------------------------------------------\n");
        gotoxy(44, 8);
        color(160);
        printf("1- Clientes \n");
        gotoxy(44, 12);
        color(160);
        printf("2- Consumos \n");
        color(7);
        opc = getch();
        switch (opc){
            case 49:
                SubMenuClientes();
                break;
            case 50:
                SubMenuConsumos();
                break;
            default:
                system("cls");
                printf("Opcion Incorrecta \n");
        }
        system("cls");
        printf("\nPresione ENTER volver al MENU PRINCIPAL o ESC para Salir \n");
        opc2 = getch();
    }while(opc2 != ESC);
}


void SubMenuClientes(){
    int opc;
    system("cls");
    color(10);
    printf("-------------------------------------------- Psychonauts Inc --------------------------------------------\n");
    gotoxy(43, 6);
    color(160);
    printf("1- Alta de Clientes\n");
    gotoxy(43, 8);
    color(160);
    printf("2- Baja de Clientes\n");
    gotoxy(39, 10);
    color(160);
    printf("3- Modificacion de Clientes\n");
    gotoxy(40, 12);
    color(160);
    printf("4- Listar Clientes Activos\n");
    gotoxy(39, 14);
    color(160);
    printf("5- Listar Clientes Inactivos\n");
    opc = getch();
    switch (opc){
        case 49:
            SubMenuAltaClientes();
            break;
        case 50:
            SubMenuBajaClientes();
            break;
        case 51:
            SubMenuModificacionClientes();
            break;
        case 52:
            SubMenuListarClientesActivos();
            break;
        case 53:
            SubMenuListarClientesInactivos();
            break;
        default:
            system("cls");
            printf("Opcion Incorrecta \n");
        }
}

void SubMenuAltaClientes(){
    int opc;
    char apellido[30];
    int numCliente;
    stCliente c;
    color(10);
    system("cls");
    printf("-------------------------------------------- Alta de Clientes --------------------------------------------\n");
    printf("1- Alta de Nuevo Cliente \n");
    printf("2- Alta de Cliente Inactivo \n");
    opc = getch();
    switch (opc){
        case 49:
            CargarArchivoClientes();
            break;
        case 50:
            printf("\n Ingrese apellido a buscar.. \n");
            scanf("%s", apellido);
            do{
                system("cls");
                BuscaClientesInactivosApellido(apellido);
                printf("\n\n Ingrese el numero del cliente a dar de Alta \n");
                scanf("%d", &numCliente);
                if(ExisteNumCliente(numCliente) == 0){
                printf("\n \n El numero de Cliente seleccionado no existe \n");
                system("pause");
                }
            }while(ExisteNumCliente(numCliente) == 0);
            c = BuscaClienteNumCliente(numCliente);
            if (c.id != -1){
                c.baja = 0;
                ModificaRegistro(c);
                printf("El cliente fue dado de Alta con Exito \n");
            } else {
                printf("El cliente no existe \n");
            }
            break;
        default:
            printf("La opcion es Invalida...");
    }
    printf("\n\n\t");
    system("pause");
}

void SubMenuBajaClientes(){
    color(10);
    char apellido[30];
    int numCliente;
    stCliente c;
    system("cls");
    printf("-------------------------------------------- Baja de Clientes --------------------------------------------\n");
    printf("\n Ingrese apellido a buscar.. \n");
    scanf("%s", apellido);
    do{
        system("cls");
        BuscaClientesApellido(apellido);
        printf("\n\n Ingrese el numero del cliente a dar de baja \n");
        scanf("%d", &numCliente);
        if(ExisteNumCliente(numCliente) == 0){
            printf("\n \n El numero de Cliente seleccionado no existe \n");
        }
    }while(ExisteNumCliente(numCliente) == 0);
    c = BuscaClienteNumCliente(numCliente);
    if (c.id != -1){
        c.baja = 1;
        ModificaRegistro(c);
        printf("El cliente fue dado de Baja con Exito \n");
    } else {
        printf("El cliente no existe \n");
    }
    system("pause");
}

void SubMenuModificacionClientes(){
    color(10);
    char apellido[30];
    int numCliente;
    stCliente c;
    system("cls");
    printf("--------- Modificacion de Clientes ---------\n");
    printf("\n Ingrese apellido a buscar.. \n");
    scanf("%s", apellido);
    do{
        system("cls");
        BuscaClientesApellido(apellido);
        printf("\n\n Ingrese el numero del cliente a Modificar \n");
        scanf("%d", &numCliente);
        if(ExisteNumCliente(numCliente) == 0){
            printf("\n \n El numero de Cliente seleccionado no existe \n");
        }
    }while(ExisteNumCliente(numCliente) == 0);
    c = BuscaClienteNumCliente(numCliente);
    system("cls");
    c = ModificacionCliente(c);
    ModificaRegistro(c);
    system("pause");
}

void SubMenuListarClientesActivos(){
    color(10);
    int opc;
    char apellido[30];
    char nombre[30];
    system("cls");
    printf("-------------------------------------- Listado de Clientes Activos --------------------------------------\n");
    printf("\n1- Mostrar Clientes Ordenados por DNI \n");
    printf("\n2- Mostrar Clientes Ordenados por Apellido \n");
    printf("\n3- Buscar Cliente \n");
    opc = getch();
    switch (opc){
        case 49:
            MostrarClientesActivosDNI();
            break;
        case 50:
            MostrarClientesActivosApellido();
            break;
        case 51:
            printf("\n Ingrese Nombre a buscar.. \n");
            scanf("%s", nombre);
            printf("\n Ingrese apellido a buscar.. \n");
            scanf("%s", apellido);
            BuscaCliente(nombre, apellido);
            break;
        default:
            system("cls");
            printf("Opcion Incorrecta \n");
    }
    system("pause");
}

void SubMenuListarClientesInactivos(){
        color(10);
        system("cls");
        printf("--------- Listado de Clientes Inactivos ---------\n");
        printf("\n Ordenados por Mail: \n");
        MostrarClientesInactivos();
        system("pause");
}

void SubMenuConsumos(){
    int opc;
        system("cls");
        color(10);
        printf("-------------------------------------------- Psychonauts Inc --------------------------------------------\n");
        gotoxy(43, 8);
        color(160);
        printf("1- Alta de Consumo\n");
        gotoxy(43, 10);
        color(160);
        printf("2- Baja de Consumo\n");
        gotoxy(39, 12);
        color(160);
        printf("3- Modificacion de Consumo\n");
        gotoxy(43, 14);
        color(160);
        printf("4- Listar Consumos\n");
        opc = getch();
        switch (opc){
            case 49:
                SubMenuAltaConsumo();
                break;
            case 50:
                SubMenuBajaConsumo();
                break;
            case 51:
                SubMenuModificacionConsumo();
                break;
            case 52:
                SubMenuListarConsumo();
                break;
            default:
                system("cls");
                printf("Opcion Incorrecta \n");
            }
}

void SubMenuAltaConsumo(){
        system("cls");
        color(10);
        printf("--------- Alta de Consumos ---------\n");
        CargarArchivoConsumos();
        system("pause");
}

void SubMenuBajaConsumo(){
    color(10);
    stConsumos c;
    char NombreArchivo[] = {"consumos.dat"};
    stConsumos Consumos[CuentaRegistros(NombreArchivo, sizeof(stConsumos))]; // CREAMOS ARREGLO PARA GUARDAR CONSUMOS
    int vConsumo;
    int vFecha;
    int x;
    system("cls");
    printf("--------- Baja de Consumo ---------\n");
    do {
        system("cls");
        printf("Ingrese la Fecha del consumo a Buscar en formato dd/mm/aaaa: ");
        scanf("%d/%d/%d", &c.Fecha.dd, &c.Fecha.mm, &c.Fecha.aaaa);
        vFecha = ValidacionFecha(c.Fecha);
        if (vFecha != 1){
            printf("Fecha invalida, intente nuevamente");
            system("pause");
        }
    }while(vFecha != 1);
    vConsumo = BuscaConsumosFecha(c.Fecha.aaaa, c.Fecha.mm, c.Fecha.dd, Consumos); // GUARDA EN EL ARREGLO LOS CONSUMOS DE LA FECHA CORRESPONDIENTE
    MuestraArregloConsumos(Consumos, vConsumo);
    printf("\nIngrese el numero del consumo a dar de baja: "); // MOSTRAMOS ARREGLO Y EL USUARIO ELIJE QUE CONSUMO QUIERE DAR DE BAJA
    scanf("%d", &x);
    Consumos[x-1].baja = 1; // DAMOS DE BAJA EL CONSUMO
    ModificaRegistroConsumo(Consumos[x-1]); // LO GUARDAMOS EN EL ARCHIVO
    system("pause");
}

void SubMenuModificacionConsumo(){
    color(10);
    stConsumos c;
    char NombreArchivo[] = {"consumos.dat"};
    stConsumos Consumos[CuentaRegistros(NombreArchivo, sizeof(stConsumos))]; // CREAMOS ARREGLO PARA GUARDAR CONSUMOS
    int vConsumo;
    int vFecha;
    int x;
    system("cls");
    printf("--------- Modificacion de Consumo ---------\n");
    do {
        system("cls");
        printf("Ingrese la Fecha del consumo a Buscar en formato dd/mm/aaaa: ");
        scanf("%d/%d/%d", &c.Fecha.dd, &c.Fecha.mm, &c.Fecha.aaaa);
        vFecha = ValidacionFecha(c.Fecha);
        if (vFecha != 1){
            printf("Fecha invalida, intente nuevamente");
            system("pause");
        }
    }while(vFecha != 1);
    vConsumo = BuscaConsumosFecha(c.Fecha.aaaa, c.Fecha.mm, c.Fecha.dd, Consumos); // GUARDA EN EL ARREGLO LOS CONSUMOS DE LA FECHA CORRESPONDIENTE
    MuestraArregloConsumos(Consumos, vConsumo);
    printf("\nIngrese el numero del consumo a Modificar: "); // MOSTRAMOS ARREGLO Y EL USUARIO ELIJE QUE CONSUMO MODIFICAR
    scanf("%d", &x);
    c = ModificacionConsumo(Consumos[x-1]); // MODIFICAMOS EL CONSUMO
    ModificaRegistroConsumo(c); // LO GUARDAMOS EN EL ARCHIVO
    system("pause");
}

void SubMenuListarConsumo(){
    color(10);
    int opc;
    char NombreArchivo[] = {"consumos.dat"};
    stConsumos Consumos[CuentaRegistros(NombreArchivo, sizeof(stConsumos))];
    int vConsumo;
    char apellido[30];
    char nombre[30];
    stCliente cliente;
    system("cls");
    printf("1- Listar Consumos de un Cliente \n");
    printf("2- Estadisticas de Consumo \n");
    opc = getch();
    switch (opc){
        case 49:
            do{
            system("cls");
            printf("\n Ingrese Nombre a buscar.. \n");
            scanf("%s", nombre);
            printf("\n Ingrese apellido a buscar.. \n");
            scanf("%s", apellido);
            cliente = BuscaYRetornaCliente(nombre, apellido);
            if(cliente.id == -1){
                printf("Error el Cliente No Existe\n");
            }
            }while(cliente.id == -1);
            vConsumo = BuscaConsumosId(cliente.id, Consumos);
            OrdenaArregloFecha(Consumos, vConsumo);
            MuestraArregloConsumos(Consumos, vConsumo);
            system("pause");
            break;
        case 50:
            EstadisticasConsumo();
            break;
        default:
            printf("\n\n\tOpcion Incorrecta");
    }
    printf("\n");
    system("pause");
}
