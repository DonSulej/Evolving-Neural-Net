#include <vector>
#include <string>
#pragma once

class node {

	float inputs[16];  //-1.0 <-> 1.0
	float weights[16]; //-4.0 <-> 4.0
	float nodeOut();
};

void HexGen(std::vector<std::string>& genehex, int genelen, bool debug);
void BinGen(std::vector<std::vector<int>>& genebin, std::vector<std::string> genehex, int genelen);

class Cell {
public:

	int x;
	int y;
	int geneLen;

	std::vector<std::string> geneHex;
	std::vector<std::vector<int>> geneBin;

	//Cell(int startX, int startY, int len, int neuronN);
	Cell(int startX, int startY, int len, int neuronN) {
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
	
	//Cell();
	Cell(void) {
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

	std::vector<float> N;
	std::vector<float> ActionBuffer;
};


void printHexGenome(Cell c);
void printBinGenome(Cell c);

std::vector<Cell> GenNCells(int count, int genelen, int Ns);
int** makeMap(std::vector<Cell> cellvec);
void printMap(int** map);

/*
* es: 1|011|0|001|1010 1110
* field 1: input type. 0 = input, 1 = internal node
* field 2: source id (0-7)
* field 3: sink type. 0 = output, 1 = internal node
* field 5: sink id (0-7)
* field 4: weight (max 511, primo valore è segno, da trovare divisore che porta a 4.0/-4.0)
*/
