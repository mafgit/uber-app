#pragma once
#include "Functions.h"

void askName(string &name, bool first, bool editing)
{
     bool is_err;
     do
     {
          cout << endl
               << "Enter " << (first ? "first" : "last") << " name: ";
          cin >> name;

          if (editing && name == "-1")
               break;

          is_err = !isValidName(name);

          if (is_err)
               cerr << endl
                    << "Error: each of the first and last names must contain at least 1 and at most 30 alphanumeric characters" << endl;
     } while (is_err);
}

bool is_err;

void askDate(int type, int &date, int min, int max, bool editing)
{
     string str;

     if (type == 1)
          str = "Enter date of your birth [1 to 31]: ";
     else if (type == 2)
          str = "Enter month of your birth [1 to 12]: ";
     else
          str = "Enter year of your birth: ";

     do
     {
          cout << endl
               << str;
          cin >> date;

          if (editing && date == -1)
               break;
     } while (date > max && date < min);
}

// void askDOB(int &day, int &month, int &year, bool isPassenger, bool editing)
// {
//      int age;
//      bool err_1;

//      do
//      {
//           cout << endl
//                << "Enter date of your birth [1 to 31]: ";
//           // LATER: check for no of days being correct for a particular month can be implemented
//           cin >> day;
//           cout << endl
//                << "Enter month of your birth [1 to 12]: ";
//           cin >> month;
//           cout << endl
//                << "Enter year of your birth: ";
//           cin >> year;

//           err_1 = day > 31 || month > 12 || year > current_year;

//           if (editing)
//                is_err = !err_1 && !(day < -1 || month < -1 || (year < -1 || (year > -1 && year < current_year - 120)));
//           else
//                is_err = !err_1 && !(day < 1 || month < 1 || year < current_year - 120);

//           if (is_err)
//                cerr
//                    << endl
//                    << "Error: invalid date of birth" << endl;

//           age = getAge(day, month, year);
//           if (!is_err && !isPassenger)
//           {
//                if (age < 18)
//                     cerr << endl
//                          << "Error: driver must be at least 18 years old" << endl;
//           }
//      } while (is_err || (age < 18 && !isPassenger));
// }

void askPhoneNum(string &phoneNum, bool isPassenger, bool editing)
{
     bool phoneNumExists = false;
     string filename;
     do
     {
          cout << endl
               << "Enter phone number (start with 0): ";
          cin >> phoneNum;

          if (editing && phoneNum == "-1")
               break;

          is_err = !isPhoneNumValid(phoneNum);

          if (is_err)
               cerr << endl
                    << "Error: invalid phone number" << endl;
          else
          {
               if (isPassenger)
                    filename = "passengers.csv";
               else
                    filename = "drivers.csv";

               phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, filename);
          }

          if (phoneNumExists)
               cerr << endl
                    << "Error: this phone number is already in use" << endl;

     } while (is_err || phoneNumExists);
}

void askNIC(bool editing, string &nic)
{
     bool nicExists;

     do
     {
          cout << endl
               << "Enter NIC number (without dashes): ";
          cin >> nic;

          if (editing && nic == "-1")

               is_err = !isValidNIC(nic);

          if (is_err)
               cerr << endl
                    << "Error: invalid NIC" << endl;

          nicExists = doesPhoneNumOrNicExist(nic, false, "drivers.csv");
          if (nicExists)
               cerr << endl
                    << "Error: this NIC is already in use" << endl;
     } while (is_err || nicExists);
}

void askPassword(string &password, string currentPassword, bool editing)
{
     string confirmPassword;
     bool doNotModify = false;
     is_err = false;

     if (editing) // ask for current password
     {
          string currentPasswordConfirm;
          do
          {
               cout << endl
                    << "Enter current password: ";
               cin >> currentPasswordConfirm;

               if (currentPasswordConfirm == "-1")
               {
                    doNotModify = true;
                    break;
               }

               is_err = currentPasswordConfirm != currentPassword;

               if (is_err)
                    cerr << endl
                         << "Error: invalid password" << endl;
          } while (is_err);
     }

     if (!doNotModify)
     {
          string newWord = editing ? "new " : "";
          do
          {
               is_err = false;

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
}

void askVehicle(bool editing, string &type, int &yearOfManufacture, string &make, string &model, string &trimLevel, string &plateNum, string &color)
{
     int minYearOfManufacture = current_year - 17;

     cout << endl
          << "Enter a number to select the type of your vehicle: " << endl;
     type = typesMenu(editing);

     do
     {
          cout << endl
               << "Enter year of manufacture of your vehicle [" << minYearOfManufacture << " - " << current_year << "]: ";
          cin >> yearOfManufacture;

          if (editing && yearOfManufacture == -1)
               break;
     } while (yearOfManufacture < minYearOfManufacture || yearOfManufacture > current_year);

     do
     {
          cout << endl
               << "Enter make (manufacturer) of the vehicle [e.g. Toyota]: ";
          cin >> make;

          if (editing && make == "-1")
               break;
     } while (!isValidName(make));

     do
     {
          cout << endl
               << "Enter model of the vehicle [e.g. Corolla]: ";
          cin >> model;

          if (editing && model == "-1")
               break;
     } while (!isValidName(model));

     do
     {

          cout << endl
               << "Enter trim level of the vehicle [e.g. LE]: ";
          cin >> trimLevel;

          if (editing && trimLevel == "-1")
               break;
     } while (!isValidName(trimLevel));

     do
     {

          cout << endl
               << "Enter plate number of the vehicle [e.g. AAA-1111]: ";
          cin >> plateNum;

          if (editing && plateNum == "-1")
               break;
     } while (!isValidPlateNum(plateNum));

     do
     {

          cout << endl
               << "Enter color of the vehicle [e.g. blue]: ";
          cin >> color;

          if (editing && color == "-1")
               break;
     } while (!isValidName(color));
}