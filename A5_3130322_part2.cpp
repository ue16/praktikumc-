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
#include <string.h>
#include <iostream>

using namespace std;

void menuitems1()
{
    cout << "" << endl
         << "CALL CENTER BOOKING REQUEST" << endl
         << "0 end" << endl
         << "1 new reservation request standard" << endl
         << "2 new reservation request superior" << endl
         << "3 show reservation request" << endl
         << "4 show all reservation requests" << endl
         << "your choice:" << endl;
}

void menuitems2()
{
    cout << "0 self travel" << endl
         << "1 by flight" << endl
         << "2 by train" << endl
         << "your choice:" << endl;
}

class Date
{
private:
    unsigned short day;
    unsigned short month;
    unsigned short year;

public:
    Date()
    {
        this->day = 1;
        this->month = 1;
        this->year = 2000;
    }
    Date(unsigned short y, unsigned short m, unsigned short d)
    {
        this->day = d;
        this->month = m;
        this->year = y;
    }

    int daysInMonth(int month)
    {
        int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return monthDays[month];
    }

    Date &operator+(unsigned int n)
    {
        int y = this->year;
        int m = this->month;
        int d = this->day;

        if (m != 12)
        {
            if ((d + n) > daysInMonth(this->month))
            {
                m += 1;
                d = d + n - daysInMonth(this->month);
            }
            else
            {
                d = d + n;
            }
        }
        else
        {
            if ((day + n) > daysInMonth(12))
            {
                y += 1;
                m = 1;
                d = day + n - daysInMonth(12);
            }
            else
            {
                d = d + n;
            }
        }

        Date *departDay = new Date(y, m, d);

        return *departDay;
    };

    friend istream &operator>>(istream &in, Date &date);
    friend ostream &operator<<(ostream &out, const Date &);
};

istream &operator>>(istream &in, Date &date)
{
    string input;
    in >> input;

    date = Date(stoi(input.substr(0, 4)), stoi(input.substr(5, 2)), stoi(input.substr(8, 2)));

    return in;
};

ostream &operator<<(ostream &out, const Date &date)
{
    return out << date.year << "-" << date.month << "-" << date.day;
};

enum Board
{
    no_meals,
    breakfast,
    half_board,
    all_inclusive

};

ostream &operator<<(ostream &out, const Board selectedBoard)
{

    switch (selectedBoard)
    {
    case no_meals:
        return out << "no_meals";
    case breakfast:
        return out << "breakfast";
    case half_board:
        return out << "half_board";
    case all_inclusive:
        return out << "all_inclusive";
    }
};

float get_board_price(const Board board)
{
    if (board == breakfast)
    {
        return 10;
    }
    else if (board == half_board)
    {
        return 20;
    }
    else if (board == all_inclusive)
    {
        return 50;
    }
    else
    {
        return 0;
    };
};

class Accomodation
{
private:
    string location;
    Date arrival;
    int nights, singles, doubles;
    double priceNightSingle, priceNightDouble, priceOneDayParking;
    char selectedBoardChar;
    Board selectedBoard;
    char parkingChar;
    bool parking;
    string parkingMsg;

public:
    Accomodation(int pns, int pnd, int pop)
    {
        priceNightSingle = pns;
        priceNightDouble = pnd;
        priceOneDayParking = pop;
        ask_data();
    };
    ~Accomodation()
    {
        cout << "destructor Accomodation " << location << " at " << arrival << " for " << get_guests() << " guest(s) done" << endl;
    }

    string get_location()
    {
        return location;
    }

    Date get_arrival()
    {
        return arrival;
    }
    Date get_departure()
    {
        Date departure;

        departure = arrival + nights;

        return departure;
    }

    int get_guests()
    {

        return singles + (doubles * 2);
    }

    float get_price()
    {
        return ((singles * priceNightSingle) + (doubles * priceNightDouble) + (get_board_price(selectedBoard) * get_guests()) + parking * priceOneDayParking) * nights;
    }

    void ask_data()
    {
        cout << "location of accomodation:" << endl;
        cin >> location;
        cout << "arrival on (yyyy-mm-dd):" << endl;
        cin >> arrival;
        cout << "how many nights (maximum 4 weeks):" << endl;
        cin >> nights;
        cout << "how many single bed rooms (" << priceNightSingle << " EUR/night):" << endl;
        cin >> singles;
        cout << "how many double bed rooms (" << priceNightDouble << "  EUR/night):" << endl;
        cin >> doubles;

        cout << "a all inclusive (50.00 EUR/day)" << endl
             << "b breakfast     (10.00 EUR/day)" << endl
             << "h half board    (20.00 EUR/day)" << endl
             << "n no meals" << endl
             << "Your choice:" << endl;
        cin >> selectedBoardChar;
        switch (selectedBoardChar)
        {
        case 'a':
            selectedBoard = all_inclusive;
            break;
        case 'b':
            selectedBoard = breakfast;
            break;
        case 'h':
            selectedBoard = half_board;
            break;
        case 'n':
            selectedBoard = no_meals;
            break;
        default:
            selectedBoard = no_meals;
            break;
        }

        cout << "with parking place (" << priceOneDayParking << "  EUR/day; y(es) or n(o)):" << endl;
        cin >> parkingChar;
        if (parkingChar == 'y' || parkingChar == 'Y')
        {
            parking = 1;
            parkingMsg = "included";
        }
        else if (parkingChar == 'n' || parkingChar == 'N')
        {
            parking = 0;
            parkingMsg = "no parking place booked";
        }
        cout << "price:" << get_price() << " EUR" << endl;
    }

    void print()
    {
        cout << "accomodation at:    " << location << endl
             << "number of guests:   " << get_guests() << endl
             << "number of nights:   " << nights << endl
             << "check-in date:      " << arrival << endl
             << "check-out date:     " << get_departure() << endl
             << "single bed room(s): " << singles << "(" << priceNightSingle << " EUR/night)" << endl
             << "double bed room(s): " << doubles << "(" << priceNightDouble << " EUR/night)" << endl
             << "board:              " << selectedBoard << "(" << get_board_price(selectedBoard) << " EUR/day and person)" << endl
             << "parking:            " << parkingMsg << "(" << priceOneDayParking << " EUR/day)" << endl
             << "price accomodation: " << get_price() << "EUR" << endl;
    }
};

class Transport
{
public:
    virtual ~Transport()
    {
        cout << "destructor Transport done" << endl;
    };

    virtual bool includedTransfer()
    {
        return false;
    };

    virtual float get_price() = 0;

    virtual void print() = 0;
};

class SelfTravel : public Transport
{
public:
    SelfTravel(){};

    virtual ~SelfTravel()
    {
        cout << "destructor SelfTravel" << endl;
    };

    virtual float get_price()
    {
        return 0.00;
    }
    virtual void print()
    {
        cout << "Self travel no transfer" << endl;
    };
};

class PublicTransport : public Transport
{

protected:
    Date dateFlight;
    string code;
    string from;
    string to;
    float priceOneSeat;
    bool firstClass;

public:
    PublicTransport(){};
    PublicTransport(Date dateFlight, string code, string from, string to, float priceOneSeat, bool firstClass = false)
    {
    }
    virtual ~PublicTransport()
    {
        cout << "destructor PublicTransport " << code << " at " << dateFlight << " from " << from << " to " << to << " done" << endl;
    };

    virtual void print()
    {
        cout << dateFlight << " " << code << " from " << from << " to " << to << "(" << priceOneSeat << " EUR/person) transfer included" << endl;
    }
};

class Flight : public PublicTransport
{
protected:
    bool transfer;

public:
    Flight(){};
    Flight(Date dateFlight, string code, string departurePlace, string arrivalPlace, float priceOneSeat, bool firstClass = false, bool transfer = true)
    {
        PublicTransport::dateFlight = dateFlight;
        PublicTransport::code = code;
        PublicTransport::from = departurePlace;
        PublicTransport::to = arrivalPlace;
        PublicTransport::priceOneSeat = priceOneSeat;
        PublicTransport::firstClass = firstClass;
    };

    ~Flight(){
        cout<<"destructor Flight done"<<endl;
    };

    virtual bool includedTransfer()
    {
        return transfer;
    };

    virtual float get_price()
    {
        if (!firstClass)
        {
            return priceOneSeat;
        }
        else
        {
            return 2 * priceOneSeat;
        } 
    };
    virtual void print()
    {
        cout << "flight ";
        PublicTransport::print();
    }
};

class Train : public PublicTransport
{
protected:
    bool transfer;
public:
    Train(Date dateFlight, string code, string departurePlace, string arrivalPlace, float priceOneSeat, bool firstClass = false, bool transfer = true){

        PublicTransport::dateFlight = dateFlight;
        PublicTransport::code = code;
        PublicTransport::from = departurePlace;
        PublicTransport::to = arrivalPlace;
        PublicTransport::priceOneSeat = priceOneSeat;
        PublicTransport::firstClass = firstClass;
    };

    ~Train(){
        cout<<"destructor Train done"<<endl;

    };

    virtual float get_price()
    {
        if (!firstClass)
        {
            return priceOneSeat;
        }
        else
        {
            return 2 * priceOneSeat;
        }
    };
    virtual void print()
    {
        cout << "train ";
        PublicTransport::print();
    }
};
class Request
{

private:
    unsigned int no;

    static unsigned int lastNo;

    Accomodation *accomodation;

    Transport *transportOutward;
    Transport *transportReturn;

public:
    Request(Accomodation *acc, Transport *transOutward = nullptr, Transport *transReturn = nullptr)
    {
        lastNo++;
        no = lastNo;
        accomodation = acc;
        transportOutward = transOutward;
        transportReturn = transReturn;
    }
    ~Request()
    {
        accomodation->~Accomodation();
        transportOutward->~Transport();
        transportReturn->~Transport();

        cout << "destructor Request " << no << " done" << endl;
    }

    int get_no()
    {
        return no;
    }

    int get_price()
    {

        return accomodation->get_price() + (transportOutward->get_price() + transportReturn->get_price()) * accomodation->get_guests();
    }

    void print()
    {
        float totalPrice;
        cout << "" << endl;
        cout << "********REQUEST NO: " << no << "********" << endl;
        accomodation->print();
        cout << "outward journey: ";
        transportOutward->print();
        cout << "journey back: ";
        transportReturn->print();

        totalPrice = (transportOutward->get_price() + transportReturn->get_price()) * accomodation->get_guests() + accomodation->get_price();
        cout << "price total: " << totalPrice << " EUR"<<endl;
    }
};

class CallCenter
{
private:
    list<Request *> requests;
    int n;

public:
    CallCenter()
    {
        requests.push_back(nullptr);
    }

    void append(Request *req)
    {
        requests.push_back(req);
    }

    void cancel(Request *req)
    {
        int number = req->get_no();
        requests.remove(req);

        cout << "Remove successful!" << endl;
        req->~Request();
    }

    Request *get_request(int num)
    {
        for (list<Request *>::const_iterator iter = this->requests.begin(),
                                             end = this->requests.end();
             iter != end;
             ++iter)
        {

            if (*iter != nullptr && num == (*iter)->get_no())
            {

                return *iter;
            }
        }

        return nullptr;
    }

    void print_all()
    {
        int n = 0;
        for (list<Request *>::const_iterator iter = this->requests.begin(),
                                             end = this->requests.end();
             iter != end;
             ++iter)
            if (*iter != nullptr)
            {
                n++;
                (*iter)->print();
            }
    }
};

struct transportInfo
{
    string code;
    string departPlace;
    string arrivalPlace;
    float priceOnePassenger;
    bool isFirstClass;
    char firstClass;
};

transportInfo *addFlightOrTrain(bool isFlight)
{
    char firstClass;

    transportInfo *info = new transportInfo();
    if (isFlight)
    {
        cout << "code of flight: ";
        cin >> info->code;
        cout << "airport of departure:";
        cin >> info->departPlace;
        cout << "airport of arrival:";
        cin >> info->arrivalPlace;
        cout << "standard price for one passenger:";
        cin >> info->priceOnePassenger;
        cout << "first class ((y)es or (n)o):";
        cin >> firstClass;
        if (firstClass == 'y')
        {
            info->isFirstClass = true;
        }
        else
        {
            info->isFirstClass = false;
        }
    }
    else
    {
        cout << "code of train: ";
        cin >> info->code;
        cout << "main train station of departure:";
        cin >> info->departPlace;
        cout << "main train station  of arrival:";
        cin >> info->arrivalPlace;
        cout << "price for one passenger:";
        cin >> info->priceOnePassenger;
        cout << "first class ((y)es or (n)o):";
        cin >> firstClass;
        if (firstClass == 'y')
        {
            info->isFirstClass = true;
        }
        else
        {
            info->isFirstClass = false;
        }
    }

    return info;
};

unsigned int Request::lastNo = 0;

int main(void)
{
    char choice;
    char choiceOutward;
    char choiceReturn;
    char firstClass;

    string noRequest;
    CallCenter *call = new CallCenter;
    Date dateTransport;
    string code;
    string departPlace;
    string arrivalPlace;
    float priceOnePassenger;
    bool isFirstClass;

    Transport *outwardTrans;
    Transport *returnTrans;

    do
    {
        menuitems1();
        cin >> choice;
        switch (choice)
        {
        case '1':
        {
            Accomodation *acc1 = new Accomodation(80, 150, 10);

            cout << "please choose transport outward" << endl;
            menuitems2();
            cin >> choiceOutward;
            switch (choiceOutward)
            {
            case '0':
            {
                outwardTrans = new SelfTravel();
                break;
            }

            case '1':
            {
                transportInfo *flight = addFlightOrTrain(true);
                outwardTrans = new Flight(acc1->get_arrival(), flight->code, flight->departPlace, flight->arrivalPlace, flight->priceOnePassenger, flight->isFirstClass);

                break;
            }
            case '2':
            {
                transportInfo *train = addFlightOrTrain(false);
                outwardTrans = new Train(acc1->get_arrival(), train->code, train->departPlace, train->arrivalPlace, train->priceOnePassenger, train->isFirstClass);

                break;
            }
            }

            cout << "please choose transport return" << endl;
            menuitems2();
            cin >> choiceOutward;
            switch (choiceOutward)
            {
            case '0':
            {
                returnTrans = new SelfTravel();
                break;
            }

            case '1':
            {
                transportInfo *flight = addFlightOrTrain(true);

                returnTrans = new Flight(acc1->get_departure(), flight->code, flight->departPlace, flight->arrivalPlace, flight->priceOnePassenger, flight->isFirstClass);

                break;
            }
            case '2':
            {
                transportInfo *train = addFlightOrTrain(false);

                returnTrans = new Train(acc1->get_departure(), train->code, train->departPlace, train->arrivalPlace, train->priceOnePassenger, train->isFirstClass);

                break;
            }
            }

            Request *req = new Request(acc1, outwardTrans, returnTrans);
            call->append(req);
            break;
        }

        case '2':
        {

            Accomodation *acc2 = new Accomodation(110, 210, 20);

            cout << "please choose transport outward" << endl;
            menuitems2();
            cin >> choiceOutward;
            switch (choiceOutward)
            {
            case '0':
            {
                outwardTrans = new SelfTravel();
                break;
            }

            case '1':
            {
                transportInfo *flight = addFlightOrTrain(true);

                outwardTrans = new Flight(acc2->get_arrival(), flight->code, flight->departPlace, flight->arrivalPlace, flight->priceOnePassenger, flight->isFirstClass);
                break;
            }
            case '2':
            {
                transportInfo *train = addFlightOrTrain(false);

                outwardTrans = new Train(acc2->get_arrival(), train->code, train->departPlace, train->arrivalPlace, train->priceOnePassenger, train->isFirstClass);

                break;
            }
            }

            cout << "please choose transport return" << endl;
            menuitems2();
            cin >> choiceOutward;
            switch (choiceOutward)
            {
            case '0':
            {
                returnTrans = new SelfTravel();
                break;
            }

            case '1':
            {
                transportInfo *flight = addFlightOrTrain(true);

                returnTrans = new Flight(acc2->get_departure(), flight->code, flight->departPlace, flight->arrivalPlace, flight->priceOnePassenger, flight->isFirstClass);

                break;
            }
            case '2':
            {
                transportInfo *train = addFlightOrTrain(false);

                returnTrans = new Train(acc2->get_departure(), train->code, train->departPlace, train->arrivalPlace, train->priceOnePassenger, train->isFirstClass);

                break;
            }
            }

            Request *req = new Request(acc2, outwardTrans, returnTrans);
            call->append(req);
            break;
        }

        case '3':
        {
            cout << "number of reservation request:" << endl;
            cin >> noRequest;
            Request *getRequest = call->get_request(stoi(noRequest));
            if (getRequest == nullptr)
            {
                cout << "reservation request not found" << endl;
                break;
            }
            else
            {
                getRequest->print();
                cout << "(c)ancel this request or (n)ot: " << endl;
                cin >> choice;
                if (choice == 'c')
                {
                    call->cancel(getRequest);
                    break;
                }
                else
                {
                    break;
                };
            }
        }
        case '4':
        {
            call->print_all();
            break;
        }
        }

    } while (
        choice != '0');

    return 0;
}