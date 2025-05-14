#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

class ShopperStop
{
public:
    // this class has all the databases persay, all the static vectors to store the data
    static vector<string> usernames;
    static vector<string> password;
    static vector<string> email;
    static vector<int> superuserstat;
    static vector<int> cartID;
public:
    // along with that it also acts as a abstract class, creating layouts for the auth class
    virtual int checksignupentry(string input_email, string input_username, string input_pass) = 0;
    virtual int verifyloginentry(string input_email, string input_pass) = 0;
};
vector<string> ShopperStop::usernames = {"admin"};
vector<string> ShopperStop::password = {"SuperIsHere"};
vector<string> ShopperStop::email = {"admin1711@gmail.com"};
vector<int> ShopperStop::superuserstat = {1};


class Auth : public ShopperStop
{
    // heavy lifting class
public:
    int checksignupentry(string input_email, string input_username, string input_pass)
    {
        int size = ShopperStop::email.size();
        // Checking if email is repeated
        for (int i = 0; i < size; i++)
        {
            if (email[i] == input_email)
            {
                cout << "You account already exists\n";
                // break the complete function and return 0
                return 0;
            }
            else
            {
                // check the next entry
                continue;
            }
        }
        // if the email is not repeated, check if username is repeated
        for (int i = 0; i < size; i++)
        {
            if (usernames[i] == input_username)
            {
                cout << "You username is already taken\n";
                break;
            }
            else
            {
                continue;
            }
        }
        // if this line is accessed, it means that bothe username and email are available, at this point push the user into the vector
        usernames.push_back(input_username);
        password.push_back(input_pass);
        email.push_back(input_email);
        superuserstat.push_back(0);


        return 1;
        // as all are pushed together the user will have all the data stored at the same index at every vector, kindoff like a triple hashed map
    }
    int verifyloginentry(string input_email, string input_pass)
    {
        // this function is meant to recieve input email and password, verify if any such entry exists in the vector database and based on
        // what it gets, it will either return a 0 or the index at which his information is stored

        int size = ShopperStop::email.size();
        // Checking if email present
        for (int i = 0; i < size; i++)
        {
            if (email[i] == input_email)
            {
                if (password[i] == input_pass)
                {
                    cout << "Login successful ! ";
                    cout << "Welcome " << usernames[i] << endl;
                    return i;
                }
            }
            else
            {
                // check the next entry
                continue;
            }
        }
        // if program makes it here, then it has searched all the entries for a matching email, hasnt found a hit and will therefore return 0
        cout << "Your Login Info was Incorrect, please enter again\n";
        return -1;
    }
};
struct Product
{   public:
    string name;
    int code;
    float price;
    
    Product()
    {
        name = " ";
        code = -1;
        price = 0;
    }

    Product(string n, int c, float p)
    {
        name = n;
        code = c;
        price = p;
    }

    void input()
    {
        cout << "Enter item1: ";
        cin >> name;
        cout << "Enter item code1: ";
        cin >> code;
        cout << "Enter item price1: ";
        cin >> price;
    }

    void display() const
    {
        cout << "- " << name << " | Code: " << code <<  " | Price: " << price << endl;
    }

    void display2() const
    {
        cout << "- " << name << " | Code: " << code <<  " | Price: " << price << endl;
    }
};

class Shop
{
private:
    vector<Product> electronics;
    vector<Product> clothing;
    vector<Product> toys;

public:
    void Electronics()
    {
        int n;
        Product p;
        cout << "\nEnter how many Electronics Products: ";
        cin >> n;
        electronics.clear();
        for (int i = 0; i < n; i++)
        {
            cout << "Enter item: ";
            cin >> p.name;
            cout << "Enter item code: ";
            cin >> p.code;
            cout << "Enter item Price: ";
            cin >> p.price;
            electronics.push_back(p);
        }
    }

    void Clothing()
    {
        int n;
        Product p;
        cout << "\nEnter how many Clothing Products: ";
        cin >> n;
        clothing.clear();
        for (int i = 0; i < n; i++)
        {
            cout << "Enter item: ";
            cin >> p.name;
            cout << "Enter item code: ";
            cin >> p.code;
            cout << "Enter item Price: ";
            cin >> p.price;
            clothing.push_back(p);
        }
    }

    void Toys()
    {
        int n;
        Product p;
        cout << "\nEnter how many Toy Products: ";
        cin >> n;
        toys.clear();
        for (int i = 0; i < n; i++)
        {
            cout << "Enter item: ";
            cin >> p.name;
            cout << "Enter item code: ";
            cin >> p.code;
            cout << "Enter item Price: ";
            cin >> p.price;
            toys.push_back(p);
        }
    }

    void display()
    {
        cout << "\nItems in the Store:\n";
        cout << "-------------------\nElectronics:\n";
        for (const auto &item : electronics)
            cout << "- " << item.name << " " << "Code " << item.code << "Price " << item.price << endl;

        cout << "-------------------\nClothing:\n";
        for (const auto &item : clothing)
            cout << "- " << item.name << " " << "Code " << item.code << "Price " << item.price << endl;

        cout << "-------------------\nToys:\n";
        for (const auto &item : toys)
            cout << "- " << item.name << " " << "Code " << item.code << "Price " << item.price <<endl;
        cout << "-------------------\n";
    }

    Product findProduct(int code)
    {

        for (auto &item : electronics)
        {
            if (item.code == code)
            {
                return item;
            }
        }
        for (auto &item : clothing)
        {
            if (item.code == code)
            {
                return item;
            }
        }
        for (auto &item : toys)
        {
            if (item.code == code)
            {
                return item;
            }
        }
        return Product("Invalid", -1 ,0);
    }
};

class superuser : public Auth
{
    // class specifically for superuser capabilities
    // no data required
public:
    void show_data()
    {
        cout << left
             << setw(6) << "UserId"
             << setw(15) << "Username"
             << setw(25) << "Email"
             << right << setw(10) << "Admin" << endl;
        // Data rows
        for (int i = 0; i < usernames.size(); ++i)
        {
            cout << left
                 << setw(6) << i
                 << setw(15) << usernames[i]
                 << setw(25) << email[i]
                 << right << setw(10) << showpoint << superuserstat[i] << endl;
        }
    }
    void fill_store(Shop &S)
    {
        int category;
        cout << "\n Enter Category of Product=\n";
        cout << "1 : Electronics\n";
        cout << "2 : Clothing\n";
        cout << "3 : Toys\n";
        cin >> category;

        switch (category)
        {
        case 1:
            S.Electronics();
            break;
        case 2:
            S.Clothing();
            break;
        case 3:
            S.Toys();
            break;
        default:
            cout << "Product out of Stock";
        }
        S.display();
    }
};
class user
{
    // the connection is made here as superuser is also a type of user
private:
    string email;
    string pass;
    string username;
    int superuserstatus = 0;

public:
    void enteremail(string e)
    {
        email = e;
    }

    void enterpass(string p)
    {
        pass = p;
    }

    void enterusername(string u)
    {
        username = u;
    }

    string put_email()
    {
        return email;
    }
    string put_pass()
    {
        return pass;
    }
    string put_username()
    {
        return username;
    }
};
class store_actions{
    private:
    vector<Product> cart;
    

    public:
    void browse_store(Shop &S)
    {
        cout << "\n WELCOME TO SHOPERSTOP!!!!.....";
        S.display();
    }

    void add_To_Cart(Shop &store, int code)
    {
        Product product = store.findProduct(code);
        if (product.code != -1)
        {
            cart.push_back(product);
            cout << product.name << "Successfully Added to Cart!!\n";
        }
        else
        {
            cout << "Product with Code " << code << " not found.\n";
        }
    }

    void viewCart()
    {
        cout << "\n--- Your Cart ---\n";
        if (cart.empty())
        {
            cout << "Cart is empty.\n";
        }
        else
        {
            for (const auto &item : cart)
                item.display();
        }
        cout << "------------------\n";
    }

};

class transaction:public Auth {
    public:
    vector<Product> purchase;
    float total_amount;
    int transaction;
    float remaining_balance;


    void purchase_code(Shop &store , int buy ,float wallet)
    {
        Product product2 = store.findProduct(buy);
        if(product2.code != -1)
        {
            if(wallet >= product2.price){
                purchase.push_back(product2);
                total_amount = total_amount + product2.price;
                cout<< product2.name << "Successfully Added to Purchase!!\n";
            }
            else {
                cout<<"\n Not enough Balance in wallet";
            }
            cout<<"\n Total Amount = "<<total_amount;
            
        }
        else
        {
            cout << "Product with Code " << buy << " not found.\n";
        }

    }

    void viewPurchase(float wallet)
    {
        cout << "\n--- Your Purchase ---\n";
        cout<<"\n Total_amount to be paid ="<<total_amount;

        if (purchase.empty())
        {
            cout << "No Purchase.\n";
        }
        else
        {
            for (const auto &item2 : purchase)
                item2.display2();
        }

        cout<< "\n Enter 1 to carry out the transaction=";
        cin>>transaction;

        if(transaction == 1) {
            cout<<"\n Payment Successful !!! Visit Again...";
            remaining_balance = wallet - total_amount ;

        }
        else {
            cout <<"\n Payment Denied";
        }

        cout << "------------------\n";
    }

    float current(){
        cout<<"\n Current Balance =";
        return total_amount;
    }

    void setcredit(float *walletaddress, int userid){

        cout<<"Verify Your Identity\n";
        string temp1, temp2;
        cout << "Enter Your email: ";
        cin >> temp1;
        cout << "Enter Your Password: ";
        cin >> temp2;
        int useridtemp=verifyloginentry(temp1,temp2);
        cout<<useridtemp<<" "<<userid;

        if(useridtemp==userid){
            cout<<"Your Account has been Verified.\n What is the Sum you will like to add to our store credit? : ";
            cin>> *walletaddress;
            cout<<"Your Digital wallet has been credited with "<<*walletaddress<<" store credits";
        }
        else{
            cout<<"Your login attempt was unsuccessful, please try again";
            return;
        }

        

    }
};

class customer : public user, public store_actions,public transaction
{
public:
    void signup()
    {
        string temp1, temp2;
        cout << "Enter Your email: ";
        cin >> temp1;
        enteremail(temp1);

        cout << "Enter Your Password:";
        cin >> temp1;
        enterpass(temp1);

        cout << "Enter Your Username: ";
        cin >> temp1;
        enterusername(temp1);

        checksignupentry(put_email(), put_username(), put_pass());
    }

    int login()
    {
        string temp1, temp2;
        cout << "Enter Your email: ";
        cin >> temp1;
        enteremail(temp1);

        cout << "Enter Your Password: ";
        cin >> temp1;
        enterpass(temp1);

        return verifyloginentry(put_email(), put_pass());
    }
    
};


class System : public superuser,public transaction
{
private:
    int userid = -1;

public:
    void run()
    {
        int wish;
        int choice;
        int code;
        int buy;
        float money;
        vector<float> wallet={100};
        int process_payment;
        customer c0;
        vector<customer> c={c0};
        
        Shop mainstore;

        while (choice != 3)
        {
            
            if (userid == -1)
            {
                cout << "====== MENU ======\n";
                cout << "1. Login\n";
                cout << "2. Signup\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    userid = c0.login();
                    break;
                case 2:
                    {c0.signup();
                    customer ctemp;
                    c.push_back(ctemp);
                    wallet.push_back(0);
                    break;}
                case 3:
                    cout << "Exiting...\n";
                    continue;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            }
            else
            {
                if (superuserstat[userid] == 0)
                {
                    cout << "\n===== SHOP MENU =====\n";
                    
                    cout << "1. View Items\n";
                    cout << "2. View Cart\n";
                    cout << "3. Add to Cart\n";
                    cout << "4. Credit Balance\n";
                    cout << "5. Current Balance\n";
                    cout << "6. Purchase\n";
                    cout << "7. View Purchase\n";
                    cout << "8. Logout\n";
                    
                    cout << "Enter your choice: ";
                    cin >> wish;

                    switch (wish)
                    {
                    case 1:
                        mainstore.display();
                        break;
                    case 2:
                        c[userid].viewCart();
                        break;
                    case 3:
                        cout << "Enter product code to add: ";
                        cin >> code;
                        c[userid].add_To_Cart(mainstore, code);
                        break;
                    case 4:
                    {
                        float *tempptr= &wallet[userid];
                        c[userid].setcredit(tempptr,userid);
                        break;}
                    case 5:
                        money = c[userid].current();
                        cout<<"\n Current Balance in wallet ="<<money;
                        break;
                    case 6:
                        cout << "Enter codes of Items to Buy :\n";
                        cin>>buy;
                        c[userid].purchase_code(mainstore,buy,wallet[userid]);
                        break;
                    case 7:
                        c[userid].viewPurchase(wallet[userid]);
                        break;
                        
                    case 8:
                        cout << "Logging out...\n\n";
                        userid = -1;
                        break; 
                    default:
                        cout << "Invalid choice. Try again.\n\n";
                    }
                }
                else
                {
                    if (superuserstat[userid] == 1 && (userid!=-1))
                    {
                        cout << "===== SUPERUSER PANEL =====\n";
                        cout << "1. View All Users\n";
                        cout << "2. Fill Store\n";
                        cout << "3. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> wish;

                        switch (wish)
                        {
                        case 1:
                            show_data();
                            break;
                        case 2:
                            fill_store(mainstore);
                            break;
                        case 3:
                            cout << "Superuser logged out.\n\n";
                            userid = -1;
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n\n";
                        }
                    }
                }
            }
        }
    }
};

int main()
{
    System s;
    s.run();


}
