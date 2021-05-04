#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

#include "draw.h"
#include "utility.h"

using namespace std;

char readAGuess()
{
    char guess;
    cout << "Please enter your next guess: ";
    cin >> guess;
    return guess;
}

void update(string& guessedWord, const string& word, char guess)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}

int numupdate(string& guessedWord, const string& word, char guess)
{
    int countt=0;
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
        {
            countt++;
        }
    }
    return countt;
}

void chooseTopic(char& topic, char& level)
{

    cout << "Choose one topic! (type a number)" << endl;
    cout << "1. Animal       2. Environment      3. Fruits" << endl
         << "4. Landscape    5. Vegetales        6. Weather" << endl;
    cin >> topic;
    cout << "Choose level! (type a number)" << endl
         << "1. Easy \t 2. Hard" << endl;
    cin >> level;
}


int main()
{
    int score = 0;
    int highScore;
    srand(time(0));
    char topic, level;
    string fileName;
    chooseTopic(topic, level);
        switch(topic)
        {
            case '1':
            {
                if (level=='1') fileName="animal1.txt";
                else fileName="animal2.txt";
                break;
            }
            case '2':
            {
                if (level=='1') fileName="environment1.txt";
                else fileName="environment2.txt";
                break;
            }

            case '3':
            {
                if (level=='1') fileName="fruits1.txt";
                else fileName="fruits2.txt";
                break;
            }
            case '4':
            {
                if (level=='1') fileName="landscape1.txt";
                else fileName="landscape2.txt";
                break;
            }
            case '5':
            {
                if (level=='1') fileName="vegetables1.txt";
                else fileName="vegetables2.txt";
                break;
            }
            case '6':
            {
                if (level=='1') fileName="weather1.txt";
                else fileName="weather2.txt";
                break;
            }
        }

    while (true) {
        string word = chooseWord(fileName);
        if (word.empty()) {
            cout << "No word available in " << fileName << endl;
            return 0;
        }
        string guessedWord = string(word.length(), '-');
        int badGuessCount = 0;
        const int MAX_BAD_GUESS = 7;
        string badGuess;
        do {
            renderGame(score,guessedWord, badGuessCount, badGuess);
            char guess = readAGuess();

            if (contains(word, guess)) {
                update(guessedWord, word, guess);
                score += 10*numupdate(guessedWord, word, guess);
            } else {
                badGuessCount++;
                badGuess += guess;
            }
        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

        printGameOverInfo(guessedWord, word, badGuessCount,score);

        ifstream readfile("highscore.txt");
        while (!readfile.eof())
        {
            readfile >> highScore;
        }
        readfile.close();

        ofstream writefile("highscore.txt");
        if (writefile.is_open())
        {
            if (score > highScore)
                highScore = score;
            writefile << highScore;
        }
        writefile.close();

        cout << "High Score: " << highScore << endl;

        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
    }

    return 0;
}

