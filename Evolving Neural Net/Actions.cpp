#include "Structures.h"
#include <iostream>
#include<cmath>

int movX(float in, Cell &c, int** map) {
	std::cout<< "in: " << in;
	if (std::tanh(in) > 0.4f) {
		std::cout <<"c.x:" << c.x << "|";
		if (c.x <= 126 && map[c.x + 1][c.y] == 0) {
			map[c.x][c.y] = 0;
			map[c.x+1][c.y] = 1;
			c.x += 1;
			std::cout << "action proc\n";
			return 1;
		}
	} else if (std::tanh(in) < -0.4f) {
		std::cout << "c.x:" << c.x << "|";
		if (c.x >= 1 && map[c.x - 1][c.y] == 0) {
			map[c.x][c.y] = 0;
			map[c.x-1][c.y] = 1;
			c.x -= 1;
			std::cout << "action proc\n";
			return -1;
		}
	} else {
		std::cout << "no proc\n";
		return 0;
	}
} //00, 10 ...

int movY(float in, Cell &c, int** map) {
	std::cout << in;
	if (std::tanh(in) > 0.4f) {
		std::cout << "c.y:" << c.y << "|";
		if (c.y <= 126 && map[c.x][c.y+1] == 0) {
			map[c.x][c.y] = 0;
			map[c.x][c.y+1] = 1;
			c.y += 1;
			std::cout << "action proc\n";
			return 1;
		}
	} else if (std::tanh(in) < -0.4f) {
		std::cout << "c.y:" << c.y << "|";
		if (c.y >= 1) {
			if (map[c.x][c.y - 1] == 0) {
				map[c.x][c.y] = 0;
				map[c.x][c.y - 1] = 1;
				c.y -= 1;
				std::cout << "action proc\n";
				return -1;
			}
		}
	} else {
		std::cout << "not proc\n"; return 0;
	}
} //01, 11 ...

int Actions(int actionId, float in, Cell &c, int** map) {
	if (actionId % 2 == 0) return movX(in, c, map);
	else return movY(in, c, map);
}