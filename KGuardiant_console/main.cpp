#include <iostream>

using namespace std;

#define MAX_INPUT_SIZE 256

bool exit = false;

void showOptions()
{
    cout << "   Benvido a KGuardiant \n"
            "\n"
            " 1 (1).- Test Kinnect.\n"
            " 2 (q).- Sair.\n"
    << endl;

}

void parseInput(char strInput)
{
    switch (strInput)
    {
    case '1' :
        break;
    case 'q' :
        exit = true;
        break;
    default  :
        break;
    }
}



int main()
{
    char strInput;

    while (!exit)
    {
        showOptions();
        cin.get(strInput);
        parseInput(strInput);
    }

    return 0;
}

