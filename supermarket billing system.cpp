#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int stock;

public:
    Product(int i = 0, string n = "", double p = 0, int s = 0) {
        id = i;
        name = n;
        price = p;
        stock = s;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name
             << " | Price: " << price << " | Stock: " << stock << endl;
    }

    int getId() { return id; }
    double getPrice() { return price; }
    int getStock() { return stock; }

    void reduceStock(int qty) {
        if (qty > stock)
            throw "Not enough stock!";
        stock -= qty;
    }
};

class User {
protected:
    string name;

public:
    User(string n = "") { name = n; }
    virtual void menu() = 0;
};

class Customer : public User {
private:
    double total;

public:
    Customer(string n = "") : User(n) {
        total = 0;
    }

    void addToCart(double price) {
        total += price;
    }

    void addToCart(double price, int qty) {
        total += price * qty;
    }

    void showTotal() {
        cout << "Total Bill: " << total << endl;
    }

    void menu() {
        cout << "\nCustomer Menu\n";
    }
};

class Admin : public User {
public:
    Admin(string n = "") : User(n) {}

    void menu() {
        cout << "\nAdmin Menu\n";
    }
};

class Bill {
public:
    double amount;

    Bill(double a = 0) { amount = a; }

    Bill operator+(Bill b) {
        return Bill(amount + b.amount);
    }
};

int main() {
    int rows = 5, cols = 4;

    string productTable[5][4] = {
        {"1","Phone","20000","10"},
        {"2","Laptop","70000","5"},
        {"3","Headphones","3000","15"},
        {"4","Mouse","1500","20"},
        {"5","Keyboard","2500","10"}
    };

    Product* products = new Product[5];

    for(int i = 0; i < rows; i++) {
        products[i] = Product(
            stoi(productTable[i][0]),
            productTable[i][1],
            stod(productTable[i][2]),
            stoi(productTable[i][3])
        );
    }

    Customer customer("Eric");
    int choice, id, qty;
    Bill totalBill;

    do {
        cout << "\n===== E-COMMERCE SYSTEM =====\n";
        cout << "1. View Products\n";
        cout << "2. Buy Product\n";
        cout << "3. View Total\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
        case 1:
            for(int i = 0; i < rows; i++) {
                products[i].display();
            }
            break;

        case 2:
            try {
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity: ";
                cin >> qty;

                bool found = false;

                for(int i = 0; i < rows; i++) {
                    if(products[i].getId() == id) {
                        products[i].reduceStock(qty);

                        double cost = products[i].getPrice() * qty;
                        customer.addToCart(products[i].getPrice(), qty);

                        totalBill = totalBill + Bill(cost);

                        cout << "Item purchased successfully!\n";
                        found = true;
                        break;
                    }
                }

                if(!found)
                    throw "Product not found!";

            } catch(const char* msg) {
                cout << "Error: " << msg << endl;
            }
            break;

        case 3:
            customer.showTotal();
            cout << "Total (Operator Overloading): " << totalBill.amount << endl;
            break;

        case 4:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    delete[] products;

    return 0;
}
