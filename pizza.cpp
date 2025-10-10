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
            cout << "\nEnter flavor number:";
            cin >> flavorChoice;

            cout << "\nAvailable Sizes:\n";
            for(int i=0; i < 3; i++){
            cout << "[" << i + 1 << "]" << " " << sizes[i] << endl;
            }
            cout << "\nEnter Size:";
            cin >> sizeNum;

            cout << "\nEnter Quantity: ";
            cin >> qty;

            int basePrice = flavorPrices[flavorChoice - 1];
            int sizeExtra = sizeExtraCst[sizeNum -1];
            int totalPrice = (basePrice + sizeExtra)* qty;

            grandTotal += totalPrice;

            cout << "Your Order:\n";
            cout << qty << "pcs " << sizes[sizeNum-1] << " " << flavors[flavorChoice -1] << endl;
            cout << "Subtotal: ₱" << totalPrice << endl;

            moreItems = false;
     }

}