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
	VICTORY_IN_FIRST_HALF,
	VICTORY_IN_SECOND_HALF,
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

bool checkIfCountryExists(string repeatedTeams[32], string country);
Game simulateGame(Team firstTeam, Team secondTeam);
int generateRandomNumber(int number);
void draftGroups(Cup &cup);
void chooseTeam(Team &team, Team bowlTeam[8], string repeatedTeams[32]);
void filterBowlTeam(Team teams[], Team (&bowlTeam)[8], Bowl bowl);
void simulateCup(Cup cup);
void simulateGroup(Group &group);
void simulatePlayoffs(Group groups[8]);
Team getTeamWithHighestPoints(Team teams[4]);
Team getSecondTeamWithHighestPoints(Team teams[4], string invalidTeamName);

int generateRandomNumber(int number)
{
	return rand() % number;
}

bool checkIfCountryExists(string repeatedTeams[32], string country)
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

Game simulateGame(Team firstTeam, Team secondTeam)
{
	int firstTeamGoals = 0, secondTeamGoals = 0;
	int victoryInHalf = generateRandomNumber(2);
	int firstTeamPower = generateRandomNumber(firstTeam.power);
	int secondTeamPower = generateRandomNumber(secondTeam.power);

	if (firstTeamPower > secondTeamPower)
	{
		firstTeamGoals++;
		firstTeam.points += 3;
	}
	else if (firstTeamPower < secondTeamPower)
	{
		secondTeamGoals++;
		secondTeam.points += 3;
	}
	else
	{
		firstTeam.points++;
		secondTeam.points++;
		cout << firstTeam.name << " - " << firstTeamGoals << " | EMPATOU | " << secondTeamGoals << " - " << secondTeam.name << endl;
		return {{firstTeam, secondTeam}, Results::TIE, firstTeamGoals, secondTeamGoals};
	}

	if (victoryInHalf)
	{
		cout << firstTeam.name << " - " << firstTeamGoals << " | FEZ O GOL NO SEGUNDO TEMPO | " << secondTeamGoals << " - " << secondTeam.name << endl;
		return {{firstTeam, secondTeam}, Results::VICTORY_IN_SECOND_HALF, firstTeamGoals, secondTeamGoals};
	}
	else
	{
		cout << firstTeam.name << " - " << firstTeamGoals << " | FEZ O GOL NO PRIMEIRO TEMPO | " << secondTeamGoals << " - " << secondTeam.name << endl;
		return {{firstTeam, secondTeam}, Results::VICTORY_IN_FIRST_HALF, firstTeamGoals, secondTeamGoals};
	}
}

void chooseTeam(Team &team, Team bowlTeam[8], string repeatedTeams[32])
{
	team = bowlTeam[generateRandomNumber(8)];
	bool alreadyExists = checkIfCountryExists(repeatedTeams, team.name);
	while (alreadyExists)
	{
		team = bowlTeam[generateRandomNumber(8)];
		alreadyExists = checkIfCountryExists(repeatedTeams, team.name);
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

void draftGroups(Cup &cup)
{
	int repeatedTeamsLength = 0;
	string repeatedTeams[32];
	Team bowlOne[8], bowlTwo[8], bowlThree[8], bowlFour[8];

	filterBowlTeam(cup.teams, bowlOne, Bowl::ONE);
	filterBowlTeam(cup.teams, bowlTwo, Bowl::TWO);
	filterBowlTeam(cup.teams, bowlThree, Bowl::THREE);
	filterBowlTeam(cup.teams, bowlFour, Bowl::FOUR);

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
				break;
			}
			case 1:
			{
				chooseTeam(randomTeam, bowlTwo, repeatedTeams);
				break;
			}
			case 2:
			{
				chooseTeam(randomTeam, bowlThree, repeatedTeams);
				break;
			}
			case 3:
			{
				chooseTeam(randomTeam, bowlFour, repeatedTeams);
				break;
			}
			default:
			{
				cout << "Ops! Algum erro aconteceu ao fazer o sorteio da copa!";
				return;
			}
			}

			repeatedTeams[repeatedTeamsLength] = randomTeam.name;
			repeatedTeamsLength++;

			cup.groups[i].teams[j] = randomTeam;
		}
	}
}

void simulateGroup(Group &group)
{
	int currentTeamIndex = 0, setCurrectTeamIndex = 0, adversaryTeamIndex = 1, adversaryAuxiliarTeamIndex = 2, currectTeamLimitIndex = 3;
	while (currentTeamIndex < 3)
	{
		Game game = simulateGame(group.teams[currentTeamIndex], group.teams[adversaryTeamIndex]);
		group.teams[currentTeamIndex].points = game.teams[0].points;
		group.teams[adversaryTeamIndex].points = game.teams[1].points;

		adversaryTeamIndex++;
		setCurrectTeamIndex++;
		if (setCurrectTeamIndex == currectTeamLimitIndex)
		{
			currentTeamIndex++;
			currectTeamLimitIndex--;
			setCurrectTeamIndex = 0;
			adversaryTeamIndex = adversaryAuxiliarTeamIndex;
			adversaryAuxiliarTeamIndex++;
		}
	}
}

void simulatePlayoffs(Group groups[8])
{
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		Team highestTeamPoint = getTeamWithHighestPoints(groups[i].teams);
		Team secondHighestTeamPoint = getSecondTeamWithHighestPoints(groups[i].teams, highestTeamPoint.name);

		cout << "Times classificados do Grupo " << groups[i].name << ": " << highestTeamPoint.name << " (" << highestTeamPoint.points << (highestTeamPoint.points == 1 ? " Ponto) e " : " Pontos) e ") << secondHighestTeamPoint.name << " (" << secondHighestTeamPoint.points << (secondHighestTeamPoint.points == 1 ? " Ponto)" : " Pontos)") << endl;
	}
}

Team getTeamWithHighestPoints(Team teams[4])
{
	Team highestTeamPoint;
	int highestPoints = 0;

	for (int i = 0; i < 4; i++)
	{
		if (teams[i].points > highestPoints)
		{
			highestPoints = teams[i].points;
			highestTeamPoint = teams[i];
		}
	}

	return highestTeamPoint;
}

Team getSecondTeamWithHighestPoints(Team teams[4], string invalidTeamName)
{
	Team highestTeamPoint;
	int highestPoints = 0;

	for (int i = 0; i < 4; i++)
	{
		if (teams[i].points > highestPoints && teams[i].name != invalidTeamName)
		{
			highestPoints = teams[i].points;
			highestTeamPoint = teams[i];
		}
	}

	return highestTeamPoint;
}

void simulateCup(Cup cup)
{
	draftGroups(cup);

	for (int i = 0; i < 8; i++)
	{
		simulateGroup(cup.groups[i]);
	}

	simulatePlayoffs(cup.groups);
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

	simulateCup(cup);

	return 0;
}
