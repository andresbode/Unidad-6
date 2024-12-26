#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main()
{
	// Crear una ventana SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce");
	// Definir la posición y velocidad inicial de la bola
	sf::Vector2f position(400.0f, 100.0f);
	sf::Vector2f velocity(0.0f, 0.0f);
	// Constante de gravedad para la caída libre
	const float gravity = 0.000098f;
	// Bucle principal del juego
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Actualizar la velocidad de la bola en función de la gravedad
		velocity.y += gravity;
		// Actualizar la posición de la bola en función de la velocidad
		position += velocity;
		// Comprobar si la bola ha llegado al suelo (límite inferior de la ventana)
		if (position.y > 560.0f)
		{
		
			velocity.y = -velocity.y+0.05f;
			position.y = 560.0f;
		}
		// Limpiar la ventana
		window.clear();
		// Dibujar la bola en su posición actual
		sf::CircleShape ball(20.0f);
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(position);
		window.draw(ball);
		// Mostrar todo en la ventana
		window.display();
	}
	return 0;
}