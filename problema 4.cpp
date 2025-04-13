#include <iostream>
#include <string>
#include <algorithm>

// Función auxiliar para convertir una cadena a minúsculas
std::string aMinusculas(std::string texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

int main() {
    std::string C, E;

    // Entrada del usuario
    std::cout << "Ingrese la cadena (C): ";
    std::getline(std::cin, C);

    std::cout << "Ingrese la palabra a buscar (E): ";
    std::cin >> E;

    // Convertir ambas a minúsculas para comparación sin distinción de mayúsculas
    std::string C_min = aMinusculas(C);
    std::string E_min = aMinusculas(E);

    int count = 0;
    size_t pos = C_min.find(E_min);

    while (pos != std::string::npos) {
        std::cout << "Encontrado en la posición: " << pos << std::endl;
        count++;
        pos = C_min.find(E_min, pos + 1);
    }

    std::cout << "La palabra '" << E << "' aparece " << count << " veces en la cadena (sin distinguir mayúsculas)." << std::endl;

    return 0;
}
