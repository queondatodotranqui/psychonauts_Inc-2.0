#include <stdio.h>
#include <stdlib.h>
#include "carga_Random_Lib.h"
#include "cliente_Lib.h"
#include "consumos_Lib.h"
#include "archivo_Clientes_Lib.h"
#include "archivo_Consumos_Lib.h"
#include <conio.h>
#include <string.h>

#define ESC 27
#define arCliente "clientes.dat"
#define arConsumo "consumos.dat"
#define AnioMax 2020
#define AnioMin 2000

int randomRango(int min, int max){
    return rand()%(max-min)+min;
}

int NumClienteRandom(){
    return randomRango(1,9999);
}

void NombreRandom(char n[]){
    char nombres[][30] = {"Amadeo","Alberto","Cristiano","Ana","Enzo","Anibal","Eric","Jose",
                           "Eva","Arturo","Hugo","Ivan","Lara","Pedro","iara","Luz",
                           "Raul","Sara","Hector","Zeus","Ulises","Nahuel","Mariana"};

    strcpy(n,nombres[randomRango(0,sizeof(nombres)/(sizeof(char)*30))]);
}

void ApellidoRandom(char a[]){
    char apellidos[][30] = {"Asenjo","Bottoni","Brizuela","Brondino","Busto","Carrillo", "Castillon", "Cosi", "Depetris", "Esposito",
                            "Fleita", "Franco", "Gioda", "Gomez", "Minondi", "Gonzalez", "La Mastra", "Lettieri", "Lopez", "Lorenzo",
                            "Maldonado", "Martinez", "Mater", "Melo", "Juarez", "Miceli", "Minaglia", "Monteagudo", "Rossi", "Orfano",
                            "Palmieri","Quintulen","Rehak","Sanchez","Silva","Soto","Tapia","Trovento","Valdez","Vazquez","Vivas"};

    strcpy(a,apellidos[randomRango(0,sizeof(apellidos)/(sizeof(char)*30))]);
}

int DniRandom(){
    return randomRango(630,1987)* randomRango(531,19903);
}

void CalleRadom(char c[]){
    char calles[][30] = {"Guemes","Olavarria","Alsina","Sarmiento","Las Heras","Laprida", "Tucuman", "Buenos Aires", "Entre rios", "Corrientes",
                            "Santa Fe", "11 de Septiembre", "Santiago del estero", "Balcarce", "Cordoba", "Mendoza", "Italia", "Salta", "Jujuy", "Brown",
                            "Bolivar", "Alberti", "Castelli", "La Rioja", "Maipu", "Salta", "Chacabuco", "Francia", "La Pampa", "Dorrego",
                            "Paunero","Viamonte","Santa Cruz","Strobel","Estrada","Formosa","La Rioja","Chubut","Rejon","Larrea","Vieytes"};

    strcpy(c,calles[randomRango(0,sizeof(calles)/(sizeof(char)*30))]);
}

int NroCalleRandom(){
    return randomRango(0,9999);
}

stCliente ClienteRandom(){
    stCliente c;

    // id cliente

    c.id = BuscaUltimoId() + 1;

    // numero de cliente

    c.numCliente = NumClienteRandom();

    // Nombre

    NombreRandom(c.nombre);

    // Apellido

    ApellidoRandom(c.apellido);

    // dni

    c.dni = DniRandom();

    // email

    strcpy(c.email,c.nombre);
    strcat(c.email,".");
    strcat(c.email,c.apellido);
    strcat(c.email,"@gmail.com");

    // calle

    CalleRadom(c.domicilio);
    char nro[5];
    strcat(c.domicilio," ");
    strcat(c.domicilio, itoa(NroCalleRandom(),nro,10));

    // telefono

    c.movilPre = 223;
    c.movilSu = rand()%8999999+1000000;

    // baja

    c.baja=0;
    return c;
}

void CargarArchivoClientesRandom(){
    int i = 0;
    while(i<100){
        GuardaCliente(ClienteRandom()); // CARGAR CLIENTE RANDOM EN EL ARCHIVO
        i++;
    }
}

stConsumos CargaConsumoRandom(){
    stConsumos c;

    // id

    c.id = BuscaUltimoIdConsumo() + 1;

    // idcliente

    c.idCliente = randomRango(0, CuentaRegistros(arCliente, sizeof(stCliente)));

    // Fecha

    do{
        c.Fecha.aaaa = randomRango(2000,2021);
        c.Fecha.mm = randomRango(1,13);
        c.Fecha.dd = randomRango(1,32);
    }while(ValidacionFecha(c.Fecha) != 1);


    // datos

    c.datosConsumidos = randomRango(1, 2049);

    //baja
    c.baja = 0;

    return c;
}

void CargarArchivoConsumosRandom(){
    int i = 0;
    while(i<2500){
        GuardaConsumo(CargaConsumoRandom());
        i++;
    }
}
