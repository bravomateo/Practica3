#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include "funcionesString.h"
using namespace std;

void convertirArchivoBinario(string nombreArchivoFuente, string nombreArchivoDestino) {
    // Abrir el archivo de texto
    ifstream lectura(nombreArchivoFuente);

    if (!lectura) {
        cout << endl;
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return;
    }
    
    // Leer el archivo de texto y almacenar los datos en un string
    string datos;
    char caracter;
    while (lectura.get(caracter)) {
        datos += caracter;
    }

    // Cerrar el archivo de texto
    lectura.close();

    // Crear el archivo binario y guardar la representación binaria de cada caracter
    ofstream escritura(nombreArchivoDestino);
    if (!escritura) {
        cout << "Error al crear el archivo " << nombreArchivoDestino << endl;
        return;
    }

    for (unsigned int i = 0; i < datos.length(); i++)
    {
        // Convertir el caracter a su formato binario ASCII correspondiente
        bitset<8> caracterBinario(datos[i]);
        escritura << caracterBinario;
    }

    // Cerrar el archivo binario
    escritura.close();
}

bool leerArchivoTexto(string nombreArchivoFuente, string &datosTextoBinario) {
    
    ifstream lecturaTexto(nombreArchivoFuente);

    if (!lecturaTexto) {
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return false;
    }

    datosTextoBinario = "";
    string linea;
    while (getline(lecturaTexto, linea)) {
        datosTextoBinario += linea;
    }

    lecturaTexto.close();
    return true;
}

void codificarMetodoUno(const string &datosBinarios,  unsigned int n, string &datosCodificadosMod) {

    unsigned int LONGI = datosBinarios.length();
    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    string datosBinariosNuevo[numBloques]; // Arreglo para guardar los resultados de la segmentación por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        datosBinariosNuevo[i] = datosBinarios.substr(i*n, n); // Segmentar en bloques de longitud n
        if(datosBinariosNuevo[i].length() < n) {
            datosBinariosNuevo[i] += string(n - datosBinariosNuevo[i].length(), '1'); // Agregar '1' a bloques incompletos
        }
    }

    // Inicio de la codificación
    string datosCodificados[numBloques]; // Arreglo de strings

    // Cambiar todos los '1' por '0' y viceversa en la primera fila
    for (unsigned int j = 0; j < n; j++) {
        datosCodificados[0] += (datosBinariosNuevo[0][j] == '0') ? '1' : '0';
    }

    // Calcular la cantidad de '1's y '0's en la fila anterior y aplicar las reglas
    for (unsigned int i = 1; i < numBloques; i++) {
        int cant_0 = 0;
        int cant_1 = 0;
        for (unsigned int j = 0; j < n; j++) {
            if (datosBinariosNuevo[i-1][j] == '0') {
                cant_0++;
            } else {
                cant_1++;
            }
        }
        // Aplicar las reglas de acuerdo a la cantidad de '1's y '0's
        if (cant_0 == cant_1) {
            for (unsigned int j = 0; j < n; j++) {
                datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
            }
        }
        else if (cant_0 > cant_1) {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 2) {
                    datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                    cnt = 0;
                }
                else {
                    datosCodificados[i] += datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }
        else {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 3) {
                    cnt = 0;
                    datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                }
                else {
                    datosCodificados[i] += datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }
    }

    datosCodificadosMod = "";
    for (unsigned int i = 0; i < numBloques; i++) {
        datosCodificadosMod += datosCodificados[i];
    }

}

void codificarMetodoDos(const string &datosBinarios,  unsigned int n, string &datosCodificadosMod) {

    unsigned int LONGI = datosBinarios.length();
    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    string datosBinariosNuevo[numBloques]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        datosBinariosNuevo[i] = datosBinarios.substr(i*n, n); // Extraer bloques completos
        if(datosBinariosNuevo[i].length() < n) {
            datosBinariosNuevo[i].append(n-datosBinariosNuevo[i].length(), '1'); // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la codificación
    // arreglo donde van los datos codificados 
    string datosCodificados[numBloques];

    // Corrimiento de bits a la derecha
    for (unsigned int i = 0; i < numBloques; i++) {
        datosCodificados[i].push_back(datosBinariosNuevo[i][n-1]); // El último bit pasa a ser el primero
        datosCodificados[i].append(datosBinariosNuevo[i].substr(0, n-1)); // El resto de los bits se desplaza a la derecha
    }

    datosCodificadosMod.clear();
    for (unsigned int i = 0; i < numBloques; i++) {
        datosCodificadosMod.append(datosCodificados[i]);
    }

}

void DeCodificarMetodoUno(const string &datosBinariosCodif,  unsigned int n, string &datosDeCodificadosMod) {

    unsigned int LONGI = datosBinariosCodif.length();
    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    string datosBinariosNuevo[numBloques]; // Arreglo para guardar los resultados de la segmentación por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        datosBinariosNuevo[i] = datosBinariosCodif.substr(i*n, n); // Segmentar en bloques de longitud n
        if(datosBinariosNuevo[i].length() < n) {
            datosBinariosNuevo[i] += string(n - datosBinariosNuevo[i].length(), '1'); // Agregar '1' a bloques incompletos
        }
    }

    // Inicio de la codificación
    string datosCodificados[numBloques]; // Arreglo de strings

    // Cambiar todos los '1' por '0' y viceversa en la primera fila
    for (unsigned int j = 0; j < n; j++) {
        datosCodificados[0] += (datosBinariosNuevo[0][j] == '0') ? '1' : '0';
    }

    // Calcular la cantidad de '1's y '0's en la fila anterior y aplicar las reglas
    for (unsigned int i = 1; i < numBloques; i++) {
        int cant_0 = 0;
        int cant_1 = 0;
        for (unsigned int j = 0; j < n; j++) {
            if (datosCodificados[i-1][j] == '0') {
                cant_0++;
            } else {
                cant_1++;
            }
        }
        // Aplicar las reglas de acuerdo a la cantidad de '1's y '0's
        if (cant_0 == cant_1) {
            for (unsigned int j = 0; j < n; j++) {
                datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
            }
        }
        else if (cant_0 > cant_1) {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 2) {
                    datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                    cnt = 0;
                }
                else {
                    datosCodificados[i] += datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }
        else {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 3) {
                    cnt = 0;
                    datosCodificados[i] += (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                }
                else {
                    datosCodificados[i] += datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }
    }

    datosDeCodificadosMod = "";
    for (unsigned int i = 0; i < numBloques; i++) {
        datosDeCodificadosMod += datosCodificados[i];
    }

}

void DeCodificarMetodoDos(const string &datosBinariosCodif,  unsigned int n, string &datosDeCodificadosMod) {

    unsigned int LONGI = datosBinariosCodif.length();
    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    string datosBinariosNuevo[numBloques]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        datosBinariosNuevo[i] = datosBinariosCodif.substr(i*n, n); // Extraer bloques completos
        if(datosBinariosNuevo[i].length() < n) {
            datosBinariosNuevo[i].append(n-datosBinariosNuevo[i].length(), '1'); // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la decodificación
    // arreglo donde van los datos decodificados 
    string datosDeCodificados[numBloques];

    // Corrimiento de bits a la izquierda
    for (unsigned int i = 0; i < numBloques; i++) {
        datosDeCodificados[i].append(datosBinariosNuevo[i].substr(1, n-1)); // El resto de los bits se desplaza a la izquierda
        datosDeCodificados[i].push_back(datosBinariosNuevo[i][0]); // El primer bit pasa a ser el último
    }

    datosDeCodificadosMod.clear();
    for (unsigned int i = 0; i < numBloques; i++) {
        datosDeCodificadosMod.append(datosDeCodificados[i]);
    }

}

void escribirArchivoTexto(const string &nombreArchivoSalida, const string &textoEscribir) {
    ofstream archivoSalida(nombreArchivoSalida);
    archivoSalida << textoEscribir;
    archivoSalida.close();
}

void convertirArchivoAscii(const string &nombreArchivoFuente, const string &nombreArchivoDestino) {
    // Abrir el archivo binario
    ifstream lectura(nombreArchivoFuente, ios::binary);

    if (!lectura) {
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return;
    }

    // Leer el archivo binario y convertir cada 8 bits en un caracter
    string datos;
    bitset<8> bits;

    while (lectura >> bits) {
        char caracter = static_cast<char>(bits.to_ulong());
        datos += caracter;
    }

    // Cerrar el archivo binario
    lectura.close();

    // Crear el archivo de texto y guardar los caracteres
    ofstream escritura(nombreArchivoDestino);
    if (!escritura) {
        cout << "Error al crear el archivo " << nombreArchivoDestino << endl;
        return;
    }

    escritura << datos;

    // Cerrar el archivo de texto
    escritura.close();
}
