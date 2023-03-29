#pragma once
#include "Classes.h"
#include <regex>

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

    for (int i = 0; i < name.length(); i++) {
        // includes comma check
        if (!isalnum(name[i])) {
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
    
    if (nic[0] != '4') {
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

bool isValidPlateNum(string plateNum) {
    // AA-111
    // AAA-1111
    regex plateNumRegex("[A-Z]{2,3}-[0-9]{3,4}");
    return regex_match(plateNum, plateNumRegex);
}