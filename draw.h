#ifndef __DRAW_H__
#define __DRAW_H__

#include <string>

std::string getHangPicture(int badGuessCount);
void clearScreen();
void renderGame(int score, std::string guessedWord, int badGuessCount, std::string badGuess = "");
void printGameOverInfo(std::string guessedWord, std::string word, int badGuessCoun, int score);


#endif // __DRAW_H__

