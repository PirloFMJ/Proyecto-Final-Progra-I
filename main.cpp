#include <iostream>
#include <mysql/jdbc.h>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>

using namespace std;


void baseDeDatos();
void tablaCursos();
void tablaEstudiantes();
void tablaCalifiaciones();

/***********************************************************establecerConexion()*************************************************************************/
sql::Connection* establecerConexion() {
    sql::Driver* driver = get_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "sqluser", "password");
        con->setSchema("controlescolar");
    return con;
}

/************************************************************insertarEstudiante()*************************************************************************/
void insertarEstudiante(sql::Connection* con, std::string nombre, int grado) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("INSERT INTO estudiantes (nombre_estudiante, grado) VALUES ('" + nombre + "', " + std::to_string(grado) + ")");
    delete stmt;
}

/************************************************************obtenerEstudiantes()*************************************************************************/
void obtenerEstudiantes(sql::Connection* con) {
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM estudiantes");
    while (res->next()) {
        std::cout << res->getInt("id") << " " << res->getString("nombre_estudiante") << " " << res->getInt("grado") << std::endl;
    }
    delete res;
    delete stmt;
}

/************************************************************actualizarEstudiante()*************************************************************************/
void actualizarEstudiante(sql::Connection* con, int id, std::string nombre, int grado) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("UPDATE estudiantes SET nombre_estudiante = '" + nombre + "', grado = " + std::to_string(grado) + " WHERE id = " + std::to_string(id));
    delete stmt;
}

/************************************************************eliminarEstudiante()*************************************************************************/
void eliminarEstudiante(sql::Connection* con, int id) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("DELETE FROM estudiantes WHERE id = " + std::to_string(id));
    delete stmt;
}


/************************************************************insertarCurso()*************************************************************************/
void insertarCurso(sql::Connection* con, std::string nombre, int creditos) {
    sql::Statement* stmt = con->createStatement();
    try {
        stmt->execute("INSERT INTO cursos (nombre_cursos, creditos) VALUES ('" + nombre + "', " + std::to_string(creditos) + ")");
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error al insertar curso: " << e.what() << std::endl;
    }
    delete stmt;
}

/************************************************************obtenerCursos()*************************************************************************/
void obtenerCursos(sql::Connection* con) {
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM cursos");
    while (res->next()) {
        std::cout << res->getInt("id") << " " << res->getString("nombre_cursos") << " " << res->getInt("creditos") << std::endl;
    }
    delete res;
    delete stmt;
}

/************************************************************actualizarCurso()*************************************************************************/
void actualizarCurso(sql::Connection* con, int id, std::string nombre, int creditos) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("UPDATE cursos SET nombre_cursos = '" + nombre + "', creditos = " + std::to_string(creditos) + " WHERE id = " + std::to_string(id));
    delete stmt;
}

/************************************************************eliminarCurso()*************************************************************************/
void eliminarCurso(sql::Connection* con, int id) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("DELETE FROM cursos WHERE id = " + std::to_string(id));
    delete stmt;
}

/************************************************************insertarCalificacion()*************************************************************************/
void insertarCalificacion(sql::Connection* con, int idEstudiante, int idCurso, int calificacion) {
    sql::Statement* stmt = con->createStatement();
    try {
        stmt->execute("INSERT INTO calificaciones (id_estudiante, id_curso, calificacion) VALUES (" + std::to_string(idEstudiante) + ", " + std::to_string(idCurso) + ", " + std::to_string(calificacion) + ")");
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error al insertar calificaci�n: " << e.what() << std::endl;
    }
    delete stmt;
}

/************************************************************obtenerCalificaciones()*************************************************************************/
void obtenerCalificaciones(sql::Connection* con) {
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM calificaciones");
    while (res->next()) {
        std::cout << res->getInt("id") << " " << res->getInt("id_estudiante") << " " << res->getInt("id_curso") << " " << res->getInt("calificacion") << std::endl;
    }
    delete res;
    delete stmt;
}

/************************************************************actualizarCalificacion()*************************************************************************/
void actualizarCalificacion(sql::Connection* con, int id, int idEstudiante, int idCurso, int calificacion) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("UPDATE calificaciones SET id_estudiante = " + std::to_string(idEstudiante) + ", id_curso = " + std::to_string(idCurso) + ", calificacion = " + std::to_string(calificacion) + " WHERE id = " + std::to_string(id));
    delete stmt;
}

/************************************************************eliminarCalificacion()*************************************************************************/
void eliminarCalificacion(sql::Connection* con, int id) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("DELETE FROM calificaciones WHERE id = " + std::to_string(id));
    delete stmt;
}

/************************************************************baseDeDatos()*************************************************************************/
void baseDeDatos() {
    int opcion;
    system("cls");

    do {
        cout << "Bienvenido a la base de datos\n\n";
        cout << "\tMenu de la base de datos\n\n";
        cout << "1. Tabla de estudiantes\n";
        cout << "2. Tabla de cursos\n";
        cout << "3. Tabla de calificaciones\n";
        cout << "4. Salir de la base de datos\n\n";
        cout << "Seleccionar tabla: ";
        cin >> opcion;
        cin.ignore();
        system("cls");

        switch (opcion) {
        case 1:
            tablaEstudiantes();
            break;
        case 2:
            tablaCursos();
            break;
        case 3:
            tablaCalifiaciones();
            break;
        }
    } while (opcion != 4);
}


/************************************************************tablaEstudiantes()*************************************************************************/
void tablaEstudiantes() {

    sql::Connection* con = establecerConexion();

    int opcion;
    do {
       
        string nombreEstudiante;
        int grado;
        int id;

        cout << "\tMenu de la tabla de estudiantes\n\n";
        cout << "1. Insertar estudiante: \n";
        cout << "2. Ver todos los estudiantes: \n";
        cout << "3. Actualizar estudiantes: \n";
        cout << "4. Eliminar estudiantes: \n";
        cout << "5. Salir de la tabla\n\n";

        cout << "Opcion a elegir: ";
        cin >> opcion;
        cin.ignore();

        system("cls");

        switch (opcion) {
        case 1:
            cout << "Ingrese el nombre del estudiante: ";
            getline(cin, nombreEstudiante);
            cout << "Ingrese el grado del estudiante: ";
            cin >> grado;
            cin.ignore();
            insertarEstudiante(con, nombreEstudiante, grado);
            break;
        case 2:
            cout << "ID - NOMBRE - GRADO\n";
            obtenerEstudiantes(con);
            break;
        case 3:
            cout << "Escribe el ID a actualizar del estudiante: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese el nuevo nombre del estudiante: ";
            getline(cin, nombreEstudiante);
            cout << "Ingrese el nuevo grado del estudiante: ";
            cin >> grado;
            cin.ignore();
            actualizarEstudiante(con, id, nombreEstudiante, grado);
            break;
        case 4: 
            cout << "Escribe el ID del estudiante a eliminar: ";
            cin >> id;
            cin.ignore();
            eliminarEstudiante(con, id);
            break;
        case 5:
            cout << "Has salido correctamente";
            break;
        }
        system("pause");
        system("cls");
    } while (opcion != 5);

    delete con;
}

/************************************************************tablaCursos()*************************************************************************/
void tablaCursos() {

    sql::Connection* con = establecerConexion();
    int opcion;

    do {
        int id;
        string nombreCurso;
        int credito;

        cout << "\tMenu de la tabla de cursos\n\n";
        cout << "1. Ingrese el curso: \n";
        cout << "2. Ver todos los cursos: \n";
        cout << "3. Actualizar curso: \n";
        cout << "4. Eliminar curso: \n";
        cout << "5. Salir de la tabla: \n\n";
        cout << "Opcion a elegir: ";
        cin >> opcion;
        cin.ignore();
        system("cls");

        switch (opcion) {
        case 1:
            cout << "Ingrese el nombre del curso: ";
            getline(cin, nombreCurso);
            cout << "Ingrese los creditos del curso: ";
            cin >> credito;
            cin.ignore();
            insertarCurso(con, nombreCurso, credito);
            break;
        case 2:
            cout << " ID - CURSO - CREDITOS\n";
            obtenerCursos(con);
            break;
        case 3:
            cout << "Ingrese el ID del curso a actualizar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese el nuevo curso: ";
            getline(cin, nombreCurso);
            cout << "Ingrese el nuevo credito del curso: ";
            cin >> credito;
            cin.ignore();
            actualizarCurso(con, id, nombreCurso, credito);
            break;
        case 4:
            cout << "Ingrese el ID del curso a eliminar: ";
            cin >> id;
            cin.ignore();
            eliminarCurso(con, id);
            break;
        case 5:
            cout << "Has salido correctamente";
            break;
        }
        system("pause");
        system("cls");
    } while (opcion != 5);

    delete con;
}

/************************************************************tablaCalificaciones()*************************************************************************/
void tablaCalifiaciones() {
    sql::Connection* con = establecerConexion();

    int opcion;
    do {

        int id, idCurso, idEstudiante, idCalificacion;
        float calificacion;

        cout << "\tMenu de la tabla de calificaciones\n\n";
        cout << "1. Insertar calificacion: \n";
        cout << "2. Ver todas las calificaciones: \n";
        cout << "3. Actualizar calificaciones: \n";
        cout << "4. Eliminar calificaciones: \n";
        cout << "5. Salir de la tabla: \n\n";

        cout << "Opcion a elegir: ";
        cin >> opcion;
        cin.ignore();

        system("cls");

        switch (opcion) {
        case 1:
            cout << "Ingrese el ID del estudiante: ";
            cin >> idEstudiante;
            cin.ignore();
            cout << "Ingrese el ID del curso: ";
            cin >> idCurso;
            cin.ignore();
            cout << "Indique la calificacion del estudiante: ";
            cin >> calificacion;
            cin.ignore();
            insertarCalificacion(con, idEstudiante, idCurso, calificacion);
            break;
        case 2:
            cout << "ID CALIFICACION - ID ESTUDIANTE - ID CURSO - CALIFICACION\n";
            obtenerCalificaciones(con);
            break;
        case 3:
            cout << "Escribe el ID a actualizar de la calificacion: ";
            cin >> idCalificacion;
            cin.ignore();
            cout << "Ingrese el nuevo ID del estudiante: ";
            cin >> idEstudiante;
            cout << "Ingrese el nuevo curso del estudiante: ";
            cin >> idCurso;
            cout << "Ingrese la nueva calificacion del estudiante: ";
            cin >> calificacion;
            cin.ignore();
            actualizarCalificacion(con, idCalificacion ,idEstudiante, idCurso, calificacion);
            break;
        case 4:
            cout << "Escribe el ID de la calificacion a eliminar: ";
            cin >> idCalificacion;
            cin.ignore();
            eliminarCalificacion(con, idCalificacion);
            break;
        case 5:
            cout << "Has salido correctamente";
            break;
        }
        system("pause");
        system("cls");
    } while (opcion != 5);

    delete con;
}

/************************************************************gotoxy()*************************************************************************/
void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
class persona
{
private:
    string nombre, apellido, ocupacion;
    int edad, DPI;

public:
    // Constructor sin DPI
    persona(string nombre1, string apellido1, string ocupacion1, int edad1) {
        nombre = nombre1;
        apellido = apellido1;
        ocupacion = ocupacion1;
        edad = edad1;
    }

    // Constructor con DPI
    persona(string nombre1, string apellido1, string ocupacion1, int edad1, int DPI1) {
        nombre = nombre1;
        apellido = apellido1;
        ocupacion = ocupacion1;
        edad = edad1;
        DPI = DPI1;
    }

    void mostrarInfo()
    {
        cout << "_________________________________"
            << "\nNombre: " << nombre << "\nApellido: " << apellido << "\nOcupacion: " << ocupacion << "\nEdad: " << edad << "\nDPI: " << DPI << "\n_________________________________" << endl;
    }
    void mostrarInfoArchivo(ofstream& archivo) const {
        archivo << nombre << "," << apellido << "," << ocupacion << "," << edad << "," << DPI << endl;
    }

    const string& getNombre() const { return nombre; } // Se hace esto para poder acceder a esta información
    const string& getApellido() const { return apellido; }
    const string& getOcupacion() const { return ocupacion; }
    const int& getEdad() const { return edad; }
    const int& getDPI() const { return DPI; }
};

class estudiante : public persona // Hereda de la clase persona
{
private:
    string numeroCarnet;
    double promedioCalificaciones;

public:
    estudiante(string nombre1, string apellido1, int edad1, string carnet, double promedio)
        : persona(nombre1, apellido1, "", edad1), numeroCarnet(carnet), promedioCalificaciones(promedio) {}

    void mostrarInfo() const
    {
        cout << "_________________________________"
            << "\nNombre: " << getNombre()
            << "\nApellido: " << getApellido()
            << "\nEdad: " << getEdad()
            << "\nCarnet: " << numeroCarnet
            << "\nPromedio: " << promedioCalificaciones
            << "\n_________________________________" << endl;
    }
    void mostrarInfoArchivo(ofstream& archivo) const {
        archivo << getNombre() << "," << getApellido() << "," << getEdad() << "," << numeroCarnet << "," << promedioCalificaciones << endl;
    }

    const string& getNumeroCarnet() const { return numeroCarnet; }
    const double& getPromedioCalificaciones() const { return promedioCalificaciones; }
};

vector<estudiante> listaEstudiantes; // Se inicializan estos vectores que son como listas, para manejar de mejor manera los datos.
vector<persona> listaPersonas;
string crearArchivo();
bool archivoExiste(const string& nombreArchivo);
void crearPersona(const string& nombreArchivo);
void crearEstudiante(const string& nombreArchivo);
void actualizarArchivo(const string& nombreArchivo);
void modificarPersona(const string& nombreArchivo);
void modificarEstudiante(const string& nombreArchivo);
void eliminarPersona(const string& nombreArchivo);
void eliminarEstudiante(const string& nombreArchivo);
void buscarPersonaPorDPI(const string& nombreArchivo);
void buscarEstudiantePorCarnet(const string& nombreArchivo);
void leerTodo(const string& nombreArchivo);
void trabajoConArchivos();

/************************************************************MAIN*************************************************************************/
/************************************************************MAIN*************************************************************************/
int main() {
    int opcion;

    do {
        system("cls");
        cout << "\t Menu general\n\n";
        cout << "1. Trabajar con archivos\n";
        cout << "2. Trabajar con base de datos\n";
        cout << "3. Salir del programa\n\n";
        cout << "opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            trabajoConArchivos();
            break;
        case 2:
            baseDeDatos();
            break;
        case 3:
            cout << "Has salido correctamente del programa\n";
        }
    } while (opcion != 3);


    return 0;
}

/************************************************************trabajoConArchivos()************************************************************************/
void trabajoConArchivos()
{
    //string nombreArchivo = crearArchivo();
    system("cls");
    int opc;
    string nombreArchivo;
    do
    {
        gotoxy(45, 1);
        cout << "MENU PRINCIPAL" << endl;
        cout << "1- Crear archivo.txt y trabajar con el apartir de ahora." << endl;
        cout << "2- Crear persona." << endl;
        cout << "3- Crear estudiante." << endl;
        cout << "4- Modificar persona" << endl;
        cout << "5- Modificar estudiante." << endl;
        cout << "6- Eliminar persona." << endl;
        cout << "7- Eliminar estudiante" << endl;
        cout << "8- Buscar persona por su DPI." << endl;
        cout << "9- Buscar estudiante por su Carnet." << endl;
        cout << "10- Leer todo el archivo .txt" << endl;
        cout << "11- Salir del menu." << endl;
        cout << "Opcion: ";
        cin >> opc;
        cin.ignore();

        switch (opc)
        {
        case 1:
        {
            system("cls");

            nombreArchivo = crearArchivo();

            system("pause");
            cout << endl;
            break;
        }

        case 2:
        {
            system("cls");

            crearPersona(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 3:
        {
            system("cls");

            crearEstudiante(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 4:
        {
            system("cls");

            modificarPersona(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 5:
        {
            system("cls");

            modificarEstudiante(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 6:
        {
            system("cls");

            eliminarPersona(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 7:
        {
            system("cls");

            eliminarEstudiante(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 8:
        {
            system("cls");

            buscarPersonaPorDPI(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 9:
        {
            system("cls");

            buscarEstudiantePorCarnet(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        case 10:
        {
            system("cls");

            leerTodo(nombreArchivo);

            system("pause");
            cout << endl;
            break;
        }

        default:
            break;
        }
        system("cls");
    } while (opc != 11);

    cout << "Fuera del programa" << endl;
    system("pause");
}
/************************************************************crearArchivo()*************************************************************************/
string crearArchivo() {
    string nombreArchivo;
    do {
        system("cls");
        gotoxy(45, 1);
        cout << "Crear archivo txt:" << endl << endl;
        cout << "Ingrese el nombre del archivo (sin .txt): ";
        getline(cin, nombreArchivo); // Leer toda la línea, permitiendo espacios
        nombreArchivo += ".txt";

        if (archivoExiste(nombreArchivo)) {
            cout << "El archivo '" << nombreArchivo << "' ya existe. Desea utilizarlo? (s/n): ";
            char respuesta;
            cin >> respuesta;
            cin.ignore(); // Ignorar el salto de línea
            if (respuesta == 's' || respuesta == 'S') {
                return nombreArchivo;
            }
            else {
                continue;
            }
        }
        else {
            ofstream archivo(nombreArchivo.c_str());
            if (archivo.is_open()) {
                cout << "Archivo '" << nombreArchivo << "' creado exitosamente." << endl;
                archivo.close();
                return nombreArchivo;
            }
            else {
                cout << "No se pudo crear el archivo '" << nombreArchivo << "'." << endl;
            }
        }
    } while (true);
}
/************************************************************comprobacionArchivo()******************************************************************/
bool archivoExiste(const string& nombreArchivo) { // Verifica si el archivo existe
    ifstream archivo(nombreArchivo.c_str());
    bool existe = archivo.good();
    archivo.close();
    return existe;
}
/************************************************************crearPersona()******************************************************************/
void crearPersona(const string& nombreArchivo) {
    string nombre, apellido, ocupacion;
    int edad, dpi;
    gotoxy(45, 1);
    cout << "Ingresar Persona:" << endl << endl;
    cout << "Ingrese el nombre: ";
    getline(cin, nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    cout << "Ingrese la ocupacion: ";
    getline(cin, ocupacion);
    cout << "Ingrese la edad: ";
    cin >> edad;
    cout << "Ingrese el DPI: ";
    cin >> dpi;

    persona p(nombre, apellido, ocupacion, edad, dpi);
    listaPersonas.push_back(p);

    ofstream archivo(nombreArchivo.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "1,"; // Identificador de tipo para persona
        p.mostrarInfoArchivo(archivo);
        cout << "Persona creada exitosamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}

/************************************************************CrearEstudiante()******************************************************************/
void crearEstudiante(const string& nombreArchivo) {
    string nombre, apellido, carnet;
    int edad;
    double promedio;
    gotoxy(45, 1);
    cout << "Ingresar Estudiante:" << endl << endl;
    cout << "Ingrese el nombre: ";
    getline(cin, nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    cout << "Ingrese la edad: ";
    cin >> edad;
    cout << "Ingrese el carnet: ";
    cin >> carnet;
    cout << "Ingrese el promedio: ";
    cin >> promedio;

    estudiante e(nombre, apellido, edad, carnet, promedio);
    listaEstudiantes.push_back(e);

    ofstream archivo(nombreArchivo.c_str(), ios::app);
    if (archivo.is_open()) {
        archivo << "2,"; // Identificador de tipo para estudiante
        e.mostrarInfoArchivo(archivo);
        cout << "Estudiante creado exitosamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}
/************************************************************actualizarArchivo()******************************************************************/
void actualizarArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo.c_str()); // Convertir std::string a const char*
    if (archivo.is_open()) {
        // Escribir información de personas
        for (size_t i = 0; i < listaPersonas.size(); ++i) {
            archivo << "1,";
            listaPersonas[i].mostrarInfoArchivo(archivo);
        }

        // Escribir información de estudiantes
        for (size_t i = 0; i < listaEstudiantes.size(); ++i) {
            archivo << "2,";
            listaEstudiantes[i].mostrarInfoArchivo(archivo);
        }

        cout << "Archivo actualizado exitosamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo para actualizar." << endl;
    }
    archivo.close();
}
/************************************************************modificarPersona()******************************************************************/
void modificarPersona(const string& nombreArchivo) {
    int dpi;
    gotoxy(45, 1);
    cout << "Modificar Persona:" << endl << endl;
    cout << "Ingrese el DPI de la persona a modificar: ";
    cin >> dpi;
    cin.ignore();

    vector<persona>::iterator it;
    for (it = listaPersonas.begin(); it != listaPersonas.end(); ++it) {
        if ((*it).getDPI() == dpi) {
            break;
        }
    }

    if (it != listaPersonas.end()) {
        string nombre, apellido, ocupacion;
        int edad;

        cout << "Ingrese el nuevo nombre: ";
        getline(cin, nombre);
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, apellido);
        cout << "Ingrese la nueva ocupacion: ";
        getline(cin, ocupacion);
        cout << "Ingrese la nueva edad: ";
        cin >> edad;
        cin.ignore();

        *it = persona(nombre, apellido, ocupacion, edad, dpi);

        ofstream archivo(nombreArchivo.c_str(), ios::out);
        if (archivo.is_open()) {
            for (vector<persona>::iterator it = listaPersonas.begin(); it != listaPersonas.end(); ++it) {
                archivo << "1," << it->getNombre() << "," << it->getApellido() << "," << it->getOcupacion() << "," << it->getEdad() << "," << it->getDPI() << endl;
            }
            for (vector<estudiante>::iterator it = listaEstudiantes.begin(); it != listaEstudiantes.end(); ++it) {
                archivo << "2," << it->getNombre() << "," << it->getApellido() << "," << it->getEdad() << "," << it->getNumeroCarnet() << "," << it->getPromedioCalificaciones() << endl;
            }
            cout << "Persona modificada exitosamente." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        archivo.close();
    }
    else {
        cout << "No se encontro una persona con el DPI ingresado." << endl;
    }
}

/************************************************************modificarEstudiante()******************************************************************/
void modificarEstudiante(const string& nombreArchivo) {
    string carnet;
    gotoxy(45, 1);
    cout << "Modificar Estudiante:" << endl << endl;
    cout << "Ingrese el carnet del estudiante a modificar: ";
    getline(cin, carnet);

    vector<estudiante>::iterator it;
    for (it = listaEstudiantes.begin(); it != listaEstudiantes.end(); ++it) {
        if ((*it).getNumeroCarnet() == carnet) {
            break;
        }
    }

    if (it != listaEstudiantes.end()) {
        string nombre, apellido;
        int edad;
        double promedio;

        cout << "Ingrese el nuevo nombre: ";
        getline(cin, nombre);
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, apellido);
        cout << "Ingrese la nueva edad: ";
        cin >> edad;
        cin.ignore();
        cout << "Ingrese el nuevo promedio: ";
        cin >> promedio;
        cin.ignore();

        *it = estudiante(nombre, apellido, edad, carnet, promedio);

        ofstream archivo(nombreArchivo.c_str(), ios::out);
        if (archivo.is_open()) {
            for (vector<persona>::iterator it = listaPersonas.begin(); it != listaPersonas.end(); ++it) {
                archivo << "1," << it->getNombre() << "," << it->getApellido() << "," << it->getOcupacion() << "," << it->getEdad() << "," << it->getDPI() << endl;
            }
            for (vector<estudiante>::iterator it = listaEstudiantes.begin(); it != listaEstudiantes.end(); ++it) {
                archivo << "2," << it->getNombre() << "," << it->getApellido() << "," << it->getEdad() << "," << it->getNumeroCarnet() << "," << it->getPromedioCalificaciones() << endl;
            }
            cout << "Estudiante modificado exitosamente." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        archivo.close();
    }
    else {
        cout << "No se encontro un estudiante con el carnet ingresado." << endl;
    }
}
/************************************************************eliminarPersona()******************************************************************/
void eliminarPersona(const string& nombreArchivo) {
    int dpi;
    gotoxy(45, 1);
    cout << "Eliminar Persona:" << endl << endl;
    cout << "Ingrese el DPI de la persona a eliminar: ";
    cin >> dpi;
    cin.ignore();

    vector<persona>::iterator it = listaPersonas.begin();
    bool encontrado = false;
    while (it != listaPersonas.end()) {
        if ((*it).getDPI() == dpi) {
            encontrado = true;
            break;
        }
        ++it;
    }

    if (encontrado) {
        listaPersonas.erase(it);

        ofstream archivo(nombreArchivo.c_str(), ios::out);
        if (archivo.is_open()) {
            for (vector<persona>::iterator pit = listaPersonas.begin(); pit != listaPersonas.end(); ++pit) {
                archivo << "1," << (*pit).getNombre() << "," << (*pit).getApellido() << "," << (*pit).getOcupacion() << "," << (*pit).getEdad() << "," << (*pit).getDPI() << endl;
            }
            for (vector<estudiante>::iterator eit = listaEstudiantes.begin(); eit != listaEstudiantes.end(); ++eit) {
                archivo << "2," << (*eit).getNombre() << "," << (*eit).getApellido() << "," << (*eit).getEdad() << "," << (*eit).getNumeroCarnet() << "," << (*eit).getPromedioCalificaciones() << endl;
            }
            cout << "Persona eliminada exitosamente." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        archivo.close();
    }
    else {
        cout << "No se encontro una persona con el DPI ingresado." << endl;
    }
}

/************************************************************eliminarEstudiante()******************************************************************/
void eliminarEstudiante(const string& nombreArchivo) {
    string carnet;
    gotoxy(45, 1);
    cout << "Eliminar Estudiante:" << endl << endl;
    cout << "Ingrese el carnet del estudiante a eliminar: ";
    getline(cin, carnet);

    vector<estudiante>::iterator it = listaEstudiantes.begin();
    bool encontrado = false;
    while (it != listaEstudiantes.end()) {
        if ((*it).getNumeroCarnet() == carnet) {
            encontrado = true;
            break;
        }
        ++it;
    }

    if (encontrado) {
        listaEstudiantes.erase(it);

        ofstream archivo(nombreArchivo.c_str(), ios::out);
        if (archivo.is_open()) {
            for (vector<persona>::iterator pit = listaPersonas.begin(); pit != listaPersonas.end(); ++pit) {
                archivo << "1," << (*pit).getNombre() << "," << (*pit).getApellido() << "," << (*pit).getOcupacion() << "," << (*pit).getEdad() << "," << (*pit).getDPI() << endl;
            }
            for (vector<estudiante>::iterator eit = listaEstudiantes.begin(); eit != listaEstudiantes.end(); ++eit) {
                archivo << "2," << (*eit).getNombre() << "," << (*eit).getApellido() << "," << (*eit).getEdad() << "," << (*eit).getNumeroCarnet() << "," << (*eit).getPromedioCalificaciones() << endl;
            }
            cout << "Estudiante eliminado exitosamente." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        archivo.close();
    }
    else {
        cout << "No se encontro un estudiante con el carnet ingresado." << endl;
    }
}
/************************************************************buscarPersonaPorDPI()******************************************************************/
void buscarPersonaPorDPI(const string& nombreArchivo) {
    int dpi;
    gotoxy(45, 1);
    cout << "Buscar Persona:" << endl << endl;
    cout << "Ingrese el DPI de la persona a buscar: ";
    cin >> dpi;
    cin.ignore();

    bool encontrado = false;
    ifstream archivo(nombreArchivo.c_str());
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string tipo, nombre, apellido, ocupacion;
            int edad, dpiActual;
            getline(iss, tipo, ',');
            if (tipo == "1") {
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, ocupacion, ',');
                iss >> edad;
                iss.ignore();
                iss >> dpiActual;
                if (dpiActual == dpi) {
                    encontrado = true;
                    persona p(nombre, apellido, ocupacion, edad, dpiActual);
                    p.mostrarInfo();
                    break;
                }
            }
        }
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();

    if (!encontrado) {
        cout << "No se encontro una persona con el DPI ingresado." << endl;
    }
}

/***********************************************************buscarEstudiantePorCarnet()******************************************************************/
void buscarEstudiantePorCarnet(const string& nombreArchivo) {
    string carnet;
    gotoxy(45, 1);
    cout << "Buscar Estudiante:" << endl << endl;
    cout << "Ingrese el carnet del estudiante a buscar: ";
    getline(cin, carnet);

    bool encontrado = false;
    ifstream archivo(nombreArchivo.c_str());
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string tipo, nombre, apellido;
            int edad;
            double promedio;
            string carnetActual;
            getline(iss, tipo, ',');
            if (tipo == "2") {
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                iss >> edad;
                iss.ignore();
                getline(iss, carnetActual, ',');
                iss >> promedio;
                if (carnetActual == carnet) {
                    encontrado = true;
                    estudiante e(nombre, apellido, edad, carnetActual, promedio);
                    e.mostrarInfo();
                    break;
                }
            }
        }
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();

    if (!encontrado) {
        cout << "No se encontro un estudiante con el carnet ingresado." << endl;
    }
}
/************************************************************leerTodo()******************************************************************/
void leerTodo(const string& nombreArchivo) {
    gotoxy(45, 1);
    cout << "Informacion del archivo:" << endl << endl;
    ifstream archivo(nombreArchivo.c_str());
    if (archivo.is_open()) {
        string linea;
        cout << "Personas:" << endl;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string tipo, nombre, apellido, ocupacion;
            int edad, dpi;
            getline(iss, tipo, ',');
            if (tipo == "1") {
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, ocupacion, ',');
                iss >> edad;
                iss.ignore();
                iss >> dpi;
                persona p(nombre, apellido, ocupacion, edad, dpi);
                p.mostrarInfo();
            }
        }

        cout << "Estudiantes:" << endl;
        archivo.clear(); // Limpiar el estado de error del archivo
        archivo.seekg(0, ios::beg); // Regresar al inicio del archivo

        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string tipo, nombre, apellido;
            int edad;
            double promedio;
            string carnet;
            getline(iss, tipo, ',');
            if (tipo == "2") {
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                iss >> edad;
                iss.ignore();
                getline(iss, carnet, ',');
                iss >> promedio;
                estudiante e(nombre, apellido, edad, carnet, promedio);
                e.mostrarInfo();
            }
        }
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.close();
}


