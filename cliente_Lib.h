#ifndef CLIENTE_LIB_H_INCLUDED
#define CLIENTE_LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    int numCliente;
    char nombre[30];
    char apellido[30];
    int dni;
    char email[30];
    char domicilio[30];
    int movilPre;
    int movilSu;
    int baja;
} stCliente;

stCliente CargaCliente();
int ValidacionEmail (char email[]);
void MuestraCliente(stCliente c);
stCliente ModificacionCliente(stCliente c);

#endif // CLIENTE_LIB_H_INCLUDED
