#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
class Adj {
	public:
		int F;
		int i;
		int j;
};
class Grid {
	private:
		static const int width = 38, height = 20;
		int grid[width][height];
	public:
		const int size = 50;
		int F, G, H;

		int startH = 0, startV = 0, curH, curV;
		int endH = 0, endV = 0;

		bool finish;
		Adj adj, lowest;
		std::vector<Adj> arr;

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
						case 4:
							shape.setFillColor(sf::Color::Green);
					}
					window.draw(shape);
				}
			}
	    }

	void setBlock(int x, int y, int type) {
		switch(type) {
			case 1:
				grid[x][y] = 1;
				
				startH = x;
				startV = y;

				curH = x;
				curV = y;

				break;
			case 2:
				grid[x][y] = 2;

				endH = x;
				endV = y;
				break;
			case 3:
				grid[x][y] = 3;
				break;
		}
	}

	void calculateH(int sh, int sv) {
		H = round(std::sqrt(pow(sh - endH, 2) + pow(sv - endV, 2)) * 10);
		// H = abs(startH - endH) + abs(startV - endV);
	}
	
	void calculateG() {
		arr.clear();
		for(int i = -1; i <= 1; ++i) {
			for(int j = -1; j <= 1; ++j) {
				if(i != 0 || j != 0) {
					if(grid[curH + i][curV + j] == 3) continue;
					if(grid[curH + i][curV + j] == 4) continue;
					G = abs(startH - curH + i) + abs(startV - curV + j);
		
					calculateH(curH + i, curV + j);

					F = G + H;
					adj.F = F;
					adj.i = i;
					adj.j = j;

					arr.push_back(adj);
					std::cout << F << " " << G << " " << H << " " << i << " " << j << std::endl;
				}
			}
		}
		getLowest();
		std:: cout << lowest.F << " " << lowest.i << " " << lowest.j << std::endl << std::endl;

		curH += lowest.i;
		curV += lowest.j;
		if(grid[curH][curV] == 2) {
			finish = true;
			return;
		} 
		grid[curH][curV] = 4;
	}

	void getLowest() {
		double min = arr[0].F;
		for(int i = 1; i < arr.size(); i++) {
			if(min >= arr[i].F) { 
				min = arr[i].F;
				lowest = arr[i];
			}
		}
	}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "a* pathfinding");
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
			} else if(event.key.code == sf::Keyboard::Enter) {
				while(grid.finish != true) {
					grid.calculateG();
					sf::sleep(sf::milliseconds(20));

					window.clear();
					grid.draw(window);
					window.display();
				}
			}
        } 
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			// calculating area clicked
			int gridX = floor(localPosition.x / grid.size);
			int gridY = floor(localPosition.y / grid.size);
			grid.setBlock(gridX, gridY, type);
			} 
		}

        window.clear();
	grid.draw(window);
        window.display();
    }

    return 0;
}

// g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -o app -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system && ./app

//	1  0  0  0  0  0
//	0  0  0  0  0  0
//	0  0  2  0  0  0
//	0  0  0  0  0  0
//	0  0  0  0  0  0
