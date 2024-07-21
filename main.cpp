#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    // Configura las palas y la pelota
    sf::RectangleShape pala1(sf::Vector2f(10, 100));
    sf::RectangleShape pala2(sf::Vector2f(10, 100));
    sf::CircleShape pelota(10);


    // Inicializa las posiciones de las palas
    pala1.setPosition(20, 250);
    pala2.setPosition(770, 250);

    // Velocidad de las palas y la pelota
    float palaSpeed = .1f;
    sf::Vector2f pelotaSpeed(3.0f, 2.0f); // Velocidad inicial de la pelota

    // Contadores de puntos
    int puntosJugador1 = 0;
    int puntosJugador2 = 0;

    // Fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return 1;
    }

    // Texto para mostrar los puntos
    sf::Text textoPuntos;
    textoPuntos.setFont(font);
    textoPuntos.setCharacterSize(24);
    textoPuntos.setFillColor(sf::Color::White);

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento de las palas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pala1.move(0, -palaSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pala1.move(0, palaSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pala2.move(0, -palaSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pala2.move(0, palaSpeed);
        }

        // Movimiento de la pelota
        pelota.move(pelotaSpeed);
        if (pelota.getPosition().y <= 0 || pelota.getPosition().y >= 590) {
            // Rebote en las paredes superior e inferior
            pelotaSpeed.y = -pelotaSpeed.y;
        }

        // Colisiones con las palas
        if (pelota.getGlobalBounds().intersects(pala1.getGlobalBounds()) ||
            pelota.getGlobalBounds().intersects(pala2.getGlobalBounds())) {
            pelotaSpeed.x = -pelotaSpeed.x;
        }



        // Actualiza el texto de los puntos
        textoPuntos.setString("Jugador 1: " + std::to_string(puntosJugador1) +
                              " - Jugador 2: " + std::to_string(puntosJugador2));

        window.clear();
        // Dibuja las palas y la pelota
        window.draw(pala1);
        window.draw(pala2);
        window.draw(pelota);
        // Dibuja los puntos
        window.draw(textoPuntos);

        window.display();
    }

    return 0;
}
