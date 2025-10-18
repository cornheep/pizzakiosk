//note: COMMENTS ARE NOT AI. I'm practicing proper commenting so it'll become my practice,
//      but correct comments are helped by Copilot since I do not know some of the correct terminologies.

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;
using namespace chrono;

// fallback if the user inputs number not in the choices
int getSafeInt(string prompt, int min, int max){
    int val;

    while(true){
        cout << "\nPick a number between " << min << "-" << max << ": ";

    if (cin >> val){
            if (val >= min && val <= max){
            return val; 
            }
            else {
                cout << "Number is out of range. Please pick a number between " << min << " and " << max << ".\n";
            }
        }   
        else {
            cout << "Invalid Input. Only numbers are allowed.\n";
            cin.clear();
            while(cin.get() != '\n'){}
        } 
    }
}    
// fallback but for the size
int getSafeIntSize(string prompt, int min, int max){
    int val;

    while(true){
        cout << "\nEnter quantity between " << min << "-" << max << ": ";

    if (cin >> val){
            if (val >= min && val <= max){
            return val; 
            }
            else {
                cout << "We can only accomodate up to " << max << " pizzas. Please pick a quantity up to" << max << ".\n";
            }
        }   
        else {
            cout << "Invalid Input. Only numbers are allowed.\n";
            cin.clear();
            while(cin.get() != '\n'){}
        } 
    }
} 

//open orderCount file
int openOrderCount(){ 
    ifstream in("orderCount.txt");
    int orderCount = 0;

    if (in >> orderCount){
        return orderCount;    
    }
    else {
        ofstream out("orderCount.txt");
        out << 0;
        out.close();
        return orderCount; 
    }
}

// save current order number 
int saveOrderCount(int count) {
    ofstream out("orderCount.txt");
    out << count;
    return count;
}

//  time when reciept is printed
void receiptTimeandDate(){
        auto now = system_clock::now();
        time_t currentTime = system_clock::to_time_t(now); 
        tm* local = localtime(&currentTime);               

        char formattedDate[30];
        char formmattedTime [30];

        strftime(formattedDate, sizeof(formattedDate), "%a %b %d, %Y", local);
        strftime(formmattedTime , sizeof(formmattedTime), "%I:%M:%S %p", local); 

        cout << "\nBusiness Date: " << formattedDate << "\n";
        cout << "Time: " << formmattedTime << "\n" ;
       }

// modularized the addmoreitem
bool addItem(){
    char answer;
    bool validAnswer = false;

    while (!validAnswer) {
        cout << "Add another item? \n";
        cout << "[Y] Yes [N] No : ";
        cin >> answer;

        switch (answer) {
            case 'Y':
            case 'y':
                cout << "\n";
                return true;

            case 'N':
            case 'n':
                cout << "\n";
                return false;

            default:
                cout << "Invalid input. Please type Y or N.\n\n";
                cin.clear();
                while (cin.get() != '\n') {}
                break;
        }
    }
    return false;
}
// modular prit reciept
void printReceipt(int& orderCount, int qty, int sizeNum, int flavorChoice, int totalPrice, int grandTotal, int payment, int change,
    string sizes[], string flavors[], string& itemSummary) { 
    orderCount++; // new order placed
    saveOrderCount(orderCount);

    cout << "\n[==================== RECEIPT ====================]\n";
    cout << "Order Number: #" << orderCount;

    receiptTimeandDate(); // prints Business Date and Time

    cout << "\nItem Summary:\n";
    //lists total items bought
    cout << itemSummary << "\n";

    cout << "Grand Total: ₱" << grandTotal << "\n";
    cout << "Payment: ₱" << payment << "\n";
    cout << "Change: ₱" << change << "\n";
    cout << "Thank you for purchasing!\n";
    cout << "[=================================================]\n";
}

int main(){ 
    
    string flavors[] ={"Pepperoni", "Hawaiian", "All Meat", "Vegetarian"};
    int flavorPrices[] = {250, 270, 300, 230};

    string sizes[] = {"8\"", "12\"", "16\""};
    int sizeExtraCst[] = {0, 100, 200};
    
    int grandTotal = 0;
    bool moreItems = true;

    string itemSummary = "";    
    int orderCount = openOrderCount();
    
        while(moreItems){
            
            cout <<  "\nAvailable Flavors:\n";
            for (int i=0; i < 4; i++){
                cout << "[" << i + 1 << "]" << " " << flavors[i] << " "<< "₱" << flavorPrices[i] << endl;
            }
              
            int flavorChoice = getSafeInt("\nEnter flavor choice; ", 1, 4);
            
            cout << "\nAvailable Sizes:\n";
            for (int i=0; i < 3; i++){
            cout << "[" << i + 1 << "]" << " " << sizes[i];
                if (sizeExtraCst[i] == 0){
                    cout << "(No Extra Charge)\n";
                }
                else{
                    cout << "(₱" << sizeExtraCst[i] << ")\n";
                }
            }
            int sizeNum = getSafeInt ("Enter size: ",1, 3);
            
            int qty = getSafeIntSize ("Enter quantity", 1, 50);
                
            int basePrice = flavorPrices[flavorChoice - 1];
            int sizeExtra = sizeExtraCst[sizeNum -1];
            int totalPrice = (basePrice + sizeExtra)* qty;

            grandTotal += totalPrice;

            itemSummary += "   " + to_string(qty) + "pcs " + sizes[sizeNum - 1] + " " +
                   flavors[flavorChoice - 1] + " - ₱" + to_string(totalPrice) + "\n";

            cout << "\nYour Order:\n";
            cout << qty << "pcs " << sizes[sizeNum-1] << " " << flavors[flavorChoice -1] << endl;
            cout << "Subtotal: ₱" << totalPrice << endl;
            cout << "Current Total: ₱" << grandTotal << "\n\n"; 

            moreItems = addItem(); // it returns value to moreItems
            
            // payment section
            if (!moreItems){
            bool paymentPrompt = false;
            int payment;
            int change;
            while(!paymentPrompt){ 
            cout << "Payment: ";
            cin >> payment;
            
            if (payment > grandTotal){
                change = payment - grandTotal;
                paymentPrompt = true;
            }
            else if (payment == grandTotal){
                change = 0;
                paymentPrompt = true;
            }
            
            else if (payment < grandTotal){
                change = payment - grandTotal;
                cout << "Insuficient Payment. Please add " << change << "\n";
                paymentPrompt = false;
            }
            }
            //calls  the printreciept after all is done
            printReceipt(orderCount, qty, sizeNum, flavorChoice, totalPrice, grandTotal, payment, change, sizes, flavors, itemSummary);
            }

        }  
}
