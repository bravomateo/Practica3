#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include "funcionesArray.h"
using namespace std;

int countCharacters(string nombreArchivo) {
   int count = 0;
   char ch;

   // Abrimos el archivo en modo lectura
   ifstream file(nombreArchivo);

   // Verificamos si el archivo se ha abierto correctamente
   if (!file) {
      cout << "Error al abrir el archivo." << endl;
      return -1;
   }

   // Contamos los caracteres en el archivo
   while (file.get(ch)) {
      count++;
   }

   // Cerramos el archivo
   file.close();

   return count;
}

void convertirArchivoBinario(string nombreArchivoFuente, string nombreArchivoDestino, int MAX_TAM) {
    // Abrir el archivo de texto
    ifstream lectura(nombreArchivoFuente);

    if (!lectura) {
        cout << endl;
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return;
    }
    
    // Leer el archivo de texto y almacenar los datos en un arreglo
    char datos[MAX_TAM];
    int indice = 0;

    char caracter;
    while (lectura.get(caracter)) {
        datos[indice] = caracter;
        indice++;
    }

    // Cerrar el archivo de texto
    lectura.close();

    // Crear el archivo binario y guardar la representación binaria de cada caracter
    ofstream escritura(nombreArchivoDestino);
    if (!escritura) {
        cout << "Error al crear el archivo " << nombreArchivoDestino << endl;
        return;
    }

    for (int i = 0; i < indice; i++)
    {
        // Convertir el caracter a su formato binario ASCII correspondiente
        bitset<8> caracterBinario(datos[i]);
        escritura << caracterBinario;
    }

    // Cerrar el archivo binario
    escritura.close();
}

void convertirArchivoAscii(string nombreArchivoFuente, string nombreArchivoDestino, int MAX_TAM) {
    // Abrir el archivo binario
    ifstream lectura(nombreArchivoFuente, ios::binary);

    if (!lectura) {
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return;
    }

    // Leer el archivo binario y convertir cada 8 bits en un caracter
    char datos[MAX_TAM];
    int indice = 0;

    bitset<8> bits;
    while (lectura >> bits) {
        char caracter = static_cast<char>(bits.to_ulong());
        datos[indice] = caracter;
        indice++;
    }

    // Cerrar el archivo binario
    lectura.close();

    // Crear el archivo de texto y guardar los caracteres
    ofstream escritura(nombreArchivoDestino);
    if (!escritura) {
        cout << "Error al crear el archivo " << nombreArchivoDestino << endl;
        return;
    }

    for (int i = 0; i < indice; i++) {
        escritura << datos[i];
    }

    // Cerrar el archivo de texto
    escritura.close();
}

bool leerArchivoTexto(string nombreArchivoFuente, char datosTextoBinario[], int& tamano, int MAX_TAM) {
    
    ifstream lecturaTexto(nombreArchivoFuente);

    if (!lecturaTexto) {
        cout << "Error al abrir el archivo " << nombreArchivoFuente << endl;
        return false;
    }

    tamano = 0;
    char caracter;
    while (lecturaTexto.get(caracter) && tamano < MAX_TAM) {
        datosTextoBinario[tamano] = caracter;
        tamano++;
    }

    lecturaTexto.close();
    return true;
}

void codificarMetodoUno(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosCodificadosMod) {

    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    char datosBinariosNuevo[numBloques][n]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        for(unsigned int j = 0; j < n; j++) {
            datosBinariosNuevo[i][j] = (i*n+j < LONGI) ? datosBinarios[i*n+j] : '1'; // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la codificación
    // arreglo donde van los datos codificados 
    char datosCodificados[numBloques][n];

    // Cambiar todos los '1' por '0' y viceversa en la primera fila
    for (unsigned int j = 0; j < n; j++) {
        datosCodificados[0][j] = (datosBinariosNuevo[0][j] == '0') ? '1' : '0';
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
                datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
            }
        }

        else if (cant_0 > cant_1) {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 2) {
                    datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                    cnt = 0;
                } 
                else {
                    datosCodificados[i][j] = datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        } 

        else {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 3) {
                    cnt = 0;
                    datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                } else {
                    datosCodificados[i][j] = datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }

    }

    datosCodificadosMod = new char[numBloques*n];
    int k = 0;
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 0; j < n; j++) {
            datosCodificadosMod[k++] = datosCodificados[i][j];
        }
    }

    //Impresion de arreglo unidimensional
    for (unsigned int i = 0; i < numBloques * n; i++) {
        cout << datosCodificadosMod[i];
    }

}

void codificarMetodoDos(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosCodificadosMod) {

    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    char datosBinariosNuevo[numBloques][n]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        for(unsigned int j = 0; j < n; j++) {
            datosBinariosNuevo[i][j] = (i*n+j < LONGI) ? datosBinarios[i*n+j] : '1'; // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la codificación
    // arreglo donde van los datos codificados 
    char datosCodificados[numBloques][n];

        // Corrimiento de bits a la derecha
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 0; j < n-1; j++) {
            datosCodificados[i][j+1] = datosBinariosNuevo[i][j];
        }
        datosCodificados[i][0] = datosBinariosNuevo[i][n-1]; // El último bit pasa a ser el primero
    }


    datosCodificadosMod = new char[numBloques*n];
    int k = 0;
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 0; j < n; j++) {
            datosCodificadosMod[k++] = datosCodificados[i][j];
        }
    }

}

void DeCodificarMetodoUno(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosDeCodificadosMod) {

    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    char datosBinariosNuevo[numBloques][n]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        for(unsigned int j = 0; j < n; j++) {
            datosBinariosNuevo[i][j] = (i*n+j < LONGI) ? datosBinarios[i*n+j] : '1'; // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la codificación
    // arreglo donde van los datos deCodificados 
    char datosCodificados[numBloques][n];

    // Cambiar todos los '1' por '0' y viceversa en la primera fila
    for (unsigned int j = 0; j < n; j++) {
        datosCodificados[0][j] = (datosBinariosNuevo[0][j] == '0') ? '1' : '0';
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
                datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
            }
        }

        else if (cant_0 > cant_1) {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 2) {
                    datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                    cnt = 0;
                } 
                else {
                    datosCodificados[i][j] = datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        } 

        else {
            int cnt = 1;
            for (unsigned int j = 0; j < n; j++) {
                if (cnt == 3) {
                    cnt = 0;
                    datosCodificados[i][j] = (datosBinariosNuevo[i][j] == '0') ? '1' : '0';
                } else {
                    datosCodificados[i][j] = datosBinariosNuevo[i][j];
                }
                cnt++;
            }
        }

    }

    datosDeCodificadosMod = new char[numBloques*n];
    int k = 0;
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 0; j < n; j++) {
            datosDeCodificadosMod[k++] = datosCodificados[i][j];
        }
    }

    //Impresion de arreglo unidimensional
    for (unsigned int i = 0; i < numBloques * n; i++) {
        cout << datosDeCodificadosMod[i];
    }

}

void DeCodificarMetodoDos(const char datosBinarios[], const unsigned int LONGI, const unsigned int n, char* &datosDeCodificadosMod) {

    unsigned int numBloques = (LONGI + n - 1) / n; // Ajustar para bloques incompletos
    char datosBinariosNuevo[numBloques][n]; // Arreglo para guardar los resultados de la segmentacion por bloques

    for(unsigned int i = 0; i < numBloques; i++) {
        for(unsigned int j = 0; j < n; j++) {
            datosBinariosNuevo[i][j] = (i*n+j < LONGI) ? datosBinarios[i*n+j] : '1'; // Agregar '1' a bloques incompletos
        }
    }
    
    // Inicio de la codificación
    // arreglo donde van los datos deCodificados 

    char datosDeCodificados[numBloques][n];

    // Corrimiento de bits a la izquierda
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 1; j < n; j++) {
            datosDeCodificados[i][j-1] = datosBinariosNuevo[i][j];
        }
        datosDeCodificados[i][n-1] = datosBinariosNuevo[i][0]; // El primer bit pasa a ser el último
    }

    datosDeCodificadosMod = new char[numBloques*n];
    int k = 0;
    for (unsigned int i = 0; i < numBloques; i++) {
        for (unsigned int j = 0; j < n; j++) {
            datosDeCodificadosMod[k++] = datosDeCodificados[i][j];
        }
    }

    //Impresion de arreglo unidimensional
    for (unsigned int i = 0; i < numBloques * n; i++) {
        cout << datosDeCodificadosMod[i];
    }

}

void escribirArchivoTexto(const string& nombreArchivo, char *arreglo, int MAX_TAM) {

    ofstream archivoSalida(nombreArchivo);
    for(int i = 0; i < MAX_TAM; i++) {
        archivoSalida << arreglo[i];
    }
    archivoSalida.close();
}


