#ifndef CARGA_RANDOM_LIB_H_INCLUDED
#define CARGA_RANDOM_LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "consumos_Lib.h"

int randomRango(int min, int max);
int NumClienteRandom();
void NombreRandom(char n[]);
void ApellidoRandom(char a[]);
int DniRandom();
void CalleRadom(char c[]);
int NroCalleRandom();
void CargarArchivoClientesRandom();
stConsumos CargaConsumoRandom();
void CargarArchivoConsumosRandom();

#endif // CARGA_RANDOM_LIB_H_INCLUDED
