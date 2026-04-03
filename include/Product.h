#pragma once

#include <string>

/**
 * @brief Modelo base para representar un producto del inventario.
 */
struct Producto {
private:
    std::string nombre;
    std::string codigoBarra;
    std::string categoria;
    std::string fechaCaducidad;
    std::string marca;
    double precio;
    int stock;

    /**
     * @brief Valida si un anio es bisiesto.
     */
    static bool esBisiesto(const int anio) {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    }

    /**
     * @brief Convierte una subcadena numerica a entero.
     */
    static int convertirEntero(const std::string& valor, const std::size_t inicio, const std::size_t longitud) {
        int resultado = 0;
        for (std::size_t i = inicio; i < inicio + longitud; ++i) {
            if (valor[i] < '0' || valor[i] > '9') {
                return -1;
            }
            resultado = (resultado * 10) + static_cast<int>(valor[i] - '0');
        }
        return resultado;
    }

    /**
     * @brief Verifica formato y consistencia de una fecha ISO YYYY-MM-DD.
     */
    static bool fechaIsoValida(const std::string& fecha) {
        if (fecha.size() != 10) {
            return false;
        }
        if (fecha[4] != '-' || fecha[7] != '-') {
            return false;
        }

        const int anio = convertirEntero(fecha, 0, 4);
        const int mes = convertirEntero(fecha, 5, 2);
        const int dia = convertirEntero(fecha, 8, 2);

        if (anio < 0 || mes < 1 || mes > 12 || dia < 1) {
            return false;
        }

        int diaMaximo = 31;
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            diaMaximo = 30;
        } else if (mes == 2) {
            diaMaximo = esBisiesto(anio) ? 29 : 28;
        }

        return dia <= diaMaximo;
    }

public:
    /**
     * @brief Constructor por defecto.
     */
    Producto()
        : nombre(""),
          codigoBarra(""),
          categoria(""),
          fechaCaducidad(""),
          marca(""),
          precio(0.0),
          stock(0) {
    }

    /**
     * @brief Constructor con todos los campos del producto.
     */
    Producto(const std::string& nombre,
             const std::string& codigoBarra,
             const std::string& categoria,
             const std::string& fechaCaducidad,
             const std::string& marca,
             const double precio,
             const int stock)
        : nombre(nombre),
          codigoBarra(codigoBarra),
          categoria(categoria),
          fechaCaducidad(fechaCaducidad),
          marca(marca),
          precio(precio),
          stock(stock) {
    }

    /**
     * @brief Retorna el nombre del producto.
     */
    const std::string& obtenerNombre() const {
        return nombre;
    }

    /**
     * @brief Define el nombre del producto.
     */
    void establecerNombre(const std::string& valor) {
        nombre = valor;
    }

    /**
     * @brief Retorna el codigo de barras.
     */
    const std::string& obtenerCodigoBarra() const {
        return codigoBarra;
    }

    /**
     * @brief Define el codigo de barras.
     */
    void establecerCodigoBarra(const std::string& valor) {
        codigoBarra = valor;
    }

    /**
     * @brief Retorna la categoria del producto.
     */
    const std::string& obtenerCategoria() const {
        return categoria;
    }

    /**
     * @brief Define la categoria del producto.
     */
    void establecerCategoria(const std::string& valor) {
        categoria = valor;
    }

    /**
     * @brief Retorna la fecha de caducidad en formato ISO.
     */
    const std::string& obtenerFechaCaducidad() const {
        return fechaCaducidad;
    }

    /**
     * @brief Define la fecha de caducidad en formato ISO.
     */
    void establecerFechaCaducidad(const std::string& valor) {
        fechaCaducidad = valor;
    }

    /**
     * @brief Retorna la marca del producto.
     */
    const std::string& obtenerMarca() const {
        return marca;
    }

    /**
     * @brief Define la marca del producto.
     */
    void establecerMarca(const std::string& valor) {
        marca = valor;
    }

    /**
     * @brief Retorna el precio del producto.
     */
    double obtenerPrecio() const {
        return precio;
    }

    /**
     * @brief Define el precio del producto.
     */
    void establecerPrecio(const double valor) {
        precio = valor;
    }

    /**
     * @brief Retorna el stock disponible.
     */
    int obtenerStock() const {
        return stock;
    }

    /**
     * @brief Define el stock disponible.
     */
    void establecerStock(const int valor) {
        stock = valor;
    }

    /**
     * @brief Valida reglas de integridad basicas del producto.
     */
    bool esValido() const {
        return !codigoBarra.empty() && precio >= 0.0 && stock >= 0 && fechaIsoValida(fechaCaducidad);
    }

    /**
     * @brief Compara productos por codigo de barras.
     */
    bool operator==(const Producto& otro) const {
        return codigoBarra == otro.codigoBarra;
    }

    /**
     * @brief Ordena productos alfabeticamente por nombre.
     */
    bool operator<(const Producto& otro) const {
        return nombre < otro.nombre;
    }
};
