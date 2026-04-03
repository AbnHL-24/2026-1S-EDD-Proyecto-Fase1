# Reporte Tecnico - Fase actual (Listas enlazadas + AVL)

## 1. Introduccion

Este documento resume el diseno de las estructuras de datos implementadas hasta el momento en el
proyecto de catalogo de productos, asi como el analisis de complejidad temporal (Big-O) para sus
operaciones principales.

Alcance actual implementado:

- Lista enlazada simple no ordenada
- Lista enlazada simple ordenada por nombre
- Arbol AVL ordenado por nombre
- Modelo `Producto` y nodos de soporte (`Nodo<T>`, `NodoAVL`)

Fuera de alcance en esta fase:

- Arbol B
- Arbol B+
- Carga robusta desde CSV
- Visualizacion `.dot`/imagenes

---

## 2. Modelo de datos

### 2.1 Estructura `Producto`

La estructura `Producto` representa la entidad principal del sistema con los siguientes campos:

- `nombre`
- `codigoBarra`
- `categoria`
- `fechaCaducidad` (formato ISO `YYYY-MM-DD`)
- `marca`
- `precio`
- `stock`

Validaciones implementadas (`esValido`):

- `codigoBarra` no vacio
- `precio >= 0`
- `stock >= 0`
- fecha ISO valida (incluyendo validacion de mes, dia y bisiesto)

Ademas:

- `operator==` compara por `codigoBarra`
- `operator<` ordena alfabeticamente por `nombre`

---

## 3. Diseno de estructuras implementadas

### 3.1 Nodo generico para listas (`Nodo<T>`)

#### Proposito

Proveer una base simple y reusable para listas enlazadas.

#### Diseno

Cada nodo almacena:

- `dato` de tipo `T`
- puntero `siguiente`

Operaciones basicas:

- obtener/establecer dato
- obtener/establecer siguiente nodo

#### Justificacion

Permite implementar listas enlazadas sin depender de contenedores STL prohibidos para esta tarea.

---

### 3.2 Lista enlazada no ordenada (`ListaEnlazada`)

#### Proposito

Servir como estructura secuencial base para insercion simple y busqueda lineal por codigo.

#### Diseno interno

Atributos principales:

- `cabeza_`: puntero al primer nodo
- `tamano_`: cantidad de elementos
- `ultimoTiempoBusquedaNanosegundos_`: medicion de la ultima busqueda

Operaciones implementadas:

- `insertarAlFrente(const Producto&)`
- `buscar(const std::string& codigoBarra)` (version mutable y const)
- `eliminar(const std::string& codigoBarra)`
- `recorrer(callback)`
- consultas: `obtenerTamano()`, `estaVacia()`, `obtenerPrimero()`
- medicion: `obtenerUltimoTiempoBusquedaNanosegundos()`

#### Decisiones de diseno

- Insercion al frente para costo O(1).
- Busqueda por `codigoBarra` de forma secuencial.
- Liberacion de memoria en destructor recorriendo todos los nodos.

---

### 3.3 Lista enlazada ordenada (`ListaEnlazadaOrdenada`)

#### Proposito

Mantener productos ordenados alfabeticamente por nombre dentro de una lista simple.

#### Diseno interno

Atributos principales:

- `cabeza_`
- `tamano_`
- `ultimoTiempoBusquedaNanosegundos_`

Operaciones implementadas:

- `insertarOrdenado(const Producto&)`
- `buscar(const std::string& codigoBarra)` (secuencial)
- `buscarPorNombre(const std::string& nombre)` (secuencial)
- `eliminar(const std::string& codigoBarra)`
- `recorrer(callback)`
- consultas de estado y tamano
- medicion de ultima busqueda

#### Decisiones de diseno

- Mantener orden por nombre en insercion para facilitar recorridos ordenados.
- Aunque este orden existe, la busqueda por codigo sigue siendo lineal.
- Se conserva implementacion manual sin listas STL.

---

### 3.4 Arbol AVL (`ArbolAVL`)

#### Proposito

Soportar busqueda binaria eficiente por nombre y mantener el catalogo balanceado automaticamente.

#### Diseno interno

Atributos principales:

- `raiz_`
- `tamano_`

Estructura de nodo (`NodoAVL`):

- `Producto dato`
- `izquierdo`
- `derecho`
- `altura`

Operaciones privadas clave:

- `altura`, `actualizarAltura`
- `rotarDerecha`, `rotarIzquierda`
- `rebalancear`
- `insertarRec`, `eliminarRec`
- `buscarRec`, `buscarPorCodigoRec`
- `inOrderRec`, `liberarRec`

Operaciones publicas:

- `insertar(const Producto&)`
- `buscar(const std::string& nombre)`
- `buscarPorCodigo(const std::string& codigoBarra)`
- `eliminar(const std::string& nombre)`
- `recorrerInOrder(callback)`
- `obtenerTamano()`, `estaVacia()`, `obtenerAltura()`

#### Reglas relevantes implementadas

- Convencion de alturas:
  - `altura(nullptr) = -1`
  - nodo hoja = `0`
- Balance AVL mediante factor `altura(izq) - altura(der)`
- Insercion rechaza codigo de barras duplicado (validado contra arbol)
- Eliminacion por nombre con sucesor in-order en caso de dos hijos

---

## 4. Coherencia entre estructuras (estado actual)

En el flujo actual de insercion del programa principal se intenta insertar en:

1. lista no ordenada
2. lista ordenada
3. AVL

Si una insercion intermedia falla, se realiza rollback sobre las estructuras previas para evitar
inconsistencia parcial.

En eliminacion por codigo:

- se localiza primero en AVL (por codigo, recorrido in-order),
- luego se elimina en AVL (por nombre) y en ambas listas por codigo.

---

## 5. Analisis Big-O (listas y AVL)

### 5.1 Tabla de complejidades

| Estructura | Operacion | Complejidad |
|---|---|---|
| ListaEnlazada | insertar al frente | O(1) |
| ListaEnlazada | buscar por codigo | O(n) |
| ListaEnlazada | eliminar por codigo | O(n) |
| ListaEnlazada | recorrer | O(n) |
| ListaEnlazadaOrdenada | insertar ordenado por nombre | O(n) |
| ListaEnlazadaOrdenada | buscar por codigo | O(n) |
| ListaEnlazadaOrdenada | buscar por nombre | O(n) |
| ListaEnlazadaOrdenada | eliminar por codigo | O(n) |
| ListaEnlazadaOrdenada | recorrer | O(n) |
| ArbolAVL | insertar por nombre | O(log n) |
| ArbolAVL | buscar por nombre | O(log n) |
| ArbolAVL | eliminar por nombre | O(log n) |
| ArbolAVL | buscar por codigo (in-order) | O(n) |
| ArbolAVL | recorrido in-order | O(n) |

### 5.2 Justificacion breve

#### Lista no ordenada

- Buscar/eliminar: requiere recorrer nodos hasta encontrar coincidencia o llegar al final.
- Insertar al frente: solo actualiza puntero de cabeza.

#### Lista ordenada

- Insertar: necesita ubicar la posicion correcta (recorrido lineal).
- Buscar por codigo/nombre: implementacion secuencial nodo a nodo.

#### AVL

- Buscar/insercion/eliminacion por nombre: el arbol mantiene altura balanceada, por eso la
  profundidad es logaritmica.
- Buscar por codigo: no es la clave de orden del arbol, por lo que se recorre in-order completo en
  el peor caso.

---

## 6. Limitaciones actuales frente al enunciado

Aun pendientes para cumplimiento total:

- Arbol B por fecha de caducidad
- Arbol B+ por categoria
- Carga robusta desde CSV con log de errores
- Medicion formal y reporte estadistico completo (N consultas, M repeticiones)
- Generacion de archivos `.dot` e imagenes

---

## 7. Conclusiones de la fase

- Se implemento correctamente la base estructural del proyecto con listas enlazadas y AVL desde
  cero.
- El sistema ya permite altas, busquedas, eliminacion y recorrido ordenado por nombre.
- El analisis Big-O observado coincide con el comportamiento esperado:
  - listas con costo lineal para busqueda,
  - AVL con mejora logaritmica para operaciones por clave primaria (`nombre`).
- Esta fase deja preparado el camino para integrar Arbol B, Arbol B+ y el pipeline de carga CSV.
