/*
        adaptor_structural_dp.cpp

Adaptor DP? Converts the interface of a class into another interface the client expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

This Example:
        FlatPinPlug want to interact with roundSwitchBoard.
        We need adapter in between.

How it works? Adapter will have pointer to object of target class.
- Please see UML for complete understanding

                Plug    //Abstract-class                switchBoard//Abstract Class
                /\ /\                                   /\      /\
                |   |                                   --      |
 ---------------    -------------------   ---------------       --------
|Genralization          Genralization |   |Aggregation                  |Genralization
|                                     |   |                             |
flatPinPlug                          Adapter                            flatSwitchBoard
*/


#include<iostream>
using namespace std;

class Plug{             //ABSRACT CLASS
public:
        void virtual plug_fun()=0;
};

class flatPinPlug : public Plug{
public:
        void plug_fun(){
                cout<<"Inside flatPin class\n";
        }
};

class switchBoard {     //ABSTRACT CLASS
public:
  void virtual switchBoard_fun()=0;
};

class roundSwitchBoard : public switchBoard {   //CONCREATE CLASS
public:
  void switchBoard_fun(){
          cout<<"Inside roundSwitchBoard class\n";
  }
};

class Adapter : public Plug {
public:
  switchBoard *sbObj;                   //Aggregation
  Adapter(switchBoard *t):sbObj(t){}
  void plug_fun(){
        cout<<"Adapter Taking signal from Plug and passing to Switchboard\n";
        sbObj->switchBoard_fun();
  }
};
// Client code

int main(){
  roundSwitchBoard *ptr = new roundSwitchBoard; // Adaptee
  // Target = Adapter(Adaptee)
  Plug *adapter = new Adapter(ptr);
  adapter->plug_fun();
}
/*
Output:
# ./a.out
Adapter Taking signal from Plug and passing to Switchboard
Inside roundSwitchBoard class
 */
