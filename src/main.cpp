#include <iostream>

using namespace std;

struct Group {
	string name;
	Team teams[4];
};

struct Team {
	string name, code;
	int pote, power, points;
};

enum Result {
	TIE,
	FIRST_TEAM_VICTORY,
	SECOND_TEAM_VICTORY,
};

struct Game {
	Team teams[2];
	int goals;
	Result result;
};

struct Cup {
	Group groups[8];
};

int main() {
  return 0;
}
