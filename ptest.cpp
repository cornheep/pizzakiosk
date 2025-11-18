//note: COMMENTS ARE NOT AI. I'm practicing proper commenting so it'll become my practice,                
//      but correct comments are helped by Copilot since I do not know some of the correct terminologies. 

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;
using namespace chrono;

// structure to hold order details
struct OrderItem {
    int qty;
    int sizeNum;
    int flavorChoice;
    int totalPrice;
    string itemDescription;
};

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

// display current cart items
void displayCart(const vector<OrderItem>& cart, int grandTotal) {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }
    
    cout << "\n[========== CURRENT CART ==========]\n";
    for (size_t i = 0; i < cart.size(); i++) {
        cout << "[" << i + 1 << "] " << cart[i].itemDescription 
             << " - ₱" << cart[i].totalPrice << "\n";
    }
    cout << "\nGrand Total: ₱" << grandTotal << "\n";
    cout << "[==================================]\n";
}

// remove item from cart
bool removeItem(vector<OrderItem>& cart, int& grandTotal) {
    if (cart.empty()) {
        cout << "\nNo items to remove!\n";
        return false;
    }
    
    displayCart(cart, grandTotal);
    
    int choice = getSafeInt("\nEnter item number to remove (0 to cancel)", 0, cart.size());
    
    if (choice == 0) {
        return false;
    }
    
    // subtract the price from grand total
    grandTotal -= cart[choice - 1].totalPrice;
    
    cout << "\nRemoved: " << cart[choice - 1].itemDescription << "\n";
    
    // remove the item from vector
    cart.erase(cart.begin() + (choice - 1));
    
    return true;
}

// menu for add/remove/checkout
char showActionMenu() {
    char answer;
    while (true) {
        cout << "\n[A] Add Item [R] Remove Item [C] Checkout : ";
        cin >> answer;
        answer = toupper(answer);
        
        if (answer == 'A' || answer == 'R' || answer == 'C') {
            return answer;
        }
        
        cout << "Invalid input. Please type A, R, or C.\n";
        cin.clear();
        while (cin.get() != '\n') {}
    }
} 

// modular print receipt
void printReceipt(int& orderCount, int grandTotal, int payment, int change,
    const vector<OrderItem>& cart) { 
    orderCount++; // new order placed
    saveOrderCount(orderCount);
    cout << "\n[==================== RECEIPT ====================]\n";
    cout << "Order Number: #" << orderCount;
    receiptTimeandDate(); // prints Business Date and Time
    cout << "\nItem Summary:\n";
    
    // lists total items bought
    for (const auto& item : cart) {
        cout << "   " << item.itemDescription << " - ₱" << item.totalPrice << "\n";
    }
    
    cout << "\nGrand Total: ₱" << grandTotal << "\n";
    cout << "Payment: ₱" << payment << "\n";
    cout << "Change: ₱" << change << "\n";
    cout << "Thank you for purchasing!\n";
    cout << "[=================================================]\n";
}

int main(){ 
    string flavors[] ={"Pepperoni", "Hawaiian", "All Meat", "Vegetarian", "Cheese"};
    int flavorPrices[] = {600, 540, 760, 560, 580};
    string sizes[] = {"8\"", "12\"", "16\""};
    int sizeExtraCst[] = {0, 100, 200};
    
    int grandTotal = 0;
    vector<OrderItem> cart; 
    int orderCount = openOrderCount();
    
    bool shopping = true;
    bool firstItem = true; // tracker if its the first item
    
    while(shopping){
        char action;
        
        // skip if first item
        if (firstItem) {
            action = 'A';
            firstItem = false;
        } else {
            action = showActionMenu();
        }
        
        if (action == 'A') {
            // add item logic
            cout <<  "\nAvailable Flavors:\n";
            for (int i=0; i < 5; i++){
                cout << "[" << i + 1 << "]" << " " << flavors[i] << " "<< "₱" << flavorPrices[i] << endl;
            } 
              
            int flavorChoice = getSafeInt("\nEnter flavor choice", 1, 5);
            
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
            int sizeNum = getSafeInt ("Enter size", 1, 3);
            
            int qty = getSafeIntSize ("Enter quantity", 1, 50);
                
            int basePrice = flavorPrices[flavorChoice - 1];
            int sizeExtra = sizeExtraCst[sizeNum -1];
            int totalPrice = (basePrice + sizeExtra) * qty;
            grandTotal += totalPrice;
            
            // create order item
            OrderItem newItem;
            newItem.qty = qty;
            newItem.sizeNum = sizeNum;
            newItem.flavorChoice = flavorChoice;
            newItem.totalPrice = totalPrice;
            newItem.itemDescription = to_string(qty) + "pcs " + sizes[sizeNum - 1] + 
                                      " " + flavors[flavorChoice - 1];
            
            cart.push_back(newItem);
            
            cout << "\nAdded to cart: " << newItem.itemDescription << " - ₱" << totalPrice << "\n";
            displayCart(cart, grandTotal);
        }
        else if (action == 'R') {
            removeItem(cart, grandTotal);
            if (!cart.empty()) {
                displayCart(cart, grandTotal);
            }
        }
        else if (action == 'C'){
            if (cart.empty()) {
                cout << "\nYour cart is empty! Please add items first.\n";
                continue;
            }
            
            displayCart(cart, grandTotal);
            
            bool paymentPrompt = false;
            int payment;
            int change;
            
            while(!paymentPrompt){ 
                cout << "\nPayment: ";
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
                    change = grandTotal - payment;
                    cout << "Insufficient Payment. Please add ₱" << change << "\n";
                    paymentPrompt = false;
                }
            }
            
            // print reciept and end program
            printReceipt(orderCount, grandTotal, payment, change, cart);
            shopping = false;
        }
    }
    
    return 0;
}
