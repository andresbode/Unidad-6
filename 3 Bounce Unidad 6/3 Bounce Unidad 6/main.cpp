#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main()
{
	// Crear una ventana SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce");
	// Definir la posici�n y velocidad inicial de la bola
	sf::Vector2f position(400.0f, 100.0f);
	sf::Vector2f velocity(0.0f, 0.0f);
	// Constante de gravedad para la ca�da libre
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
		// Actualizar la velocidad de la bola en funci�n de la gravedad
		velocity.y += gravity;
		// Actualizar la posici�n de la bola en funci�n de la velocidad
		position += velocity;
		// Comprobar si la bola ha llegado al suelo (l�mite inferior de la ventana)
		if (position.y > 560.0f)
		{
		
			velocity.y = -velocity.y+0.05f;
			position.y = 560.0f;
		}
		// Limpiar la ventana
		window.clear();
		// Dibujar la bola en su posici�n actual
		sf::CircleShape ball(20.0f);
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(position);
		window.draw(ball);
		// Mostrar todo en la ventana
		window.display();
	}
	return 0;
}