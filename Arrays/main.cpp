#include <iostream>
#include <fstream>
#include <bitset>
#include "funcionesArray.h"
#include "funcionesArray.cpp"

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


int main()
{

    cout << endl;
    cout << " +-----------------------------+" << endl;
    cout << " +        Menu principal       +" << endl;
    cout << " +-----------------------------+" << endl;
    cout << " + 1. Codificar archivos       +" << endl;
    cout << " + 2. Decodificar archivos     +" << endl;
    cout << " + 0. Para salir               +" << endl;
    cout << " +-----------------------------+" << endl;
    cout << endl;
    cout << " -> Seleccione una opcion: ";

    int seleccionOperacion; // Seleccionar codificacion o decodificacion
    cin >> seleccionOperacion;


    if (seleccionOperacion == 1) { // Se elige la operacion codificacion 

    
        // Datos ingresados por el Usuario
        cout << endl;
        string ArchivoFuente;
        cout << " -> Nombre del archivo a codificar : ";
        cin >> ArchivoFuente;


        string ArchivoSalidaCodificado;
        cout << " -> Nombre del archivo en el que se guarda la codificacion: ";
        cin >> ArchivoSalidaCodificado;
        cout << endl;


        // cuantas letras tiene el archivo de entrada 
        const int TAM_LET = countCharacters(ArchivoFuente);  
        const int MAX_TAM = TAM_LET*8;

        // escribir en "archivoBinario.txt" el ascii correspondiente binario de 8 bits de "archivoCaracteres.txt"
        convertirArchivoBinario(ArchivoFuente,"00-auxBinario.txt", MAX_TAM); 

        int tamano;
        char datosBinarios[MAX_TAM];

        cout << " +-----------------------------+" << endl;
        cout << " +    Metodo de codificacion   +" << endl;
        cout << " +-----------------------------+" << endl;
        cout << " + 1. Primer Metodo            +" << endl;
        cout << " + 2. Segundo Metodo           +" << endl;
        cout << " +-----------------------------+" << endl;
        cout << endl;
        int selecMetodoCod;
        cout << " -> Seleccione una opcion: ";
        cin >> selecMetodoCod;

        int semillaCodificacion;
        cout << " -> Escriba la semilla de codificacion: ";
        cin >> semillaCodificacion;

        if (leerArchivoTexto("00-auxBinario.txt", datosBinarios, tamano, MAX_TAM)) {

            cout << "Lectura archivo binario..." << endl;
            cout << "Informacion en binario: ";
            for (int i = 0; i < tamano; i++) {
                cout << datosBinarios[i];
            }
            cout << endl;

            char *datosCodificadosMod = nullptr;
            // el arreglo codificado está en datosCodificadosMod

            if (selecMetodoCod == 1) {
                cout << "Metodo de Codificacion Uno... " << endl;
                codificarMetodoUno(datosBinarios, MAX_TAM, semillaCodificacion, datosCodificadosMod);
                // escrbir sobre archivoBinarioCodif sobre el archivo de salida codificado (ArchivoSalidaCodificado)
                escribirArchivoTexto(ArchivoSalidaCodificado, datosCodificadosMod, MAX_TAM);
                delete[] datosCodificadosMod;
            }
            else if (selecMetodoCod == 2) {
                cout << "Metodo de Codificacion Dos... " << endl;
                codificarMetodoDos(datosBinarios, MAX_TAM, semillaCodificacion, datosCodificadosMod);
                // escrbir sobre archivoBinarioCodif sobre el archivo de salida codificado (ArchivoSalidaCodificado)
                escribirArchivoTexto(ArchivoSalidaCodificado, datosCodificadosMod, MAX_TAM);
                delete[] datosCodificadosMod;
            }
            else {
                cout << "Metodo de Codificacion Invalido " << endl;
            }

        }
    }


    else if (seleccionOperacion == 2) { // Se elige la operacion decodificar 


        string ArchivoFuenteCodificado;
        cout << " -> Nombre del archivo a decodificar: ";
        cin >> ArchivoFuenteCodificado;

        string ArchivoSalidaDeCodificado;
        cout << " -> Nombre del archivo a decodificar: ";
        cin >> ArchivoSalidaDeCodificado;

        cout << endl;
        cout << " +------------------------------------------+" << endl;
        cout << " + Metodo con el que se codifco el archivo  +" << endl;
        cout << " +------------------------------------------+" << endl;
        cout << " + 1. Primer Metodo                         +" << endl;
        cout << " + 2. Segundo Metodo                        +" << endl;
        cout << " +------------------------------------------+" << endl;
        cout << endl;

        int selecMetodoDeCod;
        cout << " -> Seleccione el metodo: ";
        cin >> selecMetodoDeCod;


        // Datos a ingresar por el usuario 
        cout << " -> Escriba la semilla con la que se codifico el archivo: ";
        int semillaCodificacion;
        cin >> semillaCodificacion;

        // cuantas letras tiene el archivo de entrada 
        const int TAM_LET = countCharacters(ArchivoFuenteCodificado);  
        const int MAX_TAM = TAM_LET;

    
        int tamano;
        char datosBinariosDeco[MAX_TAM];

        if (leerArchivoTexto(ArchivoFuenteCodificado, datosBinariosDeco, tamano, MAX_TAM)) {

            cout << "Lectura archivo binario..." << endl;
            cout << "Informacion en binario: ";
            for (int i = 0; i < tamano; i++) {
                cout << datosBinariosDeco[i];
            }
            cout << endl;

            char *datosDeCodificadosMod = nullptr;
            // el arreglo codificado está en datosDecoCodificadosMod

            if (selecMetodoDeCod == 1) {
                cout << "Metodo de Decodificacion Uno... " << endl;
                DeCodificarMetodoUno(datosBinariosDeco, MAX_TAM, semillaCodificacion, datosDeCodificadosMod);
                // escrbir sobre archivoBinarioCodif sobre el archivo de salida codificado (ArchivoSalidaCodificado)
                escribirArchivoTexto("00-AuxBinarioDeCodif.txt", datosDeCodificadosMod, MAX_TAM);
                convertirArchivoAscii("00-AuxBinarioDeCodif.txt", ArchivoSalidaDeCodificado, MAX_TAM);
                delete[] datosDeCodificadosMod;
            }
            else if (selecMetodoDeCod == 2) {
                cout << "Metodo de Decodificacion Dos... " << endl;
                DeCodificarMetodoDos(datosBinariosDeco, MAX_TAM, semillaCodificacion, datosDeCodificadosMod);
                // escrbir sobre archivoBinarioCodif sobre el archivo de salida codificado (ArchivoSalidaCodificado)
                escribirArchivoTexto("00-AuxBinarioDeCodif.txt", datosDeCodificadosMod, MAX_TAM);
                convertirArchivoAscii("00-AuxBinarioDeCodif.txt", ArchivoSalidaDeCodificado, MAX_TAM);
                delete[] datosDeCodificadosMod;
            }
            else {
                cout << "Metodo de Codificacion Invalido " << endl;
            }

        }
    }

    else {
        cout << "Operacion Invalida " << endl;
    }

    return 0;
}


