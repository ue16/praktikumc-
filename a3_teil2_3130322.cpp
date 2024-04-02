/***********************************************************************
Matr.-Nr:                     3130322
Nachname/Surname:             Wu
Vorname/Given name:           LiRong
Uni-Email:                    li-rong.wu@stud.uni-due.de
Studiengang/Course of studis: Software Engineering, ISE
***********************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <list>
#include <math.h>
using namespace std;

const int n = 4;

struct binary_number
{
    bool arr_binary_number[n];
};
enum InputOptions
{
    quit,
    inputa,
    inputb,
    copiedResulta,
    copiedResultb,
    bitwiseNegationa,
    bitwiseNegationb,
    unaryMinusa,
    unaryMinusb,
    add,
    sub,
    isEqual,
    isUnequal,
    isNega,
    isNegb,
    isZeroa,
    isZerob,
    preIncrea,
    preIncreb,
    leftShifta,
    leftShiftb

};

InputOptions resolveOption(string inputChoice);
void menuitems(binary_number *a, binary_number *b, binary_number *result);
void menuitems(binary_number *a, binary_number *b, binary_number *result);

istream &operator>>(istream &in, binary_number &num);
ostream &operator<<(ostream &out, const binary_number &num);
void copyResult(binary_number &result, const binary_number num);
binary_number operator!(const binary_number num);
binary_number operator-(const binary_number num);
binary_number operator+(const binary_number a, const binary_number b);
binary_number operator-(const binary_number a, const binary_number b);
binary_number operator++(binary_number num);
bool operator==(const binary_number a, const binary_number b);
bool operator!=(const binary_number a, const binary_number b);
binary_number operator<<(binary_number num, int shiftDigit);

bool isNegative(const binary_number num);
void copyResult(binary_number &result, const binary_number num);
bool isZero(const binary_number num);
int toDecimal(binary_number &num);

int main(void)
{

    binary_number a;
    binary_number b;
    binary_number result;

    string inputChoice;
    string inputContent;
    char shiftDigit;
    int shiftDigitInt;

    fill(begin(a.arr_binary_number), end(a.arr_binary_number), 0);
    fill(begin(b.arr_binary_number), end(b.arr_binary_number), 0);
    fill(begin(result.arr_binary_number), end(result.arr_binary_number), 0);

    do
    {
        menuitems(&a, &b, &result);

        cin >> inputChoice;

        switch (resolveOption(inputChoice))
        {
        case quit:
            break;

        case inputa:
            cin >> a;
            break;

        case inputb:
            cin >> b;
            break;

        case copiedResulta:
            copyResult(result, a);
            break;

        case copiedResultb:
            copyResult(result, b);
            break;

        case bitwiseNegationa:
            result = !a;
            break;

        case bitwiseNegationb:
            result = !b;

            break;

        case unaryMinusa:
            result = -a;
            break;

        case unaryMinusb:
            result = -b;
            break;

        case add:
            result = a + b;
            break;

        case sub:
            result = a - b;
            break;

        case isEqual:
            cout << "a == b returns " << (a == b) << endl;
            break;

        case isUnequal:
            cout << "a != b returns " << (a != b) << endl;
            break;

        case isNega:
            cout << "is Negative? " << isNegative(a)
                 << endl;
            break;

        case isNegb:
            cout << "is Negative? " << isNegative(b)
                 << endl;
            break;

        case isZeroa:

            cout << "is Zero? " << isZero(a)
                 << endl;
            break;

        case isZerob:
            cout << "is Zero? " << isZero(b)
                 << endl;
            break;
        case preIncrea:
            result = ++a;
            a = result;
            break;
        case preIncreb:
            result = ++b;
            b = result;
            break;
        case leftShifta:
            shiftDigit = inputChoice[2];
            shiftDigitInt = int(shiftDigit) - 48;
            result = a << shiftDigitInt;
            a = result;
            break;
        case leftShiftb:
            shiftDigit = inputChoice[2];
            shiftDigitInt = int(shiftDigit) - 48;
            result = b << shiftDigitInt;
            b = result;

            break;

        default:
            cout << "Please enter a valid option." << endl;
            break;
        }

    } while (
        inputChoice != "q");

    return 0;
};

int toDecimal(binary_number &num)
{
    binary_number temp;
    temp = num;
    int d = n - 2;
    int decimalResult = 0;

    if (temp.arr_binary_number[0])
    {
        for (int i = 1; i < n; i++)
        {
            if (temp.arr_binary_number[i] == false)
            {
                decimalResult -= pow(2, d);
            }
            d -= 1;
        }
        decimalResult -= 1;
    }
    else
    {
        for (int i = 1; i < n; i++)
        {
            if (temp.arr_binary_number[i])
            {
                decimalResult += pow(2, d);
            }
            d -= 1;
        }
    }

    return decimalResult;
}

binary_number operator++(binary_number num)
{

    binary_number temp;
    fill(begin(temp.arr_binary_number), end(temp.arr_binary_number), 0);
    temp.arr_binary_number[n - 1] = true;
    temp = num + temp;

    return temp;
}

binary_number operator<<(binary_number num, int shiftDigit)
{
    binary_number temp;
    int tempDigit = 0;
    fill(begin(temp.arr_binary_number), end(temp.arr_binary_number), 0);
    cout << shiftDigit << endl;

    for (int i = shiftDigit; i < n; i++)
    {
        temp.arr_binary_number[tempDigit] = num.arr_binary_number[i];
        tempDigit = tempDigit + 1;
        cout << tempDigit << endl;
    }
    cout << num.arr_binary_number[0] << endl;
    cout << num.arr_binary_number[1] << endl;
    cout << tempDigit << endl;

    for (int i = tempDigit; i < n; i++)
    {
        temp.arr_binary_number[tempDigit] = false;
        tempDigit += 1;
    }
    return temp;
}

InputOptions resolveOption(string inputChoice)

{

    if (inputChoice == "q")
        return quit;
    if (inputChoice == "a")
        return inputa;
    if (inputChoice == "b")
        return inputb;
    if (inputChoice == "va")
        return copiedResulta;
    if (inputChoice == "vb")
        return copiedResultb;
    if (inputChoice == "!a")
        return bitwiseNegationa;
    if (inputChoice == "!b")
        return bitwiseNegationb;
    if (inputChoice == "ma")
        return unaryMinusa;
    if (inputChoice == "mb")
        return unaryMinusb;
    if (inputChoice == "+")
        return add;
    if (inputChoice == "-")
        return sub;
    if (inputChoice == "e")
        return isEqual;
    if (inputChoice == "u")
        return isUnequal;
    if (inputChoice == "na")
        return isNega;
    if (inputChoice == "nb")
        return isNegb;
    if (inputChoice == "za")
        return isZeroa;
    if (inputChoice == "zb")
        return isZerob;
    if (inputChoice == "ia")
        return preIncrea;
    if (inputChoice == "ib")
        return preIncreb;
    if (inputChoice[0] == 'l' && inputChoice[1] == 'a')
        return leftShifta;
    if (inputChoice[0] == 'l' && inputChoice[1] == 'b')
        return leftShiftb;

    return quit;
};

istream &operator>>(istream &in, binary_number &num)
{
    string input;
    in >> input;

    for (int i = 0; i < n; i++)
    {
        char inputChar = input[i];

        switch (inputChar)
        {
        case '0':
            num.arr_binary_number[i] = 0;
            break;

        case '1':
            num.arr_binary_number[i] = 1;
            break;

        default:
            num.arr_binary_number[i] = 0;
            break;
        }
    }
    return in;
}
ostream &operator<<(ostream &out, const binary_number &num)
{
    string output;

    for (int i = 0; i < n; i++)
    {
        char outputChar;
        bool outputCharBool = num.arr_binary_number[i];

        if (outputCharBool == true)
        {
            outputChar = '1';
        }
        else
        {
            outputChar = '0';
        }

        output += outputChar;
    }

    return out << output;
}

binary_number operator!(const binary_number num)
{
    binary_number temp;
    for (int i = 0; i < n; i++)
    {
        temp.arr_binary_number[i] = !num.arr_binary_number[i];
    }

    return temp;
}

binary_number operator-(const binary_number num)
{
    binary_number temp;
    binary_number temp1;

    // create 1
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            temp1.arr_binary_number[i] = true;
        }
        else
        {
            temp1.arr_binary_number[i] = false;
        }
    }

    temp = !num; // invert all bits of b
    temp = temp + temp1;

    return temp;
}

binary_number operator+(const binary_number a, const binary_number b)
{
    binary_number temp;
    bool carryIn = false;

    for (int i = n - 1; i >= 0; i--)
    {

        temp.arr_binary_number[i] = carryIn ^ (a.arr_binary_number[i] ^ b.arr_binary_number[i]);

        if (a.arr_binary_number[i] & b.arr_binary_number[i])
        {
            carryIn = true;
        }
        else if (carryIn & (a.arr_binary_number[i] | b.arr_binary_number[i]))
        {
            carryIn = true;
        }
        else
        {
            carryIn = false;
        }
    }

    return temp;
}

binary_number operator-(const binary_number a, const binary_number b)
{
    binary_number temp;
    binary_number tempb;

    tempb = -b;
    temp = a + tempb; // 2 complement's

    return temp;
}

bool operator==(const binary_number a, const binary_number b)
{
    bool isEqual = true;
    for (int i = 0; i < n; i++)
    {
        if (a.arr_binary_number[i] != b.arr_binary_number[i])
        {
            return !isEqual;
        }
    }

    return isEqual;
}
bool operator!=(const binary_number a, const binary_number b)
{
    bool isNotEqual = true;

    if (a == b)
    {
        return !isNotEqual;
    }
    return isNotEqual;
}
void menuitems(binary_number *a, binary_number *b, binary_number *result)
{

    cout << "     a = " << *a << "(" << toDecimal(*a) << ")" << endl
         << "     b = " << *b << "(" << toDecimal(*b) << ")" << endl
         << "result = " << *result << "(" << toDecimal(*result) << ")" << endl
         << "a\tinput a" << endl
         << "b\tinput b" << endl
         << "va, vb  value of result copied to a, b" << endl
         << "!a, !b  bitwise negation" << endl
         << "ma, mb  unary minus -a, -b" << endl
         << "+\tbinary addition a+b" << endl
         << "-\tbinary subtraction a-b" << endl
         << "e\tequality check a == b" << endl
         << "u\tunequality check a != b" << endl
         << "na, nb  is_negative(a), is_negative(b)?" << endl
         << "ia, ib   pre-increment operator ++a, ++b" << endl
         << "lak, lbk left shift operator a << k, b << k" << endl;
}
bool isNegative(const binary_number num)
{
    bool isNeg = true;
    if (num.arr_binary_number[0] != false)
    {
        return isNeg;
    }
    else
    {
        return !isNeg;
    }
}
bool isZero(const binary_number num)
{
    bool isZero = true;
    for (int i = 0; i < n; i++)
    {
        if (num.arr_binary_number[i] != false)
        {
            return !isZero;
        }
    };

    return isZero;
}
void copyResult(binary_number &result, const binary_number num)
{
    for (int i = 0; i < n; i++)
    {
        result.arr_binary_number[i] = num.arr_binary_number[i];
    }
}
