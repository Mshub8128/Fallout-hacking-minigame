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

string consoleText[20] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

void upText(int row, int indent, string textInput) {

	for (int i = 0; i < sizeof(consoleText) / sizeof(consoleText[0]) - 1; i++) {
		consoleText[i] = consoleText[i+1];
	}
	consoleText[20] = textInput;

	for (int i = 0; i < sizeof(consoleText) / sizeof(consoleText[0]); i++) {
		std::printf("\033[%d;%dH", row  -1, indent);
		std::cout << consoleText[i];

	}
}			