#pragma once
#include <string>

using namespace std;

class LogWalki {
private:
	int x;
	int y;
	string nazwa1;
	string nazwa2;
	string coZrobil;
public:
	LogWalki(int x, int y, string n1, string n2, string coZ);

	int getX();
	int getY();
	string getOrg1();
	string getOrg2();
	string getCoZrobil();
};