cmake_minimum_required(VERSION 3.16)
project(CalculadoraSFML)

# Configurar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar SFML
find_package(sfml-all REQUIRED)

# Si no encuentra SFML automáticamente, intentar con pkg-config
if(NOT sfml-all_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SFML REQUIRED sfml-all>=2.5)
endif()

# Crear el ejecutable
add_executable(calculadora main.cpp)

# Enlazar con SFML
if(sfml-all_FOUND)
    target_link_libraries(calculadora sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(calculadora ${SFML_LIBRARIES})
    target_include_directories(calculadora PRIVATE ${SFML_INCLUDE_DIRS})
    target_compile_options(calculadora PRIVATE ${SFML_CFLAGS_OTHER})
endif()

# Para Windows, copiar las DLLs necesarias
if(WIN32)
    # Copiar DLLs de SFML al directorio de salida
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(SFML_SUFFIX "-d")
    else()
        set(SFML_SUFFIX "")
    endif()
    
    # Intentar encontrar las DLLs de SFML
    find_file(SFML_GRAPHICS_DLL "sfml-graphics${SFML_SUFFIX}-2.dll" PATHS ${SFML_ROOT}/bin)
    find_file(SFML_WINDOW_DLL "sfml-window${SFML_SUFFIX}-2.dll" PATHS ${SFML_ROOT}/bin)
    find_file(SFML_SYSTEM_DLL "sfml-system${SFML_SUFFIX}-2.dll" PATHS ${SFML_ROOT}/bin)
    
    if(SFML_GRAPHICS_DLL AND SFML_WINDOW_DLL AND SFML_SYSTEM_DLL)
        add_custom_command(TARGET calculadora POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_GRAPHICS_DLL} ${SFML_WINDOW_DLL} ${SFML_SYSTEM_DLL}
            $<TARGET_FILE_DIR:calculadora>)
    endif()
endif()
