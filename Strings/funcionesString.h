#ifndef FUNCIONESSTRING_H
#define FUNCIONESSTRING_H
#include <string>
using namespace std;


void convertirArchivoBinario(string nombreArchivoFuente, string nombreArchivoDestino);

bool leerArchivoTexto(string nombreArchivoFuente, string &datosTextoBinario);

void codificarMetodoUno(const string &datosBinarios,  unsigned int n, string &datosCodificadosMod);

void codificarMetodoDos(const string &datosBinarios,  unsigned int n, string &datosCodificadosMod);

void DeCodificarMetodoUno(const string &datosBinariosCodif, const unsigned int n, string &datosDeCodificadosMod);

void DeCodificarMetodoDos(const string &datosBinariosCodif, const unsigned int n, string &datosDeCodificadosMod);

void escribirArchivoTexto(const string &nombreArchivoSalida, const string &textoEscribir);

void convertirArchivoAscii(const string &nombreArchivoFuente, const string &nombreArchivoDestino);


#endif