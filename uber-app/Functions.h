#pragma once
#include "Classes.h"
#include <regex>
using namespace std;

bool doesPhoneNumOrNicExist(string str, bool isItPhoneNum, string fileName)
{
    ifstream file_in(fileName);
    istringstream ss;
    bool phoneNumOrNicExists = false;

    if (file_in)
    {
        string line, thisStr;

        int skip = isItPhoneNum ? 6 : 8;

        while (getline(file_in, line))
        {
            ss.clear();
            ss.str(line);

            for (int i = 0; i < skip; i++)
            {
                getline(ss, thisStr, ',');
            }

            getline(ss, thisStr, ',');

            if (thisStr == str)
            {
                phoneNumOrNicExists = true;
                break;
            }
        }
    }

    file_in.close();
    return phoneNumOrNicExists;
}

bool countOccurrences(string str, char ch)
{
    int occurrences = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
            occurrences++;
    }

    return occurrences;
}

bool containsComma(string str)
{
    return countOccurrences(str, ',') >= 1;
}

bool isValidName(string name)
{
    bool valid = name.length() >= 1 && name.length() <= 30;

    if (!valid)
        return valid;

    for (int i = 0; i < name.length(); i++)
    {
        // includes comma check
        if (!isalnum(name[i]))
        {
            valid = false;
            return valid;
        }
    }

    return valid;
}

bool isPhoneNumValid(string phoneNum)
{
    bool valid = phoneNum.length() == 11;

    if (!valid)
        return false;

    if (phoneNum[0] != '0' || phoneNum[1] != '3')
    {
        valid = false;
        return valid;
    }

    for (int i = 0; i < phoneNum.length(); i++)
    {
        // includes comma check
        if (!isdigit(phoneNum[i]))
        {
            valid = false;
            break;
        }
    }

    return valid;
}

bool isValidNIC(string nic)
{
    bool valid = nic.length() == 13;

    if (!valid)
        return valid;

    if (nic[0] != '4')
    {
        valid = false;
        return valid;
    }

    for (int i = 0; i < nic.length(); i++)
    {
        if (!isdigit(nic[i]))
        {
            // includes comma check
            valid = false;
            return valid;
        }
    }

    return valid;
}

bool isValidPlateNum(string plateNum)
{
    // AA-111
    // AAA-1111
    regex plateNumRegex("[A-Z]{2,3}-[0-9]{3,4}");
    return regex_match(plateNum, plateNumRegex);
}

int menu1()
{
    int opt;

    do
    {
        cout << endl
             << "Enter a number for one of the following commands:" << endl;
        cout << "1) Signup" << endl;
        cout << "2) Login" << endl;
        cout << "3) Exit" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

int menu2()
{
    int opt = 0;

    do
    {
        cout << endl
             << "1) As passenger" << endl;
        cout << "2) As driver" << endl;
        cout << "3) Go back" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

string typesMenu()
{
    int opt = 0;

    do
    {
        cout << endl
             << "1) Uber Auto [Rickshaw] [3 passengers]" << endl;
        cout << "2) Uber Moto [Bike] [1 passenger]" << endl;
        cout << "3) UberX [A private ride at an everyday price] [4 passengers]" << endl;
        cout << "4) UberXL [Affordable rides for groups up to 6] [6 passengers]" << endl;
        cout << "5) Uber Black [Premium rides in luxury cars]" << endl;
        cin >> opt;
    } while (opt < 1 || opt > 5);

    if (opt == 1)
        return "Uber Auto";
    else if (opt == 2)
        return "Uber Moto";
    else if (opt == 3)
        return "UberX";
    else if (opt == 4)
        return "UberXL";
    else
        return "Uber Black";
}

int getLastId(string fileName)
{
    ifstream file_in(fileName);
    istringstream ss;

    string returnId = "0";

    if (file_in)
    {
        string line, thisIdStr;

        while (getline(file_in, line))
        {
            ss.clear();
            ss.str(line);

            getline(ss, thisIdStr, ',');
            returnId = thisIdStr;
        }
    }

    file_in.close();
    return stoi(returnId);
}

string getCurrentTime()
{
    time_t current_time;
    current_time = time(NULL);
    string time = ctime(&current_time);
    time[time.length() - 1] = ' '; // LATER: check '\0'
    return time;
}