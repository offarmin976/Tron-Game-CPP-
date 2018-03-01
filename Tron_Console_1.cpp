// Tron_Console_1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "stdlib.h"
#include <conio.h>
#include "ConsoleLogger.h"
#include "windows.h"
#include <wincon.h>
#include <ctime>
#include <cstdlib>
extern void center(char *);
#pragma warning(disable: 4996)

static bool isUsed[80][20] = {false};

const short unsigned int Keyleft = 37;				//Keys for AWSD
const short unsigned int Keytop = 38;
const short unsigned int Keyright = 39;
const short unsigned int Keydown = 40;
const short unsigned int Keyexit = 81;

static int firstPlayerScore = 0;
static int firstPlayerDirection = Keyright;
static int firstPlayerColumn = 0;
static int firstPlayerRow = 10;

static int secondPlayerScore = 0;
static int secondPlayerDirection = Keyleft;
static int secondPlayerColumn = 80;
static int secondPlayerRow = 10;

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
static int PL1_C = 0;
static int PL2_C = 0;
static int RandomNumber = 15;
static bool firstPlayerLooseB = false;
static bool secondPlayerLooseB = false; 

static int highscore = 0;
void HighScore();
void BasisMap();

void Menu();

void chooseColor();
void MovePlayers();
void ChangePlayerDirection(int);
bool PlayerLooses(int, int);
void NewGame();
void BeginNewGame();
void NewGameMap();
void ResetGame();
void WriteColor(int, int, char,int);
int getKey();
void LoadingFont();
bool running = true;
void gotoXY(int, int); 
void SetColor(int);
void MapSettings();

static int Level = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

class Map
{
public:
	virtual void Mappen()	//Still under maintance, right now not working
	{
		int abc, def;
		for (int i = 0; i < 10; i++)
		{

			abc = rand() % RandomNumber + 1;
			def = rand() % RandomNumber + 1;
			gotoXY(abc, def);
			SetColor(15);
			cout << "X";
			isUsed[abc][def] = true;
		}
	}
};
class MapMedium : public Map
{
public: void Mappen()
{

			int abc, def;
			for (int i = 0; i < 20; i++)
			{

				abc = rand() % RandomNumber + 5;
				def = rand() % RandomNumber + 5;
				gotoXY(abc, def);
				SetColor(15);
				cout << "X";
				isUsed[abc][def] = true;
			}
}

};
class MapHeavy : public Map
{
public: void Mappen()
{

			int abc, def;
			for (int i = 0; i < 25; i++)
			{

				abc = rand() % RandomNumber + 15;
				def = rand() % RandomNumber + 15;
				SetColor(15);
				gotoXY(abc, def);
				cout << "X";
				isUsed[abc][def] = true;
			}
}

};


int _tmain(int argc, _TCHAR* argv[])
{
	LoadingFont();
	int test;
	for (int i = 0; i < 80; i++)
	{
		SetConsoleTitle(TEXT("LOADING"));
		std::cout << "_";
		_sleep(10);
	}
	SetConsoleTitle(TEXT("TRON"));


	system("cls");
	

	center ("TRON");
	std::cout << "" << endl;
	center("Ready for a new game?");
	std::cout << "" << endl;
	
	gotoXY(18, 5); cout << "Main Menu";
	gotoXY(18, 7); cout << "->";

		Menu();
	
	gotoXY(20, 21);
	return 0;
}
void MapSettings()
{
	for (int i = 0; i < 80; i++)
	{
		std::cout << "_";
		_sleep(10);
	}
	center("Map Settings...");
	_sleep(40);
	gotoXY(0, 10);
	cout << "Activate Map Settings ? ( < | > )";
	while ((true))
	{

		if (GetAsyncKeyState(VK_LEFT))
		{
			gotoXY(5, 3);
			center("Map has been activated");
			_sleep(1000);
			gotoXY(5, 4);
			center("Choose the Level of your Map ( 1 | 2 | 3 )");
			cin >> Level;
			switch (Level)
			{
			case 1:
				center("Difficult Level for Map has been changed");
				cout << "Level is:" << Level;
				break;
			case 2:
				center("Difficult Level for Map has been changed");
				cout << "Level is:" << Level;
				break;
			case 3:
				center("Difficult Level for Map has been changed");
				cout << "Level is:" << Level;
				break;
			default:
				break;
			}
			break;
		}
		system("pause>nul");
		if (GetAsyncKeyState(VK_RIGHT))
		{
			gotoXY(10, 12);
			center("Map has been deactivated");
			Level = 0;
			cout << "LEVEL NOW:" + Level<<endl;
			_sleep(3000);
			break;
		}
	}
	center("Exiting");
	_sleep(1000);
	
}
void center(char* s)
{
	running = 1;
	int l = strlen(s);
	int pos = (int)((80 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";
	cout << s;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void chooseColor()
{
	int xcv;
	system("cls");
	
	int x = 7;
	for (int i = 0; i < 80; i++)
	{
		
		std::cout << "_";
		_sleep(10);
	}
	center("Player 1 Choose Color now [ /\ | V ]");
	_sleep(100);
	for (int count = -1; count < 15; count++)
	{	
		system("pause>nul");
		if ((GetAsyncKeyState(VK_DOWN)) || (GetAsyncKeyState(VK_UP) ))
		{
			SetColor(count);
			gotoXY(20, 7);
			cout<<"Your Bike ->   *-|-*";
			system("pause>nul");
			x++; 
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			PL1_C = count;
			SetColor(15);
			gotoXY(0, 10);
			cout << "Player 1 have chosen Color";
			gotoXY(0, 1);
			_sleep(800);
			for (int i = 0; i < 80; i++)
			{
				SetColor(count);
				std::cout << "_";
				_sleep(10);
				
			}
			break;
			system("cls");
		}
	}

	again:
	SetColor(15);
	center("Player 2 Choose Color now [ /\ | V ]");
	_sleep(100);
	for (int count = 0; count < 16; count++)
	{
		system("pause>nul");
		if ((GetAsyncKeyState(VK_DOWN)) || (GetAsyncKeyState(VK_UP)))
		{
			SetColor(count);
			gotoXY(20, 7);
			cout << "Your Bike ->   *-|-*";
			system("pause>nul");
			x++;

		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			PL2_C = count;
			if (PL1_C == PL2_C)
			{
				gotoXY(0, 18);
				SetColor(15);
				cout << "Choose another Color, Player 1 have it already "<<endl;
				for (int i = 0; i < 80; i++)
				{

					std::cout << "_";
					_sleep(10);

				}
				
				goto again;
				system("cls");
			}
			
			gotoXY(0, 11);
			SetColor(15);
			cout<<"Player 2 have chosen Color";
			gotoXY(0, 2);
			_sleep(800);
			for (int i = 0; i < 80; i++)
			{
				SetColor(count);
				std::cout << "_";
				_sleep(10);
				
			}
			break;
			system("cls");

		}
	}
	system("cls");
	
	BeginNewGame();

}
void NewGame()
{	
	running = false;
	gotoXY(20, 16);
	cout << "New Game...     " << endl;
	for (int i = 0; i < 80; i++)
	{
		cout << "_";
		_sleep(10);

	}
	gotoXY(0, 20);
	for (int i = 0; i < 80; i++)
	{
		cout << "_";
		_sleep(10);

	}

	chooseColor();

}

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Throw out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void LoadingFont()
{
	gotoXY(20, 0);
	cout << "  ______    ____        __      _     _    ";
	_sleep(500);
	gotoXY(20, 1);
	cout << "    /       /    )    /    )    /|   /     ";
	_sleep(500);
	gotoXY(20, 2);
	cout << "---/-------/___ /----/----/----/-| -/------";
	_sleep(500);
	gotoXY(20, 3);
	cout << "  /       /    |    /    /    /  | /       ";
	_sleep(500);
	gotoXY(20, 4);
	cout << "_/_______/_____|___(____/____/___|/________";
	_sleep(500);
	gotoXY(0, 5);






}

void BeginNewGame()
{
	
	while (true)
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ChangePlayerDirection(38);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			ChangePlayerDirection(39);
		}
		if (GetAsyncKeyState(VK_UP))
		{
			ChangePlayerDirection(37);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			ChangePlayerDirection(40);
		}


		if (GetAsyncKeyState(0x57))
		{
			ChangePlayerDirection(119);
		}
		if (GetAsyncKeyState(0x41))
		{
			ChangePlayerDirection(97);
		}
		if (GetAsyncKeyState(0x44))
		{
			ChangePlayerDirection(100);
		}
		if (GetAsyncKeyState(0x53))
		{
			ChangePlayerDirection(115);
		}


		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
			system("pausel>nul");
			gotoXY(0, 10);
			center("Exiting to Main Menu");
			_sleep(1000);
			Menu();
			
		}
		
		MovePlayers();
		

		firstPlayerLooseB = PlayerLooses(firstPlayerRow, firstPlayerColumn);
		secondPlayerLooseB = PlayerLooses(secondPlayerRow, secondPlayerColumn);

		if ((firstPlayerLooseB == true) && (secondPlayerLooseB == true))
		{
			firstPlayerScore++;
			secondPlayerScore++;
			gotoXY(0, 20);
			SetColor(15);
			center("GAME OVER | DRAW GAME");
			
			if (firstPlayerScore > highscore)
			{
				highscore = firstPlayerScore;
			}
			if (secondPlayerScore > highscore)
			{
				highscore = secondPlayerScore;
			}
			gotoXY(0, 22);
			cout << "Current Scores:";
			gotoXY(0, 23);
			cout << "Player 1: " << firstPlayerScore;
			gotoXY(0, 24);
			cout << "Player 2: " << secondPlayerScore;
			system("pause>nul");
			ResetGame();
		}
		if (firstPlayerLooseB == true)
		{
			secondPlayerScore++;
			SetColor(15);
			gotoXY(0, 20);
			center("GAME OVER | PLAYER 2 WINS");
			if (secondPlayerScore > highscore)
			{
				highscore = secondPlayerScore;
			}
			gotoXY(0, 22);
			cout << "Current Scores:";
			gotoXY(0, 23);
			cout << "Player 1: " << firstPlayerScore;
			gotoXY(0, 24);
			cout << "Player 2: " << secondPlayerScore;
			system("pause>nul");
			ResetGame();
		}
		if (secondPlayerLooseB == true)
		{
			firstPlayerScore++;
			SetColor(15);
			gotoXY(0, 20);
			center("GAME OVER | PLAYER 1 WINS");
			if (firstPlayerScore > highscore)
			{
				highscore = firstPlayerScore;
			}
			gotoXY(0, 22);
			cout<<"Current Scores:";
			gotoXY(0, 23);
			cout << "Player 1: " << firstPlayerScore;
			gotoXY(0, 24);
			cout << "Player 2: " << secondPlayerScore;
			system("pause>nul");

			ResetGame();

		}
		else
		{
			WriteColor(firstPlayerColumn, firstPlayerRow, '*', PL1_C);
			WriteColor(secondPlayerColumn, secondPlayerRow, '*', PL2_C);

			_sleep(10);
		}

		bool *b;
		isUsed[firstPlayerColumn][firstPlayerRow] = true;
		isUsed[secondPlayerColumn][secondPlayerRow] = true;



	}

}
int getKey()
	{
		while (true)
		{
			for (int i = 8; i <= 256; i++)
			{
				if (GetAsyncKeyState(i) & 0x7FFF)
				{

					// This if filters the keys, i want to allow direction arrows
					// and q for quit. If you want to add more just add the code for the key,
					// to know the key code just coment the if line and print the keycode.
					if ((i >= 37 && i <= 40) || i == 81)
						return i;
				}
			}
		}
	}

static void ChangePlayerDirection(int keyselect)
	{
		if (keyselect == 119 && firstPlayerDirection != Keydown)
		{
			firstPlayerDirection = Keytop;
		}
		if (keyselect == 97 && firstPlayerDirection != Keyright)
		{
			firstPlayerDirection = Keyleft;
		}
		if (keyselect == 100 && firstPlayerDirection != Keyleft)
		{
			firstPlayerDirection = Keyright;
		}
		if (keyselect == 115 && firstPlayerDirection != Keytop)
		{
			firstPlayerDirection = Keydown;
		}

		if (keyselect == 37 && secondPlayerDirection != Keydown)
		{
			secondPlayerDirection = Keytop;
		}
		if (keyselect == 38 && secondPlayerDirection != Keyright)
		{
			secondPlayerDirection = Keyleft;
		}
		if (keyselect == 39 && secondPlayerDirection != Keyleft)
		{
			secondPlayerDirection = Keyright;
		}
		if (keyselect == 40 && secondPlayerDirection != Keytop)
		{
			secondPlayerDirection = Keydown;
		}

	}

static void MovePlayers()
	{

		if (firstPlayerDirection == Keyright)
		{
			firstPlayerColumn++;
		}
		if (firstPlayerDirection == Keyleft)
		{
			firstPlayerColumn--;
		}
		if (firstPlayerDirection == Keytop)
		{
			firstPlayerRow--;
		}
		if (firstPlayerDirection == Keydown)
		{
			firstPlayerRow++;
		}


		if (secondPlayerDirection == Keyright)
		{
			secondPlayerColumn++;
		}
		if (secondPlayerDirection == Keyleft)
		{
			secondPlayerColumn--;
		}
		if (secondPlayerDirection == Keytop)
		{
			secondPlayerRow--;
		}
		if (secondPlayerDirection == Keydown)
		{
			secondPlayerRow++;
		}
	}

static bool PlayerLooses(int row, int col)
	{
		if (row < 0)
		{
			return true;
		}
		if (col < 0)
		{
			return true;
		}
		if (row >= 20)
		{
			return true;
		}
		if (col >= 80)
		{
			return true;
		}
		//bool control = false;

		if (isUsed[col][row] == true)
		{
			return true;
		}

	}
static void ResetGame()
	{
		system("cls");
		gotoXY(0, 21);
		for (int x = 0; x < 80; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				isUsed[x][y] = false;
			}
			
		}
		for (int i = 0; i < 80; i++)
		{
			cout << "_";
			_sleep(10);

		}
		firstPlayerColumn = 0;
		firstPlayerRow = 10;
		secondPlayerColumn = 80;
		secondPlayerRow = 10;
		firstPlayerDirection = Keyright;
		secondPlayerDirection = Keyleft;
		
			gotoXY(0, 10);
			MovePlayers();

		
	}
static void WriteColor(int X, int Y, char x, int Color_Player)
	{
		SetColor(Color_Player);
		gotoXY(X, Y);
		isUsed[X][Y] = true;
		cout << '*';
		
		_sleep(100);

	}
static void HighScore()
	{
		system("cls");
		gotoXY(20, 16);
		cout << "HIGHSCORE:" + highscore;
		
	}
static void NewGameMap()
{
	running = false;
	gotoXY(20, 16);
	cout << "New Game...     " << endl;
	for (int i = 0; i < 80; i++)
	{
		cout << "_";
		_sleep(10);

	}
	gotoXY(0, 20);
	for (int i = 0; i < 80; i++)
	{
		cout << "_";
		_sleep(10);

	}

	chooseColor();


}
static void Menu()
{
	gotoXY(18, 5); cout << "Main Menu";
	gotoXY(18, 7); cout << "->";
	
	int menu_item = 0, run, x = 7;
	while (true)
	{

		

		gotoXY(20, 7);  cout << "1) New Game";
		gotoXY(20, 8);  cout << "2) HighScore";
		gotoXY(20, 9);  cout << "3) Map Settings";
		gotoXY(20, 10); cout << "4) Credits";
		gotoXY(20, 11); cout << "5) Exit Tron";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != 11)
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7)
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)){

			switch (menu_item){

			case 0: {
						cout << "cls";
						NewGame();
						running = false;
						break;
			}

			case 1: {
						cout << "cls";
						system("cls");
						HighScore();
						break;
			}

			case 2: {
						cout << "cls";
						cout << string(300, '\n');
						MapSettings();
						NewGameMap();
						Map* map[3];

						map[0] = new Map();
						map[1] = new MapMedium();
						map[2] = new MapHeavy();

						map[Level]->Mappen();
						center("Map Level activted");

						running = false;
						break;
			}

			case 3: {
						gotoXY(5, 16);
						cout << "Credits";
						gotoXY(5, 18);
						center("Everything by Armin Bajrica | 2017 Copyright | HTL MOEDLING");
						break;
			}

			case 4: {
						gotoXY(20, 16);
						cout << "Exiting" << endl;
						for (int x = 0; x < 80; x++)
						{
							cout << "_";
							_sleep(500);
							exit(0);
						}

						running = false;
			}



			}
		}

	}

}