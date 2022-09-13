#include<iostream>
#include<string>
#include<vector>

float SumOfArr(float Arr[], int len) {
	float out = 0.0f;
	for (int i = 0; i<len; i++) {
		out += Arr[i];
	}
	return out;
}

int powerOfInt(int base, int exp) {
	if (base == 0) return 0;
	if (exp == 0)  return 1;

	int power = base;
	for (int i = 1; i < exp; i++) {
		power *= base;
	}
	return power;
}

int* IntToArr(int n, int len, int arr[]) { // Dato un int n ne mette ogni cifra in arr di lunghezza len
	for (len; len > 0; len--) {
		arr[len - 1] = n % 10;
		n /= 10;
	}
	return arr;
}

int BinToDec(int bin[]) { // per bin sotto il byte
	int Dec = 0;
	for (int i = 0; i < 8; i++) {
		if (bin[i] != 0 && bin[i] != 1) return 0;
		Dec += bin[i] * (powerOfInt(2,(8 - i - 1)));
		std::cout << bin[i] << "* " << (powerOfInt(2, (8 - i - 1))) <<" += " <<Dec << "\n";
	}
	return Dec;
}

int BinToDec(std::vector<int> bin) { //vettore scalabile
	int Dec = 0;
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] != 0 && bin[i] != 1) return 0;
		Dec += bin[i] * powerOfInt(2, (bin.size() - i - 1));
	}
	return Dec;
}

int BinToDecSing(std::vector<int> bin) { //vettore scalabile, primo valore è segno
	int Dec = 0;
	for (int i = 1; i < bin.size(); i++) {
		if (bin[i] != 0 && bin[i] != 1) return 0;
		Dec += bin[i] * powerOfInt(2, (bin.size() - i - 2));
	}
	if (bin[0] == 1) Dec *= -1;
	return Dec;
}

int* DecToBin(int Dec) { // per int sotto il byte (Dec<256)
	int Bin[8];
	for (int i = 0; i < 8; i++) {
		Bin[i] = Dec % 2;
		Dec /= 2;
	}
	return Bin;
}

std::vector<int> DecToBinVec(int Dec) { //Esclusivamente per interi da 0 a 15
	std::vector<int> Vec;
	Vec.resize(4);
	if (Dec == 0) Vec = { 0,0,0,0 };
	else {
		for (int i = 3; i >= 0; i--) {
			Vec[i] = Dec % 2;
			Dec /= 2;
		}
	}
	return Vec;
}

std::vector<int> HexToBin(std::string s) { //stringhe da 4 cifre hex a bin da 16 bit
	std::vector<int> Vec;
	Vec.resize(16);

	for (int i = 0; i < 4; i++) {
		int temp = 0;
		if (s.at(i)>='a') {
			temp = (int)(s.at(i) - 87);
			//std::cout << temp << " ";
		} else {
			temp = (int)(s.at(i) - 48);
			//std::cout << temp << " ";
		}
		std::vector<int> tempVec = DecToBinVec(temp);

		for (int j = 0; j < 4; j++) {
			int t = j + (i * 4);
			Vec[t] = tempVec[j];
			//std::cout << tempVec[j];
		}
	}

	//std::cout << " ";

	return Vec;
}


std::vector<std::pair<int, int>> coordGen(int cellCount) {
	std::vector<std::pair<int, int>> coordVec;
	coordVec.resize(cellCount);

	std::vector<int> Num;
	Num.resize(16348);

	for (int i = 0; i < 16348; i++) {
		Num[i] = i+1;
	}
	
	for (int i = 0; i < cellCount; i++) {
		int index;
		while (1) {
			index = rand() % 16348;
			if (Num[index] != 0) {
				break;
			}
		}
		coordVec[i].first = Num[index] / 128;
		coordVec[i].second = Num[index] % 128;
		Num[index] = 0;
	}


	return coordVec;
}