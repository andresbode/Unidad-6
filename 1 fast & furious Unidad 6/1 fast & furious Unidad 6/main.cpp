#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fast & Furious");

    // Definir la posici�n inicial y velocidad del objeto
    sf::Vector2f position(100.0f, 300.0f);
    sf::Vector2f velocity(1.0f, 0.0f); // Velocidad inicial

    // Par�metros de velocidad
    const float incrementoVelocidad = 1.0f; // Incremento de velocidad
    const float velocidadMaxima = 10.0f;      // L�mite m�ximo de velocidad

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Tiempo transcurrido (deltaTime)
        float deltaTime = 1.0f / 60.0f; // Suponemos que el juego se est� ejecutando a 60 FPS

        // Actualizar la posici�n del objeto
        position += velocity * deltaTime;

        // Verificar si el objeto sali� por el lado derecho
        if (position.x > 800.0f) {
            position.x = 0.0f; // Reiniciar posici�n al lado izquierdo

            // Incrementar la velocidad hasta el l�mite m�ximo
            if (velocity.x < velocidadMaxima) {
                velocity.x += incrementoVelocidad;
            }
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el objeto en su posici�n actual
        sf::CircleShape object(20.0f); // C�rculo con radio de 20 p�xeles
        object.setPosition(position);
        object.setFillColor(sf::Color::Blue);
        window.draw(object);

        // Mostrar todo en la ventana
        window.display();
    }

    return 0;
}
