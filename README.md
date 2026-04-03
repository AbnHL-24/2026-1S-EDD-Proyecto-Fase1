# Mini Catalogo de Productos (Listas + AVL)

Aplicacion de consola en C++20 para gestionar un catalogo de productos usando estructuras implementadas manualmente:

- Lista enlazada no ordenada
- Lista enlazada ordenada por nombre
- Arbol AVL ordenado por nombre

> Alcance actual: se excluyen Arbol B, Arbol B+ y carga por CSV.

## Requisitos

- C++20
- CMake (si esta disponible) o compilador g++ (CLion/MinGW)

## Compilacion

### Con CMake

```powershell
cmake -S . -B build -G Ninja
cmake --build build
```

### Con g++ (alternativo)

```powershell
g++ -std=gnu++20 -Iinclude main.cpp src/ListaEnlazada.cpp src/ListaEnlazadaOrdenada.cpp src/ArbolAVL.cpp -o mini_catalogo.exe
```

## Ejecucion

```powershell
.\build\src.exe
```

o

```powershell
.\mini_catalogo.exe
```

## Funcionalidades actuales

1. Agregar producto manualmente
2. Buscar por nombre (AVL)
3. Buscar por codigo (comparativa listas/AVL)
4. Eliminar por codigo (propagado a listas y AVL)
5. Listar catalogo ordenado por nombre (AVL in-order)
6. Ver estado de estructuras
7. Cargar 1000 datos quemados para pruebas

## Notas tecnicas

- Unicidad en AVL por `codigoBarra`.
- En AVL, `buscarPorCodigo` es O(n) (recorrido in-order completo).
- Convencion de alturas AVL:
  - `altura(nullptr) = -1`
  - hoja = `0`
