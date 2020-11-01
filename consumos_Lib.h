#ifndef CONSUMOS_LIB_H_INCLUDED
#define CONSUMOS_LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int aaaa;
    int mm;
    int dd;
} stFecha;

typedef struct{
    int id;
    int idCliente;
    stFecha Fecha;
    int datosConsumidos;
    int baja;
} stConsumos;

stConsumos CargaConsumo(int idCliente);
int AnioBiciesto(int anio);
int ValidacionFecha(stFecha Fecha);
void MuestraConsumo(stConsumos c);
void OrdenaArregloFecha(stConsumos c[], int v);
int ComparaFecha(stFecha F1, stFecha F2);
stConsumos ModificacionConsumo(stConsumos c);

#endif // CONSUMOS_LIB_H_INCLUDED
