/*
Build an online shopping interface where buyers and sellers can buy and sell inventory and engage in efficient transactions across a wide range of products.

Modules :

1. Profile service.
2. Inventory service.
3. Order service.
4. Payment service.
Requirements :

Allow buyers and sellers to register and log in.
Allow sellers to manage their inventory of products. (Operations : addItem(), updateItem())
Allow buyers to add items to the cart, place the order, and make payment (Operations: listInventory(), butItem(), addToCart(), makePayment ()).
Orders should be validated against inventory.
Password validation and encryption.

*/
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int pId = 1;
class Product {
public:
    int id;
    string productName;
    string productType;
    int price;
    int quantity;
public:
    Product(string productName, string productType, int price, int quantity) {
        this->id = pId++;
        this->productName = productName;
        this->productType = productType;
        this->price = price;
        this->quantity = quantity;
    }
};
class Seller {
    string username;
    string password;
public:
    vector <Product> products;
    Seller(string username, string password) {
        this->username = username;
        this->password = password;
    }
    string getUserName() {
        return username;
    }
    string getPassword() {
        return password;
    }
    void addProduct() {
        string name, type;
        int price, qty;
        cout<<"Enter Product Name : ";
        cin>>name;
        cout<<"Enter Product Type : ";
        cin>>type;
        cout<<"Enter Product Price : ";
        cin>>price;
        cout<<"Enter Product Quantity : ";
        cin>>qty;
        products.emplace_back(name, type, price, qty);
    }
    void deleteProduct() {
        int dId;
        while(true) {
            cout<<"Enter Product ID to be deleted : ";
            cin>>dId;
            if(cin.fail()) {
                cin.clear();
                cout<<"....Please Enter a Integer....\n";
            }
            else {
                break;
            }
        }
        for(auto it = products.begin(); it!=products.end(); it++) {
            if(dId == it->id) {
                products.erase(it);
                break;
            }
        }
    }
    void viewProduct() {
        cout<<setw(15)<<"Product ID"<<setw(20)<<"Product Name"<<setw(20)<<"Product Type"<<setw(20)<<"Product Price"<<setw(22)<<"Product Quantity\n";
        for(auto & product : products) {
            cout<<setw(15)<<product.id<<setw(20)<<product.productName<<setw(20)<<product.productType<<setw(20)<<product.price<<setw(22)<<product.quantity;
            cout<<endl;
        }
    }
};
class Buyer {
    string username;
    string password;
public:
    vector<Product> cart;
    vector <Product> orders;
    Buyer(string username, string password) {
        this->username = username;
        this->password = password;
    }
    string getUserName() {
        return username;
    }
    string getPassword() {
        return password;
    }
    string viewOrders() {
        cout<<setw(15)<<"Product ID"<<setw(20)<<"Product Name"<<setw(20)<<"Product Type"<<setw(20)<<"Product Price"<<setw(22)<<"Product Quantity\n";
        for(auto & product : orders) {
            cout<<setw(15)<<product.id<<setw(20)<<product.productName<<setw(20)<<product.productType<<setw(20)<<product.price<<setw(22)<<product.quantity;
            cout<<endl;
        }
    }
};

class InventoryManagement {
    vector<Seller> sellers;
    vector<Buyer> buyers;
public:
    void registerSeller() {
        string username, password;
        cout<<"Enter New Seller User Name : ";
        cin>>username;
        cout<<"Enter Password : ";
        cin>>password;
        sellers.push_back(Seller(username, password));
    }
    void registerBuyer() {
        string username, password;
        cout<<"Enter New Buyer User Name : ";
        cin>>username;
        cout<<"Enter Password : ";
        cin>>password;
        buyers.push_back(Buyer(username, password));
    }
    void sellerLogin() {
        string username, password;
        cout<<"Enter Seller User Name : ";
        cin>>username;
        cout<<"Enter Password : ";
        cin>>password;
        for(auto & s : sellers) {
            if(s.getUserName() == username) {
                if(s.getPassword() == password) {
                    cout<<"\nLogin Successful.....";
                    sellerProfile(&s);
                    break;
                }
            }
        }
    }
    void sellerProfile(Seller *s) {
        int ch;
        while(true) {
            cout<<"\n1. Add Product";
            cout<<"\n2. Delete Product";
            cout<<"\n3. View Product";
            cout<<"\n4.Logout";
            cout<<"\nEnter your choice : ";
            cin>>ch;
            switch (ch) {
                case 1: {
                    s->addProduct();
                    break;
                }
                case 2: {
                    s->deleteProduct();
                    break;
                }
                case 3: {
                    s->viewProduct();
                    break;
                }
                case 4: {
                    run();
                    break;
                }
            }
        }
    }
    void buyerLogin() {
        string username, password;
        cout<<"Enter Seller User Name : ";
        cin>>username;
        cout<<"Enter Password : ";
        cin>>password;
        for(auto & b : buyers) {
            if(b.getUserName() == username) {
                if(b.getPassword() == password) {
                    cout<<"\nLogin Successful.....";
                    buyerProfile(&b);
                    break;
                }
            }
        }
    }
    void buyerProfile(Buyer *b) {
        int ch;
        while(true) {
            cout<<"\n1. List Inventory \n";
            cout<<"2. Add Items to Cart \n";
            cout<<"3. View Cart \n";
            cout<<"4. View Orders \n";
            cout<<"4. Logout \n";
            while (true) {
                cout<<"\nEnter your choice : ";
                cin>>ch;
                if(cin.fail()) {
                     cin.clear();
                     cout<<"Enter input as integer....";
                }
                else {
                    break;
                }
            }
            switch (ch) {
                case 1 : {
                    listInventory();
                    break;
                }
                case 2: {
                    int pId, qty;
                    while (true) {
                        cout<<"\nSelect Product ID : ";
                        cin>>pId;
                        if(cin.fail()) {
                            cin.clear();
                            cout<<"Enter input as integer....";
                        }
                        else {
                            break;
                        }
                    }
                    while (true) {
                        cout<<"\nEnter No of Quantity : ";
                        cin>>qty;
                        if(cin.fail()) {
                            cin.clear();
                            cout<<"Enter input as integer....";
                        }
                        else {
                            break;
                        }
                    }
                    for(auto & s : sellers) {
                        for(auto & product : s.products) {
                            if(product.id == pId) {
                                if(product.quantity >= qty) {
                                    Product p = product;
                                    p.quantity = qty;
                                    p.price = qty * product.price;
                                    b->cart.push_back(p);
                                    cout<<"\nAdded to Cart Successfully";
                                    break;
                                }
                                else {
                                    cout<<"\nProduct Quantity is less than your required quantity";
                                    break;
                                }
                            }
                        }
                    }
                    cout<<"\nProduct ID is wrong...";
                    break;
                }
                case 3: {
                    cout<<"\n CART DETAILS...\n";
                    cout<<setw(15)<<"ProductID"<<setw(20)<<"ProductName"<<setw(20)<<"ProductType"<<setw(20)<<"ProductPrice"<<setw(22)<<"ProductQuantity\n";
                        for(auto & product : b->cart) {
                            cout<<setw(15)<<product.id<<setw(20)<<product.productName<<setw(20)<<product.productType<<setw(20)<<product.price<<setw(22)<<product.quantity;
                            cout<<endl;
                        }

                    int c;
                    cout<<"\nDo you want to proceed to buy these itmes?";
                    cout<<"\n1. Buy";
                    cout<<"\n2. Go Back";
                    while (true) {
                        cout<<"\nEnter your choice: ";
                        cin>>c;
                        if(cin.fail()) {
                            cout<<"Enter a Interger";
                            cin.clear();
                        }
                        else {
                            break;
                        }
                    }
                    if(c == 1) {
                        for(auto &p : b->cart) {
                            int pId = p.id;
                            for(auto & s : sellers) {
                                for(auto & product : s.products) {
                                    if(product.id == pId) {
                                        product.quantity -= p.quantity;
                                        b->orders.push_back(p);
                                        break;
                                    }
                                }
                            }
                            b->cart.clear();
                        }
                    }
                    break;
                }
                case 4: {
                    b->viewOrders();
                    break;
                }
                default:
                    return;
            }
        }
    }
    void listInventory() {
        cout<<setw(15)<<"ProductID"<<setw(20)<<"ProductName"<<setw(20)<<"ProductType"<<setw(20)<<"ProductPrice"<<setw(22)<<"ProductQuantity\n";
        for(auto & s : sellers) {
            for(auto & product : s.products) {
                cout<<setw(15)<<product.id<<setw(20)<<product.productName<<setw(20)<<product.productType<<setw(20)<<product.price<<setw(22)<<product.quantity;
                cout<<endl;
            }
        }
    }

    void run() {
        while(true) {
            int choice;
            cout<<"\n1. Register as a Seller  \n";
            cout<<"2. Register as a Buyer  \n";
            cout<<"3. Login as a Seller  \n";
            cout<<"4. Login as a Buyer \n";
            cout<<"5. Exit the application \n";
            cout<<endl;
            while(true) {
                cout<<"\nEnter Your Choice : ";
                cin>>choice;
                if(cin.fail()) {
                    cin.clear();
                    cout<<"....Please Enter a Integer....\n";
                }
                else {
                    break;
                }
            }
            switch (choice) {
                case 1: {
                    registerSeller();
                    break;
                }
                case 2: {
                    registerBuyer();
                    break;
                }
                case 3: {
                    sellerLogin();
                    break;
                }
                case 4: {
                    buyerLogin();
                    break;
                }
                case 5:
                    exit(0);
                default:
                    run();
            }
        }
    }
};

int main() {
    InventoryManagement obj;
    obj.run();
    return 0;
}
