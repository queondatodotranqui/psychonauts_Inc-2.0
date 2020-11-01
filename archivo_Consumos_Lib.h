#ifndef ARCHIVO_CONSUMOS_LIB_H_INCLUDED
#define ARCHIVO_CONSUMOS_LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "consumos_Lib.h"

int BuscaUltimoIdConsumo();
void GuardaConsumo(stConsumos c);
void CargarArchivoConsumos();
void ModificaRegistroConsumo(stConsumos c);
int BuscaPosicionConsumo(int id);
int ExisteConsumoRetornaDatos (int id, int anio, int mes, int dia);
int BuscaConsumosFecha(int anio, int mes, int dia, stConsumos C[]);
void MuestraArregloConsumos(stConsumos c[], int v);
int BuscaConsumosId(int id, stConsumos C[]);
int ExisteConsumoRetornaID (int id, int anio, int mes, int dia);

#endif // ARCHIVO_CONSUMOS_LIB_H_INCLUDED
