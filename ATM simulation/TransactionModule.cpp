#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <limits>
#define MAX 20
#define encryptval 20
using namespace std;


class Transaction{

private:
    string n[MAX]; //database
    string bday[MAX];
    long long contn[MAX];
    int money[MAX];


    int accNum1[MAX];//database
    string epassDB[MAX];
    char dpassD;

    int counter;

    char dpassAtm;//usb
    int accNum2;
    string epassATM;

    char getpin[7];//Input by user
    char Dgetpin[7];
    string getOrigpin;

    char getDECPINFD[7];//USB decrypt

    char getDECPINDB[7];//DATA BASE decrypt

    char enewPin[7];//Change Pin

public:

void readDataBase(){ //reading the infos in database
string firstn;
string secondn;
string thirdn;
ifstream filePtr("DataBase.txt");

    if (filePtr.is_open()){
string line;
int strline = 0;
while(getline(filePtr,line)){
    istringstream data(line);
    if((strline%2)==0){
        data >> firstn >> secondn >> thirdn;
        if(secondn.empty()){
            n[strline/2] = firstn;
            }else if(thirdn.empty()){
                n[strline/2] = firstn + " " + secondn;
            }else
            n[strline/2] = firstn + " " + secondn + " " + thirdn;
            thirdn.erase();
    }else {
        data >> bday[strline/2] >> contn[strline/2] >> money[strline/2] >> accNum1[strline/2] >> epassDB[strline/2];
        }
        strline++;

    }
    counter = strline / 2 - 1;
}else{
cout<<"Empty Bank."<<endl;
}filePtr.close();
}

void readAtm(){// readin the infos in atm/flashdrive
string accName;
ifstream filePtr("E:\\sample.txt");
if(filePtr.is_open()){
    string line;
    int strline = 0;
    while(getline(filePtr,line)){
        istringstream data(line);
        if((strline%2)==0){
            data >> accNum2;
        }else {
        data >> epassATM;
        }strline++;
    }

}
filePtr.close();
}

void EnterPinEncrypted(){// Enter Pin of the user to be checked
int i;
system("cls");
cout<<"\n\n\n\t\t\tEnter Pin: ";
      for( i = 0;i<6;i++){
            getpin[i] = getch()+encryptval;
            putch('*');
        } getpin[i]= '\0';
        system("pause>0");

}
void decryptPin(){// Decrypt the pin which was inserted by the user
    int i;
        for(i = 0;i<6;i++){
            getpin[i] =  getpin[i]-encryptval;
            Dgetpin[i] = getpin[i];
        }
getOrigpin = Dgetpin;

}

void decryptFDPIN(){//DECRYPT THE PIN IN THE FLASH DRIVE
    int i,y;
    char charToArray[epassATM.length() + 1];

for(i = 0;i<epassATM.length();i++){
        charToArray[i] = epassATM[i];
    }
    charToArray[epassATM.length()] = '\0';

for(y = 0;y<6;y++){
        charToArray[y] =  charToArray[y]-encryptval;
        getDECPINFD[y] = charToArray[y];
    }


}

bool IsMatch(){//Return if the pin in the flashdrive matches with the password inserted by the user
return getDECPINFD == getOrigpin;
}

bool locateAccNum(){//locate the account number to check
for(int i = 0;i<=counter;i++){
 if(accNum1[i]==accNum2){
    return true;
 }

} return false;
}

int locateAccNumAndReturn(int a){// return the index number
for(int i = 0;i<=counter;i++){
 if(accNum1[i]==accNum2){
    return i;
 }
  ;
}return false;
}

string decryptDBPIN(int a){// Returns the decrypted pin from the database
int p = locateAccNumAndReturn(a);
int i,y;
char charToArrayDB[epassDB[p].length() + 1];

for(i = 0;i<epassDB[p].length();i++){
        charToArrayDB[i] = epassDB[p][i];
    }
    charToArrayDB[epassDB[p].length()] = '\0';

for(y = 0;y<6;y++){
        charToArrayDB[y] =  charToArrayDB[y]-encryptval;
        getDECPINDB[y] = charToArrayDB[y];
    }

return getDECPINDB;
}

void CheckIfInDB(){//checking if the account is in the system

if(locateAccNum()){
    if (decryptDBPIN(accNum2) == getOrigpin){
    cout<<"\nAccount is here"<<endl;
    cout<<"You may now proceed"<<endl;
    system("pause>0");

}else {

    cout<<"\nWARNING"<<endl;
cout<<"Account is not here"<<endl;
}
}
}

void CheckingPinIn(){
system("cls");
int maxAttempt = 3;
int attempt = 0;
while(attempt< maxAttempt){
EnterPinEncrypted();
decryptPin();
    if(IsMatch()){

   CheckIfInDB();//LAST CHECK
    break;
}else{
cout<<"\nWrong Password"<<endl;
system("pause>0");
attempt++;
}
}
if (attempt == maxAttempt) {
        system("cls");
        cout << "Max attempts reached. Program terminated." <<endl;
        exit(0);  // Exit the program with an error code.
    }
}


void balance(){

int loc = locateAccNumAndReturn(accNum2);
cout<<"YOUR BALANCE"<<endl;
cout<<"PESOS "<<money[loc]<<endl;
system("pause>0");
}

void withdraw(){
int wd = locateAccNumAndReturn(accNum2);
int wdAmount;
while (true){
cout<<"Enter the amount you are going to withdraw(withdraw only in divisible by 100): ";
cin>>wdAmount;
if( wdAmount % 100 == 0){
    money[wd] = money[wd] - wdAmount;
    break;
}else  {
    cout << "Invalid input. Enter number divisible by 100" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
}writeDataBase();
}
void deposit(){
int dp = locateAccNumAndReturn(accNum2);
int dpAmount;
while (true){
cout<<"Enter the amount you are going to deposit(deposit only in divisible by 100): ";
cin>>dpAmount;

if( dpAmount % 100 == 0){
    money[dp] = money[dp] + dpAmount;
break;
}else  {
    cout << "Invalid input. Enter number divisible by 1" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
}writeDataBase();
}

int FindAcc(string accName,  int accNo){
for(int i = 0;i<=counter;i++){
    if(n[i] == accName&& accNum1[i] == accNo){
        return i;
    }
}return false;
}
bool locateNameForTF(string accName,  int accNo){
for(int i = 0;i<=counter;i++){
    if(n[i] == accName&& accNum1[i] == accNo){
        return true;
    }
}return false;
}
void fundTransfer(){
string nm;
int accN;
int amt;//amount that will transfered
while (true){cout<<"Enter the name of the account that will be transfered: ";
getline(cin>>ws,nm);
cout<<"Enter the  account number: ";
cin>>accN;
int trns = FindAcc(nm, accN);
int lessTrns = locateAccNumAndReturn(accNum2);
if(locateNameForTF(nm,accN)){
while (true){
cout<<"Enter the amount you are going to transfer(transfer only in divisible by 100): ";
cin>>amt;
if( amt % 100 == 0){
    money[trns] = money[trns] + amt;
    money[lessTrns] = money[lessTrns] -amt;
    cout<<"Money Transfer: "<<money[trns]<<endl;
    cout<<"Your Current money: "<<money[lessTrns]<<endl;
    break;
}else  {
    cout << "Invalid input. Enter number divisible by 100" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
}
writeDataBase();
break;
}else {cout<<"Invalid account. Type the correct name and account number."<<endl;
}
}
}
void ChangePin(){
int i,np;
cout<<"Enter new pin: ";
      for( i = 0;i<6;i++){
            enewPin[i] = getch()+encryptval;
            putch('*');
        } enewPin[i]= '\0';
np = locateAccNumAndReturn(accNum2);
epassDB[np] = epassATM = enewPin;

writeDataBase();
writeAtm();
}

void writeDataBase(){
    fstream filePtr;
    filePtr.open("DataBase.txt",ios:: out);
    if(filePtr.is_open()){
        for(int i = 0;i<=counter;i++){
        filePtr<<n[i]<<endl<<bday[i]<<" "<<contn[i]<<" "<<money[i]<<" "<<accNum1[i]<<" "<<epassDB[i]<<endl;
        }
    }filePtr.close();
}

void writeAtm(){
    fstream filePtr;
    filePtr.open("E:\\sample.txt",ios:: out);
if(filePtr.is_open()){
filePtr<<accNum2<<endl<<epassATM;
    }
filePtr.close();
}



};

