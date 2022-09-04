#include <iostream>
#include <time.h>

using namespace std;

enum Bowl
{
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
};

struct Team
{
	string name;
	Bowl bowl;
	int power, points;
};

struct Group
{
	char name;
	Team teams[4];
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
	int firstTeamGoals, secondTeamGoals;
};

struct Cup
{
	Group groups[8];
	Team teams[32];
};

bool checkIfExistsCountry(string repeatedTeams[32], string country);
int generateRandomNumber(int number);
void draftGroups(Cup cup);
void chooseTeam(Team &team, Team bowlTeam[8], string repeatedTeams[32]);
void filterBowlTeam(Team teams[], Team (&bowlTeam)[8], Bowl bowl);

int generateRandomNumber(int number)
{
	return rand() % number;
}

bool checkIfExistsCountry(string repeatedTeams[32], string country)
{
	for (int i = 0; i < 32; i++)
	{
		if (repeatedTeams[i] == country)
		{
			return true;
		}
	}
	return false;
}

void chooseTeam(Team &team, Team bowlTeam[8], string repeatedTeams[32])
{
	team = bowlTeam[generateRandomNumber(8)];
	bool alreadyExists = checkIfExistsCountry(repeatedTeams, team.name);
	while (alreadyExists)
	{
		team = bowlTeam[generateRandomNumber(8)];
		alreadyExists = checkIfExistsCountry(repeatedTeams, team.name);
	}
}

void filterBowlTeam(Team teams[], Team (&bowlTeam)[8], Bowl bowl)
{
	int length = 0;

	for (int i = 0; i < 32; i++)
	{
		if (teams[i].bowl == bowl)
		{
			bowlTeam[length] = teams[i];
			length++;
		}
	}
}

void draftGroups(Cup cup)
{
	Team bowlOne[8], bowlTwo[8], bowlThree[8], bowlFour[8];

	filterBowlTeam(cup.teams, bowlOne, Bowl::ONE);
	filterBowlTeam(cup.teams, bowlTwo, Bowl::TWO);
	filterBowlTeam(cup.teams, bowlThree, Bowl::THREE);
	filterBowlTeam(cup.teams, bowlFour, Bowl::FOUR);

	string repeatedTeams[32];
	int repeatedTeamsLength = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Team randomTeam;
			switch (j)
			{
			case 0:
			{
				chooseTeam(randomTeam, bowlOne, repeatedTeams);
				repeatedTeams[repeatedTeamsLength] = randomTeam.name;
				repeatedTeamsLength++;

				break;
			}
			case 1:
			{
				chooseTeam(randomTeam, bowlTwo, repeatedTeams);
				repeatedTeams[repeatedTeamsLength] = randomTeam.name;
				repeatedTeamsLength++;

				break;
			}
			case 2:
			{
				chooseTeam(randomTeam, bowlThree, repeatedTeams);
				repeatedTeams[repeatedTeamsLength] = randomTeam.name;
				repeatedTeamsLength++;

				break;
			}
			case 3:
			{
				chooseTeam(randomTeam, bowlFour, repeatedTeams);
				repeatedTeams[repeatedTeamsLength] = randomTeam.name;
				repeatedTeamsLength++;

				break;
			}
			default:
			{
				cout << "Ops! Algum erro aconteceu ao fazer o sorteio da copa!";
				return;
			}
			}

			cup.groups[i].teams[j] = randomTeam;
		}
	}
}

int main()
{
	srand(time(NULL));

	Cup cup = {
			{{'A', {}},
			 {'B', {}},
			 {'C', {}},
			 {'D', {}},
			 {'E', {}},
			 {'F', {}},
			 {'G', {}},
			 {'H', {}}},
			{{"Catar", Bowl::ONE, 30, 0},
			 {"Equador", Bowl::TWO, 35, 0},
			 {"Senegal", Bowl::FOUR, 20, 0},
			 {"Holanda", Bowl::TWO, 67, 0},
			 {"Inglaterra", Bowl::ONE, 80, 0},
			 {"Irã", Bowl::THREE, 60, 0},
			 {"Estados Unidos", Bowl::FOUR, 15, 0},
			 {"País de Gales", Bowl::THREE, 35, 0},
			 {"Argentina", Bowl::ONE, 79, 0},
			 {"Arábia Saudita", Bowl::FOUR, 52, 0},
			 {"México", Bowl::TWO, 60, 0},
			 {"Polônia", Bowl::TWO, 54, 0},
			 {"França", Bowl::ONE, 82, 0},
			 {"Austrália", Bowl::THREE, 56, 0},
			 {"Dinamarca", Bowl::THREE, 74, 0},
			 {"Tunísia", Bowl::FOUR, 41, 0},
			 {"Espanha", Bowl::ONE, 75, 0},
			 {"Costa Rica", Bowl::THREE, 40, 0},
			 {"Alemanha", Bowl::TWO, 63, 0},
			 {"Japão", Bowl::TWO, 62, 0},
			 {"Bélgica", Bowl::ONE, 72, 0},
			 {"Canadá", Bowl::FOUR, 33, 0},
			 {"Marrocos", Bowl::FOUR, 37, 0},
			 {"Croácia", Bowl::TWO, 65, 0},
			 {"Brasil", Bowl::ONE, 85, 0},
			 {"Sérvia", Bowl::THREE, 75, 0},
			 {"Suíça", Bowl::THREE, 67, 0},
			 {"Camarões", Bowl::FOUR, 49, 0},
			 {"Portugal", Bowl::ONE, 76, 0},
			 {"Gana", Bowl::FOUR, 54, 0},
			 {"Uruguai", Bowl::TWO, 60, 0},
			 {"Córeia do Sul", Bowl::THREE, 42, 0}},
	};

	draftGroups(cup);

	return 0;
}
