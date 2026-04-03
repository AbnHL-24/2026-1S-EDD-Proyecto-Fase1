#pragma once

#include <string>

#include "Product.h"

/**
 * @brief Nodo base para arbol B con orden configurable.
 */
template <int M = 3>
class NodoB {
private:
    std::string claves[M - 1];
    Producto* valores[M - 1];
    NodoB<M>* hijos[M];
    int numeroClaves;
    bool esHoja;

public:
    /**
     * @brief Construye un nodo B vacio.
     */
    explicit NodoB(const bool esHoja = true)
        : numeroClaves(0), esHoja(esHoja) {
        for (int i = 0; i < M - 1; ++i) {
            claves[i] = "";
            valores[i] = nullptr;
        }
        for (int i = 0; i < M; ++i) {
            hijos[i] = nullptr;
        }
    }

    /**
     * @brief Retorna la clave en una posicion del nodo.
     */
    const std::string& obtenerClave(const int indice) const {
        return claves[indice];
    }

    /**
     * @brief Define la clave en una posicion del nodo.
     */
    void establecerClave(const int indice, const std::string& clave) {
        claves[indice] = clave;
    }

    /**
     * @brief Retorna el valor asociado a una posicion.
     */
    Producto* obtenerValor(const int indice) const {
        return valores[indice];
    }

    /**
     * @brief Define el valor asociado a una posicion.
     */
    void establecerValor(const int indice, Producto* valor) {
        valores[indice] = valor;
    }

    /**
     * @brief Retorna el hijo en una posicion.
     */
    NodoB<M>* obtenerHijo(const int indice) const {
        return hijos[indice];
    }

    /**
     * @brief Define el hijo en una posicion.
     */
    void establecerHijo(const int indice, NodoB<M>* hijo) {
        hijos[indice] = hijo;
    }

    /**
     * @brief Retorna la cantidad de claves actuales.
     */
    int obtenerNumeroClaves() const {
        return numeroClaves;
    }

    /**
     * @brief Define la cantidad de claves actuales.
     */
    void establecerNumeroClaves(const int valor) {
        numeroClaves = valor;
    }

    /**
     * @brief Indica si el nodo es hoja.
     */
    bool obtenerEsHoja() const {
        return esHoja;
    }

    /**
     * @brief Define si el nodo es hoja.
     */
    void establecerEsHoja(const bool valor) {
        esHoja = valor;
    }

    /**
     * @brief Verifica si el nodo alcanzo su maxima capacidad de claves.
     */
    bool estaLleno() const {
        return numeroClaves == (M - 1);
    }

    /**
     * @brief Busca una clave dentro del nodo y retorna su indice o -1.
     */
    int buscar(const std::string& clave) const {
        for (int i = 0; i < numeroClaves; ++i) {
            if (claves[i] == clave) {
                return i;
            }
        }
        return -1;
    }
};
