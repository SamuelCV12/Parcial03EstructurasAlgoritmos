#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Estructura para representar un curso
struct Curso {
    string nombre;
    double nota;
    int creditos;
};

// Estructura para representar un estudiante
struct Estudiante {
    string nombre;
    string id;
    vector<Curso> cursos;
};

// Funcion para calcular el promedio ponderado
double calcularPromedioPonderado(const Estudiante& est) {
    double sumaPonderada = 0;
    int totalCreditos = 0;

    for (const auto& curso : est.cursos) {
        sumaPonderada += curso.nota * curso.creditos;
        totalCreditos += curso.creditos;
    }

    if (totalCreditos == 0) return 0;
    return sumaPonderada / totalCreditos;
}

// Funcion para encontrar al estudiante con mejor desempeno
Estudiante mejorEstudiante(const vector<Estudiante>& lista) {
    Estudiante mejor;
    double mejorPromedio = -1;

    for (const auto& est : lista) {
        double promedio = calcularPromedioPonderado(est);
        if (promedio > mejorPromedio) {
            mejorPromedio = promedio;
            mejor = est;
        }
    }
    return mejor;
}

// Limpia el buffer de entrada
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Funcion para pedir un numero entero positivo validado
int pedirEnteroPositivo(const string& mensaje) {
    string entrada;
    int valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        bool esEntero = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esEntero = false;
                break;
            }
        }

        if (!esEntero || entrada.empty()) {
            cout << "Error: debe ingresar un numero entero positivo." << endl;
            continue;
        }

        try {
            valor = stoi(entrada);
            if (valor > 0) {
                return valor;
            } else {
                cout << "Error: el numero debe ser mayor que cero." << endl;
            }
        } catch (...) {
            cout << "Error: entrada no valida." << endl;
        }
    }
}

// Funcion para pedir una nota valida (0.0 a 5.0)
double pedirNota() {
    double nota;
    while (true) {
        cout << "Nota obtenida (0.0 a 5.0): ";
        if (cin >> nota && nota >= 0.0 && nota <= 5.0) {
            limpiarEntrada();
            return nota;
        } else {
            cout << "Error: la nota debe estar entre 0.0 y 5.0." << endl;
            limpiarEntrada();
        }
    }
}

int main() {
    vector<Estudiante> estudiantes;
    int numEstudiantes;

    cout << "===== Registro de Estudiantes =====" << endl;

    numEstudiantes = pedirEnteroPositivo("Ingrese la cantidad de estudiantes: ");

    for (int i = 0; i < numEstudiantes; i++) {
        Estudiante est;
        cout << "\n--- Estudiante " << i + 1 << " ---" << endl;

        cout << "Nombre: ";
        getline(cin, est.nombre);
        while (est.nombre.empty()) {
            cout << "Error: el nombre no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, est.nombre);
        }

        cout << "ID: ";
        getline(cin, est.id);
        while (est.id.empty()) {
            cout << "Error: el ID no puede estar vacio. Ingrese nuevamente: ";
            getline(cin, est.id);
        }

        int numCursos = pedirEnteroPositivo("Cantidad de cursos: ");

        for (int j = 0; j < numCursos; j++) {
            Curso curso;
            cout << "\nCurso " << j + 1 << ":" << endl;

            cout << "Nombre del curso: ";
            getline(cin, curso.nombre);
            while (curso.nombre.empty()) {
                cout << "Error: el nombre del curso no puede estar vacio. Ingrese nuevamente: ";
                getline(cin, curso.nombre);
            }

            curso.nota = pedirNota();
            curso.creditos = pedirEnteroPositivo("Creditos del curso: ");

            est.cursos.push_back(curso);
        }

        estudiantes.push_back(est);
    }

    // Calcular el mejor estudiante
    Estudiante top = mejorEstudiante(estudiantes);
    double promTop = calcularPromedioPonderado(top);

    cout << "\n===== Resultados =====" << endl;
    cout << "El estudiante con mejor desempeno es: " << top.nombre << endl;
    cout << "ID: " << top.id << endl;
    cout << "Promedio ponderado: " << promTop << endl;

    cout << "\nFin del programa." << endl;
    return 0;
}
