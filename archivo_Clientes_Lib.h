#ifndef ARCHIVO_CLIENTES_LIB_H_INCLUDED
#define ARCHIVO_CLIENTES_LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "cliente_Lib.h"

void GuardaCliente(stCliente c);
void CargarArchivoClientes();
void MuestraArchivoClientes();
int BuscaUltimoId();
int ExisteCliente (int dni);
int ExisteNumCliente (int numCliente);
void BuscaClientesApellido(char apellido[]);
void BuscaClientesInactivosApellido(char apellido[]);
stCliente BuscaClienteNumCliente(int numCliente);
int BuscaPosicion(int id);
void ModificaRegistro(stCliente);
int CuentaRegistros (char NombreArchivo[], int dato);
void MuestraArregloClientes(stCliente c[], int v);
void OrdenarInsercionEmail(stCliente C[], int v);
void MostrarClientesInactivos();
int buscaPosMenorDNI(stCliente C[], int v, int c);
void OrdenarSeleccionDNI (stCliente C[], int v);
void MostrarClientesActivosDNI();
void OrdenarInsercionApellido(stCliente C[], int v);
void MostrarClientesActivosApellido();
void BuscaCliente(char nombre[], char apellido[]);
stCliente BuscaYRetornaCliente(char nombre[], char apellido[]);

#endif // ARCHIVO_CLIENTES_LIB_H_INCLUDED
