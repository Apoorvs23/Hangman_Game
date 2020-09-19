#include <iostream>
#include <vector>
#include <fstream>  //filestream
#include <string>
#include <time.h>
#include<cstdlib>
using namespace std;
void PrintMessage(string message, bool printTop = true, bool printBottom = true) // print top is to print top border
{
	if (printTop) // print upper top border
	{
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";  // if we dont print top and bottom - print |        |
	}
	bool front = true; // in front of message - hangman ke aage space or piche space to make it centered
	for (int i = message.length(); i < 33; i++) //33 is no. of characters we can add as message
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front; // ek baar chala toh aage space and 2nd time chala toh piche space - balance rkhne ke liye
	}
	cout << message.c_str();   //returns a pointer to an array that contains a null-terminated sequence of characters representing the current value of the basic_string object. This array includes the same sequence of characters that make up the value of the basic_string object plus an additional terminating null-character at the end.

	if (printBottom)
	{
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}
void DrawHangman(int guessCount = 0)
{
	if (guessCount >= 1)
		PrintMessage("|", false, false); // false,false will stop the printing of top border and bottom border
	else
		PrintMessage("", false, false); // we dont print anything if no guesses are made - we need to have blank line here

	if (guessCount >= 2)
		PrintMessage("|", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount >= 3)
		PrintMessage("O", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount == 4)
		PrintMessage("/  ", false, false);

	if (guessCount == 5)
		PrintMessage("/| ", false, false);

	if (guessCount >= 6)
		PrintMessage("/|\\", false, false); // we use two esacape character to show we want '\'
	else
		PrintMessage("", false, false);

	if (guessCount >= 7)
		PrintMessage("|", false, false);
	else
		PrintMessage("", false, false);

	if (guessCount == 8)  //left leg
		PrintMessage("/", false, false);

	if (guessCount >= 9)
		PrintMessage("/ \\", false, false);
	else
		PrintMessage("", false, false);
}
void PrintLetters(string input, char from, char to) // all the characters already typed by the user will not be displayed.
{
	string s;
	for (char i = from; i <= to; i++) //traverse by ascii values from='a' to='z'
	{
		if (input.find(i) == string::npos)  //npos is returned when character 'i' is not found
		{
		    //jo jo character already guessed word mein nhi hai unko type krte jao
			s += i;
			s += " ";
		}
		else
			s += "  "; // agar already user type kar chuka hai toh space daldo, uski jagah khali chordo
	}
	PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
	PrintMessage("Available letters");
	PrintLetters(taken, 'a', 'm');
	PrintLetters(taken, 'n', 'z');
}
bool PrintWordAndCheckWin(string word, string guessed) //whether user guessed and won - bool
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ "; // agar guessed character string mein nahi hai toh placerholder daldo uski jagah
		}
		else
		{
			s += word[i];
			s += " "; //agar hai toh show krdo user ko
		}
	}
	PrintMessage(s, false); // top border nahi chaiye bottom chaiye
	return won;
}
string LoadRandomWord(string path)  // random word from .txt file will be loaded as string
{
	//int lineCount = 0;
	string word; // the word to be loaded
	vector<string> v;
	ifstream reader(path.c_str()); //iftream is input stream
	if (reader.is_open()) //file is open
	{
		while (std::getline(reader, word))  // from which file it will get the line and store the line
			v.push_back(word); // read line  by line

		int randomLine = rand() % v.size(); // random line generated range from 0 to no. of lines

		word = v.at(randomLine); // at will return element at index=randomLine - index starting from 0
		reader.close();
	}
	return word;
}
int TriesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos) // if actual word doesnot contain in guessed charatacter
			error++;
	}
	return error;
}
int main()
{
	srand(time(0)); // will return current time - if we dont use srand then same word will be picked by reader again again
    //The "seed" is a starting point for the sequence and the guarantee is that if you start from the same seed you will get the same sequence of numbers.It sets seeds for random functions
	string guesses="";
	string wordToGuess;
	wordToGuess = LoadRandomWord("words.txt");
	int tries = 0;
	bool win = false;
	do
	{
		system("cls"); // it just clears the screen - also can used system("cls")
		PrintMessage("HANGMAN BY APOORV");
		DrawHangman(tries);
		PrintAvailableLetters(guesses);
		PrintMessage("Guess the word");
		win = PrintWordAndCheckWin(wordToGuess, guesses);

		if (win)
			break;

		char x;
		cout << ">"; cin >> x;

		if (guesses.find(x) == string::npos) // if the user typed character is not present in guesses-we will add it
			guesses += x;

		tries = TriesLeft(wordToGuess, guesses); //kitni baar try kr chuke hai

	} while (tries < 10);

	if (win)
		PrintMessage("YOU WON!");
	else
		PrintMessage("GAME OVER");

	system("pause"); // will hold the output screen
	getchar();
	return 0;
}
/*
+---------------------------------+
|             HANG MAN            |
+---------------------------------+
|               |                 |
|               |                 |
|               O                 |
|              /|\                |
|               |                 |
|              / \                |
|         +----------+            |
|         |          |            |
+---------------------------------+
|        Available letters        |
+---------------------------------+
|     A B C D E F G H I J K L M   |
|     N O P Q R S T U V W X Y Z   |
+---------------------------------+
|         Guess the word          |
+---------------------------------+
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |
+---------------------------------+
>
*/
