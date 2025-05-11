#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>


using namespace std;


class ShopperStop{
    public:
    // this class has all the databases persay, all the static vectors to store the data
    static vector<string> usernames;
    static vector<string> password;
    static vector<string> email;
    static vector<int> superuserstat;

    public:
    // along with that it also acts as a abstract class, creating layouts for the auth class
    virtual int checksignupentry(string input_email, string input_username, string input_pass)=0;
    virtual int verifyloginentry(string input_email, string input_pass)=0;

};
vector<string> ShopperStop::usernames={"admin"};
vector<string> ShopperStop::password={"SuperIsHere"};
vector<string> ShopperStop::email={"admin1711@gmail.com"};
vector<int> ShopperStop::superuserstat={1};
    
class Auth:public ShopperStop{
    // heavy lifting class
    public:
    int checksignupentry(string input_email, string input_username, string input_pass){
        int size = ShopperStop::email.size();
        //Checking if email is repeated
        for (int i=0;i<size;i++){
            if( email[i]==input_email){
                cout<<"You account already exists";
                //break the complete function and return 0
                return 0;
            }
            else{
                //check the next entry
                continue;                
            } 
        }
        //if the email is not repeated, check if username is repeated
        for (int i=0;i<size;i++){
            if( usernames[i]==input_username){
                cout<<"You username is already taken";
                break;
            }
            else{
                continue;                
            } 
        }
        //if this line is accessed, it means that bothe username and email are available, at this point push the user into the vector
        usernames.push_back(input_username);
        password.push_back(input_pass);
        email.push_back(input_email);
        superuserstat.push_back(0);
        
        return 1;
        //as all are pushed together the user will have all the data stored at the same index at every vector, kindoff like a triple hashed map


    }
    int verifyloginentry(string input_email, string input_pass){
        //this function is meant to recieve input email and password, verify if any such entry exists in the vector database and based on
        //what it gets, it will either return a 0 or the index at which his information is stored

        int size = ShopperStop::email.size();
        //Checking if email present
        for (int i=0;i<size;i++){
            if( email[i]==input_email){
                if(password[i]==input_pass){
                    cout<<"Login successful ! ";
                    cout<<"Welcome "<<usernames[i]<<endl;
                    return i;
                }
                
            }
            else{
                //check the next entry
                continue;                
            } 
        }        
        //if program makes it here, then it has searched all the entries for a matching email, hasnt found a hit and will therefore return 0
        return 0;
    }
};

class superuser:public Auth{
    //class specifically for superuser capabilities
    //no data required
    public:
    void show_data(){
        cout << left
         << setw(6) << "UserId"
         << setw(15) << "Username"
         << setw(25) << "Email"
         << right << setw(10) << "Admin" << endl;
    // Data rows
    for (int i = 0; i < usernames.size(); ++i) {
        cout << left
             << setw(6) << i
             << setw(15) << usernames[i]
             << setw(25) << email[i]
             << right << setw(10) << showpoint << superuserstat[i]<< endl;  
    }
    }
};
class user{
    //the connection is made here as superuser is also a type of user
    private:
    string email;
    string pass;
    string username;
    int superuserstatus=0;

    public:

    void enteremail(string e){
        email=e;
    }

    
    void enterpass(string p){
        pass=p;
    }

    void enterusername(string u){
        username=u;
    }

    string put_email(){
        return email;
    }
    string put_pass(){
        return pass;
    }  
    string put_username(){
        return username;
    }


};

class customer: public user,public Auth{
    public:
    void signup(){
        string temp1,temp2;
        cout<<"Enter Your email: ";
        cin>>temp1;
        enteremail(temp1);

        cout<<"Enter Your Password:";
        cin>>temp1;
        enterpass(temp1);

        cout<<"Enter Your Username: ";
        cin>>temp1;
        enterusername(temp1);

        checksignupentry(put_email(),put_username(),put_pass());
    

    }

    int login(){
        string temp1,temp2;
        cout<<"Enter Your email: ";
        cin>>temp1;
        enteremail(temp1);

        cout<<"Enter Your Password: ";
        cin>>temp1;
        enterpass(temp1);

        return verifyloginentry(put_email(),put_pass());
    }

};

class System: public customer,public superuser{
    private:
    int userid=-1;

    public:
    void run(){
        int choice;
        customer c;
        while (choice!=3 ) {
            if( userid==-1){
                cout << "====== MENU ======\n";
                cout << "1. Login\n";
                cout << "2. Signup\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        userid=c.login();
                        break;
                    case 2:
                        c.signup();
                        break;
                    case 3:
                        cout << "Exiting...\n";
                        continue;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            }
            else{
                if(superuserstat[userid]==0){
                cout << "===== SHOP MENU =====\n";
                cout << "1. View Items\n";
                cout << "2. View Cart\n";
                cout << "3. Previous Orders\n";
                cout << "4. Current Balance\n";
                cout << "5. Logout\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout<<"Showing Items\n";
                        break;
                    case 2:
                        cout<<"Showing Cart\n";
                        break;
                    case 3:
                        cout<<"Showing Previous Orders\n";
                        break;
                    case 4:
                        cout<<"Showing current balance\n";
                        break;
                    case 5:
                        cout << "Logging out...\n\n";
                        userid=-1;
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n\n";
                }}
                else{
                while (true) {
                cout << "===== SUPERUSER PANEL =====\n";
                cout << "1. View All Users\n";
                cout << "2. Logout\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        show_data();
                        break;
                    case 2:
                        cout << "Superuser logged out.\n\n";
                        userid=-1;
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

int main(){
    System s;
    s.run();
}
