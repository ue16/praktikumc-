/***********************************************************************
Matr.-Nr:                     3130322
Nachname/Surname:             Wu
Vorname/Given name:           LiRong
Uni-Email:                    li-rong.wu@stud.uni-due.de
Studiengang/Course of studis: Software Engineering, ISE
***********************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <math.h>
#include <fstream>

using namespace std;

string fileName;

void menuitems()
{
    cout << "q quit " << endl
         << "c city " << endl
         << "f from to " << endl
         << "w write HTML file" << endl;
}

struct City
{
    string cityName;
    string cityAddition;
    City *next;
};
ostream &operator<<(ostream &out, const City *city)
{

    string cityName;
    string addtion;
    string cityFullName;
    string cityStr;

    while (city != nullptr)
    {

        cityName = city->cityName;
        addtion = city->cityAddition;

        if (addtion[0] != ',')
        {
            cityFullName = cityName + " " + addtion;
        }
        else
        {
            cityFullName = cityName + addtion;
        }

        if (cityStr == "")
        {
            cityStr = cityFullName;
        }
        else
        {
            cityStr = cityStr + "| " + cityFullName;
        }

        city = city->next;
    }

    return out << cityStr;
}

void print(City *cityArr[], int arrLength, int PLZFrom, int PLZTo)
{

    for (int i = PLZFrom; i <= PLZTo; i++)
    {

        string cityName;
        string cityAddtion;
        string cityFullName;
        City *head = cityArr[i];

        string citys = "";

        if (head != NULL)
        {
            cout << i << " " << head << endl;
        }
    }
}

City *readFile(string fileName, City *cityArr[], int arrLength)
{
    ifstream file(fileName);
    string line = "\n";
    string delimiter = ";";
    string cityName;
    string cityAddition;
    int cityPlz;
    int beginPosition;
    int endPosition;
    City *head;

    for (size_t i = 0; i < arrLength; i++)
    {
        cityArr[i] = NULL;
    }

    // skip first line
    getline(file, line);

    while (getline(file, line))
    {

        // skip the empty line
        if (line.length() > 1)
        {

            endPosition = line.find(delimiter);
            cityName = line.substr(0, endPosition);

            beginPosition = endPosition + 1;
            endPosition = line.find(delimiter, beginPosition);
            cityAddition = line.substr(beginPosition, endPosition - beginPosition);

            beginPosition = endPosition + 1;
            endPosition = line.find(delimiter, beginPosition);
            cityPlz = stoi(line.substr(beginPosition, endPosition - beginPosition));

            if (cityArr[cityPlz] == nullptr)
            {

                City *c = new City();

                c->cityName = cityName;
                c->cityAddition = cityAddition;
                c->next = nullptr;

                cityArr[cityPlz] = c;
            }
            else
            {

                head = cityArr[cityPlz];

                City *c = new City();
                c->cityName = cityName;
                c->cityAddition = cityAddition;
                c->next = head;
                cityArr[cityPlz] = c;
            }
        }
    }

    return *cityArr;
}

void writeFile(string fileName, City *cityArr[], int arrLength, int PLZFrom, int PLZTo)
{
    ofstream file(fileName);
    file << "<!DOCTYPE html>" << endl;
    file << "<html>" << endl;
    file << "<head>" << endl;
    file << "<title>PLZ in Germany from " + to_string(PLZFrom) + " to " + to_string(PLZTo) + "</title>" << endl;
    file << "</head>" << endl;
    file << "<h1>PLZ in Germany from " + to_string(PLZFrom) + " to " + to_string(PLZTo) + "</h1>" << endl;
    file << "<table border=\"1\">" << endl;
    file << "<tr><th>PLZ</th><th>Area</th></tr>" << endl;

    for (int i = PLZFrom; i <= PLZTo; i++)
    {

        string cityName;
        string cityAddtion;
        string cityFullName;

        City *head = cityArr[i];

        while (cityArr[i] != NULL)
        {
            cityName = cityArr[i]->cityName;
            cityAddtion = cityArr[i]->cityAddition;

            if (cityAddtion[0] != ',')
            {
                cityFullName = cityName + " " + cityAddtion;
            }
            else
            {
                cityFullName = cityName + cityAddtion;
            }

            file << "<tr><td>" + to_string(i) + "</td><td>" + cityFullName + "</td></tr>" << endl;

            cityArr[i] = cityArr[i]->next;
        }
        cityArr[i] = head;
    }
    file << "</table>" << endl;
    file << "</body>" << endl;
    file << "</html>" << endl;

    file.close();
}

int main(void)
{
    string fileName;
    City *cityArr[100000];
    char input;
    int from;
    int to;
    int zipCode;

    cout << "please input file name:" << endl;
    cin >> fileName;
    *cityArr = readFile(fileName, cityArr, 100000);

    while (input != 'q')
    {
        menuitems();
        cin >> input;

        switch (input)
        {
        case 'c':
            cout << "please input zip code:" << endl;
            cin >> zipCode;
            if (zipCode < 10)
            {

                from = zipCode * 10000;
                to = (zipCode + 1) * 10000 - 1;
            }
            else if (zipCode >= 10 && zipCode < 100)
            {

                from = zipCode * 1000;
                to = (zipCode + 1) * 1000 - 1;
            }
            else if (zipCode >= 100 && zipCode < 1000)
            {

                from = zipCode * 100;
                to = (zipCode + 1) * 100 - 1;
            }
            else if (zipCode >= 1000 && zipCode < 10000)
            {

                from = zipCode * 10;
                to = (zipCode + 1) * 10 - 1;
            }
            else if (zipCode >= 10000)
            {
                from = zipCode;
                to = zipCode;
            }

            print(cityArr, 100000, from, to);

            break;

        case 'f':
            cout << "from which zip code:" << endl;
            cin >> from;
            cout << "up to which zip code:" << endl;
            cin >> to;
            print(cityArr, 100000, from, to);
            break;

        case 'w':
            cout << "please input file name:" << endl;
            cin >> fileName;
            cout << "from which zip code:" << endl;
            cin >> from;
            cout << "up to which zip code:" << endl;
            cin >> to;
            writeFile(fileName, cityArr, 100000, from, to);

        case 'q':
            break;
        }
    }
}