#pragma once

#include "Product.h"

/**
 * @brief Nodo base para arbol AVL.
 */
class NodoAVL {
private:
    Producto dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

public:
    /**
     * @brief Construye un nodo AVL con altura inicial 0.
     */
    explicit NodoAVL(const Producto& dato)
        : dato(dato), izquierdo(nullptr), derecho(nullptr), altura(0) {
    }

    /**
     * @brief Retorna el dato del nodo.
     */
    Producto& obtenerDato() {
        return dato;
    }

    /**
     * @brief Retorna el dato del nodo (solo lectura).
     */
    const Producto& obtenerDato() const {
        return dato;
    }

    /**
     * @brief Define el dato del nodo.
     */
    void establecerDato(const Producto& valor) {
        dato = valor;
    }

    /**
     * @brief Retorna el hijo izquierdo.
     */
    NodoAVL* obtenerIzquierdo() const {
        return izquierdo;
    }

    /**
     * @brief Define el hijo izquierdo.
     */
    void establecerIzquierdo(NodoAVL* nodo) {
        izquierdo = nodo;
    }

    /**
     * @brief Retorna el hijo derecho.
     */
    NodoAVL* obtenerDerecho() const {
        return derecho;
    }

    /**
     * @brief Define el hijo derecho.
     */
    void establecerDerecho(NodoAVL* nodo) {
        derecho = nodo;
    }

    /**
     * @brief Retorna la altura actual del nodo.
     */
    int obtenerAltura() const {
        return altura;
    }

    /**
     * @brief Define la altura del nodo.
     */
    void establecerAltura(const int valor) {
        altura = valor;
    }

    /**
     * @brief Calcula el factor de balance: altura(izq) - altura(der).
     */
    int obtenerFactorBalance() const {
        const int alturaIzquierda = (izquierdo == nullptr) ? -1 : izquierdo->altura;
        const int alturaDerecha = (derecho == nullptr) ? -1 : derecho->altura;
        return alturaIzquierda - alturaDerecha;
    }
};
