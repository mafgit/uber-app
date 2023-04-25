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

          if (editing && name == "-")
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

     cout << endl
          << str;
     cin >> date;

     do
     {
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

          if (editing && (phoneNum == "-" || phoneNum == "0"))
               break;

          is_err = !isPhoneNumValid(phoneNum);

          if (is_err)
               cerr << endl
                    << "Error: invalid phone number" << endl;
          else
          {
               if (isPassenger)
                    filename = "passengers.txt";
               else
                    filename = "drivers.txt";

               phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, filename);
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

               if (currentPasswordConfirm == "-")
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
}