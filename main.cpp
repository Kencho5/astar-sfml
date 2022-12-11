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
					
					switch(grid[i][j]) {
						case 0:
							shape.setFillColor(sf::Color::White);
							break;
						case 1:
							shape.setFillColor(sf::Color::Blue);
							break;
						case 2:
							shape.setFillColor(sf::Color::Red);
							break;
						case 3:
							shape.setFillColor(sf::Color::Black);
							break;
					}
					window.draw(shape);
				}
			}
	    }

		void setBlock(int x, int y, int type) {
			switch(type) {
				case 1:
					grid[x][y] = 1;
					break;
				case 2:
					grid[x][y] = 2;
					break;
				case 3:
					grid[x][y] = 3;
					break;
			}
		}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "a* pathfinding");
    window.setFramerateLimit(60);

	Grid grid;
	int type;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::Closed) window.close();
			if(event.key.code == sf::Keyboard::S) {
				type = 1;
			} else if(event.key.code == sf::Keyboard::E) {
				type = 2;
			} else if(event.key.code == sf::Keyboard::W) {
				type = 3;
			}
        } 
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			// calculating area clicked
			int gridX = floor(localPosition.x / grid.size);
			int gridY = floor(localPosition.y / grid.size);
			if(event.mouseButton.button == sf::Mouse::Left) {
				grid.setBlock(gridX, gridY, type);
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

//	0  0  0  0  0
//	0  1  0  0  0
//	0  0  0  0  0
//	0  0  0  2  0
//	0  0  0  0  0
