#!/bin/bash

echo "========================================"
echo "  COMPILADOR AUTOMATICO - CALCULADORA SFML"
echo "  Edicion FC Barcelona"
echo "========================================"
echo

# Función para instalar SFML en diferentes distribuciones
instalar_sfml() {
    echo "SFML no está instalado. Intentando instalar automáticamente..."
    
    if command -v apt-get &> /dev/null; then
        # Ubuntu/Debian
        echo "Detectado sistema Ubuntu/Debian"
        sudo apt-get update
        sudo apt-get install -y libsfml-dev cmake build-essential
    elif command -v yum &> /dev/null; then
        # CentOS/RHEL/Fedora (yum)
        echo "Detectado sistema CentOS/RHEL"
        sudo yum install -y SFML-devel cmake gcc-c++
    elif command -v dnf &> /dev/null; then
        # Fedora (dnf)
        echo "Detectado sistema Fedora"
        sudo dnf install -y SFML-devel cmake gcc-c++
    elif command -v pacman &> /dev/null; then
        # Arch Linux
        echo "Detectado sistema Arch Linux"
        sudo pacman -S --noconfirm sfml cmake base-devel
    elif command -v brew &> /dev/null; then
        # macOS con Homebrew
        echo "Detectado macOS con Homebrew"
        brew install sfml cmake
    else
        echo "ERROR: No se pudo detectar el gestor de paquetes"
        echo "Por favor instala SFML manualmente:"
        echo "- Ubuntu/Debian: sudo apt-get install libsfml-dev"
        echo "- Fedora: sudo dnf install SFML-devel"
        echo "- Arch: sudo pacman -S sfml"
        echo "- macOS: brew install sfml"
        exit 1
    fi
}

# Verificar si CMake está instalado
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake no está instalado"
    echo "Instalando CMake..."
    
    if command -v apt-get &> /dev/null; then
        sudo apt-get install -y cmake
    elif command -v yum &> /dev/null; then
        sudo yum install -y cmake
    elif command -v dnf &> /dev/null; then
        sudo dnf install -y cmake
    elif command -v pacman &> /dev/null; then
        sudo pacman -S --noconfirm cmake
    elif command -v brew &> /dev/null; then
        brew install cmake
    else
        echo "Por favor instala CMake manualmente"
        exit 1
    fi
fi

# Verificar si SFML está instalado
echo "Verificando instalación de SFML..."
if ! pkg-config --exists sfml-all; then
    instalar_sfml
fi

# Crear directorio de compilación
mkdir -p build
cd build

echo "Configurando proyecto con CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo
    echo "ERROR: No se pudo configurar el proyecto"
    echo "Intentando instalar SFML..."
    cd ..
    instalar_sfml
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    
    if [ $? -ne 0 ]; then
        echo "ERROR: Aún no se puede configurar el proyecto"
        echo "Por favor instala SFML manualmente e intenta de nuevo"
        exit 1
    fi
fi

echo "Compilando calculadora..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo
    echo "========================================"
    echo "  COMPILACION EXITOSA!"
    echo "========================================"
    echo
    echo "El ejecutable se encuentra en: build/calculadora"
    echo
    echo "¿Quieres ejecutar la calculadora ahora? (s/n)"
    read -r respuesta
    
    if [[ $respuesta =~ ^[Ss]$ ]]; then
        ./calculadora
    fi
else
    echo
    echo "ERROR: Falló la compilación"
    echo "Revisa los mensajes de error arriba"
    exit 1
fi

cd ..
