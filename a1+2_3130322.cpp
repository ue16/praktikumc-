/***********************************************************************
Matr.-Nr:                     3130322
Nachname/Surname:             Wu
Vorname/Given name:           LiRong
Uni-Email:                    li-rong.wu@stud.uni-due.de
Studiengang/Course of studis: Software Engineering, ISE
***********************************************************************/

#include <iostream>
using namespace std;

const unsigned int numOfRows = 13;
const unsigned int numOfColumns = 26;
char maze[numOfRows][numOfColumns];

string myName = "LiRong Wu";
string myMatriculationNum;
string input;

int row_position;
int column_position;
char symbol;

void menuitems()
{
    cout << endl;
    cout << endl;
    cout << "row and column:\n";
    cout << "e end\n";
    cout << "f fill with blank\n";
    cout << "s show\n";
    cout << "- minus sign\n";
    cout << "| vertical line\n";
    cout << "+ plus sign\n";
    cout << ". blank\n";
    cout << endl;
};

void fill_with_empty()
{

    for (int i = 0; i < numOfRows; ++i)
    {
        for (int j = 0; j < numOfColumns; ++j)
        {
            maze[i][j] = ' ';
        }
    };
}

void show()
{
    string MazeOf = "MAZE OF \"" + myName + "\" (" + myMatriculationNum + ")\n";
    cout << MazeOf;

    cout << "\tabcdefghijklmnopqrstuvwxyz" << endl;


    for (int i = 0; i < numOfRows; ++i)
    {
        cout << i+1 << "\t";
        for (int j = 0; j < numOfColumns; ++j)
        {
            cout << maze[i][j];
        }
        cout << endl;
    };
};



void pupolated_by_sign(string input)
{
   if (input == "e")
    {
        return;
    }
    else if (input == "f")
    {
        fill_with_empty();

        show();

        menuitems();

        cin >> input;

        return pupolated_by_sign(input);
    }
    else if (input == "s")
    {
        show();

        menuitems();

        cin >> input;

        return pupolated_by_sign(input);
    }

    else
    {
        symbol = input[0];
        column_position = int(input.back()) - 97;
        input = input.substr(1, input.size());
        row_position = stoi(input)-1;


        if ((column_position >= 0) && (column_position < 26) && (row_position >= 0) && (row_position < 13))
        {
            switch (symbol)
            {
            case ('+'):
                maze[row_position][column_position] = symbol;
                break;
            case ('-'):
                maze[row_position][column_position] = symbol;
                break;
            case ('|'):
                maze[row_position][column_position] = symbol;
                break;
            case ('.'):
                symbol = ' ';
                maze[row_position][column_position] = symbol;
                break;

            default:
                break;
            }
        }

        menuitems();
        
        cin >> input;

        return pupolated_by_sign(input);
    }
};

int main(void)
{
    cout << "Please enter your matriculation number:";
    cin >> myMatriculationNum;
    fill_with_empty();

    show();

    menuitems();

    cin >> input;
    pupolated_by_sign(input);

    return 0;
};