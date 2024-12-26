#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
int main()
{
	// Crear una ventana SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "Space");
	// Definir la posición y velocidad inicial de la bola
	sf::Vector2f position(400.0f, 300.0f);
	sf::Vector2f velocity(0.0f, 0.0f);
	const float deltaTime = 0.1f / 60.0f;
	const float aceleracion = 0.05f; 
	const float desaceleracion = 0.02f;

	// Bucle principal del juego
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (velocity.x > 0) {
						velocity.x -= desaceleracion; // Desacelerar si va a la derecha
					}
					else {
						velocity.x -= aceleracion; // Acelerar hacia la izquierda
					}
				}
				else if (event.key.code == sf::Keyboard::Right) {
					if (velocity.x < 0) {
						velocity.x += desaceleracion; // Desacelerar si va a la izquierda
					}
					else {
						velocity.x += aceleracion; // Acelerar hacia la derecha
					}
				}
				else if (event.key.code == sf::Keyboard::Up) {
					if (velocity.y > 0) {
						velocity.y -= desaceleracion; // Desacelerar si va hacia abajo
					}
					else {
						velocity.y -= aceleracion; // Acelerar hacia arriba
					}
				}
				else if (event.key.code == sf::Keyboard::Down) {
					if (velocity.y < 0) {
						velocity.y += desaceleracion; // Desacelerar si va hacia arriba
					}
					else {
						velocity.y += aceleracion; // Acelerar hacia abajo
					}
				}
			}
		}

		if (position.x < 0) position.x = 0;
		if (position.x > 800 - 40) position.x = 800 - 40;
		if (position.y < 0) position.y = 0;
		if (position.y > 600 - 40) position.y = 600 - 40;

		position += velocity;


		window.clear();
		
		sf::CircleShape ball(20.0f);
		ball.setFillColor(sf::Color::Red);
		ball.setPosition(position);
		window.draw(ball);
		
		window.display();
	}
	return 0;
}
