//============================================================================
// Name        : Advent1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	cout << "Start Advent day 1" << endl;

	ifstream moduleFile;
	moduleFile.open("ModuleInput.txt");


	if(moduleFile.is_open()) {

		cout << "file opened" << endl;

		int mass;
		int i = 0;

		int fuel;
		int fuelTotal = 0;

		while(moduleFile >> mass) {
			i++;
			fuel = mass/3 - 2;
			int remain = fuel/3 - 2;
			while(remain>0) {
				fuel += remain;
				remain = remain/3 - 2;
			}

			cout << "Mass " << i << " is " << mass << ", it requires "<< fuel << " amount of fuel."<<endl;
			fuelTotal += fuel;
		}
		cout << "There were " << i << " modules to launch, need a total amount of " << fuelTotal << "!"<< endl;
	}

	moduleFile.close();



	cout << "End Advent day 1" << endl;


	return 0;
}
