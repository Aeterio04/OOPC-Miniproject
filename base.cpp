#include <iostream>
#include <cstring>

using namespace std;

class user{
    
    private:
    string email;
    string pass;

    public:

    void enteremail(string e){
        email=e;
    }

    
    void enterpass(string p){
        pass=p;
    }

    virtual void signup()=0;
    virtual void login()=0;

};

class customer: private user{
    
    void signup(){
        string temp1,temp2;
        cout<<"Enter Your email";
        cin>>temp1;
        enteremail(temp1);
        cout<<"Enter Your Password:";
        cin>>temp1;
        cout<<"Re-Enter Your Password:";
        cin>>temp2;
        if( temp1 == temp2){
            enterpass(temp1);
        }
        else{
            cerr<<"Passwords Do Not Match";
            signup();
        }

    }

    void login(){

    }

};
