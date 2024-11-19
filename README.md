# Oscilador Armónico Cuántico: Guía Completa

Este proyecto incluye un programa en C y un script en Python para calcular y graficar las funciones de onda o densidades de probabilidad del oscilador armónico cuántico. A continuación, se explica qué necesita, cómo funciona el programa y cómo instalarlo.

---

## ¿Qué Necesita?

1. **Archivos del Proyecto**:
   - **`numerov.c`**: Código en C que calcula las funciones de onda y densidades de probabilidad resolviendo el problema del oscilador armónico.
   - **`graf.py`**: Script en Python para graficar los resultados generados por el programa en C.
   - **`Makefile`**: Archivo que automatiza la instalación de dependencias, compilación y ejecución.

2. **Herramientas y Bibliotecas**:
   - Compilador C (`gcc`).
   - Biblioteca GNU Scientific Library (GSL).
   - Python (3.6 o superior) con las bibliotecas `pandas` y `matplotlib`.

---

## ¿Cómo Funciona?

### **Código en C (`numerov.c`)**

1. **Construcción del Hamiltoniano**:
   - Representa la energía total del sistema como una matriz en un espacio discreto.
   - La diagonal principal incluye términos de energía cinética y potencial, mientras que las diagonales adyacentes incluyen la contribución de la energía cinética.

2. **Diagonalización de la Matriz**:
   - Usa la biblioteca GSL para calcular valores propios (energías) y vectores propios (funciones de onda).

3. **Opciones Interactivas**:
   - Seleccionar entre funciones de onda (`ψ_n(x)`) o densidades de probabilidad (`ψ_n^2(x)`).
   - Escoger el nivel de energía cuántico (`n`, de 0 a 3).

4. **Resultados**:
   - Guarda los datos en un archivo `results.csv` para graficarlos.

### **Script Python (`graf.py`)**

- Lee los datos de `results.csv` y grafica:
  - Función de onda `ψ(x)` si se seleccionó la opción correspondiente.
  - Densidad de probabilidad `ψ²(x)` si fue la opción elegida.

### **Makefile**

1. Automatiza:
   - Instalación de dependencias.
   - Compilación del programa.
   - Ejecución tanto del programa en C como del script Python.

2. Incluye un comando de limpieza para eliminar archivos generados.

---

## Instalación y Configuración

### En Linux

1. **Instalar Dependencias**:
   - Para sistemas basados en Debian/Ubuntu:
     ```bash
     sudo apt-get update
     sudo apt-get install -y build-essential libgsl-dev python3 python3-pip
     ```
   - Para sistemas basados en Fedora:
     ```bash
     sudo dnf install -y gcc gsl-devel python3 python3-pip
     ```

2. **Instalar Bibliotecas Python**:
   ```bash
   pip3 install pandas matplotlib

