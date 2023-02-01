#include "LogWalki.h"

using namespace std;

LogWalki::LogWalki(int x, int y, string n1, string n2, string coZ) : x(x), y(y), nazwa1(n1), nazwa2(n2), coZrobil(coZ) {}

int LogWalki::getX() { return x; }
int LogWalki::getY() { return y; }
string LogWalki::getOrg1() { return nazwa1; }
string LogWalki::getOrg2() { return nazwa2; }
string LogWalki::getCoZrobil() { return coZrobil; }