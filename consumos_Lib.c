#include <stdio.h>
#include <stdlib.h>
#include "consumos_Lib.h"
#include "archivo_Consumos_Lib.h"
#include <conio.h>
#include <string.h>

#define ESC 27
#define AnioMax 2020
#define AnioMin 2000

stConsumos CargaConsumo(int idCliente){
    stConsumos c;
    int vFecha;

    // id consumo auto incremental

    c.id = BuscaUltimoIdConsumo() + 1;

    // id cliente

    c.idCliente = idCliente;

    // FECHA

    do {
        system("cls");
        printf("Ingrese la Fecha del consumo en formato dd/mm/aaaa: ");
        scanf("%d/%d/%d", &c.Fecha.dd, &c.Fecha.mm, &c.Fecha.aaaa);
        vFecha = ValidacionFecha(c.Fecha);
        if (vFecha != 1){
            printf("Fecha invalida, intente nuevamente");
            system("pause");
        }
    }while(vFecha != 1);

    // DATOS CONSUMIDOS

    system("cls");
    printf("Ingrese el Consumo: ");
    scanf("%d", &c.datosConsumidos);

    // BAJA

    c.baja = 0; // SIEMPRE LO CARGAMOS ACTIVO

    return c;
}

int AnioBiciesto(int anio){
    return (((anio % 4 == 0) && (anio % 100 != 0)) || (anio % 400 == 0)); // LA FUNCION RETORNA 1 SI EL AÑO ES BICIESTO
}

int ValidacionFecha(stFecha Fecha){
    // RETORNA 0 SI LA FECHA ES INVALIDA O 1 SI ES VALIDA
    // VERIFICA RANGO DE AÑO, MES Y DIA
    if (Fecha.aaaa > AnioMax || Fecha.aaaa < AnioMin) {
        return 0;
    }
    if (Fecha.mm < 1 || Fecha.mm > 12){
        return 0;
    }
    if (Fecha.dd < 1 || Fecha.dd > 31){
        return 0;
    }
    // PARA FEBRERO
    if (Fecha.mm == 2){
        if (AnioBiciesto(Fecha.aaaa)){
            return (Fecha.dd <= 29);
        } else {
            return (Fecha.dd <= 28);
        }
    }
    // MESES CON 30 DIAS
    if (Fecha.mm == 4 || Fecha.mm == 6 || Fecha.mm == 9 || Fecha.mm == 11){
        return (Fecha.dd <= 30);
    }
    return 1;
}

void MuestraConsumo(stConsumos c){
    printf("------------------------------------- \n");
    printf("Fecha: %d/%d/%d \n", c.Fecha.dd, c.Fecha.mm, c.Fecha.aaaa);
    printf("Datos Consumidos: %d \n", c.datosConsumidos);
    printf("------------------------------------- \n");
}

void OrdenaArregloFecha(stConsumos c[], int v){
    int i = 0;
    int x = 0;
    int menorPos = i;
    stConsumos Aux;
    i++;
    while (x < v - 1){
        while (i < v){
            if (ComparaFecha(c[menorPos].Fecha, c[i].Fecha) == 2){
                menorPos = i;
            }
            i++;
        }
        Aux = c[x];
        c[x] = c[menorPos];
        c[menorPos] = Aux;
        x++;
        i = x + 1;
        menorPos = i;
    }
}

int ComparaFecha(stFecha F1, stFecha F2){
    if(F1.aaaa == F2.aaaa){
        if(F1.mm == F2.mm){
            if(F1.dd > F2.dd){
                return 2;
            } else {
                return 1;
            }
        } else {
            if(F1.mm > F2.mm){
                return 2;
            } else {
                return 1;
            }
        }
    } else {
        if(F1.aaaa > F2.aaaa) {
            return 2;
        } else {
            return 1;
        }
    }
}

stConsumos ModificacionConsumo(stConsumos c){
    int opc;
    int opc2;
    int vFecha;
    do{
        printf("Ingrese la opcion segun que desea Modificar: \n");
        printf("1- Fecha \n");
        printf("2- Datos Consumidos \n");
        opc = getch();
        switch(opc){
            case 49:
                system("cls");
                printf("Ingrese la Nueva fecha del consumo: \n");
                do {
                    system("cls");
                    printf("Ingrese la Fecha del consumo en formato dd/mm/aaaa: ");
                    scanf("%d/%d/%d", &c.Fecha.dd, &c.Fecha.mm, &c.Fecha.aaaa);
                    vFecha = ValidacionFecha(c.Fecha);
                    if (vFecha != 1){
                        printf("Fecha invalida, intente nuevamente");
                        system("pause");
                    }
                }while(vFecha != 1);
                break;
            case 50:
                system("cls");
                printf("Ingrese el Consumo: ");
                scanf("%d", &c.datosConsumidos);
                break;
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
