#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Grid {
	private:
		static const int width = 24, height = 16;
		int grid[width][height];
	public:
		const int size = 50;
		Grid(){
			for(int i = 0; i < width; i++) {
				for(int j = 0; j < height; j++) {
					grid[i][j] = 0;
				}
			}
		}
    	void draw(sf::RenderWindow &window) {
			for(int i = 0; i < width; i++) {
				for(int j = 0; j < height; j++) {
					sf::RectangleShape shape = sf::RectangleShape();
					shape.setSize(sf::Vector2f(size, size));
					shape.setOutlineThickness(5);
					shape.setOutlineColor(sf::Color::Black);
					shape.setPosition(i * size, j * size);
					
					if(grid[i][j] == 0) {
						shape.setFillColor(sf::Color::White);
					} else if(grid[i][j] == 1) {
						shape.setFillColor(sf::Color::Blue);
					} else if(grid[i][j] == 2) {
						shape.setFillColor(sf::Color::Red);
					}
					window.draw(shape);
				}
			}
	    }

		void setStart(int x, int y) {
			grid[x][y] = 1;
		}

		void setEnd(int x , int y) {
			grid[x][y] = 2;
		}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "a* pathfinding");
    window.setFramerateLimit(60);

	Grid grid;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::Closed) window.close();
			if(event.key.code == sf::Keyboard::S) {
				std::cout << "test";
			}
        } 
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			// calculating area clicked
			int gridX = floor(localPosition.x / grid.size);
			int gridY = floor(localPosition.y / grid.size);
			if(event.mouseButton.button == sf::Mouse::Left) {
				grid.setStart(gridX, gridY);
			} else if(event.mouseButton.button == sf::Mouse::Right) {
				grid.setEnd(gridX, gridY);
			}
			} 
		}

        window.clear();
		grid.draw(window);
        window.display();
    }

    return 0;
}

// g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o app -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system && ./app
