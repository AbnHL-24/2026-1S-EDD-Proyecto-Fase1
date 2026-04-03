# Manual de Usuario (Resumen)

## Inicio

Al ejecutar el programa se muestra un menu numerado. Seleccione una opcion y presione Enter.

## Opciones del menu

### 1) Agregar producto

Solicita:

- nombre
- codigo de barras
- categoria
- fecha caducidad (YYYY-MM-DD)
- marca
- precio
- stock

Valida integridad del producto y evita codigo de barras duplicado.

### 2) Buscar por nombre (AVL)

Busca por nombre exacto y muestra los datos del producto si existe.

### 3) Buscar por codigo (comparativa)

Busca por codigo en:

- lista no ordenada
- lista ordenada
- AVL (recorrido in-order)

Muestra tiempos de busqueda de listas en nanosegundos.

### 4) Eliminar producto por codigo

Ubica producto por codigo y elimina en las tres estructuras.

### 5) Listar catalogo ordenado

Muestra los productos en orden alfabetico por nombre (recorrido in-order de AVL).

### 6) Ver estado

Muestra:

- tamano de lista no ordenada
- tamano de lista ordenada
- tamano de AVL
- altura de AVL

### 7) Cargar 1000 datos quemados

Inserta 1000 productos generados automaticamente para pruebas.

### 0) Salir

Finaliza la aplicacion.

## Recomendaciones de uso

- Use opcion 7 para pruebas rapidas de rendimiento.
- Luego use opciones 3, 5 y 6 para validar comportamiento del catalogo.
