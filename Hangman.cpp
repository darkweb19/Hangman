#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
void printMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

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
void DrawHangman(int GuessCount = 0)
{
    if (GuessCount >= 1)
        printMessage("|", false, false);
    else
        printMessage("", false, false);

    if (GuessCount >= 2)
        printMessage("|", false, false);
    else
        printMessage("", false, false);

    if (GuessCount >= 3)
        printMessage("O", false, false);
    else
        printMessage("", false, false);

    if (GuessCount == 4)
        printMessage("/ ", false, false);

    if (GuessCount == 5)
        printMessage("/| ", false, false);

    if (GuessCount >= 6)
        printMessage("/|\\", false, false);
    else
        printMessage("", false, false);

    if (GuessCount >= 7)
        printMessage("|", false, false);
    else
        printMessage("", false, false);

    if (GuessCount == 8)
        printMessage("/ ", false, false);

    if (GuessCount >= 9)
        printMessage("/ \\", false, false);
    else
        printMessage("", false, false);
}
void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    printMessage(s, false, false);
}
void printAvailableLetters(string taken)
{
    printMessage("AVAILABLE LETTERS");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}

bool printWordAndCHeckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string ::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    printMessage(s, false);
    return won;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int triesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string ::npos)
        {
            error++;
        }
    }
    return error;
}
int main()
{
    srand(time(0));
    cout <<S "You have only 10 tries." << endl << endl;
    string guesses;
    string wordToGuess;
    wordToGuess = LoadRandomWord("WORDS.txt");
    int tries = 0;
    bool win = false;
    do
    {
        system("cls");
        printMessage(" HANGMAN ");
        DrawHangman(tries);
        printAvailableLetters(guesses);
        printMessage("Guess The Word");
        win = printWordAndCHeckWin(wordToGuess, guesses);

        if (win)
            break;
        char x;
        cout << ">";
        cin >> x;
        if (guesses.find(x) == string ::npos)
            guesses += x;

        tries = triesLeft(wordToGuess, guesses);

    } while (tries < 10);
    if (win){
        printMessage("YOU WON");}
    else{
        printMessage("GAME OVER");
        printMessage(wordToGuess);
    }
    
    system("pause");

    getchar();
    return 0;
}
