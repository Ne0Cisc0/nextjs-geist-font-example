# Makefile simple para compilar la calculadora SFML
# Alternativa rápida si CMake no funciona

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Detectar sistema operativo
UNAME_S := $(shell uname -s)

# Configuración específica por OS
ifeq ($(UNAME_S),Linux)
    SFML_FLAGS += -lGL
endif

ifeq ($(UNAME_S),Darwin)
    # macOS
    CXXFLAGS += -I/usr/local/include
    LDFLAGS += -L/usr/local/lib
endif

TARGET = calculadora
SOURCE = main.cpp

.PHONY: all clean install run help

all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo "Compilando calculadora SFML..."
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS) $(SFML_FLAGS)
	@echo "¡Compilación exitosa!"
	@echo "Ejecuta con: ./$(TARGET)"

clean:
	@echo "Limpiando archivos..."
	rm -f $(TARGET)
	rm -rf build/

install:
	@echo "Instalando dependencias..."
ifeq ($(shell command -v apt-get 2> /dev/null),)
ifeq ($(shell command -v dnf 2> /dev/null),)
ifeq ($(shell command -v pacman 2> /dev/null),)
ifeq ($(shell command -v brew 2> /dev/null),)
	@echo "No se pudo detectar el gestor de paquetes"
	@echo "Instala SFML manualmente"
else
	brew install sfml
endif
else
	sudo pacman -S sfml
endif
else
	sudo dnf install SFML-devel
endif
else
	sudo apt-get update && sudo apt-get install libsfml-dev
endif

run: $(TARGET)
	./$(TARGET)

help:
	@echo "Comandos disponibles:"
	@echo "  make          - Compilar la calculadora"
	@echo "  make clean    - Limpiar archivos compilados"
	@echo "  make install  - Instalar dependencias SFML"
	@echo "  make run      - Compilar y ejecutar"
	@echo "  make help     - Mostrar esta ayuda"
	@echo ""
	@echo "Si tienes problemas, usa los scripts:"
	@echo "  Windows: compilar_windows.bat"
	@echo "  Linux/Mac: ./compilar_linux.sh"
