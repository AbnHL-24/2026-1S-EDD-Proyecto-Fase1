#include <iostream>
#include <limits>
#include <string>

#include "ArbolAVL.h"
#include "ListaEnlazada.h"
#include "ListaEnlazadaOrdenada.h"

namespace {
void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void imprimirProducto(const Producto& producto) {
    std::cout << "Nombre: " << producto.obtenerNombre() << '\n';
    std::cout << "Codigo: " << producto.obtenerCodigoBarra() << '\n';
    std::cout << "Categoria: " << producto.obtenerCategoria() << '\n';
    std::cout << "Fecha caducidad: " << producto.obtenerFechaCaducidad() << '\n';
    std::cout << "Marca: " << producto.obtenerMarca() << '\n';
    std::cout << "Precio: " << producto.obtenerPrecio() << '\n';
    std::cout << "Stock: " << producto.obtenerStock() << '\n';
}

Producto leerProductoDesdeConsola() {
    std::string nombre;
    std::string codigoBarra;
    std::string categoria;
    std::string fechaCaducidad;
    std::string marca;
    double precio = 0.0;
    int stock = 0;

    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Codigo de barras: ";
    std::getline(std::cin, codigoBarra);
    std::cout << "Categoria: ";
    std::getline(std::cin, categoria);
    std::cout << "Fecha caducidad (YYYY-MM-DD): ";
    std::getline(std::cin, fechaCaducidad);
    std::cout << "Marca: ";
    std::getline(std::cin, marca);

    std::cout << "Precio: ";
    std::cin >> precio;
    if (!std::cin.good()) {
        limpiarEntrada();
        return Producto(nombre, codigoBarra, categoria, fechaCaducidad, marca, -1.0, stock);
    }

    std::cout << "Stock: ";
    std::cin >> stock;
    if (!std::cin.good()) {
        limpiarEntrada();
        return Producto(nombre, codigoBarra, categoria, fechaCaducidad, marca, precio, -1);
    }

    limpiarEntrada();
    return Producto(nombre, codigoBarra, categoria, fechaCaducidad, marca, precio, stock);
}

void mostrarMenu() {
    std::cout << "\n===== Mini Catalogo (Listas + AVL) =====\n";
    std::cout << "1. Agregar producto\n";
    std::cout << "2. Buscar por nombre (AVL)\n";
    std::cout << "3. Buscar por codigo (comparativa)\n";
    std::cout << "4. Eliminar producto por codigo\n";
    std::cout << "5. Listar catalogo ordenado (AVL in-order)\n";
    std::cout << "6. Ver estado de estructuras\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione opcion: ";
}
}

int main() {
    ListaEnlazada listaNoOrdenada;
    ListaEnlazadaOrdenada listaOrdenada;
    ArbolAVL arbol;

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        std::cin >> opcion;
        if (!std::cin.good()) {
            limpiarEntrada();
            std::cout << "Opcion invalida.\n";
            continue;
        }
        limpiarEntrada();

        if (opcion == 1) {
            std::cout << "\n--- Agregar producto ---\n";
            const Producto producto = leerProductoDesdeConsola();

            if (!producto.esValido()) {
                std::cout << "Producto invalido. Revise campos y formato de fecha.\n";
                continue;
            }

            if (arbol.buscarPorCodigo(producto.obtenerCodigoBarra()) != nullptr) {
                std::cout << "Ya existe un producto con ese codigo de barras.\n";
                continue;
            }

            if (!listaNoOrdenada.insertarAlFrente(producto)) {
                std::cout << "Fallo al insertar en lista no ordenada.\n";
                continue;
            }

            if (!listaOrdenada.insertarOrdenado(producto)) {
                listaNoOrdenada.eliminar(producto.obtenerCodigoBarra());
                std::cout << "Fallo al insertar en lista ordenada. Se aplico rollback.\n";
                continue;
            }

            if (!arbol.insertar(producto)) {
                listaNoOrdenada.eliminar(producto.obtenerCodigoBarra());
                listaOrdenada.eliminar(producto.obtenerCodigoBarra());
                std::cout << "Fallo al insertar en AVL. Se aplico rollback.\n";
                continue;
            }

            std::cout << "Producto agregado correctamente.\n";
        } else if (opcion == 2) {
            std::cout << "\nNombre a buscar: ";
            std::string nombre;
            std::getline(std::cin, nombre);

            const Producto* producto = arbol.buscar(nombre);
            if (producto == nullptr) {
                std::cout << "No encontrado.\n";
            } else {
                std::cout << "Encontrado en AVL:\n";
                imprimirProducto(*producto);
            }
        } else if (opcion == 3) {
            std::cout << "\nCodigo a buscar: ";
            std::string codigoBarra;
            std::getline(std::cin, codigoBarra);

            const Producto* encontradoNoOrdenada = listaNoOrdenada.buscar(codigoBarra);
            const auto tiempoNoOrdenada = listaNoOrdenada.obtenerUltimoTiempoBusquedaNanosegundos();

            const Producto* encontradoOrdenada = listaOrdenada.buscar(codigoBarra);
            const auto tiempoOrdenada = listaOrdenada.obtenerUltimoTiempoBusquedaNanosegundos();

            const Producto* encontradoAVL = arbol.buscarPorCodigo(codigoBarra);

            if (encontradoAVL == nullptr) {
                std::cout << "No encontrado en catalogo.\n";
            } else {
                std::cout << "Producto encontrado:\n";
                imprimirProducto(*encontradoAVL);
            }

            std::cout << "Tiempo lista no ordenada (ns): " << tiempoNoOrdenada << '\n';
            std::cout << "Tiempo lista ordenada (ns): " << tiempoOrdenada << '\n';
            std::cout << "Busqueda en AVL por codigo: O(n) (recorrido in-order).\n";

            if ((encontradoNoOrdenada != nullptr) != (encontradoOrdenada != nullptr)) {
                std::cout << "Advertencia: resultado inconsistente entre listas.\n";
            }
        } else if (opcion == 4) {
            std::cout << "\nCodigo a eliminar: ";
            std::string codigoBarra;
            std::getline(std::cin, codigoBarra);

            const Producto* producto = arbol.buscarPorCodigo(codigoBarra);
            if (producto == nullptr) {
                std::cout << "No existe un producto con ese codigo.\n";
                continue;
            }

            const std::string nombre = producto->obtenerNombre();
            const bool eliminadoAVL = arbol.eliminar(nombre);
            const bool eliminadoNoOrdenada = listaNoOrdenada.eliminar(codigoBarra);
            const bool eliminadoOrdenada = listaOrdenada.eliminar(codigoBarra);

            if (eliminadoAVL && eliminadoNoOrdenada && eliminadoOrdenada) {
                std::cout << "Producto eliminado correctamente en todas las estructuras.\n";
            } else {
                std::cout << "Eliminacion parcial detectada.\n";
                std::cout << "AVL: " << (eliminadoAVL ? "OK" : "FALLO") << " | "
                          << "Lista: " << (eliminadoNoOrdenada ? "OK" : "FALLO") << " | "
                          << "Lista ordenada: " << (eliminadoOrdenada ? "OK" : "FALLO") << '\n';
            }
        } else if (opcion == 5) {
            std::cout << "\n--- Catalogo ordenado por nombre (AVL) ---\n";
            if (arbol.estaVacio()) {
                std::cout << "Catalogo vacio.\n";
            } else {
                arbol.recorrerInOrder([](const Producto& producto) {
                    std::cout << "- " << producto.obtenerNombre()
                              << " | " << producto.obtenerCodigoBarra()
                              << " | Q" << producto.obtenerPrecio()
                              << " | stock: " << producto.obtenerStock() << '\n';
                });
            }
        } else if (opcion == 6) {
            std::cout << "\n--- Estado ---\n";
            std::cout << "Tamano lista no ordenada: " << listaNoOrdenada.obtenerTamano() << '\n';
            std::cout << "Tamano lista ordenada: " << listaOrdenada.obtenerTamano() << '\n';
            std::cout << "Tamano AVL: " << arbol.obtenerTamano() << '\n';
            std::cout << "Altura AVL: " << arbol.obtenerAltura() << '\n';
        } else if (opcion == 0) {
            std::cout << "Saliendo...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
