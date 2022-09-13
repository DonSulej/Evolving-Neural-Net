#include<string>
#include<vector>
#include<cmath>

float Age(int age, float weight) {
	return age * weight;
}
//0000

float xpos(int x, float weight) { 
	return x * weight;
}
//0001

float ypos(int y, float weight) {
	return y * weight;
}
//0010

float proxNorth(int** map, int x, int y, float weight) {
	if (y + 1 == 128) return 0.0f;
	if (map[x][y+1] != 0) return weight;
	else return 0.0f;
}
//0011

float proxEast(int** map, int x, int y, float weight) {
	if (x + 1 == 128) return 0.0f;
	if (map[x+1][y] != 0) return weight;
	else return 0.0f;
}
//0100

float proxWest(int** map, int x, int y, float weight) {
	if (x - 1 == -1) return 0.0f;
	if (map[x-1][y] != 0) return weight;
	else return 0.0f;
}
//0101

float proxSouth(int** map, int x, int y, float weight) {
	if (y - 1 == -1) return 0.0f;
	if (map[x][y-1] != 0) return weight;
	else return 0.0f;
}
//0110

float Oscil(int age, float weight) {
	return sin(age) * weight;
}
//0111

float Sensor(int sourceId, int age, int** map, int x, int y, float weight) {
	switch (sourceId) {
	case(0):
		return Age(age, weight);
		break;
	case(1):
		return xpos (x, weight);
		break;
	case(2):
		return ypos (y, weight);
		break;
	case(3):
		return proxNorth(map, x, y, weight);
		break;
	case(4):
		return proxEast (map, x, y, weight);
		break;
	case(5):
		return proxWest (map, x, y, weight);
		break;
	case(6):
		return proxSouth(map, x, y, weight);
		break;
	case(7):
		return Oscil(age, weight);
		break;
	default:
		break;
	}
}