#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

class CalculadoraAvanzada {
private:
    sf::RenderWindow window;
    sf::Font font;
    
    // Variables de entrada y resultado
    std::string pantalla = "0";
    std::string operacion = "";
    double numeroAnterior = 0;
    double numeroActual = 0;
    bool nuevaOperacion = true;
    bool puntoDecimal = false;
    
    // Historial de operaciones
    std::vector<std::string> historial;
    bool mostrarHistorial = false;
    
    // Colores mejorados
    sf::Color azulOscuro{15, 76, 129};
    sf::Color azulClaro{52, 152, 219};
    sf::Color rojoBarca{231, 76, 60};
    sf::Color verdeExito{46, 204, 113};
    sf::Color grisOscuro{52, 73, 94};
    sf::Color grisClarito{236, 240, 241};
    sf::Color blancoTexto{255, 255, 255};
    sf::Color negroTexto{44, 62, 80};
    
    // Elementos de la interfaz
    sf::RectangleShape pantallaPrincipal;
    sf::Text textoPantalla;
    sf::RectangleShape panelHistorial;
    sf::Text tituloHistorial;
    std::vector<sf::Text> textosHistorial;
    
    // Botones mejorados
    struct Boton {
        sf::RectangleShape forma;
        sf::Text texto;
        std::string accion;
        sf::Color colorNormal;
        sf::Color colorHover;
        bool esHover = false;
    };
    
    std::vector<Boton> botones;

public:
    CalculadoraAvanzada() : window(sf::VideoMode(800, 600), "Calculadora SFML Avanzada - FC Barcelona Edition") {
        if (!font.loadFromFile("arial.ttf")) {
            // Si no encuentra arial.ttf, usar fuente por defecto del sistema
            std::cout << "Advertencia: No se pudo cargar arial.ttf, usando fuente por defecto\n";
        }
        
        inicializarInterfaz();
        crearBotones();
    }
    
    void inicializarInterfaz() {
        // Pantalla principal
        pantallaPrincipal.setSize(sf::Vector2f(760, 80));
        pantallaPrincipal.setPosition(20, 20);
        pantallaPrincipal.setFillColor(grisOscuro);
        pantallaPrincipal.setOutlineThickness(3);
        pantallaPrincipal.setOutlineColor(azulOscuro);
        
        // Texto de la pantalla
        textoPantalla.setFont(font);
        textoPantalla.setCharacterSize(36);
        textoPantalla.setFillColor(blancoTexto);
        textoPantalla.setString("0");
        
        // Panel de historial
        panelHistorial.setSize(sf::Vector2f(200, 450));
        panelHistorial.setPosition(580, 120);
        panelHistorial.setFillColor(grisClarito);
        panelHistorial.setOutlineThickness(2);
        panelHistorial.setOutlineColor(azulClaro);
        
        // Título del historial
        tituloHistorial.setFont(font);
        tituloHistorial.setCharacterSize(18);
        tituloHistorial.setFillColor(negroTexto);
        tituloHistorial.setString("Historial");
        tituloHistorial.setPosition(620, 130);
    }
    
    void crearBotones() {
        // Definir botones con sus propiedades
        struct InfoBoton {
            std::string texto;
            std::string accion;
            int fila, columna;
            sf::Color color;
            sf::Color colorHover;
        };
        
        std::vector<InfoBoton> infosBotones = {
            // Fila 1
            {"C", "clear", 0, 0, rojoBarca, sf::Color(192, 57, 43)},
            {"±", "cambiar_signo", 0, 1, grisOscuro, sf::Color(127, 140, 141)},
            {"√", "raiz", 0, 2, azulClaro, sf::Color(41, 128, 185)},
            {"÷", "dividir", 0, 3, azulOscuro, sf::Color(21, 67, 96)},
            
            // Fila 2
            {"7", "7", 1, 0, grisClarito, sf::Color(189, 195, 199)},
            {"8", "8", 1, 1, grisClarito, sf::Color(189, 195, 199)},
            {"9", "9", 1, 2, grisClarito, sf::Color(189, 195, 199)},
            {"×", "multiplicar", 1, 3, azulOscuro, sf::Color(21, 67, 96)},
            
            // Fila 3
            {"4", "4", 2, 0, grisClarito, sf::Color(189, 195, 199)},
            {"5", "5", 2, 1, grisClarito, sf::Color(189, 195, 199)},
            {"6", "6", 2, 2, grisClarito, sf::Color(189, 195, 199)},
            {"-", "restar", 2, 3, azulOscuro, sf::Color(21, 67, 96)},
            
            // Fila 4
            {"1", "1", 3, 0, grisClarito, sf::Color(189, 195, 199)},
            {"2", "2", 3, 1, grisClarito, sf::Color(189, 195, 199)},
            {"3", "3", 3, 2, grisClarito, sf::Color(189, 195, 199)},
            {"+", "sumar", 3, 3, azulOscuro, sf::Color(21, 67, 96)},
            
            // Fila 5
            {"0", "0", 4, 0, grisClarito, sf::Color(189, 195, 199)},
            {".", "punto", 4, 1, grisClarito, sf::Color(189, 195, 199)},
            {"=", "igual", 4, 2, verdeExito, sf::Color(39, 174, 96)},
            {"H", "historial", 4, 3, rojoBarca, sf::Color(192, 57, 43)},
            
            // Funciones científicas adicionales
            {"x²", "cuadrado", 5, 0, azulClaro, sf::Color(41, 128, 185)},
            {"x³", "cubo", 5, 1, azulClaro, sf::Color(41, 128, 185)},
            {"1/x", "inverso", 5, 2, azulClaro, sf::Color(41, 128, 185)},
            {"%", "porcentaje", 5, 3, azulClaro, sf::Color(41, 128, 185)}
        };
        
        for (const auto& info : infosBotones) {
            Boton boton;
            
            // Configurar forma del botón
            boton.forma.setSize(sf::Vector2f(90, 60));
            boton.forma.setPosition(20 + info.columna * 100, 120 + info.fila * 70);
            boton.colorNormal = info.color;
            boton.colorHover = info.colorHover;
            boton.forma.setFillColor(info.color);
            boton.forma.setOutlineThickness(2);
            boton.forma.setOutlineColor(sf::Color(127, 140, 141));
            
            // Configurar texto del botón
            boton.texto.setFont(font);
            boton.texto.setString(info.texto);
            boton.texto.setCharacterSize(24);
            boton.texto.setFillColor((info.color == grisClarito) ? negroTexto : blancoTexto);
            
            // Centrar texto en el botón
            sf::FloatRect textoBounds = boton.texto.getLocalBounds();
            boton.texto.setPosition(
                boton.forma.getPosition().x + (90 - textoBounds.width) / 2,
                boton.forma.getPosition().y + (60 - textoBounds.height) / 2 - 5
            );
            
            boton.accion = info.accion;
            botones.push_back(boton);
        }
    }
    
    void actualizarPantalla() {
        textoPantalla.setString(pantalla);
        
        // Ajustar tamaño de fuente si el texto es muy largo
        sf::FloatRect textoBounds = textoPantalla.getLocalBounds();
        if (textoBounds.width > 720) {
            textoPantalla.setCharacterSize(24);
        } else {
            textoPantalla.setCharacterSize(36);
        }
        
        // Alinear texto a la derecha
        textoBounds = textoPantalla.getLocalBounds();
        textoPantalla.setPosition(760 - textoBounds.width, 35);
    }
    
    void procesarNumero(const std::string& num) {
        if (nuevaOperacion) {
            pantalla = num;
            nuevaOperacion = false;
            puntoDecimal = false;
        } else {
            if (pantalla == "0") {
                pantalla = num;
            } else {
                pantalla += num;
            }
        }
    }
    
    void procesarPunto() {
        if (nuevaOperacion) {
            pantalla = "0.";
            nuevaOperacion = false;
            puntoDecimal = true;
        } else if (!puntoDecimal) {
            pantalla += ".";
            puntoDecimal = true;
        }
    }
    
    void procesarOperacion(const std::string& op) {
        if (!nuevaOperacion) {
            calcular();
        }
        
        numeroAnterior = std::stod(pantalla);
        operacion = op;
        nuevaOperacion = true;
        puntoDecimal = false;
    }
    
    void calcular() {
        if (operacion.empty()) return;
        
        numeroActual = std::stod(pantalla);
        double resultado = 0;
        std::string operacionTexto = formatearNumero(numeroAnterior) + " " + operacion + " " + formatearNumero(numeroActual);
        
        try {
            if (operacion == "sumar") {
                resultado = numeroAnterior + numeroActual;
                operacionTexto = formatearNumero(numeroAnterior) + " + " + formatearNumero(numeroActual);
            } else if (operacion == "restar") {
                resultado = numeroAnterior - numeroActual;
                operacionTexto = formatearNumero(numeroAnterior) + " - " + formatearNumero(numeroActual);
            } else if (operacion == "multiplicar") {
                resultado = numeroAnterior * numeroActual;
                operacionTexto = formatearNumero(numeroAnterior) + " × " + formatearNumero(numeroActual);
            } else if (operacion == "dividir") {
                if (numeroActual == 0) {
                    pantalla = "Error: División por cero";
                    return;
                }
                resultado = numeroAnterior / numeroActual;
                operacionTexto = formatearNumero(numeroAnterior) + " ÷ " + formatearNumero(numeroActual);
            }
            
            pantalla = formatearNumero(resultado);
            
            // Agregar al historial
            std::string entradaHistorial = operacionTexto + " = " + pantalla;
            historial.push_back(entradaHistorial);
            if (historial.size() > 15) {
                historial.erase(historial.begin());
            }
            
        } catch (...) {
            pantalla = "Error";
        }
        
        operacion = "";
        nuevaOperacion = true;
        puntoDecimal = false;
    }
    
    void procesarFuncionEspecial(const std::string& funcion) {
        double num = std::stod(pantalla);
        double resultado = 0;
        std::string operacionTexto = "";
        
        try {
            if (funcion == "raiz") {
                if (num < 0) {
                    pantalla = "Error: Raíz negativa";
                    return;
                }
                resultado = std::sqrt(num);
                operacionTexto = "√" + formatearNumero(num);
            } else if (funcion == "cuadrado") {
                resultado = num * num;
                operacionTexto = formatearNumero(num) + "²";
            } else if (funcion == "cubo") {
                resultado = num * num * num;
                operacionTexto = formatearNumero(num) + "³";
            } else if (funcion == "inverso") {
                if (num == 0) {
                    pantalla = "Error: División por cero";
                    return;
                }
                resultado = 1.0 / num;
                operacionTexto = "1/" + formatearNumero(num);
            } else if (funcion == "porcentaje") {
                resultado = num / 100.0;
                operacionTexto = formatearNumero(num) + "%";
            } else if (funcion == "cambiar_signo") {
                resultado = -num;
                operacionTexto = "-(" + formatearNumero(num) + ")";
            }
            
            pantalla = formatearNumero(resultado);
            
            // Agregar al historial
            std::string entradaHistorial = operacionTexto + " = " + pantalla;
            historial.push_back(entradaHistorial);
            if (historial.size() > 15) {
                historial.erase(historial.begin());
            }
            
        } catch (...) {
            pantalla = "Error";
        }
        
        nuevaOperacion = true;
        puntoDecimal = false;
    }
    
    std::string formatearNumero(double num) {
        std::ostringstream oss;
        if (num == static_cast<long long>(num)) {
            oss << static_cast<long long>(num);
        } else {
            oss << std::fixed << std::setprecision(6) << num;
            std::string str = oss.str();
            // Eliminar ceros finales
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            str.erase(str.find_last_not_of('.') + 1, std::string::npos);
            return str;
        }
        return oss.str();
    }
    
    void limpiar() {
        pantalla = "0";
        operacion = "";
        numeroAnterior = 0;
        numeroActual = 0;
        nuevaOperacion = true;
        puntoDecimal = false;
    }
    
    void actualizarHistorial() {
        textosHistorial.clear();
        
        for (size_t i = 0; i < historial.size() && i < 15; ++i) {
            sf::Text texto;
            texto.setFont(font);
            texto.setCharacterSize(12);
            texto.setFillColor(negroTexto);
            texto.setString(historial[historial.size() - 1 - i]);
            texto.setPosition(590, 160 + i * 25);
            textosHistorial.push_back(texto);
        }
    }
    
    void manejarEventos() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Manejo del mouse
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                
                for (auto& boton : botones) {
                    if (boton.forma.getGlobalBounds().contains(mousePos)) {
                        if (!boton.esHover) {
                            boton.esHover = true;
                            boton.forma.setFillColor(boton.colorHover);
                        }
                    } else {
                        if (boton.esHover) {
                            boton.esHover = false;
                            boton.forma.setFillColor(boton.colorNormal);
                        }
                    }
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                
                for (const auto& boton : botones) {
                    if (boton.forma.getGlobalBounds().contains(mousePos)) {
                        procesarAccion(boton.accion);
                        break;
                    }
                }
            }
            
            // Manejo del teclado
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num0: case sf::Keyboard::Numpad0: procesarNumero("0"); break;
                    case sf::Keyboard::Num1: case sf::Keyboard::Numpad1: procesarNumero("1"); break;
                    case sf::Keyboard::Num2: case sf::Keyboard::Numpad2: procesarNumero("2"); break;
                    case sf::Keyboard::Num3: case sf::Keyboard::Numpad3: procesarNumero("3"); break;
                    case sf::Keyboard::Num4: case sf::Keyboard::Numpad4: procesarNumero("4"); break;
                    case sf::Keyboard::Num5: case sf::Keyboard::Numpad5: procesarNumero("5"); break;
                    case sf::Keyboard::Num6: case sf::Keyboard::Numpad6: procesarNumero("6"); break;
                    case sf::Keyboard::Num7: case sf::Keyboard::Numpad7: procesarNumero("7"); break;
                    case sf::Keyboard::Num8: case sf::Keyboard::Numpad8: procesarNumero("8"); break;
                    case sf::Keyboard::Num9: case sf::Keyboard::Numpad9: procesarNumero("9"); break;
                    case sf::Keyboard::Period: case sf::Keyboard::Comma: procesarPunto(); break;
                    case sf::Keyboard::Add: procesarOperacion("sumar"); break;
                    case sf::Keyboard::Subtract: procesarOperacion("restar"); break;
                    case sf::Keyboard::Multiply: procesarOperacion("multiplicar"); break;
                    case sf::Keyboard::Divide: procesarOperacion("dividir"); break;
                    case sf::Keyboard::Enter: case sf::Keyboard::Equal: calcular(); break;
                    case sf::Keyboard::Escape: case sf::Keyboard::C: limpiar(); break;
                    case sf::Keyboard::H: mostrarHistorial = !mostrarHistorial; break;
                }
            }
        }
    }
    
    void procesarAccion(const std::string& accion) {
        if (accion >= "0" && accion <= "9") {
            procesarNumero(accion);
        } else if (accion == "punto") {
            procesarPunto();
        } else if (accion == "sumar" || accion == "restar" || accion == "multiplicar" || accion == "dividir") {
            procesarOperacion(accion);
        } else if (accion == "igual") {
            calcular();
        } else if (accion == "clear") {
            limpiar();
        } else if (accion == "historial") {
            mostrarHistorial = !mostrarHistorial;
        } else {
            procesarFuncionEspecial(accion);
        }
    }
    
    void dibujar() {
        window.clear(sf::Color(236, 240, 241));
        
        // Dibujar pantalla
        window.draw(pantallaPrincipal);
        actualizarPantalla();
        window.draw(textoPantalla);
        
        // Dibujar botones
        for (const auto& boton : botones) {
            window.draw(boton.forma);
            window.draw(boton.texto);
        }
        
        // Dibujar historial si está activado
        if (mostrarHistorial) {
            window.draw(panelHistorial);
            window.draw(tituloHistorial);
            
            actualizarHistorial();
