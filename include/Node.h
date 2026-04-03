#pragma once

/**
 * @brief Nodo generico para listas enlazadas simples.
 */
template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;

public:
    /**
     * @brief Construye un nodo con dato inicial y sin siguiente nodo.
     */
    explicit Nodo(const T& dato)
        : dato(dato), siguiente(nullptr) {
    }

    /**
     * @brief Retorna el dato almacenado.
     */
    const T& obtenerDato() const {
        return dato;
    }

    /**
     * @brief Actualiza el dato almacenado.
     */
    void establecerDato(const T& valor) {
        dato = valor;
    }

    /**
     * @brief Retorna el puntero al siguiente nodo.
     */
    Nodo<T>* obtenerSiguiente() const {
        return siguiente;
    }

    /**
     * @brief Define el puntero al siguiente nodo.
     */
    void establecerSiguiente(Nodo<T>* nodo) {
        siguiente = nodo;
    }
};
