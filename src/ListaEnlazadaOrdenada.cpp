#include "ListaEnlazadaOrdenada.h"

#include <chrono>

ListaEnlazadaOrdenada::ListaEnlazadaOrdenada()
    : cabeza_(nullptr), tamano_(0), ultimoTiempoBusquedaNanosegundos_(0) {
}

ListaEnlazadaOrdenada::~ListaEnlazadaOrdenada() {
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

bool ListaEnlazadaOrdenada::insertarOrdenado(const Producto& producto) {
    if (!producto.esValido()) {
        return false;
    }

    Nodo<Producto>* nuevoNodo = new Nodo<Producto>(producto);

    if (cabeza_ == nullptr || producto.obtenerNombre() < cabeza_->obtenerDato().obtenerNombre()) {
        nuevoNodo->establecerSiguiente(cabeza_);
        cabeza_ = nuevoNodo;
        ++tamano_;
        return true;
    }

    Nodo<Producto>* actual = cabeza_;
    while (actual->obtenerSiguiente() != nullptr &&
           actual->obtenerSiguiente()->obtenerDato().obtenerNombre() <= producto.obtenerNombre()) {
        actual = actual->obtenerSiguiente();
    }

    nuevoNodo->establecerSiguiente(actual->obtenerSiguiente());
    actual->establecerSiguiente(nuevoNodo);
    ++tamano_;
    return true;
}

Producto* ListaEnlazadaOrdenada::buscar(const std::string& codigoBarra) {
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

const Producto* ListaEnlazadaOrdenada::buscar(const std::string& codigoBarra) const {
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

Producto* ListaEnlazadaOrdenada::buscarPorNombre(const std::string& nombre) {
    Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        const std::string& nombreActual = actual->obtenerDato().obtenerNombre();
        if (nombreActual == nombre) {
            return &actual->obtenerDato();
        }

        // Optimiza la busqueda en lista ordenada: no hay coincidencia despues de este punto.
        if (nombreActual > nombre) {
            return nullptr;
        }

        actual = actual->obtenerSiguiente();
    }
    return nullptr;
}

const Producto* ListaEnlazadaOrdenada::buscarPorNombre(const std::string& nombre) const {
    const Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        const std::string& nombreActual = actual->obtenerDato().obtenerNombre();
        if (nombreActual == nombre) {
            return &actual->obtenerDato();
        }
        if (nombreActual > nombre) {
            return nullptr;
        }
        actual = actual->obtenerSiguiente();
    }
    return nullptr;
}

bool ListaEnlazadaOrdenada::eliminar(const std::string& codigoBarra) {
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

void ListaEnlazadaOrdenada::recorrer(const std::function<void(const Producto&)>& callback) const {
    const Nodo<Producto>* actual = cabeza_;
    while (actual != nullptr) {
        callback(actual->obtenerDato());
        actual = actual->obtenerSiguiente();
    }
}

int ListaEnlazadaOrdenada::obtenerTamano() const {
    return tamano_;
}

bool ListaEnlazadaOrdenada::estaVacia() const {
    return cabeza_ == nullptr;
}

Producto* ListaEnlazadaOrdenada::obtenerPrimero() {
    if (cabeza_ == nullptr) {
        return nullptr;
    }
    return &cabeza_->obtenerDato();
}

const Producto* ListaEnlazadaOrdenada::obtenerPrimero() const {
    if (cabeza_ == nullptr) {
        return nullptr;
    }
    return &cabeza_->obtenerDato();
}

std::int64_t ListaEnlazadaOrdenada::obtenerUltimoTiempoBusquedaNanosegundos() const {
    return ultimoTiempoBusquedaNanosegundos_;
}
