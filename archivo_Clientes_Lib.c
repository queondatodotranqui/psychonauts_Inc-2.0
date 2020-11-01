#include <stdio.h>
#include <stdlib.h>
#include "archivo_Clientes_Lib.h"
#include "cliente_Lib.h"
#include <conio.h>
#include <string.h>

#define arCliente "clientes.dat"
#define ESC 27

void GuardaCliente(stCliente c){
    // RECIBE EL CLIENTE POR PARAMETRO Y LO GUARDA EN EL ARCHIVO
    FILE *pArCliente = fopen(arCliente, "ab");
    if(pArCliente){
        fwrite(&c, sizeof(stCliente), 1, pArCliente);
        fclose(pArCliente);
    }
}

void CargarArchivoClientes(){
    char opc;

    do{
        system("cls");
        GuardaCliente(CargaCliente()); // CARGA CLIENTE Y LO GUARDA EN ARCHIVO
        printf("Desea seguir Cargando Clientes? ENTER para continuar o ESC para salir");
        opc = getche();
    } while (opc != ESC);
}

void MuestraArchivoClientes(){
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while (fread(&c, sizeof(stCliente), 1, pArCliente) > 0){ // LEE EL CLIENTE Y LO ENVIA A LA FUNCION MOSTRAR
            MuestraCliente(c);
        }
        fclose(pArCliente);
    }
}

int BuscaUltimoId(){
    stCliente c;
    int id = -1; // SI EL ARCHIVO ESTA VACIO EL PRIMER ID SERA 0
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        fseek(pArCliente,sizeof(stCliente)*(-1), SEEK_END); // SE PARA AL FINAL DEL ARCHIVO Y SE MUEVE UN DATO HACIA ATRAS
        if (fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            id = c.id;
        }
        fclose(pArCliente);
    }
    return id; // SE RETORNA ID Y NO C.ID POR QUE SI EL ARCHIVO ESTA VACIO RETORNARIA BASURA
}

int ExisteCliente (int dni){
    stCliente c;
    int flag = 0;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(dni == c.dni){
                flag = 1;
            }
        }
        fclose(pArCliente);
    }
    return flag; // SI EL DNI ENVIADO POR PARAMETRO LO ENCUENTRA EN ALGUN CLIENTE YA CARGADO RETORNA 1
}

int ExisteNumCliente (int numCliente){
    stCliente c;
    int flag = 0;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(numCliente == c.numCliente){
                flag = 1;
            }
        }
        fclose(pArCliente);
    }
    return flag; // SI EL NUMERO DE CLIENTE ENVIADO POR PARAMETRO LO ENCUENTRA EN ALGUN CLIENTE YA CARGADO RETORNA 1
}

void BuscaClientesApellido(char apellido[]){
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(strcmp(apellido, c.apellido) == 0 && c.baja == 0){
                MuestraCliente(c); // SI EL APELLIDO ES IGUAL MUESTRA EL CLIENTE EN PANTALLA, MOSTRANDO ASI UN LISTADO DE TODOS LOS CLIENTES CON ESE APELLIDO
            }
        }
        fclose(pArCliente);
    }
}

void BuscaClientesInactivosApellido(char apellido[]){
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(strcmp(apellido, c.apellido) == 0 && c.baja == 1){
                MuestraCliente(c); // SI EL APELLIDO ES IGUAL MUESTRA EL CLIENTE EN PANTALLA, MOSTRANDO ASI UN LISTADO DE TODOS LOS CLIENTES CON ESE APELLIDO
            }
        }
        fclose(pArCliente);
    }
}

stCliente BuscaClienteNumCliente(int numCliente){
    stCliente c;
    int flag = 0;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(numCliente == c.numCliente){ // SI ENCUENTRA EL NUMERO DE CLIENTE CAMBIA FLAG Y RETORNA EL CLIENTE
                flag = 1;
            }
        }
        fclose(pArCliente);
    }
    if(flag == 0){ // SI NO ENCUENTRA EL NUMERO DE CLIENTE, VA A RETORNAR UN CLIENTE VACIO
        c.id = -1;
    }

    return c;
}

int BuscaPosicion(int id){
    int pos = -1; // INICIA EN ESTA POSICION POR SI EL ARCHIVO ESTA VACIO
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(pos == -1 && fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(c.id == id){
                pos = ftell(pArCliente)/sizeof(stCliente)-1; // DIVIDE EL PESO DEL ARCHIVO HASTA DONDE ESTA EL CURSOR POR EL TAÑANO DEL CLIENTE
            }
        }
        fclose(pArCliente);
    }
    return pos;
}

void ModificaRegistro(stCliente c){
    int pos = 0;
    pos = BuscaPosicion(c.id);
    FILE *pArCliente = fopen(arCliente, "r+b");
    if(pArCliente){
        fseek(pArCliente, sizeof(stCliente)*pos, SEEK_SET); // TE MOVES LA CANTIDAD DE CLIENTES QUE RESULTA DE LA MULTIPLICACION
        fwrite(&c, sizeof(stCliente), 1, pArCliente); // SOBRESCRIBE EL CLIENTE
        fclose(pArCliente);
    }
}

int CuentaRegistros (char NombreArchivo[], int dato){
    int total = 0;
    FILE *pAr = fopen(NombreArchivo, "rb"); // DE ESTA FORMA SIRVE PARA CUALQUIER TIPO DE ARCHIVO
    if(pAr){
        fseek(pAr, 0, SEEK_END); // TE PARAS AL FINAL DEL ARCHIVO
        total = ftell(pAr)/dato; // DIVIDE EL TOTAL DEL ARCHIVO POR EL TAMAÑO DEL DATO
        fclose(pAr);
    }
    return total;
}

void MuestraArregloClientes(stCliente c[], int v){
    int i = 0;
    while(i<v){
        MuestraCliente(c[i]);
        printf("\n");
        i++;
    }
}

void OrdenarInsercionEmail(stCliente C[], int v){
    int i = 1;
    int i2 = 1;
    stCliente aux;
    while(i2<v){
        while(i>0 && strcmp(C[i].email , C[i-1].email) != 1){
            aux = C[i-1];
            C[i-1] = C[i];
            C[i] = aux;
            i--;
        }
        i2++;
        i = i2;
    }
}

void MostrarClientesInactivos(){
    int dim = CuentaRegistros(arCliente, sizeof(stCliente));
    stCliente C[dim];
    int i = 0;
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while (fread(&c, sizeof(stCliente), 1, pArCliente) > 0 && i<dim){ // GUARDA LOS CLIENTES CON BAJA = 1 EN EL ARREGLO
            if (c.baja == 1){
                C[i] = c;
                i++;
            }
        }
        fclose(pArCliente);
    }
    OrdenarInsercionEmail(C, i); // ORDENA EL ARREGLO POR EMAIL
    MuestraArregloClientes(C, i); // MUESTRA EL ARREGLO  DE CLIENTES ORDENADO
}

int buscaPosMenorDNI(stCliente C[], int v, int c){
    int i = c;
    int posMenor = i;
    i++;
    while(i<v){
        if(C[i].dni<C[posMenor].dni){
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void OrdenarSeleccionDNI (stCliente C[], int v){
    int posMenor = 0;
    stCliente aux;
    for(int i=0;i<v-1;i++){
        posMenor = buscaPosMenorDNI(C,v,i);
        aux = C[posMenor];
        C[posMenor] = C[i];
        C[i] = aux;
    }
}

void MostrarClientesActivosDNI(){
    int dim = CuentaRegistros(arCliente, sizeof(stCliente));
    stCliente C[dim];
    int i = 0;
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(fread(&c, sizeof(stCliente), 1, pArCliente) > 0 && i<dim){
            if(c.baja == 0){ // CARGA ARREGLO CON CLIENTES ACTIVOS
                C[i] = c;
                i++;
            }
        }
        fclose(pArCliente);
    }
    OrdenarSeleccionDNI(C,i);
    MuestraArregloClientes(C, i);
}

void OrdenarInsercionApellido(stCliente C[], int v){
    int i = 1;
    int i2 = 1;
    stCliente aux;
    while(i2<v){
        while(i>0 && strcmp(C[i].apellido , C[i-1].apellido) == -1){
            aux = C[i-1];
            C[i-1] = C[i];
            C[i] = aux;
            i--;
        }
        i2++;
        i = i2;
    }
}

void MostrarClientesActivosApellido(){
    int dim = CuentaRegistros(arCliente, sizeof(stCliente));
    stCliente C[dim];
    int i = 0;
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(fread(&c, sizeof(stCliente), 1, pArCliente) > 0 && i<dim){
            if(c.baja == 0){ // CARGA ARREGLO CON CLIENTES ACTIVOS
                C[i] = c;
                i++;
            }
        }
        fclose(pArCliente);
    }
    OrdenarInsercionApellido(C, i);
    MuestraArregloClientes(C, i);
}

void BuscaCliente(char nombre[], char apellido[]){
    stCliente c;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(strcmp(apellido, c.apellido) == 0 && strcmp(nombre, c.nombre) == 0){
                MuestraCliente(c); // SI EL APELLIDO Y EL NOMBRE COINCIDEN CON LOS INGRESADOS POR EL USUARIO MUESTRA EL CLIENTE
            }
        }
        fclose(pArCliente);
    }
}

stCliente BuscaYRetornaCliente(char nombre[], char apellido[]){
    stCliente c;
    int flag = 0;
    FILE *pArCliente = fopen(arCliente, "rb");
    if(pArCliente){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArCliente) > 0){
            if(strcmp(apellido, c.apellido) == 0 && strcmp(nombre, c.nombre) == 0){
                flag = 1; // SI EL APELLIDO Y EL NOMBRE COINCIDEN CON LOS INGRESADOS POR EL USUARIO EL CICLO PARA
            }
        }
        fclose(pArCliente);
    }
    if(flag == 0){
        c.id = -1;
    }
    return c;
}
