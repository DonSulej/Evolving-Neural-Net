#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include "BaseHeader.h"
#include "Structures.h"


float node::nodeOut() {
	float output = SumOfArr(inputs, 16);

	if (output > 0.0f) return output;
	else return 0.0f;
}

//DOC ORIGINALE//
/* 1 gene = 8 exadecimal  num. Rappresenta una connessione
* es: f1351fe3
* es: 1 1110001 0 0110101 0001111111100011
* field 1: input type. 0 = input, 1 = internal node
* field 2: source id
* field 3: sink type. 0 = output, 1 = internal node
* field 4: weight (da dividere)
*/

//DOC MIA//
/*
* es: 1|011|0|001|1010 1110
* field 1: input type. 0 = input, 1 = internal node
* field 2: source id (0-7)
* field 3: sink type. 0 = output, 1 = internal node
* field 5: sink id (0-7)
* field 4: weight (max 511, primo valore è segno, da trovare divisore che porta a 4.0/-4.0)
*/




void HexGen(std::vector<std::string>& genehex, int genelen, bool debug) { //f = 102 ascii (f in hex = 15, diff 87)

	if (debug) std::cout << "DNA: ";
	for (int I = 0; I < genelen; I++) {

		char tstring[4];
		for (int i = 0; i < 4; i++) {
			int temp = rand() % 16;
			if (temp < 10) {
				tstring[i] = temp + '0'; //conversione int->char
			} else {
				tstring[i] = (char)(temp + 87);
			}
			if (debug) std::cout << tstring[i];
		}
		if (debug) std::cout << " ";
		std::string s;
		s.append(tstring);
		genehex[I] = s;
		genehex[I].resize(4);
		if (debug) std::cout << genehex[I] << "|";
	}
}

void BinGen(std::vector<std::vector<int>>& genebin, std::vector<std::string> genehex, int genelen) {
	for (int i = 0; i < genelen; i++) {
		std::vector<int> temp = HexToBin(genehex[i]);
		for (int j = 0; j < 16; j++) {
			genebin[i][j] = temp[j];
		}
	}
}
/*
Cell::Cell(int startX, int startY, int len, int neuronN) {
	x = startX;
	y = startY;
	geneLen = len;
	geneHex.resize(geneLen, "0000");
	geneBin.resize(geneLen, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
	HexGen(geneHex, geneLen, 0);
	BinGen(geneBin, geneHex, geneLen);

	N.resize(neuronN);
	for (float f : N) f = 0.0f;
	ActionBuffer.resize(2);
	for (float f : ActionBuffer) f = 0.0f;

}

Cell::Cell(void) {
	geneLen = 1;
	x = 0;
	y = 0;
	geneHex.resize(geneLen, "0000");
	geneBin.resize(geneLen, { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
	HexGen(geneHex, geneLen, 0);
	BinGen(geneBin, geneHex, geneLen);
	N.resize(3);
	for (float f : N) f = 0.0f;
	ActionBuffer.resize(2);
	for (float f : ActionBuffer) f = 0.0f;
}
*/

void printHexGenome(Cell c) {
	for (int i = 0; i < c.geneHex.size(); i++) {
		std::cout << c.geneHex[i];
		std::cout << " ";
	}
}

void printBinGenome(Cell c) {
	for (int i = 0; i < c.geneBin.size(); i++) {
		for (int j = 0; j < c.geneBin[i].size(); j++) {
			std::cout << c.geneBin[i][j];
		}
		std::cout << " ";
	}
}

void printCellCoord(Cell c) {
	std::cout << "X: " << c.x << " Y: " << c.y << "\n";
}

int** makeMap(std::vector<Cell> cellvec) {

	int** arr = new int* [128];
	for (int i = 0; i < 128; i++) {
		arr[i] = new int[128];
		for (int j = 0; j < 128; j++) arr[i][j] = 0;
	}

	for (Cell c : cellvec) {
		arr[c.y][c.x] = 1;
	}

	return arr;
}

void printMap(int** map) {
	std::cout << "\n";

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			if (map[i][j] == 0) std::cout << "#";
			else std::cout << "C";
		}
		std::cout << "\n";
	}
}

std::vector<Cell> GenNCells(int count, int genelen, int Ns) {

	std::vector<std::pair<int, int>> coords = coordGen(count);

	std::vector<Cell> cellvec;
	cellvec.resize(count);

	for (int i = 0; i < count; i++) {
		int x = coords[i].first;
		int y = coords[i].second;
		Cell c = Cell(x, y, genelen, Ns);
		cellvec[i] = c;
		std::cout<<i <<":\t" << c.x << "\t" << c.y << "\t";
		for (std::string s : c.geneHex) std::cout << s <<" ";
		std::cout<< "\n";
	}

	return cellvec;
}