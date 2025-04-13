#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// Genera la fila n del triángulo de Pascal
vector<int> generarFilaPascal(int n) {
    vector<int> fila(n + 1, 1);
    for (int k = 1; k < n; ++k) {
        fila[k] = fila[k - 1] * (n - k + 1) / k;
    }
    return fila;
}

// Imprime todas las filas del triángulo de Pascal desde 0 hasta n
void mostrarTrianguloPascal(int n) {
    cout << "\n🔺 Triángulo de Pascal hasta n = " << n << ":\n";
    for (int i = 0; i <= n; ++i) {
        vector<int> fila = generarFilaPascal(i);
        cout << setw((n - i) * 2) << "";  // Espaciado para formato de triángulo
        for (int num : fila) {
            cout << setw(4) << num;
        }
        cout << endl;
    }
}

// Muestra el polinomio (x+1)^n
void mostrarPolinomio(const vector<int>& coef) {
    int n = coef.size() - 1;
    cout << "\n📐 Polinomio generado: (x+1)^" << n << " = ";
    for (int i = 0; i <= n; ++i) {
        if (coef[i] == 0) continue;
        if (i > 0) cout << " + ";
        cout << coef[i];
        if (n - i > 0) {
            cout << "x";
            if (n - i > 1) cout << "^" << (n - i);
        }
    }
    cout << endl;
}

// Muestra los pasos del cálculo de f(x)
void evaluarYMostrarPasos(const vector<int>& coef, int x) {
    int n = coef.size() - 1;
    long long resultado = 0;
    cout << "\n📊 Evaluación de f(" << x << ") = (x+1)^" << n << " por pasos:\n";
    for (int i = 0; i <= n; ++i) {
        int exponente = n - i;
        long long termino = coef[i] * pow(x, exponente);
        cout << coef[i] << " * " << x << "^" << exponente << " = " << termino << endl;
        resultado += termino;
    }
    cout << "\n✅ Resultado final: f(" << x << ") = " << resultado << endl;
}

int main() {
    int n, x;

    cout << "📥 Ingrese el valor de n (entero no negativo): ";
    cin >> n;

    if (n < 0) {
        cout << "❌ n debe ser un entero no negativo.\n";
        return 1;
    }

    mostrarTrianguloPascal(n); // Paso 1: Mostrar el triángulo de Pascal

    vector<int> coef = generarFilaPascal(n);

    mostrarPolinomio(coef);   // Paso 2: Mostrar el polinomio

    cout << "\n🔢 Ingrese el valor de x para evaluar f(x): ";
    cin >> x;

    evaluarYMostrarPasos(coef, x);  // Paso 3: Evaluar f(x)

    return 0;
}
