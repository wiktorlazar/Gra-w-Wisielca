#include <iostream>
#include "game.h"
#include "utils.h"

using namespace std;

int main() {
    clearScreen();
    int choice;
    cout << "Witaj w grze w wisielca!" << endl;
    cout << "1. Rozpocznij grę" << endl;
    cout << "2. Zobacz ranking" << endl;
    cout << "3. Wyjście" << endl;
    cout << "Wybierz opcję: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            clearScreen();
            int difficulty = chooseDifficulty();
            playGame(difficulty);
            break;
        }
        case 2:
            clearScreen();
        showRanking();
        break;
        case 3:
            cout << "Do widzenia!" << endl;
        return 0;
        default:
            cout << "Niepoprawna opcja, spróbuj ponownie." << endl;
        break;
    }
    return 0;
}
