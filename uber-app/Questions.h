#pragma once
#include "Functions.h"

void askFirstAndLastNames(string &firstName, string &lastName)
{
     bool is_err;

     do
     {
          cout << endl
               << "Enter first name: ";
          cin >> firstName;

          cout << endl
               << "Enter last name: ";
          cin >> lastName;

          is_err = !isValidName(firstName) || !isValidName(lastName);

          if (is_err)
               cerr << endl
                    << "Error: each of the first and last names must contain at least 1 and at most 30 characters" << endl;
     } while (is_err);
}

bool is_err;

void askDOB(int &day, int &month, int &year, int opt2)
{
     int age;

     do
     {
          cout << endl
               << "Enter date of your birth [1 to 31]: ";
          // LATER: check for no of days being correct for a particular month can be implemented
          cin >> day;
          cout << endl
               << "Enter month of your birth [1 to 12]: ";
          cin >> month;
          cout << endl
               << "Enter year of your birth: ";
          cin >> year;

          is_err = day < 1 || day > 31 || month < 1 || month > 12 || year > current_year || year < current_year - 120;

          if (is_err)
               cerr << endl
                    << "Error: invalid date of birth" << endl;

          age = getAge(day, month, year);
          if (!is_err && opt2 == 2)
          {
               if (age < 18)
                    cerr << endl
                         << "Error: driver must be at least 18 years old" << endl;
          }
     } while (is_err || (age < 18 && opt2 == 2));
}

void askPhoneNum(string &phoneNum, int opt2)
{
     bool phoneNumExists = false;

     do
     {
          cout << endl
               << "Enter phone number (start with 0): ";
          cin >> phoneNum;

          is_err = !isPhoneNumValid(phoneNum);

          if (is_err)
               cerr << endl
                    << "Error: invalid phone number" << endl;
          else
          {
               if (opt2 == 1)
                    phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, "passengers.txt");

               else if (opt2 == 2)
                    phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, "drivers.txt");
          }

          if (phoneNumExists)
               cerr << endl
                    << "Error: this phone number is already in use" << endl;

     } while (is_err || phoneNumExists);
}

void askNIC(string &nic)
{
     bool nicExists;

     do
     {
          cout << endl
               << "Enter NIC number (without dashes): ";
          cin >> nic;

          is_err = !isValidNIC(nic);

          if (is_err)
               cerr << endl
                    << "Error: invalid NIC" << endl;

          nicExists = doesPhoneNumOrNicExist(nic, false, "drivers.txt");
          if (nicExists)
               cerr << endl
                    << "Error: this NIC is already in use" << endl;
     } while (is_err || nicExists);
}

void askPassword(string &password, bool editing)
{
     string confirmPassword;

     is_err = false;
     if (editing) // ask for current password
     {
          string currentPasswordConfirm;
          do
          {
               cout << endl
                    << "Enter current password: ";
               cin >> currentPasswordConfirm;
               is_err = currentPasswordConfirm != password;

               if (is_err)
                    cerr << endl
                         << "Error: current password is not valid" << endl;
          } while (is_err);
     }

     is_err = false;
     string newWord = editing ? "new " : "";
     do
     {
          cout << endl
               << "Enter " << newWord << "password: ";
          cin >> password;

          cout << endl
               << "Confirm " << newWord << "password: ";
          cin >> confirmPassword;

          if (password.length() < 6)
          {
               is_err = true;
               cerr << endl
                    << "Error: password must be at least six characters long" << endl;
          }

          if (password != confirmPassword)
          {
               is_err = true;
               cerr << endl
                    << "Error: passwords do not match" << endl;
          }
     } while (is_err || containsComma(password));
}