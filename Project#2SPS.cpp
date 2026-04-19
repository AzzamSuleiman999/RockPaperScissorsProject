// Project#2SPS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enGameChoice{Stone=1,Paper=2,Scissors=3};

enum enWinner{Player1=1,Computer=2,Draw=3};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner WinnerGame;
	string WinnerName;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Paper:
		return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Scissors:
		return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
	}

}

enWinner WhoWinTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone","Paper","Scissors" };
	return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Palyer1","Computer","Draw" };
	return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 0;
	do
	{
		cout << "\nYour Choice : [1]Stone [2]Paper [3]Scissors ?\n";
		cin >> Choice;
	} while (Choice < 1 || Choice>3);
	return (enGameChoice)Choice;
}

void SetWinnerScrrenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4f");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
	
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n__________________Round [" << RoundInfo.RoundNumber << "] ______________________\n\n";
	cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner : [" << RoundInfo.WinnerName << "] \n";
	cout << "__________________________________________________\n\n";
	SetWinnerScrrenColor(RoundInfo.Winner);
}

short ReadHowManyRounds()
{
	short RoundNumber = 0;
	cout << "\nHow Many Rounds do you want to play : \n";
	cin >> RoundNumber;
	return RoundNumber;
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.WinnerGame = WhoWinTheGame(Player1WinTimes,ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.WinnerGame);

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t = t + "\t";
	}
	return t;
}

void ShowGameOverScrren()
{
	cout << Tabs(2) << "______________________________________________________\n\n";
	cout << Tabs(2) << "                    ++ Game Over ++                     \n";
	cout << Tabs(2) << "______________________________________________________\n\n\n";
}

void ShowFinalResults(stGameResults GameResults)
{
	cout << Tabs(2) << "____________________ [Game Results] __________________\n\n";
	cout << Tabs(2) << "Round              : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 Won Times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl << endl;
	cout <<Tabs(2)<<"______________________________________________________\n\n";
	
	SetWinnerScrrenColor(GameResults.WinnerGame);
}

void ResetScrren()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		ResetScrren();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScrren();
		ShowFinalResults(GameResults);

		cout << endl << Tabs(2) << "Do you want to play again Y/N ?";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}



int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
