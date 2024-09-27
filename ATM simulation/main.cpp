#include <iostream>
#include "RegisterModule.cpp"
#include "TransactionModule.cpp"

using namespace std;

Register r;
Transaction t;

void menu();
void EmptyFileCheck();
bool isFlashDrive();
void readFlash();


int main(){

EmptyFileCheck();

}


void menu(){

system("cls");
int op;
while (1){
        system("cls");
cout<<"\n\n\t\t\tWELCOME TO ATM MACHINE"<<endl;
cout<<"[1]Check Balance"<<endl;
cout<<"[2]Withdraw"<<endl;
cout<<"[3]Deposit"<<endl;
cout<<"[4]Fund Transfer"<<endl;
cout<<"[5]Change Pin"<<endl;
cout<<"[6]Exit"<<endl;
cin>>op;


switch(op){

case 1 :
    system("cls");
    cout<<"\n\n\n\t\t\tBALANCE MODE"<<endl;
    t.balance();break;
case 2 :
    system("cls");
    cout<<"\n\n\n\t\t\tWITHDRAW MODE"<<endl;
    t.withdraw();break;
case 3 :
    system("cls");
    cout<<"\n\n\n\t\t\tDEPOSIT MODE"<<endl;
    t.deposit();break;
case 4 :
    system("cls");
    cout<<"\n\n\n\t\t\tFUND TRANSFER MODE"<<endl;
    t.fundTransfer();break;
case 5 :
    system("cls");
    cout<<"\n\n\n\t\t\tCHANGE PIN OPTION"<<endl;
    t.ChangePin();break;
case 6 :
    exit(0);break;
default:
    system("cls");cout<<"Choose only from 1-6"<<endl;
system("pause>0");
}
}
}

void EmptyFileCheck(){
readFlash();
ifstream filePtr("E:\\sample.txt");
filePtr.is_open();
    char ch;
    filePtr >> noskipws >> ch;
    if(filePtr.eof()){
        r.UserInfo();
        t.readAtm();
        t.readDataBase();
        menu();
    }   else{
        t.readAtm();
        t.readDataBase();
        t.decryptFDPIN();
        t.CheckingPinIn();
        menu();
            }
filePtr.close();

}

bool isFlashDrive(){
        ifstream filePtr("E:\\sample.txt");
            return filePtr.is_open();
    }

void readFlash(){
    while(!isFlashDrive()){
             cout << "\n\n\n\t\t\tInsert flash drive and press Enter when ready..." << endl;
             system("pause>0");
                }
            cout<<"\n\n\n\t\t\tFlash drive detected. Please enter any key."<<endl;
             system("pause>0");
    }

