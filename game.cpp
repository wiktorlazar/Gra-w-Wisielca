#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "game.h"
#include "utils.h"

using namespace std;

void playGame(int chances) {
    string word = getRandomWord();
    string guessedWord(word.length(), '_');
    vector<char> usedLetters;
    int remainingChances = chances;
    bool win = false;

    while (remainingChances > 0 && guessedWord != word) {
        clearScreen();
        cout << "Słowo: " << guessedWord << endl;
        cout << "Użyte litery: ";
        for (char letter: usedLetters) {
            cout << letter << " ";
        }
        cout << endl;
        cout << "Pozostałe szanse: " << remainingChances << endl;

        char guess;
        cout << "Podaj literę: ";
        cin >> guess;

        if (!isalpha(guess)) {
            cout << "Podaj pojedynczą literę!" << endl;
            continue;
        }

        guess = toupper(guess);

        if (find(usedLetters.begin(), usedLetters.end(), guess) != usedLetters.end()) {
            cout << "Ta litera została już użyta!" << endl;
            continue;
        }

        usedLetters.push_back(guess);

        if (word.find(guess) != string::npos) {
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guess) {
                    guessedWord[i] = guess;
                }
            }
        } else {
            remainingChances--;
        }
    }

    clearScreen();
    if (guessedWord == word) {
        cout << "Gratulacje! Odgadłeś słowo: " << word << endl;
    } else {
        cout << "Przegrałeś! Prawidłowe słowo to: " << word << endl;
    }

    string playerName;
    cout << "Jak masz na imię? ";
    cin >> playerName;
    int score = (guessedWord == word) ? remainingChances : 0;
    saveScore(playerName, score);
}

int chooseDifficulty() {
    int choice;
    cout << "Wybierz poziom trudności:" << endl;
    cout << "1. Łatwy (10 szans)" << endl;
    cout << "2. Trudny (5 szans)" << endl;
    cout << "Wybierz: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return 10;
        case 2:
            return 5;
        default:
            cout << "Niepoprawna opcja, wybieram poziom łatwy." << endl;
            return 10;
    }
}

void showRanking() {
    ifstream file("scores.txt");
    if (!file) {
        cout << "Ranking jest pusty." << endl;
        return;
    }

    vector<pair<string, int> > scores;
    string name;
    int score;

    while (file >> name >> score) {
        scores.push_back(make_pair(name, score));
    }

    sort(scores.begin(), scores.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });

    cout << "Top 3 Gracze:" << endl;
    for (size_t i = 0; i < 3 && i < scores.size(); ++i) {
        cout << i + 1 << ". " << scores[i].first << ": " << scores[i].second << " punktów" << endl;
    }
}
