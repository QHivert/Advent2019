//============================================================================
// Name        : Advent4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


bool checkDouble(int a, int b, int c, int d, int e, int f) {
	bool ret = false;
	int code[6] = {a,b,c,d,e,f};
	int countA(0), countB(0), countC(0), countD(0), countE(0), countF(0);

	for(int k : code) {
		if(k==a) countA++;
		if(k==b) countB++;
		if(k==c) countC++;
		if(k==d) countD++;
		if(k==e) countE++;
		if(k==f) countF++;
	}

	if(countA==2 || countB==2 || countC==2 || countD==2 || countE==2 || countF==2 ) {
		ret = true;
	}

	return ret;
}

int main() {
	cout << "Advent day 4 start!" << endl;

	int start = 276025;
	int end   = 767253;

	int count = 0;

	for(int k = start; k<=end; k++) {
		int code = k;
		int a = code/100000;
		int b = (code-a*100000)/10000;
		int c = (code-a*100000 - b*10000)/1000;
		int d = (code-a*100000 - b*10000 - c*1000)/100;
		int e = (code-a*100000 - b*10000 - c*1000 - d*100)/10;
		int f = (code-a*100000 - b*10000 - c*1000 - d*100 - e*10);
		if(a<=b && b<=c && c<=d && d<=e && e<=f) {
			if(a==b || b==c || c==d || d==e || e==f) {
				if(checkDouble(a,b,c,d,e,f)){
					count++;
				}
//				count++;
			}
		}
	}
	cout << "There is " << count << " possibilities." << endl;
	cout << "Advent day 4 end!" << endl;

	return 0;
}
