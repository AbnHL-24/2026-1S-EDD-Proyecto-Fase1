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
    if (buscarPorCodigo(producto.obtenerCodigoBarra()) != nullptr) {
        return false;
    }

    bool insertado = false;
    raiz_ = insertarRec(raiz_, producto, insertado);
    if (insertado) {
        ++tamano_;
    }
    return insertado;
}

Producto* ArbolAVL::buscarPorNombre(const std::string& nombre) {
    NodoAVL* encontrado = buscarNodoPorNombreRec(raiz_, nombre);
    if (encontrado == nullptr) {
        return nullptr;
    }
    return &encontrado->obtenerDato();
}

const Producto* ArbolAVL::buscarPorNombre(const std::string& nombre) const {
    NodoAVL* encontrado = buscarNodoPorNombreRec(raiz_, nombre);
    if (encontrado == nullptr) {
        return nullptr;
    }
    return &encontrado->obtenerDato();
}

Producto* ArbolAVL::buscarPorCodigo(const std::string& codigoBarra) {
    NodoAVL* encontrado = buscarNodoPorCodigoRec(raiz_, codigoBarra);
    if (encontrado == nullptr) {
        return nullptr;
    }
    return &encontrado->obtenerDato();
}

const Producto* ArbolAVL::buscarPorCodigo(const std::string& codigoBarra) const {
    NodoAVL* encontrado = buscarNodoPorCodigoRec(raiz_, codigoBarra);
    if (encontrado == nullptr) {
        return nullptr;
    }
    return &encontrado->obtenerDato();
}

bool ArbolAVL::eliminar(const std::string& codigoBarra) {
    NodoAVL* encontrado = buscarNodoPorCodigoRec(raiz_, codigoBarra);
    if (encontrado == nullptr) {
        return false;
    }

    bool eliminado = false;
    raiz_ = eliminarRec(raiz_, encontrado->obtenerDato().obtenerNombre(), codigoBarra, eliminado);
    if (eliminado) {
        --tamano_;
    }
    return eliminado;
}

void ArbolAVL::recorrerEnOrden(const std::function<void(const Producto&)>& callback) const {
    recorrerEnOrdenRec(raiz_, callback);
}

int ArbolAVL::obtenerTamano() const {
    return tamano_;
}

bool ArbolAVL::estaVacio() const {
    return raiz_ == nullptr;
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
        if (producto.obtenerCodigoBarra() < nodo->obtenerDato().obtenerCodigoBarra()) {
            nodo->establecerIzquierdo(insertarRec(nodo->obtenerIzquierdo(), producto, insertado));
        } else {
            nodo->establecerDerecho(insertarRec(nodo->obtenerDerecho(), producto, insertado));
        }
    }

    actualizarAltura(nodo);
    return rebalancear(nodo);
}

NodoAVL* ArbolAVL::eliminarRec(NodoAVL* nodo,
                               const std::string& nombre,
                               const std::string& codigoBarra,
                               bool& eliminado) {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string& nombreActual = nodo->obtenerDato().obtenerNombre();
    const std::string& codigoActual = nodo->obtenerDato().obtenerCodigoBarra();

    if (nombre < nombreActual || (nombre == nombreActual && codigoBarra < codigoActual)) {
        nodo->establecerIzquierdo(eliminarRec(nodo->obtenerIzquierdo(), nombre, codigoBarra, eliminado));
    } else if (nombreActual < nombre || (nombre == nombreActual && codigoActual < codigoBarra)) {
        nodo->establecerDerecho(eliminarRec(nodo->obtenerDerecho(), nombre, codigoBarra, eliminado));
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
        const std::string codigoSucesor = sucesor->obtenerDato().obtenerCodigoBarra();

        nodo->establecerDato(sucesor->obtenerDato());

        bool eliminadoSucesor = false;
        nodo->establecerDerecho(
            eliminarRec(nodo->obtenerDerecho(), nombreSucesor, codigoSucesor, eliminadoSucesor));
    }

    actualizarAltura(nodo);
    return rebalancear(nodo);
}

NodoAVL* ArbolAVL::buscarNodoPorNombreRec(NodoAVL* nodo, const std::string& nombre) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    const std::string& nombreActual = nodo->obtenerDato().obtenerNombre();
    if (nombre == nombreActual) {
        return nodo;
    }
    if (nombre < nombreActual) {
        return buscarNodoPorNombreRec(nodo->obtenerIzquierdo(), nombre);
    }
    return buscarNodoPorNombreRec(nodo->obtenerDerecho(), nombre);
}

NodoAVL* ArbolAVL::buscarNodoPorCodigoRec(NodoAVL* nodo, const std::string& codigoBarra) const {
    if (nodo == nullptr) {
        return nullptr;
    }
    if (nodo->obtenerDato().obtenerCodigoBarra() == codigoBarra) {
        return nodo;
    }

    NodoAVL* encontradoIzq = buscarNodoPorCodigoRec(nodo->obtenerIzquierdo(), codigoBarra);
    if (encontradoIzq != nullptr) {
        return encontradoIzq;
    }
    return buscarNodoPorCodigoRec(nodo->obtenerDerecho(), codigoBarra);
}

void ArbolAVL::recorrerEnOrdenRec(NodoAVL* nodo,
                                  const std::function<void(const Producto&)>& callback) const {
    if (nodo == nullptr) {
        return;
    }

    recorrerEnOrdenRec(nodo->obtenerIzquierdo(), callback);
    callback(nodo->obtenerDato());
    recorrerEnOrdenRec(nodo->obtenerDerecho(), callback);
}

void ArbolAVL::liberarRec(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberarRec(nodo->obtenerIzquierdo());
    liberarRec(nodo->obtenerDerecho());
    delete nodo;
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
    const int balance = nodo->obtenerFactorBalance();

    if (balance > 1) {
        if (nodo->obtenerIzquierdo() != nullptr && nodo->obtenerIzquierdo()->obtenerFactorBalance() < 0) {
            nodo->establecerIzquierdo(rotarIzquierda(nodo->obtenerIzquierdo()));
        }
        return rotarDerecha(nodo);
    }

    if (balance < -1) {
        if (nodo->obtenerDerecho() != nullptr && nodo->obtenerDerecho()->obtenerFactorBalance() > 0) {
            nodo->establecerDerecho(rotarDerecha(nodo->obtenerDerecho()));
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* ArbolAVL::obtenerMinimo(NodoAVL* nodo) const {
    NodoAVL* actual = nodo;
    while (actual != nullptr && actual->obtenerIzquierdo() != nullptr) {
        actual = actual->obtenerIzquierdo();
    }
    return actual;
}

int ArbolAVL::obtenerAltura(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->obtenerAltura();
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }

    const int alturaIzquierda = obtenerAltura(nodo->obtenerIzquierdo());
    const int alturaDerecha = obtenerAltura(nodo->obtenerDerecho());
    const int mayorAltura = (alturaIzquierda > alturaDerecha) ? alturaIzquierda : alturaDerecha;
    nodo->establecerAltura(mayorAltura + 1);
}
