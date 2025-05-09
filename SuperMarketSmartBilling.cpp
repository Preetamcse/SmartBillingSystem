#include<iostream>
#include<fstream>  //Jab hume file se data read ya write karna hota hai (jaise .txt
#include<sstream>  //Jab hume ek string ko input stream (jaise cin) ki tarah treat karna ho — jaise usme se number, word extract karna , fstream
#include <windows.h>  //Windows OS ke system-level features access karne ke liye // 
// Agar tum GUI app,
// dialog boxes, beep, system control, ya background processes Windows mein banana chahte ho, 
//tab ye use hota hai.
using namespace std;

class Bill
{
private:
    string Item;
    int Rate, Quantity;
public:
    Bill():Item(""), Rate(0), Quantity(0){ }
    
    void setItem(string item){
        Item = item;
    }
    
    void setRate(int rate){
        Rate = rate;
    }

    void setQuant(int quant){
        Quantity = quant;
    }

    string getItem(){
        return Item;
    }

    int getRate(){
        return Rate;
    }

    int getQuant(){
        return Quantity;
    }
};

// Pass Bill by reference so changes persist
void addItem(Bill& b){
    bool close = false;
    while(!close){
        int choice;
        cout<<"\t1.Add."<<endl;
        cout<<"\t2.close."<<endl;
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice==1){
            system("cls");
            string item;
            int rate, quant;

            cout<<"\tEnter Item Name: ";
            cin>>item;
            b.setItem(item);

            cout<<"\tEnter Rate Of Item: ";
            cin>>rate;
            b.setRate(rate);

            cout<<"\tEnter Quantity Of Item: ";
            cin>>quant;
            b.setQuant(quant);

            // Use consistent file path with proper escaping
            ofstream out("C:\\Users\\preet\\OneDrive\\Desktop\\Bill.txt", ios::app);
            if(!out){
                cout<<"\tError: File Can't Open!"<<endl;
            }
            else{
                out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuant()<<endl;
                out.close();
                cout<<"\tItem Added Successfully"<<endl;
            }
            Sleep(3000);
        }
        else if(choice == 2){
            system("cls");
            close = true;
            cout<<"\tBack To Main Menu!"<<endl;
            Sleep(3000);
        }
    }
}

void printBill(){
    system("cls");
    int count = 0;
    bool close = false;
    
    while(!close){
        system("cls");
        int choice;
        cout<<"\t1.Add Bill."<<endl;
        cout<<"\t2.Close Session."<<endl;
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice==1){
            string item;
            int quant;
            cout<<"\tEnter Item: ";
            cin>>item;
            cout<<"\tEnter Quantity: ";
            cin>>quant;

            // Use consistent file paths with proper escaping
            ifstream in("C:\\Users\\preet\\OneDrive\\Desktop\\Bill.txt");
            if(!in){
                cout<<"\tError: File can't be opened for reading!"<<endl;
                Sleep(3000);
                continue;
            }

            ofstream out("C:\\Users\\preet\\OneDrive\\Desktop\\BillTemp.txt");
            if(!out){
                cout<<"\tError: Temporary file can't be created!"<<endl;
                in.close();
                Sleep(3000);
                continue;
            }

            string line;
            bool found = false;

            while(getline(in, line)){
                stringstream ss(line);  // Initialize stringstream with the line
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                
                // Parse the line with proper format checking
                if(ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant){
                    if(item == itemName){
                        found = true;
                        if(quant <= itemQuant){
                            int amount = itemRate * quant;
                            cout<<"\t Item | Rate | Quantity | Amount"<<endl;
                            cout<<"\t"<<itemName<<"\t "<<itemRate<<"\t "<<quant<<"\t "<<amount<<endl;
                            int newQuant = itemQuant - quant;
                            
                            // Write updated quantity
                            out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<newQuant<<endl;
                            count += amount;
                        }
                        else{
                            cout<<"\tSorry, "<<item<<" Ended!"<<endl;
                            out<<line<<endl;  // Keep original line if not enough quantity
                        }
                    }
                    else{
                        out<<line<<endl;  // Copy the line as is
                    }
                }
                else{
                    out<<line<<endl;  // Copy malformed lines as-is
                }
            }
            
            if(!found){
                cout<<"\tItem Not Available!"<<endl;
            }
            
            out.close();
            in.close();
            
            // File operations for renaming
            remove("C:\\Users\\preet\\OneDrive\\Desktop\\Bill.txt");
            rename("C:\\Users\\preet\\OneDrive\\Desktop\\BillTemp.txt", 
                   "C:\\Users\\preet\\OneDrive\\Desktop\\Bill.txt");
                   
            Sleep(3000);
        }
        else if(choice == 2){
            close = true;
            cout<<"\tCounting Total Bill"<<endl;
        }
        Sleep(3000);
    }
    
    system("cls");
    cout<<endl<<endl;
    cout<<"\t Total Bill ----------------- : "<<count<<endl<<endl;
    cout<<"\tThanks For Shopping!"<<endl;
    Sleep(5000);  ////function pauses program execution for a certain number of seconds.
}

int main(){
    Bill b;
    bool exit = false;
    
    while(!exit){
        system("cls");  // // (CMD terminal) ko clear kar deta hai
        int val;

        cout<<"\tWelecom to Super Market Billing System"<<endl;
        cout<<"\t**********************************"<<endl;   //\t - Ye ek tab space deta hai — thoda aage se likhne ke liye     
        cout<<"\t\t1.Add Item."<<endl;      //1. Add Item is the text shown to the user as Option 1.
        cout<<"\t\t2.Print Bill."<<endl;   
        cout<<"\t\t3.Exit."<<endl;
        cout<<"\t\tEnter Choice :";
        cin>>val;
 

        if(val==1){
            system("cls");
            addItem(b);    
        }
        else if(val==2){
            printBill();
        }
        else if(val==3){
            system("cls");
            exit = true;
            cout<<"\tGood Luck!"<<endl;
            Sleep(3000);
        }    
    }
    
    return 0;  // Added return statement
}