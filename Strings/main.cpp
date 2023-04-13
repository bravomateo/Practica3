#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include "funcionesString.h"
#include "funcionesString.cpp"

using namespace std;

int main() {

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
        string nombreArchivoFuente;
        cout << " -> Nombre del archivo a codificar : ";
        cin >> nombreArchivoFuente;

        string nombreArchivoSalida;
        cout << " -> Nombre del archivo en el que se guarda la codificacion: ";
        cin >> nombreArchivoSalida;
        cout << endl;

        
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

        unsigned int SEMILLA;
        cout << " -> Escriba la semilla de codificacion: ";
        cin >> SEMILLA;

        // Llamar a la función para convertir el archivo de texto a binario
        convertirArchivoBinario(nombreArchivoFuente, "00-AuxBinario.txt");

        // Datos Binarios leido del archivo
        string datosBinarios;

        if (leerArchivoTexto("00-AuxBinario.txt", datosBinarios)) {
            cout << "Datos leidos desde el archivo de texto: binario.txt: "<< endl;

            // String donde se guardaran los bits codificados 
            string datosCodificados;

            if (selecMetodoCod == 1) { 
                cout << "Metodo de Codificacion Uno... " << endl;
                // Codiifacion Metedo Uno
                codificarMetodoUno(datosBinarios, SEMILLA, datosCodificados);
                // Escritura de los datosCodificados en un archivo.txt de salida
                escribirArchivoTexto(nombreArchivoSalida, datosCodificados);
            }

            else if (selecMetodoCod == 2) {
                cout << "Metodo de Codificacion Dos... " << endl;
                // Codiifacion Metedo Uno
                codificarMetodoDos(datosBinarios, SEMILLA, datosCodificados);
                // Escritura de los datosCodificados en un archivo.txt de salida
                escribirArchivoTexto(nombreArchivoSalida, datosCodificados);
            }

            else {
                cout << "Metodo de Codificacion Invalido " << endl;
            }
        }

        else {
            cout << "Error leyendo el archivo de texto: binario.txt:" << endl;
        }    
    }
    
    else if (seleccionOperacion == 2) { // Se elige la operacion decodificar 
        string ArchivoFuenteCodificado;
        cout << " -> Nombre del archivo a decodificar: ";
        cin >> ArchivoFuenteCodificado;

        string ArchivoSalidaDeCodificado;
        cout << " -> Nombre del archivo en el que se guarda la decodificacion: ";
        cin >> ArchivoSalidaDeCodificado;

        cout << endl;
        cout << " +------------------------------------------+" << endl;
        cout << " + Metodo con el que se codifco el archivo  +" << endl;
        cout << " +------------------------------------------+" << endl;
        cout << " + 1. Primer Metodo                         +" << endl;
        cout << " + 2. Segundo Metodo                        +" << endl;
        cout << " +------------------------------------------+" << endl;
        cout << endl;

        int selecMetodoCod;
        cout << " -> Seleccione el metodo: ";
        cin >> selecMetodoCod;

        cout << " -> Escriba la semilla con la que se codifico el archivo: ";
        unsigned int SEMILLA;
        cin >> SEMILLA;
        string datosBinariosCod;

        if (leerArchivoTexto(ArchivoFuenteCodificado, datosBinariosCod)) {
            cout << "Datos leidos desde el archivo de texto: " << ArchivoFuenteCodificado << endl;
            cout << datosBinariosCod << endl; // Se imprime los bits Codificados

            // String donde se guardaran los bits Decodificados 
            string datosBinariosDeCod;

            if (selecMetodoCod == 1) { 
                cout << "Metodo de Decodificacion Uno... " << endl;
                // Decodificacion Metedo Uno
                DeCodificarMetodoUno(datosBinariosCod, SEMILLA, datosBinariosDeCod);
                // Escritura de los datosDecodificados en un archivo.txt auxiliar de salida
                escribirArchivoTexto("00-AuxBinarioDeCo.txt", datosBinariosDeCod);
                convertirArchivoAscii("00-AuxBinarioDeCo.txt", ArchivoSalidaDeCodificado);
            }

            else if (selecMetodoCod == 2) {
                cout << "Metodo de Decodificacion Dos... " << endl;
                // Decodificacion Metedo Uno
                DeCodificarMetodoDos(datosBinariosCod, SEMILLA, datosBinariosDeCod);
                // Escritura de los datosDecodificados en un archivo.txt auxiliar de salida
                escribirArchivoTexto("00-AuxBinarioDeCo.txt", datosBinariosDeCod);
                convertirArchivoAscii("00-AuxBinarioDeCo.txt", ArchivoSalidaDeCodificado);
            }

            else cout << "Metodo de Decodificacion Invalido " << endl;
        }
        else cout << "Error leyendo el archivo de texto: " << ArchivoFuenteCodificado << endl;
    }    
    return 0;
}
