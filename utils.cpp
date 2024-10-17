#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "utils.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");  // Dla Windows
#else
    system("clear");  // Dla Linux/Unix/OS X
#endif
}

string getRandomWord() {
    vector<string> words;
    ifstream file("/Users/wiktorlazar/CLionProjects/Gra-w-wisielca-Wiktor-Lazar/words.txt");
    if (!file) {
        cerr << "Nie znaleziono pliku 'words.txt'!" << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        words.push_back(word);
    }

    srand(static_cast<unsigned>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void saveScore(string playerName, int score) {
    ofstream file("/Users/wiktorlazar/CLionProjects/Gra-w-wisielca-Wiktor-Lazar/scores.txt", ios::app);
    if (file) {
        file << playerName << " " << score << endl;
    } else {
        cerr << "Nie można zapisać wyniku!" << endl;
    }
}