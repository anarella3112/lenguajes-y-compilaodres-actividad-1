#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

bool validarPosicionPiezas(const std::string& campo) {
    std::stringstream ss(campo);
    std::string fila;
    int contadorFilas = 0;

    while (std::getline(ss, fila, '/')) {
        int suma = 0;
        for (char c : fila) {
            if (isdigit(c)) {
                suma += c - '0';
            } else if (std::string("rnbqkpRNBQKP").find(c) != std::string::npos) {
                suma += 1;
            } else {
                std::cout << "❌ Carácter inválido en campo de posiciones: " << c << std::endl;
                return false;
            }
        }
        if (suma != 8) {
            std::cout << "❌ Fila con número incorrecto de columnas: " << fila << std::endl;
            return false;
        }
        contadorFilas++;
    }

    if (contadorFilas != 8) {
        std::cout << "❌ El campo de posiciones debe tener 8 filas.\n";
        return false;
    }

    return true;
}

bool validarTurno(const std::string& campo) {
    if (campo != "w" && campo != "b") {
        std::cout << "❌ El campo de turno debe ser 'w' o 'b'. Valor recibido: " << campo << std::endl;
        return false;
    }
    return true;
}

bool validarEnroque(const std::string& campo) {
    if (campo == "-") return true;
    std::string permitidos = "KQkq";
    for (char c : campo) {
        if (permitidos.find(c) == std::string::npos) {
            std::cout << "❌ Carácter inválido en campo de enroque: " << c << std::endl;
            return false;
        }
    }
    return true;
}

bool validarCapturaPaso(const std::string& campo) {
    if (campo == "-") return true;
    if (!std::regex_match(campo, std::regex("^[a-h][36]$"))) {
        std::cout << "❌ Campo de captura al paso inválido. Ejemplo válido: e3 o d6. Valor recibido: " << campo << std::endl;
        return false;
    }
    return true;
}

bool validarNumero(const std::string& campo, const std::string& nombreCampo) {
    if (!std::regex_match(campo, std::regex("^\\d+$"))) {
        std::cout << "❌ El campo de " << nombreCampo << " debe ser un número entero positivo. Valor recibido: " << campo << std::endl;
        return false;
    }
    return true;
}

bool esFENValida(const std::string& fen) {
    std::stringstream ss(fen);
    std::vector<std::string> campos;
    std::string temp;

    while (ss >> temp) {
        campos.push_back(temp);
    }

    if (campos.size() != 6) {
        std::cout << "❌ La cadena FEN debe tener exactamente 6 campos separados por espacios.\n";
        return false;
    }

    bool valid = true;
    valid &= validarPosicionPiezas(campos[0]);
    valid &= validarTurno(campos[1]);
    valid &= validarEnroque(campos[2]);
    valid &= validarCapturaPaso(campos[3]);
    valid &= validarNumero(campos[4], "medio-movimientos");
    valid &= validarNumero(campos[5], "número de jugada");

    return valid;
}

int main() {
    std::string entradaFEN;
    std::cout << "Introduce una cadena en notación FEN:\n";
    std::getline(std::cin, entradaFEN);

    if (esFENValida(entradaFEN)) {
        std::cout << "✅ La cadena FEN es válida.\n";
    } else {
        std::cout << "⚠️  Revisa los errores indicados arriba.\n";
    }

    return 0;
}
