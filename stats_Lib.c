#include <stdio.h>
#include <stdlib.h>
#include "stats_Lib.h"
#include "consumos_Lib.h"
#include "archivo_Consumos_Lib.h"
#include <conio.h>
#include <string.h>

#define arConsumo "consumos.dat"
#define ESC 27

void EstadisticasConsumo(){
    int anio;
    int Consumos[12] = {0};
    do{
        system("cls");
        printf("Ingrese El a%co a Buscar en formato aaaa: ", 164);
        scanf("%d", &anio);
        if(anio < 2000 || anio > 2020){
            printf("\nError fecha Invalida...");
        }
    }while(anio < 2000 || anio > 2020);
    EstadisticaCargaArreglo(Consumos, anio);
    EstadisticaMuestraConsumos(Consumos);
    printf("\n");
    system("pause");
    Estadisticas(Consumos);
}

void EstadisticaCargaArreglo(int C[], int anio){
    stConsumos c;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if (pArConsumo){
        while (fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0) {
            if(anio == c.Fecha.aaaa){
                C[(c.Fecha.mm) - 1] = C[(c.Fecha.mm) - 1] + c.datosConsumidos;
            }
        }
        fclose(pArConsumo);
    }
}

void EstadisticaMuestraConsumos(int C[]){
    int i = 0;
    while(i<12){
        printf("\n---------------------------------");
        printf("\nMes: %d", i+1);
        printf("\nDatos consumidos: %d MBs", C[i]);
        printf("\n---------------------------------");
        i++;
    }
}

void Estadisticas(int C[]){
    int menor;
    int i = 0;
    int c = 0;
    menor = i;
    while(i<12){
        if(C[menor] > C[i]){
            menor = i;
        }
        c = c + C[i];
        i++;
    }
    printf("\n\n");
    printf("El consumo Anual es de: %d MBs \n", c);
    printf("El mes con menos consumos es el mes: %d\n", menor+1);
    printf("El promedio de Consumo Mensual es: %.2f", (float)c / 12);
}
