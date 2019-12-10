//============================================================================
// Name        : Advent6v2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int nextSteps(string start, vector<pair<string, string>> *orbits, vector<string> *step) {
	for(auto k : *orbits) {
		if(k.first==start) {
			step->push_back(start+")"+k.second);
		}
	}
	return step->size();
}

int previousSteps(string end, vector<string> *previous, vector<string> *step) {
	for(unsigned k=0; k<previous->size(); k++) {
		if(previous->at(k).substr(4,3)==end){
			step->push_back(previous->at(k));
		}
	}
	return step->size();
}

bool commonStarter(vector<string> *stepY, vector<string> *stepS) {
	bool ret = false;

	for(unsigned int y=0; y<stepY->size(); y++) {
		string startY = stepY->at(y).substr(0,3);
		for(unsigned int s=0; s<stepS->size(); s++) {
			string startS = stepS->at(s).substr(0,3);
			if(startS == startY) {
				ret = true;
			}
		}
	}

	return ret;
}

void draw(vector<vector<string>> *space) {
	for(unsigned int j=0; j<space->size(); j++) {
		cout << space->at(j)[0];
		for(unsigned int k=1; k<space->at(j).size(); k++) {
			if(space->at(j)[k].substr(0,3)==space->at(j)[k-1].substr(0,3)) {
				cout << " - " << space->at(j)[k];
			} else {
				cout << " | " << space->at(j)[k];
			}
		}
		cout << endl;
	}
}

int main() {
	cout << "Advent Day 6 Start!" << endl;

	vector<pair<string, string>> orbits;

	ifstream orbitsList;
	orbitsList.open("Orbits.txt");

	string line;
	if(orbitsList.is_open()) {
		while(getline(orbitsList, line)) {
			string del = ")";
			string o1 = line.substr(0, line.find(del));
			string o2 = line.substr(line.find(del)+1, line.size());

			orbits.push_back(make_pair(o1, o2));
		}
	}

	orbitsList.close();

	int size = orbits.size();
	cout << "There are " << size << " orbits indicators" << endl;

	vector<vector<string>> space;

	//Find starters and enders
	set<unsigned int> starters;
	for(int i=0; i<size; i++) {

		bool starter = true;
		bool ender = true;
		pair<string, string> kpi = orbits[i];
		for(int j=0; j<size; j++) {
			pair<string, string> kpj = orbits[j];
			if(kpi.first==kpj.second) {
				starter = false;
			}
		}
		if(starter) starters.insert(i);
	}
	cout << "There are " << starters.size() << " starters" << endl;

	//Push stater and next step
	vector<string> step0;
	vector<string> step1;
	for(int i: starters) {
		step0.push_back(orbits[i].first);
		step1.push_back(orbits[i].first+")"+orbits[i].second);
	}
	space.push_back(step0);
	space.push_back(step1);


	//Push all next steps
	int totalStep = 1;
	int step = 1;
	while(totalStep!=0) {
		totalStep = 0;
		vector<string> nextStep;
		for(unsigned int j=0; j<space[step].size(); j++) {
			string str = space[step][j].substr(4, 3);
			totalStep += nextSteps(space[step][j].substr(4, 3), &orbits, &nextStep);
		}
		space.push_back(nextStep);
		step++;
	}


	//draw(&space);

	//find YOU and SAN position
	pair<int, int> pYou=make_pair(0,0);
	pair<int, int> pSan=make_pair(0,0);
	for(unsigned int j=space.size()-1; j>=0; j--) {
		for(unsigned int k=0; k<space[j].size(); k++) {
			if(space[j][k].substr(4,3)=="YOU") {
				pYou = make_pair(j,k);
			}
			if(space[j][k].substr(4,3)=="SAN") {
				pSan = make_pair(j,k);
			}
			if(pYou.first && pSan.first) break;
		}
		if(pYou.first && pSan.first) break;
	}

	cout << "YOU is at position (" << pYou.first << "," << pYou.second << ")" << endl;
	cout << "SAN is at position (" << pSan.first << "," << pSan.second << ")" << endl;

	vector<vector<string>> pathYou;
	pathYou.push_back({space[pYou.first][pYou.second]});

	vector<vector<string>> pathSan;
	pathSan.push_back({space[pSan.first][pSan.second]});

	int posCom=0;

	if(pYou.first > pSan.first) {
		posCom = pSan.first;
		for(int i=0; i<pYou.first - pSan.first; i++) {
			vector<string> preStep;
			for(unsigned int k=0; k<pathYou[i].size(); k++) {
				previousSteps(pathYou[i][k].substr(0,3), &space[pYou.first-i-1], &preStep);
			}
			pathYou.push_back(preStep);
		}
	} else if(pYou.first > pSan.first) {
		posCom = pYou.first;
		for(int i=0; i<pSan.first - pYou.first; i++) {
			vector<string> preStep;
			for(unsigned int k=0; k<pathSan[i].size(); k++) {
				previousSteps(pathSan[i][k].substr(0,3), &space[pSan.first-i-1], &preStep);
			}
			pathSan.push_back(preStep);
		}
	}

	bool cross = false;
	int av = 0;
	while(!cross) {
		av++;
		vector<string> preStepY;
		vector<string> preStepS;

		cout << "Explore step " << posCom-av << endl;

		for(unsigned int k=0; k<pathYou.back().size(); k++) {
			previousSteps(pathYou.back()[k].substr(0,3), &space[posCom-av], &preStepY);
		}
		for(unsigned int k=0; k<pathSan.back().size(); k++) {
			previousSteps(pathSan.back()[k].substr(0,3), &space[posCom-av], &preStepS);
		}
		pathYou.push_back(preStepY);
		pathSan.push_back(preStepS);

		if(commonStarter(&preStepY, &preStepS)) {
			cross = true;
			cout << "CROSSED at " << posCom-av << endl;
		}
	}

	draw(&pathYou);

	cout << endl;

	draw(&pathSan);

	cout << endl;

	cout << "size pathY: " << pathYou.size() << " + size pathS " << pathSan.size() << endl;
	cout << "orbits between YOU and SAN: " << pathYou.size()+pathSan.size()-2 << endl;

	cout << "Advent Day 6 End!" << endl;
	return 0;
}
