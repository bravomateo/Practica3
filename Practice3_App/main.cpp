#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <typeinfo>

using namespace std;

bool verificarCedula(string cedulaVerificar);

void escribirUsuarioNuevo(string datosUsuarioNuevo);

bool verificarClave(string cedulaUsuario, string contrasena);

string consultarSaldo(string cedulaUsuario);

void retirarDinero(string cedula, string cantidad);

bool leerArchivoTexto(string nombreArchivoFuente, string &datosTextoBinario);

void DeCodificarMetodoDos(const string &datosBinariosCodif, const unsigned int n, string &datosDeCodificadosMod);

string bitsToAscii(string bits);

int main() {

    bool star = true;
    while (star) {
        int opcionMenu; 

    cout << endl;
    cout << " +----------------------------------+" << endl;
    cout << " +           Menu principal         +" << endl;
    cout << " +----------------------------------+" << endl;
    cout << " + 1. Ingresar como administrador   +" << endl;
    cout << " + 2. Ingresar como usuario         +" << endl;
    cout << " + 0. Para salir del programa       +" << endl;
    cout << " +----------------------------------+" << endl;
    cout << endl;
    cout << " Seleccione una opcion: ";
    cin >> opcionMenu;
    cout << endl;

    // La clave es adminInfo2023 codificado en metodo 2 semilla 8
    
    const unsigned int SEMILLA = 8;
    string claveCorrectaBin;
    string datosBinariosCod;
    leerArchivoTexto("sudo.txt", datosBinariosCod);
    DeCodificarMetodoDos(datosBinariosCod, SEMILLA, claveCorrectaBin);
    string claveCorrecta = bitsToAscii(claveCorrectaBin);

    if (opcionMenu == 1) { // Se ingresa como administrador


        string claveIngresada;        
        cout << endl;
        cout << " +-----------------------------------+" << endl;
        cout << " +       Menu de adiministrador      +" << endl;
        cout << " +-----------------------------------+" << endl;
        cout << endl;
        cout << "  -> Ingrese clave de administrador: " ;
        cin >> claveIngresada;

        if (claveIngresada == claveCorrecta) {
            
            cout << endl;
            cout << " -> Clave correcta! " << endl;
            cout << endl;

            cout << " +-----------------------------------+" << endl;
            cout << " ** >>>> Registro de usuarios <<<<  **" << endl;
            cout << " +-----------------------------------+" << endl;
            cout << endl;

            string cedulaUsuarioNuevo;
            cout << "  -> Ingrese la cedula del usuario: ";
            cin >> cedulaUsuarioNuevo;
            cout << endl;

            if (!verificarCedula(cedulaUsuarioNuevo)) {

                cout << "La cedula: " << cedulaUsuarioNuevo << " es valida" << endl;

                string claveUsuarioNuevo;
                string saldoUsuarioNuevo;

                cout << "  -> Ingrese la clave del nuevo usuario: ";
                cin >> claveUsuarioNuevo;
                cout << endl;
                
                cout << "  -> Ingrese el saldo del nuevo usuario: ";
                cin >> saldoUsuarioNuevo;
                cout << endl;

                string datosUsuarioNuevo = cedulaUsuarioNuevo + "," + claveUsuarioNuevo + "," + saldoUsuarioNuevo;
                escribirUsuarioNuevo(datosUsuarioNuevo);     

            }
            else cout << "Error! La cedula " << cedulaUsuarioNuevo << " ya existe" << endl;
        } 
        else cout << "La clave de Administrador no es valida" << endl;
        cout << endl;

    } 

    else if (opcionMenu == 2) { // Se ingresa como usuario


        cout << " +-------------------------+" << endl;
        cout << " +     Menu de usuario     +" << endl;
        cout << " +-------------------------+" << endl;


        string cedulaUsuario;
        string claveUsuario;


        cout << "  -> Ingrese su cedula: ";
        cin >> cedulaUsuario;


        cout << "  -> Ingrese su clave: ";
        cin >> claveUsuario;


        if (verificarCedula(cedulaUsuario)) {
            if (verificarClave(cedulaUsuario, claveUsuario)) {

                int seleccionUsuario;
                cout << " ** Usuario y clave correctas ** " << endl;
                cout << endl;
                cout << " +--------------------------------+" << endl;
                cout << " + 1. Consultar saldo             +" << endl;
                cout << " + 2. Retirar dinero              +" << endl;
                cout << " +--------------------------------+" << endl;
                cout << endl;
                cout << "Seleccione una opcion: ";
                cin >> seleccionUsuario;

                if (seleccionUsuario == 1) { // Consultar saldo
                    cout << endl;
                    cout << " ** Recuerde que la consulta de saldo tiene un costo de 1000 COP **" << endl;

                    cout << "   - - -  " << consultarSaldo(cedulaUsuario) << endl;

                    if (stoi(consultarSaldo(cedulaUsuario)) >= 1000) {                   
                        cout << "Su saldo es: " << consultarSaldo(cedulaUsuario) << endl;
                        //retirarDinero(cedulaUsuario, "1000"); // El retiro tiene un valor de 1000
                        cout << "Saldo despues de la consulta " << stoi(consultarSaldo(cedulaUsuario)) << endl;
                    }
                    else {
                        cout << "No tiene el saldo suficiente para realizar una consulta" << endl;
                    }
                }
                else if (seleccionUsuario == 2){ // Retirar saldo
                    string cantidadRetiro;
                    cout << endl;
                    cout << "  -> Cantidad que desea retirar: ";
                    cin >> cantidadRetiro;

                    if (stoi(consultarSaldo(cedulaUsuario)) >= stoi(cantidadRetiro) + 1000) { // 1000 del valor del retiro
                        retirarDinero(cedulaUsuario, cantidadRetiro);
                        cout << "Acaba de hacer un retiro de : " << cantidadRetiro << " y el valor de la transaccion es 1000" << endl;
                        retirarDinero(cedulaUsuario, "1000"); // El retiro tiene un valor de 1000
                        cout << "Su saldo despues de la transaccion es: " << consultarSaldo(cedulaUsuario) << endl;
                    }
                    else {
                        cout << "Saldo insuficiente, puede retirar: " << consultarSaldo(cedulaUsuario) << endl;
                    }
                } 
            }
            else cout << "Lo sentimos, clave incorrecta!" << endl;
        }
        else cout << "Lo sentimos, la su cedula: " << cedulaUsuario << " no ha sido registrada" << endl;

    }

    else if (opcionMenu == 0) {
        star = false;
    }
    }
    
    return 0;
}

bool verificarCedula(string cedulaVerificar) {
    ifstream archivo("baseDeDatos.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de base de datos" << endl;
        return false;
    }
    string linea;
    while (getline(archivo, linea)) { // leer linea a liena 
        // size_t representa tamaños y posiciones de memoria
        size_t posicion = linea.find(","); //  busca la posición de la primera aparición de la coma 
        string cedulaFila = linea.substr(0, posicion);
        if (cedulaFila == cedulaVerificar) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void escribirUsuarioNuevo(string datosUsuarioNuevo) {

    ifstream archivo("baseDeDatos.txt");
    string ultimaLinea;

    if (archivo.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
        archivo.close();
        ofstream archivoSalida("baseDeDatos.txt");
        archivoSalida << datosUsuarioNuevo;
        archivoSalida.close();
        return;
    }
    else if (archivo.is_open()) {
        while (getline(archivo, ultimaLinea)) {}
        archivo.close();
    }
    else {
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    ofstream archivoSalida("baseDeDatos.txt", ios::app);
    archivoSalida.seekp(0, ios::end);
    archivoSalida << "\n" << datosUsuarioNuevo;
    archivoSalida.close();
}

bool verificarClave(string cedulaUsuario, string clavePotencial) {
    string linea;
    ifstream archivo("baseDeDatos.txt"); // Abrir archivo en modo lectura

    if (archivo.is_open()) { // Verificar si el archivo se ha abierto correctamente
        while (getline(archivo, linea)) { // Leer línea por línea del archivo
            string datos[3];
            int i = 0;
            size_t pos = 0;
            string delimiter = ",";
            while ((pos = linea.find(delimiter)) != string::npos) { // Separar los datos de cada línea en un arreglo
                datos[i] = linea.substr(0, pos);
                linea.erase(0, pos + delimiter.length());
                i++;
            }
            datos[i] = linea;

            if (datos[0] == cedulaUsuario) { // Si la cédula coincide, verificar la contraseña
                if (datos[1] == clavePotencial) {
                    archivo.close();
                    return true;
                }
                else {
                    archivo.close();
                    return false;
                }
            }
        }
        archivo.close();
    }
    return false; // Si la cédula no se encuentra, retornar falso
}

string consultarSaldo(string cedulaUsuario) {
    
    string linea;
    ifstream archivo("baseDeDatos.txt");

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            string datos[3];
            int i = 0;
            size_t pos = 0;
            string delimiter = ",";
            while ((pos = linea.find(delimiter)) != string::npos) {
                datos[i] = linea.substr(0, pos);
                linea.erase(0, pos + delimiter.length());
                i++;
            }
            datos[i] = linea;

            if (datos[0] == cedulaUsuario) {
                archivo.close();
                return datos[2];
            }
        }
        archivo.close();
        return "Invalido";
    }
    else {
        return "Error al abrir el archivo.";
    }
}

void retirarDinero(string cedula, string cantidad) {
    // Abrir el archivo baseDeDatos.txt en modo lectura y escritura
    ifstream archivo_lectura("baseDeDatos.txt");
    ofstream archivo_escritura("temp.txt");

    if (!archivo_lectura.is_open() || !archivo_escritura.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    
    // Leer el archivo línea por línea
    string linea;
    while (getline(archivo_lectura, linea)) {
        // Separar la línea en campos utilizando la coma como delimitador
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        string cedula_actual = campo;
        getline(ss, campo, ',');
        string clave = campo;
        getline(ss, campo, ',');
        string saldo_actual_str = campo;
        int saldo_actual = stoi(saldo_actual_str);
        
        // Verificar si la cédula actual coincide con la cédula ingresada
        if (cedula_actual == cedula) {
            // Restar la cantidad de dinero especificada al saldo actual
            int cantidad_int = stoi(cantidad);
            int saldo_nuevo = saldo_actual - cantidad_int;
            // Escribir la nueva línea en el archivo temporal
            archivo_escritura << cedula_actual << "," << clave << "," << saldo_nuevo << endl;
        } else {
            // Escribir la línea original en el archivo temporal
            archivo_escritura << linea << endl;
        }
    }
    
    // Cerrar los archivos
    archivo_lectura.close();
    archivo_escritura.close();
    
    // Reemplazar el archivo original con el archivo temporal
    remove("baseDeDatos.txt");
    rename("temp.txt", "baseDeDatos.txt");
    
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

void DeCodificarMetodoDos(const string &datosBinariosCodif, const unsigned int n, string &datosDeCodificadosMod) {

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

string bitsToAscii(string bits) {
    string ascii = "";
    for (size_t i = 0; i < bits.size(); i += 8) {
        bitset<8> bits8(bits.substr(i, 8));
        char c = char(bits8.to_ulong());
        ascii += c;
    }
    return ascii;
}


