#ifndef PHONECLERKUI_H
#define PHONECLERKUI_H

//#include "LoginUI.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class PhoneClerkUI {
    public:
        PhoneClerkUI();
        int phone_menu(char run);
        char lower(char instr);
        void terminate();

    private:
        char select;
       // ToppingsHandler handler;
};

#endif // PHONECLERKUI_H
