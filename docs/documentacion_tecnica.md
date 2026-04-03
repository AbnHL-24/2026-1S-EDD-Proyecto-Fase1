# Documentacion Tecnica (Resumen)

## 1. Alcance implementado

Estructuras activas del sistema:

- `Producto`
- `Nodo<T>`
- `ListaEnlazada`
- `ListaEnlazadaOrdenada`
- `NodoAVL`
- `ArbolAVL`

Se excluyen en esta etapa:

- Arbol B
- Arbol B+
- Carga desde CSV

## 2. Modelo de datos

`Producto` contiene:

- nombre
- codigoBarra
- categoria
- fechaCaducidad
- marca
- precio
- stock

Validacion minima:

- `codigoBarra` no vacio
- `precio >= 0`
- `stock >= 0`
- fecha ISO valida (`YYYY-MM-DD`)

## 3. Estructuras y rol

### ListaEnlazada

- Insercion al frente
- Busqueda secuencial por codigo
- Eliminacion por codigo

### ListaEnlazadaOrdenada

- Insercion ordenada por nombre
- Busqueda por codigo y por nombre
- Eliminacion por codigo

### ArbolAVL

- Ordenado por nombre
- Insercion con rebalanceo
- Busqueda binaria por nombre
- Busqueda por codigo mediante in-order
- Eliminacion por nombre con sucesor in-order

## 4. Reglas clave

- Unicidad de insercion en AVL: `codigoBarra`.
- Convencion de alturas AVL:
  - `altura(nullptr) = -1`
  - hoja = `0`
- Nombres de identificadores en espanol y en ASCII (sin tildes).

## 5. Complejidades esperadas

- Lista no ordenada:
  - buscar: O(n)
  - insertar al frente: O(1)
  - eliminar: O(n)

- Lista ordenada:
  - buscar por codigo: O(n)
  - buscar por nombre: O(n)
  - insertar ordenado: O(n)
  - eliminar: O(n)

- AVL:
  - insertar: O(log n)
  - buscar por nombre: O(log n)
  - eliminar por nombre: O(log n)
  - buscar por codigo: O(n)
  - recorrer in-order: O(n)

## 6. Estado actual

El sistema funciona como mini-catalogo en consola con menu operativo y carga semilla de 1000 productos para pruebas.
