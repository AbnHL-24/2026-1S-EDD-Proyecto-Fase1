#include "ArbolAVL.h"

ArbolAVL::ArbolAVL()
    : raiz_(nullptr), tamano_(0) {
}

ArbolAVL::~ArbolAVL() {
    liberarRec(raiz_);
    raiz_ = nullptr;
    tamano_ = 0;
}

bool ArbolAVL::insertar(const Producto& producto) {
    if (!producto.esValido()) {
        return false;
    }

    bool insertado = false;
    raiz_ = insertarRec(raiz_, producto, insertado);
    if (insertado) {
        ++tamano_;
    }
    return insertado;
}

const Producto* ArbolAVL::buscar(const std::string& nombre) const {
    return buscarRec(raiz_, nombre);
}

const Producto* ArbolAVL::buscarPorCodigo(const std::string& codigoBarra) const {
    return buscarPorCodigoRec(raiz_, codigoBarra);
}

bool ArbolAVL::eliminar(const std::string& nombre) {
    bool eliminado = false;
    raiz_ = eliminarRec(raiz_, nombre, eliminado);
    if (eliminado) {
        --tamano_;
    }
    return eliminado;
}

void ArbolAVL::recorrerInOrder(std::function<void(const Producto&)> callback) const {
    if (!callback) {
        return;
    }

    inOrderRec(raiz_, callback);
}

int ArbolAVL::obtenerTamano() const {
    return tamano_;
}

bool ArbolAVL::estaVacio() const {
    return raiz_ == nullptr;
}

int ArbolAVL::obtenerAltura() const {
    return altura(raiz_);
}

int ArbolAVL::altura(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return -1;
    }
    return nodo->obtenerAltura();
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    const int alturaIzquierda = altura(nodo->obtenerIzquierdo());
    const int alturaDerecha = altura(nodo->obtenerDerecho());
    const int mayorAltura = (alturaIzquierda > alturaDerecha) ? alturaIzquierda : alturaDerecha;
    nodo->establecerAltura(mayorAltura + 1);
}

NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->obtenerIzquierdo();
    NodoAVL* subarbolTransferido = nuevaRaiz->obtenerDerecho();

    nuevaRaiz->establecerDerecho(nodo);
    nodo->establecerIzquierdo(subarbolTransferido);

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->obtenerDerecho();
    NodoAVL* subarbolTransferido = nuevaRaiz->obtenerIzquierdo();

    nuevaRaiz->establecerIzquierdo(nodo);
    nodo->establecerDerecho(subarbolTransferido);

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* ArbolAVL::rebalancear(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }

    const int balance = altura(nodo->obtenerIzquierdo()) - altura(nodo->obtenerDerecho());

    if (balance > 1) {
        const int balanceIzquierdo =
            altura(nodo->obtenerIzquierdo()->obtenerIzquierdo()) -
            altura(nodo->obtenerIzquierdo()->obtenerDerecho());

        if (balanceIzquierdo < 0) {
            nodo->establecerIzquierdo(rotarIzquierda(nodo->obtenerIzquierdo()));
        }
        return rotarDerecha(nodo);
    }

    if (balance < -1) {
        const int balanceDerecho =
            altura(nodo->obtenerDerecho()->obtenerIzquierdo()) -
            altura(nodo->obtenerDerecho()->obtenerDerecho());

        if (balanceDerecho > 0) {
            nodo->establecerDerecho(rotarDerecha(nodo->obtenerDerecho()));
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* ArbolAVL::insertarRec(NodoAVL* nodo, const Producto& producto, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(producto);
    }

    const std::string& nombreNuevo = producto.obtenerNombre();
    const std::string& nombreActual = nodo->obtenerDato().obtenerNombre();

    if (nombreNuevo < nombreActual) {
        nodo->establecerIzquierdo(insertarRec(nodo->obtenerIzquierdo(), producto, insertado));
    } else if (nombreActual < nombreNuevo) {
        nodo->establecerDerecho(insertarRec(nodo->obtenerDerecho(), producto, insertado));
    } else {
        insertado = false;
        return nodo;
    }

    actualizarAltura(nodo);
    return rebalancear(nodo);
}

NodoAVL* ArbolAVL::eliminarRec(NodoAVL* nodo, const std::string& nombre, bool& eliminado) {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string& nombreActual = nodo->obtenerDato().obtenerNombre();

    if (nombre < nombreActual) {
        nodo->establecerIzquierdo(eliminarRec(nodo->obtenerIzquierdo(), nombre, eliminado));
    } else if (nombreActual < nombre) {
        nodo->establecerDerecho(eliminarRec(nodo->obtenerDerecho(), nombre, eliminado));
    } else {
        eliminado = true;

        if (nodo->obtenerIzquierdo() == nullptr && nodo->obtenerDerecho() == nullptr) {
            delete nodo;
            return nullptr;
        }

        if (nodo->obtenerIzquierdo() == nullptr) {
            NodoAVL* derecho = nodo->obtenerDerecho();
            delete nodo;
            return derecho;
        }

        if (nodo->obtenerDerecho() == nullptr) {
            NodoAVL* izquierdo = nodo->obtenerIzquierdo();
            delete nodo;
            return izquierdo;
        }

        NodoAVL* sucesor = obtenerMinimo(nodo->obtenerDerecho());
        const std::string nombreSucesor = sucesor->obtenerDato().obtenerNombre();
        nodo->establecerDato(sucesor->obtenerDato());

        bool eliminadoSucesor = false;
        nodo->establecerDerecho(eliminarRec(nodo->obtenerDerecho(), nombreSucesor, eliminadoSucesor));
    }

    actualizarAltura(nodo);
    return rebalancear(nodo);
}

NodoAVL* ArbolAVL::obtenerMinimo(NodoAVL* nodo) const {
    NodoAVL* actual = nodo;
    while (actual != nullptr && actual->obtenerIzquierdo() != nullptr) {
        actual = actual->obtenerIzquierdo();
    }
    return actual;
}

const Producto* ArbolAVL::buscarRec(NodoAVL* nodo, const std::string& nombre) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string& nombreActual = nodo->obtenerDato().obtenerNombre();
    if (nombre == nombreActual) {
        return &nodo->obtenerDato();
    }
    if (nombre < nombreActual) {
        return buscarRec(nodo->obtenerIzquierdo(), nombre);
    }
    return buscarRec(nodo->obtenerDerecho(), nombre);
}

const Producto* ArbolAVL::buscarPorCodigoRec(NodoAVL* nodo, const std::string& codigoBarra) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    const Producto* encontradoIzquierda = buscarPorCodigoRec(nodo->obtenerIzquierdo(), codigoBarra);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    if (nodo->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
        return &nodo->obtenerDato();
    }

    return buscarPorCodigoRec(nodo->obtenerDerecho(), codigoBarra);
}

void ArbolAVL::inOrderRec(NodoAVL* nodo, std::function<void(const Producto&)>& callback) const {
    if (nodo == nullptr) {
        return;
    }

    inOrderRec(nodo->obtenerIzquierdo(), callback);
    callback(nodo->obtenerDato());
    inOrderRec(nodo->obtenerDerecho(), callback);
}

void ArbolAVL::liberarRec(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberarRec(nodo->obtenerIzquierdo());
    liberarRec(nodo->obtenerDerecho());
    delete nodo;
}
