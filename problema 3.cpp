#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stack>
#include <cctype>
#include <map>
#include <iomanip>

// Funciones matemáticas aceptadas
std::map<std::string, double(*)(double)> funciones = {
    {"sin", std::sin},
    {"cos", std::cos},
    {"tan", std::tan},
    {"log", std::log},
    {"log10", std::log10},
    {"sqrt", std::sqrt},
    {"abs", std::fabs}
};

// Precedencia de operadores
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Aplica operador entre dos valores
double aplicarOperador(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Error: División por cero.");
            return a / b;
    }
    return 0;
}

// Aplica función matemática
double aplicarFuncion(const std::string& func, double valor) {
    if (funciones.count(func)) {
        return funciones[func](valor);
    } else {
        throw std::runtime_error("Función no reconocida: " + func);
    }
}

// Evalúa la expresión matemática
double evaluarExpresion(const std::string& expr) {
    std::stack<double> valores;
    std::stack<char> ops;
    std::stack<std::string> funcStack;

    size_t i = 0;
    while (i < expr.length()) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // Funciones (como sin, cos, etc.)
        if (isalpha(expr[i])) {
            std::string nombreFuncion;
            while (i < expr.length() && isalpha(expr[i])) {
                nombreFuncion += expr[i++];
            }
            funcStack.push(nombreFuncion);
            if (expr[i] == '(') {
                ops.push('(');
                i++;
            }
        }
        // Paréntesis izquierdo
        else if (expr[i] == '(') {
            ops.push(expr[i]);
            i++;
        }
        // Paréntesis derecho
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = valores.top(); valores.pop();
                double a = valores.top(); valores.pop();
                char op = ops.top(); ops.pop();
                valores.push(aplicarOperador(a, b, op));
            }
            if (!ops.empty()) ops.pop(); // eliminar '('

            // Si había una función antes del paréntesis
            if (!funcStack.empty()) {
                double val = valores.top(); valores.pop();
                std::string func = funcStack.top(); funcStack.pop();
                valores.push(aplicarFuncion(func, val));
            }

            i++;
        }
        // Número (soporta notación científica)
        else if (std::isdigit(expr[i]) || expr[i] == '.' || 
                 ((expr[i] == '-' || expr[i] == '+') && (i == 0 || expr[i - 1] == '('))) {
            std::string numero;
            bool hayE = false;
            while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'E' || expr[i] == 'e' || 
                   (expr[i] == '-' || expr[i] == '+') && (hayE))) {
                if (expr[i] == 'E' || expr[i] == 'e') hayE = true;
                numero += expr[i++];
            }
            valores.push(std::stod(numero));
        }
        // Operadores
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (!ops.empty() && precedencia(ops.top()) >= precedencia(expr[i])) {
                double b = valores.top(); valores.pop();
                double a = valores.top(); valores.pop();
                char op = ops.top(); ops.pop();
                valores.push(aplicarOperador(a, b, op));
            }
            ops.push(expr[i]);
            i++;
        } else {
            throw std::runtime_error(std::string("Carácter no reconocido: ") + expr[i]);
        }
    }

    while (!ops.empty()) {
        double b = valores.top(); valores.pop();
        double a = valores.top(); valores.pop();
        char op = ops.top(); ops.pop();
        valores.push(aplicarOperador(a, b, op));
    }

    return valores.top();
}

int main() {
    std::string expresion;
    std::cout << "Ingrese la expresión a evaluar (puede usar sin, cos, log, sqrt, notación científica, etc.):\n";
    std::getline(std::cin, expresion);

    try {
        double resultado = evaluarExpresion(expresion);
        std::cout << "Resultado: " << std::scientific << std::setprecision(10) << resultado << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
