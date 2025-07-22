@echo off
echo ========================================
echo  COMPILADOR AUTOMATICO - CALCULADORA SFML
echo  Edicion FC Barcelona
echo ========================================
echo.

REM Verificar si existe Visual Studio
where cl >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Buscando Visual Studio...
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
    if %ERRORLEVEL% NEQ 0 (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
    )
)

REM Verificar si CMake está instalado
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake no está instalado o no está en el PATH
    echo Por favor instala CMake desde: https://cmake.org/download/
    pause
    exit /b 1
)

REM Crear directorio de compilación
if not exist "build" mkdir build
cd build

echo Configurando proyecto con CMake...
cmake .. -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: No se pudo configurar el proyecto
    echo Asegurate de tener SFML instalado correctamente
    echo.
    echo SOLUCION RAPIDA:
    echo 1. Descarga SFML desde: https://www.sfml-dev.org/download.php
    echo 2. Extrae en C:\SFML
    echo 3. Ejecuta: set SFML_ROOT=C:\SFML
    echo 4. Vuelve a ejecutar este script
    pause
    exit /b 1
)

echo Compilando calculadora...
cmake --build . --config Release

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo  COMPILACION EXITOSA!
    echo ========================================
    echo.
    echo El ejecutable se encuentra en: build\Release\calculadora.exe
    echo o en: build\calculadora.exe
    echo.
    echo Presiona cualquier tecla para ejecutar la calculadora...
    pause >nul
    
    REM Intentar ejecutar la calculadora
    if exist "Release\calculadora.exe" (
        start Release\calculadora.exe
    ) else if exist "calculadora.exe" (
        start calculadora.exe
    ) else (
        echo No se encontro el ejecutable
    )
) else (
    echo.
    echo ERROR: Fallo la compilacion
    echo Revisa los mensajes de error arriba
    pause
)

cd ..
