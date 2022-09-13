#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include "BaseHeader.h"
#include "Structures.h"
#include "SensorHeader.h"
#include "ActionsHeader.h"


void Mind(Cell &c, int Age, int** map) {
	//Quattro "stadi", scorrendo ogni volta ogni gene: in->N, N->N, in->out, N->out. 
	//I valori temporanei nei rispettivi buffer; così l'ordine in cui viene svolto il genoma non importa.
	//Le funzioni azione si eseguono solo quando i rispettivi buffer hanno fluito fino "a valle"

	for (float f : c.N) f = 0.0f; //Azzero buffer neuroni prima di ogni frame

	for (int i = 0; i < c.geneLen; i++) {


		float temp;
		std::vector<int> id1Bin = {
			c.geneBin[i][1], c.geneBin[i][2],c.geneBin[i][3] };
		
		std::vector<int> id2Bin = {
			c.geneBin[i][5], c.geneBin[i][6],c.geneBin[i][7] };

		std::vector<int> ottoBin = {
			c.geneBin[i][8], c.geneBin[i][9],c.geneBin[i][10],c.geneBin[i][11],
			c.geneBin[i][12],c.geneBin[i][13],c.geneBin[i][14],c.geneBin[i][15] };

		if (c.geneBin[i][0] == 0) { //source==input
			temp = Sensor(BinToDec(id1Bin), Age, map, c.x, c.y, BinToDecSing(ottoBin) / 31.75f);
		} else { //source==neuron
			int itemp;
			if (itemp = c.N.size() < BinToDec(id1Bin)) itemp = 0; //La connessione parte da un neurone non in uso
			temp = c.N[itemp]*BinToDecSing(ottoBin);
		}

		if (c.geneBin[i][4] == 0) { //sink==output
			if (BinToDec(id2Bin) % 2 == 0) c.ActionBuffer[0] += temp;
			else c.ActionBuffer[1] += temp;
		} else { //sink==neuron
			int itemp;
			if (itemp = c.N.size() < BinToDec(id1Bin)) itemp = 0; //La connessione arriva a un neurone non in uso
			c.N[itemp] += temp  * BinToDecSing(ottoBin);
		}
	}
	c.x += Actions(2, c.ActionBuffer[0], c, map); //Azioni vengono svolte secondo i buffer
	c.y += Actions(1, c.ActionBuffer[1], c, map);
}


void Generation(int** map, std::vector<Cell> &cellvec) {
	int Age = 1;
	std::vector < std::pair<int, int>> coord1;
	std::vector < std::pair<int, int>> coord2;

	coord1.resize(cellvec.size());
	coord2.resize(cellvec.size());
	for (int i = 0; i < cellvec.size(); i++) {
		coord1[i].first	 = cellvec[i].x; 
		coord1[i].second = cellvec[i].y;
	}

	for (Age; Age <= 30; Age++) {
		for (Cell c : cellvec) {
			Mind(c, Age, map);
		}

		for (int i = 0; i < cellvec.size(); i++) {
			coord2[i].first = cellvec[i].x;
			coord2[i].second = cellvec[i].y;

			if (coord1[i].first != coord2[i].first) std::cout << "Cell " << i << " moved!\n";
			if (coord1[i].second != coord2[i].second) std::cout << "Cell " << i << " moved!\n";
		}

		coord1 = coord2;

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
		map = makeMap(cellvec);
		printMap(map);
	}
}

int main() {
	srand(time(NULL));

	std::vector<Cell> CellVec = GenNCells(1000, 4, 4);

	int** Map = makeMap(CellVec);

	printMap(Map);

	Generation(Map, CellVec);

	/*
	for (Cell c : CellVec) {
		printCellCoord(c);
	}*/

	/*
	printCellCoord(c);
	printHexGenome(c);
	std::cout << "\n";
	printBinGenome(c);
	*/
	return 0;
}