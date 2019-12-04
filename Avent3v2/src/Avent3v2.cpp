//============================================================================
// Name        : Avent3v2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>

using namespace std;

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}
template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first-r.first,l.second-r.second};
}

//add next segment to the wire
void updateWire(char dir, int val, vector<pair<int,int>> *wire){

	switch(dir) {
		case 'U' : {
				wire->push_back(wire->back()+make_pair(0,val));
			break;
		}
		case 'R' : {
				wire->push_back(wire->back()+make_pair(val,0));
			break;
		}
		case 'L' : {
				wire->push_back(wire->back()+make_pair(-val,0));
			break;
		}
		case 'D' : {
				wire->push_back(wire->back()+make_pair(0,-val));
			break;
		}
		default: break;
	}
}

//return the distance from (0,0) of a point
int d(pair<int,int> val) {
	return abs(val.first)+abs(val.second);
}

/*
 * Segment wire1 s1 = (x1,y1) to e1 = (x2,y2)
 * Segment wire2 s2 = (a1,b1) to e2 = (a2,b2)
 * See if this two segments cross each other
 */
bool isCrossed(pair<int,int> s1, pair<int,int> e1, pair<int,int> s2, pair<int,int> e2) {
	bool ret = false;
	int x1 = s1.first;
	int x2 = e1.first;
	int y1 = s1.second;
	int y2 = e1.second;

	int a1 = s2.first;
	int a2 = e2.first;
	int b1 = s2.second;
	int b2 = e2.second;

	if(x1 == x2){
		//vertical
		if(a1 == a2){
			if(a1 != x1) {
				//parallel
				return false;
			} else {
				//check if segment contains each other
				if(y1>=min(b1,b2) && y1<=max(b1,b2)) {
					return true;
				} else if (y2>=min(b1,b2) && y2<=max(b1,b2)) {
					return true;
				} else {
					return false;
				}

			}
		} else {
			if(x1>=min(a1,a2) && x1<=max(a1,a2) && b1>min(y1,y2) && b1<max(y1,y2)){
				return true;
			} else {
				return false;
			}
		}
	} else {
		//y1 == y2, horizontal
		if(b1 == b2){
			if(b1 != y1) {
				//parallel
				return false;
			} else {
				//check if segment contains each other
				if(x1>=min(a1,a2) && x1<=max(a1,a2)) {
					return true;
				} else if (x2>=min(a1,a2) && x2<=max(a1,a2)) {
					return true;
				} else {
					return false;
				}

			}
		} else {
			if(y1>=min(b1,b2) && y1<=max(b1,b2) && a1>min(x1,x2) && a1<max(x1,x2)){
				return true;
			} else {
				return false;
			}
		}
	}

	return ret;
}

//return the coordinates of the crossed point
pair<int,int> intersection(pair<int,int> s1, pair<int,int> e1, pair<int,int> s2, pair<int,int> e2) {
	pair<int,int> ret = make_pair(0,0);

	int x1 = s1.first;
	int x2 = e1.first;
	int y1 = s1.second;
	//int y2 = e1.second;

	int a1 = s2.first;
	int a2 = e2.first;
	int b1 = s2.second;
	int b2 = e2.second;

	if(x1==x2){
		if(b1==b2){
			ret = make_pair(x1,b1);
		} else {
			cout << "Pas de bol" << endl;
		}
	} else {
		//y1==y2
		if(a1==a2){
			ret = make_pair(a1,y1);
		} else {
			cout << "Pas de bol" << endl;
		}
	}

	return ret;

}

int main() {
	cout << "Advent day 3 start" << endl;

	vector<pair<int,int>> wire1(1, make_pair(0,0));
	vector<pair<int,int>> wire2(1, make_pair(0,0));

	//put all coordinates to wires
	ifstream path;
	path.open("path.txt");
	if(path.is_open()){
		string line;
		string cmd;
		bool next = false;
		while(getline(path, line)){
			stringstream ss(line);
			while(getline(ss, cmd, ',')) {
				char dir = cmd[0];
				int val  = stoi(cmd.substr(1,cmd.size()-1));
				if(!next) {
					updateWire(dir, val, &wire1);
				} else {
					updateWire(dir, val, &wire2);
				}
			}
			next = true;
			cout << endl;

		}
	}
	path.close();

	int min = 5000000;
	int totalDistance = 5000000;

	pair<int,int> firstCrossedWire1;
	pair<int,int> firstCrossedWire2;
	pair<int,int> firstCrossed;
	for(unsigned int k=1; k<wire2.size()-1; k++) {
		for(unsigned int j=1; j<wire1.size()-1; j++) {

			bool crossed = isCrossed(wire1[j], wire1[j+1], wire2[k], wire2[k+1]);
			if(crossed){
				pair<int,int> crossedPoint = intersection(wire1[j], wire1[j+1], wire2[k], wire2[k+1]);
				cout << "Crossed between (" << wire1[j].first << "," << wire1[j].second << ")-(" << wire1[j+1].first << "," << wire1[j+1].second << ") and (" << wire2[k].first << "," << wire2[k].second << ")-(" << wire2[k+1].first << "," << wire2[k+1].second << ")" << ", distance: " << d(crossedPoint) << endl;

				//test
				firstCrossedWire1 = wire1[j];
				firstCrossedWire2 = wire2[k];
				firstCrossed = crossedPoint;

				int dist1 = 0;
				int k1 = 0;
				while(wire1[k1]!=firstCrossedWire1) {
					k1++;
					dist1 += abs(wire1[k1].first-wire1[k1-1].first) + abs(wire1[k1].second-wire1[k1-1].second);
				}
				dist1 += abs(firstCrossed.first-wire1[k1].first) + abs(firstCrossed.second-wire1[k1].second);
				cout << "Distance to crossed point from wire 1: " << dist1 << endl;

				int dist2 = 0;
				int k2= 0;
				while(wire2[k2]!=firstCrossedWire2) {
					k2++;
					dist2 += abs(wire2[k2].first-wire2[k2-1].first) + abs(wire2[k2].second-wire2[k2-1].second);
				}
				dist2 += abs(firstCrossed.first-wire2[k2].first) + abs(firstCrossed.second-wire2[k2].second);
				cout << "Distance to crossed point from wire 2: " << dist2 << endl;
				cout << "Total distance: " << dist1+dist2 << endl << endl;
				totalDistance = totalDistance<dist1+dist2 ? totalDistance : dist1+dist2;

				//



				min = min<d(crossedPoint) ? min : d(crossedPoint);
			}
		}
	}
	cout << "Minimum ->" << min << endl;
	cout << "Total distance minimum " << totalDistance << endl;



	cout << "Advent day 3 end" << endl;
	return 0;
}
