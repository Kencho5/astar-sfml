#include <SFML/Graphics.hpp>

class Grid {

}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "a* pathfinding");
    window.setFramerateLimit(60);

    int width = 100, height = 100;
    int grid[width][height];

    for(int i = 0; i < width; i++) {
    	for(int j = 0; j < height; j++) {
		grid[i][j] = 0;
	}
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed) 
			if (event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}

// g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o app -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system && ./app
