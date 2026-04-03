#include <iostream>
#include <limits>
#include <string>

#include "ArbolAVL.h"
#include "ListaEnlazada.h"
#include "ListaEnlazadaOrdenada.h"

namespace {
int siguienteIdSemilla = 1;

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

bool insertarEnEstructuras(const Producto& producto,
                           ListaEnlazada& listaNoOrdenada,
                           ListaEnlazadaOrdenada& listaOrdenada,
                           ArbolAVL& arbol) {
    if (!producto.esValido()) {
        return false;
    }

    if (arbol.buscarPorCodigo(producto.obtenerCodigoBarra()) != nullptr) {
        return false;
    }

    if (!listaNoOrdenada.insertarAlFrente(producto)) {
        return false;
    }

    if (!listaOrdenada.insertarOrdenado(producto)) {
        listaNoOrdenada.eliminar(producto.obtenerCodigoBarra());
        return false;
    }

    if (!arbol.insertar(producto)) {
        listaNoOrdenada.eliminar(producto.obtenerCodigoBarra());
        listaOrdenada.eliminar(producto.obtenerCodigoBarra());
        return false;
    }

    return true;
}

void cargarDatosQuemados(ListaEnlazada& listaNoOrdenada,
                         ListaEnlazadaOrdenada& listaOrdenada,
                         ArbolAVL& arbol) {
    static const std::string categorias[] = {"Despensa", "Bebidas", "Lacteos", "Limpieza", "Congelados"};
    static const std::string marcas[] = {"MarcaA", "MarcaB", "MarcaC", "MarcaD", "MarcaE"};

    int insertados = 0;
    int fallidos = 0;

    for (int i = 0; i < 1000; ++i) {
        const int id = siguienteIdSemilla++;

        const std::string nombre = "ProductoSemilla" + std::to_string(id);
        const std::string codigo = "SEM" + std::to_string(100000 + id);
        const std::string categoria = categorias[id % 5];
        const int mes = (id % 12) + 1;
        const int dia = (id % 28) + 1;
        const std::string fecha =
            "2027-" + std::string((mes < 10) ? "0" : "") + std::to_string(mes) + "-" +
            std::string((dia < 10) ? "0" : "") + std::to_string(dia);
        const std::string marca = marcas[id % 5];
        const double precio = 5.0 + static_cast<double>(id % 250) / 10.0;
        const int stock = 10 + (id % 400);

        const Producto producto(nombre, codigo, categoria, fecha, marca, precio, stock);
        if (insertarEnEstructuras(producto, listaNoOrdenada, listaOrdenada, arbol)) {
            ++insertados;
        } else {
            ++fallidos;
        }
    }

    std::cout << "Carga semilla finalizada. Insertados: " << insertados
              << " | Fallidos: " << fallidos << '\n';
}

void mostrarMenu() {
    std::cout << "\n===== Mini Catalogo (Listas + AVL) =====\n";
    std::cout << "1. Agregar producto\n";
    std::cout << "2. Buscar por nombre (AVL)\n";
    std::cout << "3. Buscar por codigo (comparativa)\n";
    std::cout << "4. Eliminar producto por codigo\n";
    std::cout << "5. Listar catalogo ordenado (AVL in-order)\n";
    std::cout << "6. Ver estado de estructuras\n";
    std::cout << "7. Cargar 1000 datos quemados\n";
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

            if (!insertarEnEstructuras(producto, listaNoOrdenada, listaOrdenada, arbol)) {
                std::cout << "No se pudo insertar. Valide datos o duplicados por codigo/nombre.\n";
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
        } else if (opcion == 7) {
            std::cout << "\nCargando 1000 datos quemados...\n";
            cargarDatosQuemados(listaNoOrdenada, listaOrdenada, arbol);
        } else if (opcion == 0) {
            std::cout << "Saliendo...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
