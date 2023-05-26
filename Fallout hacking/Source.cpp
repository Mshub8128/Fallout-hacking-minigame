#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <stdlib.h>     
#include <windows.h>
#include <chrono>       
#include <thread>   
#include <list>
#include <utility>
#include <vector>
#include <unordered_map>
#include "upText.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESC 27
#define KEY_ONE 49
#define KEY_TWO 50
#define KEY_THREE 51
#define KEY_FOUR 52
#define KEY_FIVE 53
#define KEY_SIX 54
#define KEY_SEVEN 55
#define KEY_EIGHT 56
#define KEY_NINE 57

void ShowConsoleCursor(bool showFlag) // hides the cursor. Purely visual.
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main(){
	srand(time(NULL));
	ShowConsoleCursor(false);

	bool toggle = true;
	HANDLE  hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 // k = 2 for unselected, 32 for selected
	SetConsoleTextAttribute(hConsole, 2);
	int spacing;


	string x[20][32] = {};
	string answer;
	int y[20][32] = {};
	string border = "0xF";
	string borderPrint;
	string borderRand = "0123456789ABCDEF";
	string blocksAttempt;
	string guessWord;
	string cursorSelect;
	string consoleText[17] = {};
	string letters = R"(abcdefghijklmnopqrstuvwxyz<>{}$,[]*&%@_-':!?)";
//	string letters = R"(--------------------------------------------)";
	string testWord[3] = {"TESTS","FIVES","MOUSE"};
	//string consoleText[20] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };

	int wordLength = testWord[0].length();
	int wordCoord[10][2] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };
	int randCol;
	int randHoriz;
	int randVert;
	int attempts = 4;
	int test = 0;
	int count = 0;
	int xPos = 10;
	int yPos = 10;
	int charMapWidth = 24;
	int charMapHeight = 17;
	bool foundWord = false;
	
	std::cout << "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL\n!!! WARNING: LOCKOUT IMMINENT !!!";
	
	for (int j = 0; j < 17; j++) {
		spacing = 8;
		for (int i = 0; i < 32; i++) {
			if (i >= 12) {
				spacing = 16;
			}
			x[j][i] = (letters[rand() % 44]);//generate random string
			

		}
		for (int k = 0; k < 2; k++) {
			if (k == 0 && j < 12) {
				borderPrint = border + "9" + borderRand[rand() % 16] + borderRand[rand() % 16];
			}
			else {
				borderPrint = border + "A" + borderRand[rand() % 16] + borderRand[rand() % 16];

			}
			std::printf("\033[%d;%dH", 6 + j, 1+ 20*k);
			std::cout << borderPrint;
		}
	}
	answer = testWord[(rand() % (sizeof(testWord) / sizeof(testWord[0])))];

	for (int i = 0; i < sizeof(testWord) / sizeof(testWord[0]);i++) {

		randCol = rand() % 2;
		randHoriz = rand() % (11 - testWord[i].length());
		randVert = rand() % 17;
		wordCoord[i][0] = randVert;
		wordCoord[i][1] = randHoriz + 12 * randCol;
		for (int p = 0; p < testWord[i].length(); p++) {
			x[randVert][randHoriz + 12 * randCol + p] = testWord[i][p];
			y[randVert][randHoriz + 12 * randCol + p+8] = testWord[i].length()-p;
		}
		test += 1;
	}
	

	//for (int u = 0; u < 29; u++) {//6-22
	//	std::printf("\033[%d;%dH", u, 41);
	//	std::cout << u;
	//}
	int n = 0;
	while (true) {
		std::printf("\033[%d;%dH", 4, 1);
		std::cout << attempts << " ATTEMPT(S) LEFT: " << blocksAttempt;
		while (n < attempts) {
			n += 1;
			blocksAttempt += (char)254u;
			blocksAttempt += " ";
		}

		std::printf("\033[%d;%dH", 4, 19);
		std::cout << "        ";
		std::printf("\033[%d;%dH", 4, 1);
		std::cout << attempts << " ATTEMPT(S) LEFT: " << blocksAttempt.substr(count*2);

		foundWord = false;
		for (int j = 0; j < charMapHeight; j++) {
			spacing = 8;
			for (int i = 0; i < charMapWidth; i++) {
				if (i >= 12) {
					spacing = 16;
				}

				SetConsoleTextAttribute(hConsole, 2);
				std::printf("\033[%d;%dH", 6 + j, spacing + i);
				if (toggle) {
					std::cout << x[j][i];
				}
				else {
					std::cout << y[j][i];

				}
			}
		}

			SetConsoleTextAttribute(hConsole, 32);
			for (int p = 0; p < wordLength; p++) {						 //left,word highlight
				if (xPos <= 12) {
					if (y[yPos][xPos + 8] != 0) {
						std::printf("\033[%d;%dH", 6 + yPos, 8 + xPos - (wordLength - y[yPos][xPos + 8]) + p);
						std::cout << x[yPos][xPos - (wordLength - y[yPos][xPos + 8]) + p];

					}
				}

				if (xPos > 12) {										//right, word highlight
					if (y[yPos][xPos] != 0) {
						std::printf("\033[%d;%dH", 6 + yPos, 8 + xPos - (wordLength - y[yPos][xPos]) + p);
						std::cout << x[yPos][xPos - (wordLength - y[yPos][xPos]) - 8 + p];

					

					}
				}
			}

			
		


			
			for (int i = 0; i < sizeof(testWord) / sizeof(testWord[0]); i++) {			//left
				for (int p = 0; p < testWord[i].length(); p++) {
					if (xPos <= 12) {
						if (yPos == wordCoord[i][0] && xPos == wordCoord[i][1] + p) {
							foundWord = true;
						}
					}
					if (xPos > 12) {
						if (yPos == wordCoord[i][0] && xPos == wordCoord[i][1] + p + 8) {		//right
							foundWord = true;
						}
					}
				}
			}
			if (foundWord) {
				for (int i = 0; i < sizeof(testWord) / sizeof(testWord[0]); i++) {			//left, letter print
					for (int p = 0; p < testWord[i].length(); p++) {
						if (yPos == wordCoord[i][0] && xPos == wordCoord[i][1] + p) {
							cursorSelect = testWord[i];
							std::printf("\033[%d;%dH", 22, 42);
							std::cout << testWord[i];


						}
						if (yPos == wordCoord[i][0] && xPos == (wordCoord[i][1] + p + 8)) {
							cursorSelect = testWord[i];								//right, letter print
							std::printf("\033[%d;%dH", 22, 42);
							std::cout << testWord[i];

						}
					}
				}
			}
			if (!foundWord) {
				if (xPos <= 12) {
						SetConsoleTextAttribute(hConsole, 32);
						cursorSelect = x[yPos][xPos];
						std::printf("\033[%d;%dH", 6 + yPos, 8 + xPos);
						std::cout << x[yPos][xPos];
					
				}
				if (xPos > 12) {
						SetConsoleTextAttribute(hConsole, 32);
						cursorSelect = x[yPos][xPos - 8];
						std::printf("\033[%d;%dH", 6 + yPos, 8 + xPos);
						std::cout << x[yPos][xPos - 8];
					
				}

			}
			guessWord = cursorSelect;
			SetConsoleTextAttribute(hConsole, 2);
			std::printf("\033[%d;%dH", 22, 41);
			std::cout << ">      ";
			std::printf("\033[%d;%dH", 22, 41);
			std::cout << ">" << cursorSelect;



			switch ((_getch())) {
			case KEY_UP:
				if (yPos > 0) {
					yPos -= 1;
				};
				break;
			case KEY_DOWN:
				if (yPos < (charMapHeight - 1)) {
					yPos += 1;
				}
				break;
			case KEY_LEFT:
				if (xPos > 0 && xPos != 19) {
					xPos -= 1;
				}
				if (xPos == 19) {
					xPos -= 8;
				}
				break;
			case KEY_RIGHT:
				if (xPos < (charMapWidth + 7) && xPos != 12) {
					xPos += 1;
				}
				if (xPos == 12) {
					xPos += 8;
				}
				break;
			case KEY_SPACE:
				if (toggle) {
					system("cls");
					toggle = false;
				}
				else {
					system("cls");
					toggle = true;
				}
				break;
			case KEY_ESC:
				return 0;
			case KEY_ONE:
				attempts += 1;
				break;
			case KEY_ENTER: 			
				string tempHidden;
				for (int i = 0; i < sizeof(testWord) / sizeof(testWord[0]); i++) {			//left
					for (int p = 0; p < testWord[i].length(); p++) {
						if (yPos == wordCoord[i][0] && xPos == wordCoord[i][1] + p) {
							guessWord = testWord[i];
						}
						if (yPos == wordCoord[i][0] && xPos == wordCoord[i][1] + p + 8) {		//right
							guessWord = testWord[i];
						}
					}
				}
				if (guessWord != answer) {
					attempts -= 1;
					if (attempts == 0) {
						std::printf("\033[%d;%dH", 20, 41);
						std::cout << ">fail!";
					}
				}
				else {
					std::printf("\033[%d;%dH", 20 , 41);
					std::cout << ">WINNER!";
				}
				//upText(25, 91, guessWord); //SORT THIS SHIT OUT
				//consoleText;
				std::printf("\033[%d;%dH", 20 - count, 41);                      //	HERE NEED TO WRITE UPWARDS CONSOLE
				std::cout <<">" << guessWord;
				count += 1;

			}

		std::printf("\033[%d;%dH", 25, 80);
		std::cout << "( " << xPos<<", "<< yPos << ") "<<toggle<<","<<foundWord << " ";
	
		}
	}
