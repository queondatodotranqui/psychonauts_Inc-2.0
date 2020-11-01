#include <stdio.h>
#include <stdlib.h>
#include "consumos_Lib.h"
#include "cliente_Lib.h"
#include "archivo_Consumos_Lib.h"
#include "archivo_Clientes_Lib.h"
#include <conio.h>
#include <string.h>

#define arConsumo "consumos.dat"
#define ESC 27
#define AnioMax 2020
#define AnioMin 2000

int BuscaUltimoIdConsumo(){
    stConsumos c;
    int id = -1;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if(pArConsumo){
        fseek(pArConsumo, sizeof(stConsumos)*(-1), SEEK_END);
        if (fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0){
            id = c.id;
        }
        fclose(pArConsumo);
    }
    return id;
}


void GuardaConsumo(stConsumos c){
    int datosC = ExisteConsumoRetornaDatos(c.idCliente, c.Fecha.aaaa, c.Fecha.mm, c.Fecha.dd); // SI EL CLIENTE YA TIENE CONSUMOS EN EL DIA LOS SUMA A LOS EXISTENTES
    if (datosC != 0){
        c.datosConsumidos = c.datosConsumidos + datosC;
        c.id = ExisteConsumoRetornaID(c.idCliente, c.Fecha.aaaa, c.Fecha.mm, c.Fecha.dd);
        ModificaRegistroConsumo(c);
    } else{
        FILE *pArConsumo = fopen(arConsumo, "ab"); // SINO LOS CREA
        if(pArConsumo){
            fwrite(&c, sizeof(stConsumos), 1, pArConsumo);
            fclose(pArConsumo);
        }
    }
}

void CargarArchivoConsumos(){
    char opc;
    char apellido[30];
    char nombre[30];
    stCliente cliente;
    do{
        system("cls");
        do{
            printf("\n Ingrese Nombre a buscar.. \n");
            scanf("%s", nombre);
            printf("\n Ingrese apellido a buscar.. \n");
            scanf("%s", apellido);
            cliente = BuscaYRetornaCliente(nombre, apellido);
            if(cliente.id == -1){
                printf("Error el Cliente no Existe \n");
            }
        }while(cliente.id == -1);
        GuardaConsumo(CargaConsumo(cliente.id)); // CARGA CONSUMO Y LO GUARDA EN ARCHIVO
        printf("Desea seguir Cargando Consumos? ENTER para continuar o ESC para salir");
        opc = getche();
    } while (opc != ESC);
}

void ModificaRegistroConsumo(stConsumos c){
    int pos = 0;
    pos = BuscaPosicionConsumo(c.id);
    FILE *pArConsumo = fopen(arConsumo, "r+b");
    if(pArConsumo){
        fseek(pArConsumo, sizeof(stConsumos)*pos, SEEK_SET); // TE MOVES LA CANTIDAD DE CLIENTES QUE RESULTA DE LA MULTIPLICACION
        fwrite(&c, sizeof(stConsumos), 1, pArConsumo); // SOBRESCRIBE EL CLIENTE
        fclose(pArConsumo);
    }
}

int BuscaPosicionConsumo(int id){
    int pos = -1; // INICIA EN ESTA POSICION POR SI EL ARCHIVO ESTA VACIO
    stConsumos c;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if(pArConsumo){
        while(pos == -1 && fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0){
            if(c.id == id){
                pos = ftell(pArConsumo)/sizeof(stConsumos)-1; // DIVIDE EL PESO DEL ARCHIVO HASTA DONDE ESTA EL CURSOR POR EL TAÑANO DEL CLIENTE
            }
        }
        fclose(pArConsumo);
    }
    return pos;
}

int ExisteConsumoRetornaDatos (int id, int anio, int mes, int dia){
    stConsumos c;
    int flag = 0;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if(pArConsumo){
        while(flag == 0 && fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0){
            if(id == c.idCliente && anio == c.Fecha.aaaa && mes == c.Fecha.mm && dia == c.Fecha.dd){
                flag = 1;
            }
        }
        fclose(pArConsumo);
    }
    if (flag == 0){
        return 0;
    }
    return c.datosConsumidos; // SI EL ID ENVIADO POR PARAMETRO LO ENCUENTRA EN ALGUN CONSUMO YA CARGADO RETORNA LOS DATOS CONSUMIDOS
}

int BuscaConsumosFecha(int anio, int mes, int dia, stConsumos C[]){
    int i = 0;
    stConsumos c;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if (pArConsumo){
        while (fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0) {
            if(c.Fecha.aaaa == anio && c.Fecha.mm == mes && c.Fecha.dd == dia && c.baja == 0){
                C[i] = c;
                i++;
            }
        }
        fclose(pArConsumo);
    }
    return i;
}

void MuestraArregloConsumos(stConsumos c[], int v){
    int i = 0;
    while(i<v){
        printf("%d- \n", i+1);
        MuestraConsumo(c[i]);
        printf("\n");
        i++;
    }
}

int BuscaConsumosId(int id, stConsumos C[]){
    int i = 0;
    stConsumos c;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if (pArConsumo){
        while (fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0) {
            if(c.idCliente == id){
                C[i] = c;
                i++;
            }
        }
        fclose(pArConsumo);
    }
    return i;
}

int ExisteConsumoRetornaID (int id, int anio, int mes, int dia){
    stConsumos c;
    int flag = 0;
    FILE *pArConsumo = fopen(arConsumo, "rb");
    if(pArConsumo){
        while(flag == 0 && fread(&c, sizeof(stConsumos), 1, pArConsumo) > 0){
            if(id == c.idCliente && anio == c.Fecha.aaaa && mes == c.Fecha.mm && dia == c.Fecha.dd){
                flag = 1;
            }
        }
        fclose(pArConsumo);
    }
    if (flag == 0){
        return 0;
    }
    return c.id; // SI EL ID ENVIADO POR PARAMETRO LO ENCUENTRA EN ALGUN CONSUMO YA CARGADO RETORNA LA ID
}
