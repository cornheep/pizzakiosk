// issues:
// no fallback if user input exceeeded the array index or bounds (sentence from Copilot, lol) 
// fallback is fixed with this if loop 
// (ISSUE: int integer limit)

#include <iostream>
#include <string>
using namespace std;

int main(){
    
    string flavors[] ={"Pepperoni", "Hawaiian", "All Meat", "Vegetarian"};
    int flavorPrices[] = {250, 270, 300, 230};

    string sizes[] = {"8\"", "12\"", "16\""};
    int sizeExtraCst[] = {0, 100, 200};
    
    int grandTotal = 0;
    bool moreItems = true;

        while(moreItems){

        int flavorChoice;
        int sizeNum;
        int qty;
        
            cout <<  "\nAvailable Flavors:\n";
            for (int i=0; i < 4; i++){
                cout << "[" << i + 1 << "]" << " " << flavors[i] << " "<< "₱" << flavorPrices[i] << endl;
            }
              
            cout << "\nEnter flavor number: ";
            cin >> flavorChoice;
            while (flavorChoice < 1 || flavorChoice > 4 ){
                cout << "Invalid Flavor choice. Try again. \n";
                cout << "\nEnter flavor number: ";
                cin >> flavorChoice;
            }
            
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

            cout << "\nEnter Size: ";
            cin >> sizeNum;
            while (sizeNum < 1 || sizeNum > 4 ){
                cout << "Invalid Size choice. Try again. \n";
                cout << "\nEnter Size: ";
                cin >> sizeNum;
            }

            cout << "\nEnter Quantity: ";
            cin >> qty;
                while(qty < 1){
                    cout << "Quantity must be at least 1 or more. Try again. \n";
                    cout << "\nEnter Quantity: ";
                    cin >> qty;
                }


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
            cout << "Your grand total is: " << "₱"<< grandTotal;
            
    }

}