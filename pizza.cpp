//note: COMMENTS ARE NOT AI. I'm practicing proper commenting so it'll become my practice,
//      but correct comments are helped by Copilot since I do not know some of the correct terminologies.

// (ISSUE: int integer limit) FIXED 
// fallback is fixed with this if number exceeds min and max and non-numeric, 
// cin.clear resets bad input, and cin.get flushes chaarter until '\n' to prevent crashes
// will try to translate this to <cstdio> printf

#include <iostream>
#include <string>
#include <limits>

using namespace std;

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
// fallback but for the size (custom prompt)
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



int main(){
    
    string flavors[] ={"Pepperoni", "Hawaiian", "All Meat", "Vegetarian"};
    int flavorPrices[] = {250, 270, 300, 230};

    string sizes[] = {"8\"", "12\"", "16\""};
    int sizeExtraCst[] = {0, 100, 200};
    
    int grandTotal = 0;
    bool moreItems = true;

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

            cout << "Your Order:\n";
            cout << qty << "pcs " << sizes[sizeNum-1] << " " << flavors[flavorChoice -1] << endl;
            cout << "Subtotal: ₱" << totalPrice << endl;

            cout << "Add another item? \n";
            cout << "[Y] Yes [N] No : ";
            char answer;
            cin >> answer;
            
            bool validAnswer = false;
                while (!validAnswer)
                switch(answer){
                    case 'Y':
                    case 'y':
                        moreItems = true;
                        validAnswer = true;
                        break;

                    case 'N':
                    case 'n':
                        moreItems = false; 
                        validAnswer = true;
                        break;

                    default:
                        cout << "Invalid input. Please type Y or N.\n";
                        break;
                }
            //to add:
            //Formal reciept like a teller's reciept

            cout << "\nReciept\n";
            cout << "Your grand total is: " << "₱"<< grandTotal;
            cout << "\nThank you for purchasing!";
            
    }

}