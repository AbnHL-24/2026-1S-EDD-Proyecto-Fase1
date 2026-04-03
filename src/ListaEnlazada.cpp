#include "ListaEnlazada.h"

#include <chrono>

ListaEnlazada::ListaEnlazada()
    : cabeza_(nullptr), tamano_(0), ultimoTiempoBusquedaNanosegundos_(0) {
}

ListaEnlazada::~ListaEnlazada() {
    Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        Nodo<Producto>* siguiente = actual->obtenerSiguiente();
        delete actual;
        actual = siguiente;
    }
    cabeza_ = nullptr;
    tamano_ = 0;
    ultimoTiempoBusquedaNanosegundos_ = 0;
}

bool ListaEnlazada::insertarAlFrente(const Producto& producto) {
    if (!producto.esValido()) {
        return false;
    }

    Nodo<Producto>* nuevoNodo = new Nodo<Producto>(producto);
    nuevoNodo->establecerSiguiente(cabeza_);
    cabeza_ = nuevoNodo;
    ++tamano_;
    return true;
}

Producto* ListaEnlazada::buscar(const std::string& codigoBarra) {
    const auto inicio = std::chrono::steady_clock::now();

    Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        if (actual->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
            const auto fin = std::chrono::steady_clock::now();
            ultimoTiempoBusquedaNanosegundos_ =
                std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();
            return &actual->obtenerDato();
        }
        actual = actual->obtenerSiguiente();
    }

    const auto fin = std::chrono::steady_clock::now();
    ultimoTiempoBusquedaNanosegundos_ =
        std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();
    return nullptr;
}

const Producto* ListaEnlazada::buscar(const std::string& codigoBarra) const {
    const auto inicio = std::chrono::steady_clock::now();

    const Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        if (actual->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
            const auto fin = std::chrono::steady_clock::now();
            ultimoTiempoBusquedaNanosegundos_ =
                std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();
            return &actual->obtenerDato();
        }
        actual = actual->obtenerSiguiente();
    }

    const auto fin = std::chrono::steady_clock::now();
    ultimoTiempoBusquedaNanosegundos_ =
        std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();
    return nullptr;
}

bool ListaEnlazada::eliminar(const std::string& codigoBarra) {
    if (cabeza_ == nullptr) {
        return false;
    }

    if (cabeza_->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
        Nodo<Producto>* nodoAEliminar = cabeza_;
        cabeza_ = cabeza_->obtenerSiguiente();
        delete nodoAEliminar;
        --tamano_;
        return true;
    }

    Nodo<Producto>* actual = cabeza_;
    while (actual->obtenerSiguiente() != nullptr) {
        if (actual->obtenerSiguiente()->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
            Nodo<Producto>* nodoAEliminar = actual->obtenerSiguiente();
            actual->establecerSiguiente(nodoAEliminar->obtenerSiguiente());
            delete nodoAEliminar;
            --tamano_;
            return true;
        }
        actual = actual->obtenerSiguiente();
    }

    return false;
}

void ListaEnlazada::recorrer(const std::function<void(const Producto&)>& callback) const {
    const Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        callback(actual->obtenerDato());
        actual = actual->obtenerSiguiente();
    }
}

int ListaEnlazada::obtenerTamano() const {
    return tamano_;
}

bool ListaEnlazada::estaVacia() const {
    return cabeza_ == nullptr;
}

Producto* ListaEnlazada::obtenerPrimero() {
    if (cabeza_ == nullptr) {
        return nullptr;
    }
    return &cabeza_->obtenerDato();
}

const Producto* ListaEnlazada::obtenerPrimero() const {
    if (cabeza_ == nullptr) {
        return nullptr;
    }
    return &cabeza_->obtenerDato();
}

std::int64_t ListaEnlazada::obtenerUltimoTiempoBusquedaNanosegundos() const {
    return ultimoTiempoBusquedaNanosegundos_;
}
