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

    NodoAVL* insertarRec(NodoAVL* nodo, const Producto& producto, bool& insertado);
    NodoAVL* eliminarRec(NodoAVL* nodo,
                         const std::string& nombre,
                         const std::string& codigoBarra,
                         bool& eliminado);
    NodoAVL* buscarNodoPorNombreRec(NodoAVL* nodo, const std::string& nombre) const;
    NodoAVL* buscarNodoPorCodigoRec(NodoAVL* nodo, const std::string& codigoBarra) const;
    void recorrerEnOrdenRec(NodoAVL* nodo, const std::function<void(const Producto&)>& callback) const;
    void liberarRec(NodoAVL* nodo);

    NodoAVL* rotarDerecha(NodoAVL* nodo);
    NodoAVL* rotarIzquierda(NodoAVL* nodo);
    NodoAVL* rebalancear(NodoAVL* nodo);
    NodoAVL* obtenerMinimo(NodoAVL* nodo) const;
    int obtenerAltura(NodoAVL* nodo) const;
    void actualizarAltura(NodoAVL* nodo);

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
     * @brief Inserta un producto si es valido y su codigo de barras es unico.
     */
    bool insertar(const Producto& producto);

    /**
     * @brief Busca un producto por nombre.
     */
    Producto* buscarPorNombre(const std::string& nombre);

    /**
     * @brief Busca un producto por nombre (solo lectura).
     */
    const Producto* buscarPorNombre(const std::string& nombre) const;

    /**
     * @brief Busca un producto por codigo de barras.
     */
    Producto* buscarPorCodigo(const std::string& codigoBarra);

    /**
     * @brief Busca un producto por codigo de barras (solo lectura).
     */
    const Producto* buscarPorCodigo(const std::string& codigoBarra) const;

    /**
     * @brief Elimina un producto por codigo de barras.
     */
    bool eliminar(const std::string& codigoBarra);

    /**
     * @brief Recorre el arbol en orden alfabetico por nombre.
     */
    void recorrerEnOrden(const std::function<void(const Producto&)>& callback) const;

    /**
     * @brief Retorna la cantidad de productos almacenados.
     */
    int obtenerTamano() const;

    /**
     * @brief Indica si el arbol esta vacio.
     */
    bool estaVacio() const;
};
