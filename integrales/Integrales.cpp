#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>
using namespace std;

// Definir una estructura para representar un término de la integral
struct TerminoIntegral {
    int coeficiente;
    int exponente;
    char operacion;
};

// Declaro las funciones
void separarTerminos(TerminoIntegral terminos[], int intervalo_b, int intervalo_a, string terminos_y_signos, string intervalos);

void integrarPrimerPaso(TerminoIntegral terminos[], int intervalo_b, int intervalo_a, string terminos_y_signos, string intervalos);

void reemplazarValores(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

void resolverTerminos(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

void resolverTerminosMultiplicando(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

void comunDenominadorB(TerminoIntegral terminos[], int intervalo_b);

void comunDenominadorA(TerminoIntegral terminos[], int intervalo_a);

void hallarFraccionB(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

void hallarFraccionA(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

void hallarValorFinal(TerminoIntegral terminos[], int intervalo_b, int intervalo_a);

int main() {
    TerminoIntegral terminos[3]; // Un arreglo de 3 términos para almacenar la integral
    int intervalo_b, intervalo_a;

    string terminos_y_signos;

    cout << "Ingresar 3 terminos de la integral junto a sus exponentes (por separado):" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Termino " << i + 1 << endl;

        cout << "Coeficiente o constante: ";
        cin >> terminos[i].coeficiente;

        cout << "Exponente (ingresar 0 si es una constante): ";
        cin >> terminos[i].exponente;

        if (i < 2) {
            char operacion;
            cout << "Operacion (+ o -): ";
            cin >> operacion;
            terminos[i].operacion = operacion;
        }
        if (terminos[i].exponente == 0) {
            // Si el exponente es 0, solo agregar el coeficiente sin "x"
            terminos_y_signos += to_string(terminos[i].coeficiente);
        }
        else if (terminos[i].exponente == 1) {
            // Si el exponente es 1, solo agregar "x" sin "^1"
            terminos_y_signos += to_string(terminos[i].coeficiente) + "x";
        }
        else {
            terminos_y_signos += to_string(terminos[i].coeficiente) + "x^" + to_string(terminos[i].exponente);
        }
        if (i < 2) {
            char operacion = terminos[i].operacion;
            terminos_y_signos += " " + string(1, operacion) + " ";
        }
    }

    cout << "Ingresar los intervalos de b y a:" << endl;
    cout << "Intervalo de b: ";
    cin >> intervalo_b;
    cout << "Intervalo de a: ";
    cin >> intervalo_a;

    // PRUEBO EL METODO SLEEP
    cout << "Procesando el ejercicio... \n";
    Sleep(3000);
    system("cls");


    // muestra intervalos en corchetes [b,a]
    string intervalos = "[" + to_string(intervalo_b) + ", " + to_string(intervalo_a) + "]";

    // Mostrar la información completa
    cout << "Funcion a integrar: (" << terminos_y_signos << ") [" << intervalo_b << ", " << intervalo_a << "] dx" << endl;


    separarTerminos(terminos, intervalo_b, intervalo_a, terminos_y_signos, intervalos);

    // Llamar a una función y pasar los términos y los intervalos
    integrarPrimerPaso(terminos, intervalo_b, intervalo_a, terminos_y_signos, intervalos);

    // Llamar a la función para reemplazar los intervalos
    reemplazarValores(terminos, intervalo_b, intervalo_a);

    // Llamar a la función para resolver los términos con potencia
    resolverTerminos(terminos, intervalo_b, intervalo_a);

    // Llamar a la función para resolver los términos multiplicando
    resolverTerminosMultiplicando(terminos, intervalo_b, intervalo_a);

   // comunDenominadorB(terminos, intervalo_b);

   // comunDenominadorA(terminos, intervalo_a);

    hallarFraccionB(terminos, intervalo_b, intervalo_a);

    hallarFraccionA(terminos, intervalo_b, intervalo_a);

    hallarValorFinal(terminos, intervalo_b, intervalo_a);

    return 0;
}


void separarTerminos(TerminoIntegral terminos[], int intervalo_b, int intervalo_a, string terminos_y_signos, string intervalos)
{
    cout << "Separo constantes: (";

    for (int i = 0; i < 3; i++) {
        cout << "(";

        if (terminos[i].coeficiente != 1) {
            cout << terminos[i].coeficiente;
        }
        else {
            cout << "1";
        }

        if (terminos[i].exponente == 1) {
            cout << "S x";
        }
        else if (terminos[i].exponente != 0) {
            cout << " S x^" << terminos[i].exponente;
        }
        else {
            cout << " S";
        }

        cout << " dx)";

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ")" << endl;

}

// Defino la función para calcular la integral y mostrarla
void integrarPrimerPaso(TerminoIntegral terminos[], int intervalo_b, int intervalo_a, string terminos_y_signos, string intervalos) {
    cout << "Eleva exponente +1: (";

    // Reemplazar 'x' con "a" y "b" y agregar el denominador como fracción
    for (int i = 0; i < 3; i++) {
        int nuevoExponente = terminos[i].exponente + 1;

        if (nuevoExponente > 1) {
            cout << terminos[i].coeficiente << "x^" << nuevoExponente << "/" << nuevoExponente;
        }
        else if (nuevoExponente == 1) {
            cout << terminos[i].coeficiente << "x";
        }
        else {
            cout << terminos[i].coeficiente;
        }

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ") [" << intervalos << "]" << endl;
}

// Defino la función para reemplazar los intervalos en lugar de x
void reemplazarValores(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    cout << "Regla de Barrow: (";

    // Reemplazar 'x' con el valor de intervalo_b y agregar el denominador como fracción
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            // Si el exponente es 0, solo multiplicar el coeficiente por el intervalo
            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }
            cout << "(" << intervalo_b << ")";
        }
        else {
            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }
            int nuevoExponente = terminos[i].exponente + 1;
            cout << "(" << intervalo_b << "^" << nuevoExponente << "/" << nuevoExponente << ")";
        }

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ")  -  (";

    // Reemplazar 'x' con el valor de intervalo_a y agregar el denominador como fracción
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            // Si el exponente es 0, solo multiplicar el coeficiente por el intervalo
            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }
            cout << "(" << intervalo_a << ")";
        }
        else {
            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }
            int nuevoExponente = terminos[i].exponente + 1;
            cout << "(" << intervalo_a << "^" << nuevoExponente << "/" << nuevoExponente << ")";
        }

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ")" << endl;
}

// Defino la función para resolver los términos con potencia
// Función para resolver los términos con potencia
void resolverTerminos(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    cout << "Resuelvo parentesis de b y a: (";

    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            // Si el exponente es 0, multiplicar el coeficiente por el intervalo_b en el primer paréntesis
            int resultado = terminos[i].coeficiente * intervalo_b;
            if (resultado < 0) {
                cout << "(" << resultado << ")";
            }
            else {
                cout << resultado;
            }
        }
        else {
            int nuevoExponente = terminos[i].exponente + 1;
            int numerador = pow(intervalo_b, nuevoExponente);
            int denominador = nuevoExponente;

            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }

            if (denominador != 1) {
                if (numerador < 0) {
                    cout << "(" << numerador << "/" << denominador << ")";
                }
                else {
                    cout << numerador << "/" << denominador;
                }
            }
            else {
                if (numerador < 0) {
                    cout << "(" << numerador << ")";
                }
                else {
                    cout << numerador;
                }
            }
        }

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ") - (";

    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            // Si el exponente es 0, multiplicar el coeficiente por el intervalo_a en el segundo paréntesis
            int resultado = terminos[i].coeficiente * intervalo_a;
            if (resultado < 0) {
                cout << "(" << resultado << ")";
            }
            else {
                cout << resultado;
            }
        }
        else {
            int nuevoExponente = terminos[i].exponente + 1;
            int numerador = pow(intervalo_a, nuevoExponente);
            int denominador = nuevoExponente;

            if (terminos[i].coeficiente != 1) {
                cout << terminos[i].coeficiente << "*";
            }

            if (denominador != 1) {
                if (numerador < 0) {
                    cout << "(" << numerador << "/" << denominador << ")";
                }
                else {
                    cout << numerador << "/" << denominador;
                }
            }
            else {
                if (numerador < 0) {
                    cout << "(" << numerador << ")";
                }
                else {
                    cout << numerador;
                }
            }
        }

        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }

    cout << ")" << endl;
}

// Función para resolver los términos multiplicando
void resolverTerminosMultiplicando(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    vector<string> resultado_b(3, "");  // Almacena los resultados del paréntesis b
    vector<string> resultado_a(3, "");  // Almacena los resultados del paréntesis a

    // Calcular los resultados del paréntesis b
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            int resultado = terminos[i].coeficiente * intervalo_b;
            if (resultado < 0) {
                resultado_b[i] = "(" + to_string(resultado) + ")";
            }
            else {
                resultado_b[i] = to_string(resultado);
            }
        }
        else {
            int nuevoExponente = terminos[i].exponente + 1;
            int numerador = terminos[i].coeficiente * pow(intervalo_b, nuevoExponente);
            int denominador = nuevoExponente;

            if (denominador != 1) {
                if (numerador < 0) {
                    resultado_b[i] = "(" + to_string(numerador) + "/" + to_string(denominador) + ")";
                }
                else {
                    resultado_b[i] = to_string(numerador) + "/" + to_string(denominador);
                }
            }
            else {
                if (numerador < 0) {
                    resultado_b[i] = "(" + to_string(numerador) + ")";
                }
                else {
                    resultado_b[i] = to_string(numerador);
                }
            }
        }
    }

    // Calcular los resultados del paréntesis a
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente == 0) {
            int resultado = terminos[i].coeficiente * intervalo_a;
            if (resultado < 0) {
                resultado_a[i] = "(" + to_string(resultado) + ")";
            }
            else {
                resultado_a[i] = to_string(resultado);
            }
        }
        else {
            int nuevoExponente = terminos[i].exponente + 1;
            int numerador = terminos[i].coeficiente * pow(intervalo_a, nuevoExponente);
            int denominador = nuevoExponente;

            if (denominador != 1) {
                if (numerador < 0) {
                    resultado_a[i] = "(" + to_string(numerador) + "/" + to_string(denominador) + ")";
                }
                else {
                    resultado_a[i] = to_string(numerador) + "/" + to_string(denominador);
                }
            }
            else {
                if (numerador < 0) {
                    resultado_a[i] = "(" + to_string(numerador) + ")";
                }
                else {
                    resultado_a[i] = to_string(numerador);
                }
            }
        }
    }

    // Mostrar los resultados del paréntesis b
    cout << "(";
    for (int i = 0; i < 3; i++) {
        cout << resultado_b[i];
        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }
    cout << ")";

    // Mostrar el signo de resta entre paréntesis
    cout << " - ";

    // Mostrar los resultados del paréntesis a
    cout << "(";
    for (int i = 0; i < 3; i++) {
        cout << resultado_a[i];
        if (i < 2) {
            char operacion = terminos[i].operacion;
            cout << " " << operacion << " ";
        }
    }
    cout << ")" << endl;
}


void comunDenominadorB(TerminoIntegral terminos[], int intervalo_b) {
    int comun_denominador = 1; // Inicializamos el común denominador en 1

    // Recorremos los términos en el paréntesis b
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente != 0) {
            int nuevoExponente = terminos[i].exponente + 1;
            int denominador = nuevoExponente;

            // Calculamos el máximo común denominador entre el denominador actual y el común denominador
            int a = denominador;
            int b = comun_denominador;
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }

            // Actualizamos el común denominador usando la fórmula del mínimo común múltiplo
            comun_denominador = (denominador * comun_denominador) / a;
        }
    }

    // Mostramos el común denominador
   // cout << "COMUN DENOMINADOR B: " << comun_denominador << endl;
}

void comunDenominadorA(TerminoIntegral terminos[], int intervalo_a) {
    int comun_denominador = 1; // Inicializamos el común denominador en 1

    // Recorremos los términos en el paréntesis a
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente != 0) {
            int nuevoExponente = terminos[i].exponente + 1;
            int denominador = nuevoExponente;

            // Calculamos el máximo común denominador entre el denominador actual y el común denominador
            int a = denominador;
            int b = comun_denominador;
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }

            // Actualizamos el común denominador usando la fórmula del mínimo común múltiplo
            comun_denominador = (denominador * comun_denominador) / a;
        }
    }

    // Mostramos el común denominador para el paréntesis de "a"
    //cout << "COMUN DENOMINADOR PARA A: " << comun_denominador << endl;
}

int calcularMCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void hallarFraccionB(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    int comun_denominador = 1;

    // Calcular el común denominador
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente != 0) {
            int nuevoExponente = terminos[i].exponente + 1;
            int denominador = nuevoExponente;
            comun_denominador = (denominador * comun_denominador) / calcularMCD(denominador, comun_denominador);
        }
    }
    // Calcular los numeradores y denominadores de las fracciones
    int numerador1 = terminos[0].coeficiente;
    int denominador1 = terminos[0].exponente + 1;

    int numerador2 = terminos[1].coeficiente;
    int denominador2 = terminos[1].exponente + 1;

    int numerador3 = terminos[2].coeficiente;
    int denominador3 = terminos[2].exponente + 1;
    


    // Obtener los signos de las operaciones entre los términos
    char signo1 = terminos[0].operacion;
    char signo2 = terminos[1].operacion;
  
    
    int resultadonum1 = (comun_denominador / denominador1) * numerador1;
    int resultadonum2 = (comun_denominador / denominador2) * numerador2;
    int resultadonum3 = (comun_denominador / denominador3) * numerador3;


    /*
        
         cout << "---------------------------------" << endl;
    cout << "Numerador1: " << resultadonum1 << endl;
    cout << "Numerador2: " << resultadonum2 << endl;
    cout << "Numerador3: " << resultadonum3 << endl;
    
    */
   

    int resultado_numerador = 0;

    resultado_numerador += resultadonum1;
    if (signo1 == '+') {

        resultado_numerador += resultadonum2;

    }
    else {

        resultado_numerador -= resultadonum2;
    }

    if (signo2 == '+') {

        resultado_numerador += resultadonum3;
    }

    else {

        resultado_numerador -= resultadonum3;
    }

    


    // Mostrar el resultado
    cout << "Resultado del parentesis de b: (" << resultado_numerador << "/" << comun_denominador << ")" << endl;


}


void hallarFraccionA(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    int comun_denominador = 1;

    // Calcular el común denominador
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente != 0) {
            int nuevoExponente = terminos[i].exponente + 1;
            int denominador = nuevoExponente;
            comun_denominador = (denominador * comun_denominador) / calcularMCD(denominador, comun_denominador);
        }
    }

    // Calcular los numeradores y denominadores de las fracciones
    int numerador1 = terminos[0].coeficiente * pow(intervalo_a, terminos[0].exponente + 1);
    int denominador1 = terminos[0].exponente + 1;

    int numerador2 = terminos[1].coeficiente * pow(intervalo_a, terminos[1].exponente + 1);
    int denominador2 = terminos[1].exponente + 1;

    int numerador3 = terminos[2].coeficiente * pow(intervalo_a, terminos[2].exponente + 1);
    int denominador3 = terminos[2].exponente + 1;

  

    // Obtener los signos de las operaciones entre los términos
    char signo1 = terminos[0].operacion;
    char signo2 = terminos[1].operacion;

    int resultadonum1 = (comun_denominador / denominador1) * numerador1;
    int resultadonum2 = (comun_denominador / denominador2) * numerador2;
    int resultadonum3 = (comun_denominador / denominador3) * numerador3;

   

    /*
        
        cout << "---------------------------------" << endl;
    cout << "Numerador1: " << resultadonum1 << endl;
    cout << "Numerador2: " << resultadonum2 << endl;
    cout << "Numerador3: " << resultadonum3 << endl;
    
    */
    
   

    int resultado_numerador = 0;

    resultado_numerador += resultadonum1;
    if (signo1 == '+') {
        resultado_numerador += resultadonum2;
    }
    else {
        resultado_numerador -= resultadonum2;
    }

    if (signo2 == '+') {
        resultado_numerador += resultadonum3;
    }
    else {
        resultado_numerador -= resultadonum3;
    }

    // Mostrar el resultado del paréntesis de a
    cout << "Resultado del parentesis de a: (" << resultado_numerador << "/" << comun_denominador << ")" << endl;
}


void hallarValorFinal(TerminoIntegral terminos[], int intervalo_b, int intervalo_a) {
    int comun_denominador = 1;

    // Calcular el común denominador para los paréntesis B y A
    for (int i = 0; i < 3; i++) {
        if (terminos[i].exponente != 0) {
            int nuevoExponente = terminos[i].exponente + 1;
            int denominador = nuevoExponente;
            comun_denominador = (denominador * comun_denominador) / calcularMCD(denominador, comun_denominador);
        }
    }

    // Variables para los numeradores de los paréntesis B y A
    int numeradorB = 0;
    int numeradorA = 0;

  

   
    // Calcular los numeradores de los paréntesis B
    for (int i = 0; i < 3; i++) {
        int numeradorTerm = terminos[i].coeficiente;
        int denominadorTerm = terminos[i].exponente + 1;
        int resultadoNumerador = (comun_denominador / denominadorTerm) * numeradorTerm;

        if (i == 0) {
            numeradorB += resultadoNumerador;  
        }
        else {
            if (terminos[i - 1].operacion == '+') {
                numeradorB += resultadoNumerador;  
            }
            else {
                numeradorB -= resultadoNumerador;  
            }
        }
        
    }
    //cout << "resultadoNumeradorB: " << numeradorB << endl;
   

    /* --------------------------------------------------------------------- */
// Calcular los numeradores de los paréntesis A
    for (int i = 0; i < 3; i++) {
        int numeradorTerm = terminos[i].coeficiente * pow(intervalo_a, terminos[i].exponente + 1);
        int denominadorTerm = terminos[i].exponente + 1;
        int resultadoNumerador = (comun_denominador / denominadorTerm) * numeradorTerm;

        if (i == 0) {
            numeradorA += resultadoNumerador;
        }
        else {
            if (terminos[i - 1].operacion == '+') {
                numeradorA += resultadoNumerador;
            }
            else {
                numeradorA -= resultadoNumerador;
            }
        }
    }

    //cout << "resultadoNumeradorA: " << numeradorA << endl;

   

    /* --------------------------------------------------------------------------- */

    // Realizar la resta y mostrar el resultado
    int resultado_numerador_final = numeradorB - numeradorA;

    cout << "Resultado Final: (" << resultado_numerador_final << "/" << comun_denominador << ")" << endl;
}
