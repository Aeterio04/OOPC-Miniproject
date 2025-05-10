#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


class ShopperStop{
    public:
    // this class has all the databases persay, all the static vectors to store the data
    static vector<string> usernames;
    static vector<string> password;
    static vector<string> email;
    public:
    // along with that it also acts as a abstract class, creating layouts for the auth class
    virtual int checksignupentry(string input_email, string input_username, string input_pass)=0;
    virtual int verifyloginentry(string input_email, string input_pass)=0;

};
vector<string> ShopperStop::usernames;
vector<string> ShopperStop::password;
vector<string> ShopperStop::email;

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

class user{
    
    private:
    string email;
    string pass;
    string username;

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

class customer: private user,public Auth{
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

    void login(){
        string temp1,temp2;
        cout<<"Enter Your email: ";
        cin>>temp1;
        enteremail(temp1);

        cout<<"Enter Your Password: ";
        cin>>temp1;
        enterpass(temp1);

        verifyloginentry(put_email(),put_pass());
    }

};

int main(){
    customer c;
      int choice;
        while (choice!=3) {
            cout << "====== MENU ======\n";
            cout << "1. Login\n";
            cout << "2. Signup\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    c.login();
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
    }
