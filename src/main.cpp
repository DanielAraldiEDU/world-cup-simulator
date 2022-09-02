#include <iostream>

using namespace std;

struct Group
{
	string name;
	Team teams[4];
};

enum Bowl
{
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
};

struct Team
{
	string name, code;
	Bowl bowl;
	int power, points;
};

enum Results
{
	TIE,
	FIRST_TEAM_VICTORY,
	SECOND_TEAM_VICTORY,
};

struct Game
{
	Team teams[2];
	Results result;
	int goals;
};

struct Cup
{
	Group groups[8];
};

int main()
{
	return 0;
}
