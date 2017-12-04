#ifndef PHONECLERKUI_H
#define PHONECLERKUI_H

#include "LoginUI.h"



class PhoneClerkUI
{
    public:
        PhoneClerkUI();
        void phone_menu(bool run);
        char lower(char instr);
        void terminate();

    private:
        LoginUI lUI;
        bool select;
        ToppingsHandler handler;
};

#endif // PHONECLERKUI_H
