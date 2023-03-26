#pragma once
#include "Classes.h"

bool doesPhoneNumExist(string phoneNum, string fileName)
{
    ifstream file_in("passengers.txt");
    istringstream ss;
    bool phoneNumExists = false;

    if (file_in)
    {
        string line;
        string skipString, phoneNumString;
        while (getline(file_in, line))
        {
            ss.clear();
            ss.str(line);

            for (int i = 0; i < 6; i++)
            {
                getline(ss, skipString, ',');
            }

            getline(ss, phoneNumString, ',');

            if (phoneNumString == phoneNum)
            {
                phoneNumExists = true;
                break;
            }
        }
    }

    file_in.close();
    return phoneNumExists;
}

bool containsAtMost(string str, char ch, int max)
{
    int occurrences = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
            occurrences++;
    }

    return occurrences <= max;
}

bool containsComma(string str)
{
    return !containsAtMost(str, ',', 0);
}

bool isNameValid(string name)
{
    // TODO: check if only valid characters for name are input
    bool valid = name.length() >= 2 && name.length() <= 30;

    if (!valid)
        return valid;

    bool includesComma = containsComma(name);

    if (includesComma)
    {
        valid = false;
        return valid;
    }

    return valid;
}

bool isPhoneNumValid(string phoneNum)
{
    bool valid = phoneNum.length() == 11;

    if (!valid)
        return valid;

    if (phoneNum[0] == '0' || phoneNum[1] == '3')
    {
        valid = false;
        return valid;
    }

    bool includesComma = containsComma(phoneNum);

    if (includesComma)
    {
        valid = false;
        return valid;
    }

    for (int i = 0; i < phoneNum.length(); i++)
    {
        if (!isdigit(phoneNum[i]))
        {
            valid = false;
            break;
        }
    }

    return false;
}

bool isValidNIC(string nic)
{
    bool valid = nic.length() != 13;
    
    if (!valid)
        return valid;
    
    if (nic[0] != '4') {
        valid = false;
        return valid;
    }

    bool includesComma = containsComma(nic);

    if (includesComma)
    {
        valid = false;
        return valid;
    }

    for (int i = 0; i < nic.length(); i++)
    {
        if (!isdigit(nic[i]))
        {
            valid = false;
            break;
        }
    }

    return valid; 
}