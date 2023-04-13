#ifndef FUNCIONESARRAY_H
#define FUNCIONESARRAY_H

#include <string>
using namespace std;



// Funcion para saber cuantos caracteres tiene el archivo
int countCharacters(string nombreArchivo);

// Funcion para leer nombreArchivoFuente y convertir a ascii binario (8bits) y escribirlo en nombreArchivoDestino
void convertirArchivoBinario(string nombreArchivoFuente, string nombreArchivoDestino, int MAX_TAM); 

// FUncion para leer un archivoFuente y convertirlo a ascii en caracter y escribirlo en nombreArchivDestinos
void convertirArchivoAscii(string nombreArchivoFuente, string nombreArchivoDestino, int MAX_TAM);

// Funcion para recibir en datosTextoBinario lo que se lee
bool leerArchivoTexto(string nombreArchivoFuente, char datosTextoBinario[], int& tamano, int MAX_TAM);

// Funcion que recibe un arreglo para ser codificado datosBinarios y devuelve en datosCodificadosMod (Codifica Metodo 1)
void codificarMetodoUno(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosCodificadosMod);

// Funcion que recibe un arreglo para ser codificado datosBinarios y devuelve en datosCodificadosMod (Codifico Metodo 2)
void codificarMetodoDos(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosCodificadosMod);

// Funcion para escribir un arreglo 
void escribirArchivoTexto(const string &nombreArchivo, char *arreglo, int MAX_TAM);

// Funcion que recibe un arreglo para ser DeCodificado datosBinarios y devuelve en datosDeCodificadosMod (Metodo 1)
void DeCodificarMetodoUno(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosDecoCodificadosMod);

// Funcion que recibe un arreglo para ser DeCodificado datosBinarios y devuelve en datosDeCodificadosMod (Metodo 2)
void DeCodificarMetodoDos(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosDecoCodificadosMod);


#endif