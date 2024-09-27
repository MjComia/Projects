#include <iostream>
#include <conio.h>
#define encryptval 20
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#define MAX 20

using namespace std;
class Register{
private:
    char Dpin[7];
    char Epin[7];
    string name[MAX];
    int bdayMonth[MAX];
    int bdayDay[MAX];
    int bdayYear[MAX];
    long long contactNo[MAX];
    int initialDeposit[MAX];
    int accountNumForEnroll;
    string formattedNumber[MAX];
    int last = 0;


public:

    void decrypt(){
        for(int i = 0;i<6;i++){
            Epin[i] =  Epin[i]-encryptval;
            Dpin[i] = Epin[i];
        }
    }

    void inputNewPin(){
        int i;
        cout<<"Input New Pin: ";
        for(i = 0;i<6;i++){
            Epin[i] = getch()+encryptval;
            putch('*');
        } Epin[i]= '\0';


    }


void UserInfo(){
system("cls");
cout<<"\n\n\n\t\t\tGetting Information."<<endl;
    cout<<"Input your full name:";
    getline(cin>>ws,name[last]);
    while (true) {
        cout << "Input your birth month [ex. 1-12]: ";
        if (cin >> bdayMonth[last] && bdayMonth[last] >= 1 && bdayMonth[last] <= 12) {
            break;
        } else {
            cout <<endl<< "Invalid input. Please enter a valid month (1-12)."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
    }
       while (true) {
        cout << "Enter the day you were born[ex. 1-31]: ";
        if (cin >> bdayDay[last] && bdayDay[last] >= 1 && bdayDay[last] <= 31) {
            break;
        } else {
            cout <<endl <<"Invalid input. Please enter a valid day(1-31)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
    }
       while (true) {
        cout << "Enter the year you were born[ex. 2003]: ";
        if (cin >> bdayYear[last] && bdayYear[last] >= 1950 && bdayYear[last] <= 2005) {
            break;
        } else {
            cout <<endl << "Invalid input. Please enter a valid year (1950-2005)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
           while (true) {
        cout << "Enter your phone number: +63 ";
        if (cin >> contactNo[last] && contactNo[last] >= 9000000000LL && contactNo[last] <= 9999999999LL) {
            break;
        } else {
            cout << endl <<"Invalid input. Please enter a valid contact number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
           while (true) {
        cout << "Enter your initial deposit: ";
        if (cin >> initialDeposit[last] && initialDeposit[last] >= 5000) {
            break;
        } else {
            cout <<endl << "Invalid input. Please enter a valid initial deposit." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    inputNewPin();
    srand(static_cast<unsigned int>(time(nullptr)));
    accountNumForEnroll =  10000 + rand() % 99999;
    formattedNumber[last] = to_string(accountNumForEnroll);
    cout << "\nAccount number: " << formattedNumber[last] <<endl;
    system("pause>0");
    last++;
    writeFile();
    writeFileInAtm();
}
void writeFile(){
    fstream filePtr;
    filePtr.open("DataBase.txt",ios:: app);
    if(filePtr.is_open()){
        for(int i = 0;i<last;i++){
        filePtr<<name[i]<<endl<<bdayMonth[i]<<"-"<<bdayDay[i]<<"-"<<bdayYear[i]<<" "<<contactNo[i]<<" "<<initialDeposit[i]<<" "<<formattedNumber[i]<<" "<<Epin<<endl;
        }
    }filePtr.close();
}
void writeFileInAtm(){
fstream filePtr;
filePtr.open("E:\\sample.txt",ios::app);
    if(filePtr.is_open()){
        for(int  i = 0;i<last;i++){
            filePtr<<formattedNumber[i]<<endl<<Epin;
        }filePtr.close();
    }
}

};
