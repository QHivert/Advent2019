//============================================================================
// Name        : Advent10.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <string>

using namespace std;

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first-r.first,l.second-r.second};
}

/*
 * For a pair (x,y) with y!=0, returns x/y
 */
double direction(pair<int,int> coord) {
	double ret = 0;
	if(coord.second!=0) {
		ret = (double)coord.first/(double)coord.second;
	}
	return ret;
}

int main() {
	cout << "Advent Day 10 start" << endl;

	ifstream map;
	map.open("map.txt");

	//Will contains all asteroids' coordinates.
	vector<pair<int,int>> asteroids;

	/*
	 * Coordinates are named (x,y) as follow :
	 *
	 * (0,0) (1,0) ... (n,0)
	 * (0,1) (1,1) ... (n,1)
	 *  ...   ...  ...  ...
	 * (0,m) (1,m) ... (n,m)
	 *
	 */
	if(map.is_open()) {
		string line;
		int y(0);
		while(getline(map, line)) {
			int x(0);
			for(char k: line) {
				if(k=='#') {
					asteroids.push_back(make_pair(x,y));
				}
				x++;
			}
			y++;
		}
	}

	cout << "There are " << asteroids.size() << " asteroids in this map." << endl;

	/*
	 * For each asteroid, we will calculate the vector between him and all the others.
	 * Our asteroids is (x,y), the other is (a,b) the vector is V=(a-x, b-y);
	 * We will separate the vectors in five sets:
	 * - Vector that goes north-east (a-x<0 and b-y<0).
	 * - ..............   north-west (a-x>0 and b-y<0).
	 * - ..............   south-east (a-x<0 and b-y>0).
	 * - ..............   south-west (a-x>0 and b-y>0).
	 * - Vector that are directly upward, downward, leftward or rightward.
	 *
	 * Once we know in which set belongs the vector, we simply make dir=(a-x)/(b-y)
	 * Two or more asteroids in the same set with the same dir means one is blocking all the others.
	 */

	set<double> NE;
	set<double> NW;
	set<double> SE;
	set<double> SW;
	set<double> DD;

	int max=0;
	pair<int, int> base;

	for(pair<int,int> ast: asteroids) {

		//ast is the main asteroids (x,y)
		for(pair<int,int> other: asteroids) {

			//other is another asteroids (a,b)
			if(ast!=other) {
				pair<int,int> vector = other-ast;
				if(vector.first<0 && vector.second<0) {
					NE.insert(direction(vector));
				}
				else if(vector.first>0 && vector.second<0) {
					NW.insert(direction(vector));
				}
				else if(vector.first<0 && vector.second>0) {
					SE.insert(direction(vector));
				}
				else if(vector.first>0 && vector.second>0) {
					SW.insert(direction(vector));
				}
				else {
					if(vector.first==0 && vector.second<0) {
						DD.insert(0.5);
					}
					else if(vector.first==0 && vector.second>0) {
						DD.insert(1.5);
					}
					else if(vector.first<0 && vector.second==0) {
						DD.insert(1);
					}
					else {
						DD.insert(0);
					}
				}
			}
		}
		//Totals asteroid in direct line of sight (los) for ast;
		int totalLos = NE.size() + NW.size() + SE.size() + SW.size() + DD.size();
		cout << "Asteroid at (" << ast.first << "," << ast.second << ") can see " << totalLos << " asteroids." << endl;

		if(max<totalLos) {
			max = totalLos;
			base = ast;
		}

		NE.clear();
		NW.clear();
		SE.clear();
		SW.clear();
		DD.clear();
	}

	cout << "Asteroid at (" << base.first << "," << base.second << ") can see the most asteroids: " << max << endl;

	cout << "Advent Day 10 end" << endl;
	return 0;
}
