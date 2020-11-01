#include <stdio.h>
#include <stdlib.h>
#include "menu_Lib.h"
#include "cliente_Lib.h"
#include "consumos_Lib.h"
#include "carga_Random_Lib.h"
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

int main()
{
    color(10);
    gotoxy(50, 13);
    printf("Cargando Datos..");
    CargarArchivoClientesRandom();
    CargarArchivoConsumosRandom();
    MenuPrincipal();
    return 0;
}
