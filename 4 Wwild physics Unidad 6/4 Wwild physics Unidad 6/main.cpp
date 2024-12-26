#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace sf;
using namespace std;

// Estructura para manejar los círculos
struct Circle {
    CircleShape shape;
    float velocity;     // Velocidad actual (para MRU o inicial para MRUV)
    float acceleration; // Aceleración (0 para MRU, > 0 para MRUV)
};

class Game {
private:
    RenderWindow* pWnd;
    vector<Circle> circles; // Almacena los círculos que caen
    int score;              // Puntaje del jugador
    Font font;
    Text scoreText;
    Texture crosshairTexture;
    Sprite crosshairSprite;

    void ProcessEvent(Event& evt);
    void DrawGame();
    void UpdateGame();
    void ProcessCollisions(Vector2f clickPosition);

public:
    Game(int alto, int ancho, string titulo);
    ~Game();
    void Go();
};

// Constructor: Inicializamos la ventana, los círculos y el puntaje
Game::Game(int alto, int ancho, string titulo) {
    pWnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    pWnd->setFramerateLimit(60); // Limitamos a 60 FPS
    score = 0;

    // Configuramos texto del puntaje
    font.loadFromFile("LiberationSans-Italic.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10.0f, 10.0f);
    scoreText.setString("Puntaje: 0");

    // Configurar el crosshair
    crosshairTexture.loadFromFile("crosshair.png");
    crosshairSprite.setTexture(crosshairTexture);
    crosshairSprite.setScale(0.5, 0.5); // Escalar si es necesario
    crosshairSprite.setOrigin(
        crosshairTexture.getSize().x / 2.0f, // Centrar en el eje X
        crosshairTexture.getSize().y / 2.0f  // Centrar en el eje Y
    );
    pWnd->setMouseCursorVisible(false); // Ocultar el cursor estándar

    // Generamos círculos en posiciones aleatorias (MRU y MRUV)
    srand((time(0))); // Semilla para aleatoriedad
    for (int i = 0; i < 10; i++) {
        Circle circle;
        circle.shape = CircleShape(20.0f); // Radio de 20 píxeles
        circle.shape.setFillColor(Color::Green);
        circle.shape.setPosition(rand() % 800, rand() % 300); // Posición inicial aleatoria

        if (i % 2 == 0) { // MRU: Velocidad constante
            circle.velocity = 100.0f + rand() % 50; // Velocidad constante aleatoria
            circle.acceleration = 0.0f;            // Sin aceleración
        }
        else { // MRUV: Velocidad inicial y aceleración
            circle.velocity = 50.0f;        // Velocidad inicial
            circle.acceleration = 20.0f;   // Aceleración (gravedad)
        }

        circles.push_back(circle);
    }
}

// Destructor: Liberamos la memoria de la ventana
Game::~Game() {
    delete pWnd;
}

// Bucle principal del juego
void Game::Go() {
    Event evt;
    while (pWnd->isOpen()) {
        while (pWnd->pollEvent(evt))
            ProcessEvent(evt);

        UpdateGame();
        pWnd->clear();
        DrawGame();
        pWnd->display();
    }
}

// Procesar eventos del jugador
void Game::ProcessEvent(Event& evt) {
    if (evt.type == Event::Closed) {
        pWnd->close();
    }

    // Detectar disparo con el mouse
    if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left) {
        Vector2f clickPosition(evt.mouseButton.x, evt.mouseButton.y);
        ProcessCollisions(clickPosition); // Verificar colisión con los círculos
    }
}

// Dibujar los círculos y el puntaje en pantalla
void Game::DrawGame() {
    for (const auto& circle : circles) {
        pWnd->draw(circle.shape);
    }
    pWnd->draw(crosshairSprite);
    pWnd->draw(scoreText); // Dibujar puntaje
}

// Actualizar el estado del juego
void Game::UpdateGame() {
    for (auto& circle : circles) {
        // Movimiento MRU
        if (circle.acceleration == 0.0f) {
            circle.shape.move(0.0f, circle.velocity * 1.0f / 60.0f); // Velocidad constante
        }
        else { // Movimiento MRUV
            circle.velocity += circle.acceleration * 1.0f / 60.0f;  // Incrementar velocidad
            circle.shape.move(0.0f, circle.velocity * 1.0f / 60.0f); // Mover con velocidad actual
        }

        // Reaparecer círculo desde arriba si sale de la pantalla
        if (circle.shape.getPosition().y > 600) {
            circle.shape.setPosition(rand() % 800, 0.0f); // Posición aleatoria arriba
            if (circle.acceleration > 0.0f) {
                circle.velocity = 50.0f; // Reiniciar velocidad inicial para MRUV
            }
        }
    }

    // Actualizar posición del crosshair
    Vector2i mousePosition = Mouse::getPosition(*pWnd);
    crosshairSprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

// Verificar colisiones entre el clic y los círculos
void Game::ProcessCollisions(Vector2f clickPosition) {
    for (auto it = circles.begin(); it != circles.end(); ++it) {
        if (it->shape.getGlobalBounds().contains(clickPosition)) {
            // Incrementar puntaje y eliminar círculo impactado
            score += 10;
            circles.erase(it);

            // Actualizar texto del puntaje
            scoreText.setString("Puntaje: " + to_string(score));
            break; // Solo un círculo por disparo
        }
    }
}

void main() {
    Game juego(600, 800, "Círculos que Caen");
    juego.Go();
}
