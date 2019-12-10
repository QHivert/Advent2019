//============================================================================
// Name        : Advent5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cout << "Advent day 5 start!" << endl;

	vector<int> intcodes;

	ifstream intcodesFile;
	intcodesFile.open("Intcodes.txt");

	if(intcodesFile.is_open()) {
		string str;
		while(getline(intcodesFile, str, ',')) {
			intcodes.push_back(stoi(str));
		}
	}

	intcodesFile.close();

	int size = intcodes.size();
	cout << "There are " << size << " intcodes" << endl;

	for(int i = 0; i<=size; i++) {
		int opcode = intcodes[i];

		if(opcode == 99) break;

		int A = opcode/10000;
		int B = (opcode - A*10000)/1000;
		int C = (opcode - A*10000 - B*1000)/100;
		int DE = (opcode - A*10000 - B*1000 - C*100);

		cout << "i: " << i << ", A: " << A << ", B: " << B << ", C: " << C << ", DE: " << DE << endl;

		//3 parameters
		if(DE==1 || DE==2 || DE==7 || DE==8) {
			int X1 = C ? ++i : intcodes[++i];
			int X2 = B ? ++i : intcodes[++i];
			int X3 = A ? ++i : intcodes[++i];

			if(DE==1) intcodes[X3] = intcodes[X1] + intcodes[X2];
			if(DE==2) intcodes[X3] = intcodes[X1] * intcodes[X2];
			if(DE==7) intcodes[X3] = intcodes[X1]<intcodes[X2] ? 1 : 0;
			if(DE==8) intcodes[X3] = intcodes[X1]==intcodes[X2] ? 1 : 0;
		}
		//1 parameter
		if(DE==3 || DE == 4) {
			int X1 = C ? ++i : intcodes[++i];

			if(DE==3) intcodes[X1] = 5;
			if(DE==4) cout << "output: " << intcodes[X1] << endl;
		}
		//2 parameters
		if(DE==5 || DE==6) {
			int X1 = C ? ++i : intcodes[++i];
			int X2 = B ? ++i : intcodes[++i];

			if(DE==5 && intcodes[X1]!=0) i=intcodes[X2]-1;
			if(DE==6 && intcodes[X1]==0) i=intcodes[X2]-1;
		}
	}

	cout << "Advent day 5 end!" << endl;
	return 0;
}
