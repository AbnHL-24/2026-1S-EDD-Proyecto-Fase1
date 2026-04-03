#pragma once

#include <functional>
#include <string>

#include "AVLNode.h"

/**
 * @brief Arbol AVL ordenado por nombre de producto.
 */
class ArbolAVL {
private:
    NodoAVL* raiz_;
    int tamano_;

    /**
     * @brief Retorna la altura de un nodo o -1 si es nulo.
     */
    int altura(NodoAVL* nodo) const;

    /**
     * @brief Actualiza la altura de un nodo segun sus hijos.
     */
    void actualizarAltura(NodoAVL* nodo);

    /**
     * @brief Aplica rotacion simple a la derecha.
     */
    NodoAVL* rotarDerecha(NodoAVL* nodo);

    /**
     * @brief Aplica rotacion simple a la izquierda.
     */
    NodoAVL* rotarIzquierda(NodoAVL* nodo);

    /**
     * @brief Rebalancea un subarbol AVL si su factor sale de rango.
     */
    NodoAVL* rebalancear(NodoAVL* nodo);

    /**
     * @brief Inserta recursivamente y retorna nueva raiz del subarbol.
     */
    NodoAVL* insertarRec(NodoAVL* nodo, const Producto& producto, bool& insertado);

    /**
     * @brief Elimina recursivamente por nombre y retorna nueva raiz del subarbol.
     */
    NodoAVL* eliminarRec(NodoAVL* nodo, const std::string& nombre, bool& eliminado);

    /**
     * @brief Retorna el nodo minimo de un subarbol.
     */
    NodoAVL* obtenerMinimo(NodoAVL* nodo) const;

    /**
     * @brief Busca recursivamente por nombre exacto.
     */
    const Producto* buscarRec(NodoAVL* nodo, const std::string& nombre) const;

    /**
     * @brief Busca por codigo de barras recorriendo in-order.
     */
    const Producto* buscarPorCodigoRec(NodoAVL* nodo, const std::string& codigoBarra) const;

    /**
     * @brief Recorre in-order y aplica callback en cada producto.
     */
    void inOrderRec(NodoAVL* nodo, std::function<void(const Producto&)>& callback) const;

    /**
     * @brief Libera memoria de todos los nodos en post-order.
     */
    void liberarRec(NodoAVL* nodo);

public:
    /**
     * @brief Construye un arbol AVL vacio.
     */
    ArbolAVL();

    /**
     * @brief Libera todos los nodos del arbol.
     */
    ~ArbolAVL();

    ArbolAVL(const ArbolAVL&) = delete;
    ArbolAVL& operator=(const ArbolAVL&) = delete;

    /**
     * @brief Inserta un producto por nombre con rebalanceo AVL.
     * @return true si inserta; false si el producto no es valido o el codigo ya existe.
     * @note Complejidad esperada: O(log n).
     */
    bool insertar(const Producto& producto);

    /**
     * @brief Busca un producto por nombre exacto.
     * @note Complejidad esperada: O(log n).
     */
    const Producto* buscar(const std::string& nombre) const;

    /**
     * @brief Busca un producto por codigo de barras recorriendo in-order.
     * @note Complejidad esperada: O(n).
     */
    const Producto* buscarPorCodigo(const std::string& codigoBarra) const;

    /**
     * @brief Elimina un producto por nombre exacto con rebalanceo AVL.
     * @return true si elimina; false si no existe.
     * @note Complejidad esperada: O(log n).
     */
    bool eliminar(const std::string& nombre);

    /**
     * @brief Recorre el arbol en orden alfabetico por nombre.
     * @note Complejidad esperada: O(n).
     */
    void recorrerInOrder(std::function<void(const Producto&)> callback) const;

    /**
     * @brief Retorna la cantidad de productos almacenados.
     */
    int obtenerTamano() const;

    /**
     * @brief Indica si el arbol esta vacio.
     */
    bool estaVacio() const;

    /**
     * @brief Retorna la altura del arbol, o -1 si esta vacio.
     */
    int obtenerAltura() const;
};
