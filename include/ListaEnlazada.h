#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "Node.h"
#include "Product.h"

/**
 * @brief Lista enlazada simple sin ordenamiento.
 */
class ListaEnlazada {
private:
    Nodo<Producto>* cabeza_;
    int tamano_;
    mutable std::int64_t ultimoTiempoBusquedaNanosegundos_;

public:
    /**
     * @brief Construye una lista vacia.
     */
    ListaEnlazada();

    /**
     * @brief Libera toda la memoria de nodos.
     */
    ~ListaEnlazada();

    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

    /**
     * @brief Inserta un producto al frente si es valido.
     */
    bool insertarAlFrente(const Producto& producto);

    /**
     * @brief Busca un producto por codigo de barra de forma secuencial.
     */
    Producto* buscar(const std::string& codigoBarra);

    /**
     * @brief Busca un producto por codigo de barra de forma secuencial.
     */
    const Producto* buscar(const std::string& codigoBarra) const;

    /**
     * @brief Elimina el primer producto que coincida con el codigo de barra.
     */
    bool eliminar(const std::string& codigoBarra);

    /**
     * @brief Recorre todos los productos aplicando un callback.
     */
    void recorrer(const std::function<void(const Producto&)>& callback) const;

    /**
     * @brief Retorna la cantidad de productos en la lista.
     */
    int obtenerTamano() const;

    /**
     * @brief Indica si la lista esta vacia.
     */
    bool estaVacia() const;

    /**
     * @brief Retorna el primer producto de la lista.
     */
    Producto* obtenerPrimero();

    /**
     * @brief Retorna el primer producto de la lista (solo lectura).
     */
    const Producto* obtenerPrimero() const;

    /**
     * @brief Retorna el ultimo tiempo de busqueda medido en nanosegundos.
     */
    std::int64_t obtenerUltimoTiempoBusquedaNanosegundos() const;
};
