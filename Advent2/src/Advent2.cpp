//============================================================================
// Name        : Advent2.cpp
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
	cout << "Start Advent day 2" << endl;

	vector<int> intcodes;

	ifstream intcodesFile;
	intcodesFile.open("Intcodes.txt");

	int j = 0;
	if(intcodesFile.is_open()) {
		string str;
		while(getline(intcodesFile, str, ',')) {
			intcodes.push_back(stoi(str));
//			intcodes[j] = stoi(str);
			j++;
		}
	}
	intcodesFile.close();
	int size = intcodes.size();
	cout << "There are " << size << " intcodes" << endl;

	int nbOpcodes = 153/4;
	int output = 0;
	int goal = 19690720;

	for(int k1 = 1; k1<99; k1++){
		for(int k2 = 1; k2<99; k2++) {
			vector<int> deux = intcodes;
			deux[1] = k1;
			deux[2] = k2;

			for(int i = 0; i<=nbOpcodes; i++) {
				int opcode = deux[4*i];

				if(opcode == 99) break;

				int pos1   = deux[4*i+1];
				int pos2   = deux[4*i+2];
				int out    = deux[4*i+3];

				if(opcode == 1) {
					deux[out] = deux[pos1] + deux[pos2];
				}
				else if (opcode == 2) {
					deux[out] = deux[pos1] * deux[pos2];
				}
			}

			output = deux[0];
			if(output == goal){
				cout << "Goal reached (" << output << ") with noun " << k1 << " and verb " << k2 <<"." << endl;
				cout <<"Answer is " << 100*deux[1]+deux[2] << endl;
			}
		}
	}


	cout << "End Advent day 2" << endl;
	return 0;
}
