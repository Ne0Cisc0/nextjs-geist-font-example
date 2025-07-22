# 🧮 CALCULADORA SFML AVANZADA - EDICIÓN FC BARCELONA

## 📋 DESCRIPCIÓN
Calculadora científica avanzada desarrollada en C++ con SFML, con diseño inspirado en los colores del FC Barcelona. Incluye funciones básicas y científicas, historial de operaciones y una interfaz moderna.

## ✨ CARACTERÍSTICAS
- ➕ Operaciones básicas: suma, resta, multiplicación, división
- 🔬 Funciones científicas: raíz cuadrada, potencias, inverso, porcentaje
- 📚 Historial de operaciones (últimas 15 operaciones)
- ⌨️ Soporte para teclado y mouse
- 🎨 Diseño moderno con colores del FC Barcelona
- 🖱️ Efectos hover en botones
- ⚡ Manejo de errores (división por cero, raíz negativa, etc.)

## 🚀 COMPILACIÓN RÁPIDA

### 🪟 WINDOWS (MÁS FÁCIL)

1. **Instalar dependencias:**
   - Descargar Visual Studio Community (gratis): https://visualstudio.microsoft.com/
   - Descargar CMake: https://cmake.org/download/
   - Descargar SFML: https://www.sfml-dev.org/download.php

2. **Configurar SFML:**
   - Extraer SFML en `C:\SFML`
   - O establecer variable de entorno: `set SFML_ROOT=C:\ruta\a\SFML`

3. **Compilar:**
   ```cmd
   cd calculadora-sfml
   compilar_windows.bat
   ```

### 🐧 LINUX (AUTOMÁTICO)

1. **Compilar (instala dependencias automáticamente):**
   ```bash
   cd calculadora-sfml
   ./compilar_linux.sh
   ```

### 🍎 macOS

1. **Instalar Homebrew si no lo tienes:**
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Compilar:**
   ```bash
   cd calculadora-sfml
   ./compilar_linux.sh
   ```

## 🛠️ COMPILACIÓN MANUAL (SI LOS SCRIPTS NO FUNCIONAN)

### Requisitos:
- C++17 o superior
- CMake 3.16+
- SFML 2.5+

### Pasos:
```bash
# 1. Instalar SFML
# Ubuntu/Debian:
sudo apt-get install libsfml-dev cmake build-essential

# Fedora:
sudo dnf install SFML-devel cmake gcc-c++

# Arch Linux:
sudo pacman -S sfml cmake base-devel

# macOS:
brew install sfml cmake

# 2. Compilar
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4  # Linux/Mac
# o
cmake --build . --config Release  # Windows
```

## 🎮 CONTROLES

### 🖱️ Mouse:
- Clic en botones para operaciones
- Botón "H" para mostrar/ocultar historial
- Efectos hover al pasar el mouse

### ⌨️ Teclado:
- **Números:** 0-9, teclado numérico
- **Operaciones:** +, -, *, /
- **Decimal:** . (punto) o , (coma)
- **Calcular:** Enter o =
- **Limpiar:** Esc o C
- **Historial:** H

## 🧮 FUNCIONES DISPONIBLES

### Básicas:
- ➕ Suma
- ➖ Resta  
- ✖️ Multiplicación
- ➗ División

### Científicas:
- √ Raíz cuadrada
- x² Cuadrado
- x³ Cubo
- 1/x Inverso
- % Porcentaje
- ± Cambio de signo

### Especiales:
- 📚 Historial de operaciones
- 🧹 Limpiar (C)
- ⚠️ Manejo de errores

## 🎨 DISEÑO

### Colores FC Barcelona:
- **Azul Marino:** `#0F4C81` - Botones principales
- **Azul Claro:** `#3498DB` - Funciones científicas  
- **Rojo Barça:** `#E74C3C` - Botones especiales
- **Verde Éxito:** `#2ECC71` - Botón igual
- **Gris Elegante:** Números y fondo

## 🐛 SOLUCIÓN DE PROBLEMAS

### Error: "No se pudo cargar arial.ttf"
- **Solución:** El programa funcionará con fuente por defecto
- **Opcional:** Coloca `arial.ttf` en la carpeta del ejecutable

### Error: "SFML no encontrado"
- **Windows:** Verifica que SFML esté en `C:\SFML` o configura `SFML_ROOT`
- **Linux:** Ejecuta `sudo apt-get install libsfml-dev`
- **macOS:** Ejecuta `brew install sfml`

### Error: "CMake no encontrado"
- Instala CMake desde: https://cmake.org/download/
- Asegúrate de que esté en el PATH del sistema

### Error de compilación en Windows:
- Instala Visual Studio Community con "Desarrollo de escritorio con C++"
- Ejecuta el script desde "Developer Command Prompt"

## 📁 ESTRUCTURA DEL PROYECTO
```
calculadora-sfml/
├── main.cpp                 # Código fuente principal
├── CMakeLists.txt           # Configuración de CMake
├── compilar_windows.bat     # Script de compilación Windows
├── compilar_linux.sh        # Script de compilación Linux/Mac
├── INSTRUCCIONES.md         # Este archivo
└── build/                   # Directorio de compilación (se crea automáticamente)
    └── calculadora(.exe)    # Ejecutable final
```

## 🏆 CARACTERÍSTICAS AVANZADAS

- **Historial Inteligente:** Guarda las últimas 15 operaciones
- **Interfaz Responsiva:** Botones con efectos hover
- **Manejo de Errores:** Previene divisiones por cero y operaciones inválidas
- **Formato Inteligente:** Elimina ceros innecesarios en decimales
- **Soporte Completo de Teclado:** Funciona sin mouse
- **Diseño Profesional:** Inspirado en calculadoras modernas

## 📞 SOPORTE

Si tienes problemas:
1. Verifica que tengas todas las dependencias instaladas
2. Usa los scripts automáticos de compilación
3. Revisa la sección de solución de problemas
4. Para Windows, asegúrate de tener Visual Studio instalado

## 🎯 VERSIÓN
**Calculadora SFML Avanzada v2.0**  
*Edición FC Barcelona*

---
*¡Disfruta calculando con estilo Barça! 🔵🔴*
