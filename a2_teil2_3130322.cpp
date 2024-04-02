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
using namespace std;

struct Station
{
    string nameStation;
    int minToNextStation;
    Station *prev;
    Station *next;
    Station *connection;
};

struct Train
{
    string nameTrain;
    int minLeftToNextStation;
    bool isOnWayBack;
    Station *nextStation;
};

void menuitems();
void output(Station *station);
int travelTime();
void output_line(Station *head);
void output(Station *station);
void init(Train &metro, string name, Station *station);
Station generate_metro_line(int numOfLine, int amountOfStation);
void simulation(Station *metroLines, Train *metroTrains);

void menuitems()
{
    cout << endl
         << "c connection option of line" << endl
         << "d duration complete outward andreturn ride of line" << endl
         << "e end" << endl
         << "l line output" << endl
         << "t train output" << endl
         << "1 simulate 1 minute" << endl;
}

int travelTime()
{

    int travelTime = (1 + rand() % 5);

    return travelTime;
};

Station generate_metro_line(int numOfLine, int amountOfStation)
{
    Station *head;
    Station *tail;

    Station *newStation = new Station;
    newStation->nameStation = "line " + to_string(numOfLine) + " station 1";
    newStation->minToNextStation = travelTime();
    newStation->next = nullptr;
    newStation->prev = nullptr;
    newStation->connection = nullptr;
    head = newStation;
    tail = newStation;

    // // for generated random travel time
    // int seed;
    // // srand((unsigned)time(0));
    // srand(seed);

    for (int i = 2; i <= amountOfStation; ++i)
    {
        Station *newStation = new Station;
        newStation->nameStation = "line " + to_string(numOfLine) + " station " + to_string(i);

        if (amountOfStation == 2 || i == amountOfStation)
        {
            newStation->minToNextStation = 0;
        }
        else
        {
            newStation->minToNextStation = travelTime();
        }
        newStation->next = nullptr;
        newStation->prev = tail;
        tail->next = newStation;
        tail = newStation;
    }

    return *newStation;
};

void output_line(Station *head)
{
    Station *iterator = head;
    while (iterator != nullptr)
    {
        output(iterator);
        iterator = iterator->next;
    }
};

void output(Station *station)
{
    if (station->next != nullptr)
    {
        if (station->connection == nullptr)
        {
            cout << station->nameStation + ": " + "time to next: " + to_string(station->minToNextStation) + " min(s)" << endl;
        }
        else
        {
            cout << station->nameStation + ": " + "time to next: " + to_string(station->minToNextStation) + " min(s) (here connection to " + station->connection->nameStation + ") " << endl;
        }
    }
    else
    {
        if (station->connection == nullptr)
        {
            cout << station->nameStation + ": end station" << endl;
        }
        else
        {
            cout << station->nameStation + ": end station (here connection to " + station->connection->nameStation + ") " << endl;
        }
    }
};

void output(Train *metro)
{

    if (metro->minLeftToNextStation == 0)
    {
        cout << "train " + metro->nameTrain + ": " + "stop at " + metro->nextStation->nameStation << endl;
    }
    else
    {
        if (metro->isOnWayBack == true)
        {
            cout << "train " + metro->nameTrain + ": " + to_string(metro->minLeftToNextStation) + " minute(s) to " + metro->nextStation->nameStation + "(On way back)" << endl;
        }
        else
        {
            cout << "train " + metro->nameTrain + ": " + to_string(metro->minLeftToNextStation) + " minute(s) to " + metro->nextStation->nameStation << endl;
        };
    };
}

void init(Train &metro, string name, Station *station)
{
    Train *train = new Train;

    train->nameTrain = name;
    train->minLeftToNextStation = 0;
    train->isOnWayBack = false;
    train->nextStation = station;
    metro = *train;
}

void output_all_trains(int minSimulation, Train metroTrains[], int lenMetro)
{
    cout << "time simulation: " + to_string(minSimulation) + " min" << endl;

    for (int i = 0; i < lenMetro; i++)
    {
        output(&metroTrains[i]);
    }
};

int get_duration_of_line(Station *iteratorStation)
{
    // Station *head = iteratorStation;

    int minDuration = 0;
    minDuration += iteratorStation->minToNextStation;

    do
    {
        iteratorStation = iteratorStation->next;
        minDuration += iteratorStation->minToNextStation;
        minDuration += 1; // 1 mins at every stop
    } while (iteratorStation->next != nullptr);

    minDuration = minDuration * 2;

    return minDuration;
}

void simulation(Train *metroTrains)
{

    for (int i = 0; i < 2; i++)
    {

        Train *iteratorTrain = &metroTrains[i];

        if (iteratorTrain->minLeftToNextStation != 0)
        {
            iteratorTrain->minLeftToNextStation -= 1;
        }
        else
        {
            if (iteratorTrain->isOnWayBack == false)
            {
                if (iteratorTrain->nextStation->next != nullptr)
                {

                    iteratorTrain->minLeftToNextStation = iteratorTrain->nextStation->minToNextStation;

                    iteratorTrain->nextStation = iteratorTrain->nextStation->next;
                }
                else
                {

                    iteratorTrain->nextStation = iteratorTrain->nextStation->prev;

                    iteratorTrain->minLeftToNextStation = iteratorTrain->nextStation->minToNextStation;

                    iteratorTrain->isOnWayBack = !iteratorTrain->isOnWayBack;
                }
            }
            else
            {

                if (iteratorTrain->nextStation->prev != nullptr)
                {
                    iteratorTrain->nextStation = iteratorTrain->nextStation->prev;

                    iteratorTrain->minLeftToNextStation = iteratorTrain->nextStation->minToNextStation;
                }
                else
                {

                    iteratorTrain->minLeftToNextStation = iteratorTrain->nextStation->minToNextStation;

                    iteratorTrain->nextStation = iteratorTrain->nextStation->next;

                    iteratorTrain->isOnWayBack = !iteratorTrain->isOnWayBack;
                }
            }
        }
    };
}

int main(void)
{
    Station metroLines[2];
    Train metroTrains[2];
    int minSimulation = 0;

    int lineChoice;
    int inputNumStationsLine1;
    int inputNumStationsLine2;
    string trainName;
    char inputChoice;

    int duration;
    int stationNumberLine1;
    int stationNumberLine2;

    // for generated random travel time
    int seed;
    // srand((unsigned)time(0));
    srand(seed);

    cout << "seed value for initialisation of random number generator (try 3, 5, 7, ...)? ";
    cin >> seed;

    cout << "input number of stations of line 1: ";
    cin >> inputNumStationsLine1;

    metroLines[0] = generate_metro_line(1, inputNumStationsLine1);
    trainName = "1";
    init(metroTrains[0], trainName, &metroLines[0]);

    cout << "input number of stations of line 2: ";
    cin >> inputNumStationsLine2;

    trainName = "2";
    metroLines[1] = generate_metro_line(2, inputNumStationsLine2);
    init(metroTrains[1], trainName, &metroLines[1]);

    do
    {
        menuitems();

        cin >> inputChoice;

        switch (inputChoice)
        {
        case 'e':

            break;

        case 'l':

            cout << "Which line? " << endl;
            cin >> lineChoice;
            output_line(&metroLines[lineChoice - 1]);
            break;

        case 't':

            output_all_trains(minSimulation, metroTrains, 2);
            break;

        case '1':

            minSimulation += 1;
            simulation(metroTrains);
            output_all_trains(minSimulation, metroTrains, 2);
            break;

        case 'd':
            cout << "Which line? " << endl;
            cin >> lineChoice;

            duration = get_duration_of_line(&metroLines[lineChoice - 1]);
            cout << "duration of line: " + to_string(duration) + " min(s)" << endl;
            break;

        case 'c':
            cout << "connection of which two line numbers?" << endl;
            cout << "connection at which station number of line 1?" << endl;
            cin >> stationNumberLine1;
            cout << "connection at which station number of line 2?" << endl;
            cin >> stationNumberLine2;


            Station *stationLine1;
            Station *stationLine2;

            stationLine1=&metroLines[0];
            stationLine2=&metroLines[1];


            for (int i = 1; i < stationNumberLine1; i++)
            {

                stationLine1 = stationLine1->next;
            }
            for (int i = 1; i < stationNumberLine2; i++)
            {

                stationLine2 = stationLine2->next;

            }

            stationLine1->connection = stationLine2;
            stationLine2->connection = stationLine1;


        default:
            break;
        }

    } while (
        inputChoice != 'e');

    return 0;
};
