#include "StoreClerk.h"

StoreClerk::StoreClerk()
{

}


void StoreClerkUI::store_menu(bool run) {

    system("CLS");

    cout << "----Store portal----" << endl;
    cout << "(N) New order" << endl;
    cout << "(A) See all orders in progress" << endl;
    cout << "(M) See all pizzas on menu" << endl;
    cout << "(T) See all toppings" << endl;
    cout << "(P) Mark orders paid/picked up" << endl;
    cout << "(L) See all old orders today" << endl;
    cout << "(B) Go back to login portal" << endl;
    cout << "(q) Quit" << endl;
    if(run){
        cout << "Incorrect input!" << endl;
    }
    cout << ": ";

    cin >> select;
    select = lower(select);

    switch (select) {
    case 'n':
        system("CLS");
        cout << "New order" << endl;
        system("PAUSE");
        store_status_menu(0);
        break;

    case 'a':
        system("CLS");
        cout << "See all orders" << endl;
        system("PAUSE");
        store_status_menu(0);
        break;

    case 'm':
        system("CLS");
        cout <<  "See all pizzas on menu" << endl;
        system("PAUSE");
        store_status_menu(0);
        break;

    case 't':
        system("CLS");
        handler.print_toppings();
        system("PAUSE");
        store_status_menu(0);
        break;

    case 'l':
        system("CLS");
        cout <<  "See everything ordered today" << endl;
        system("PAUSE");
        store_status_menu(0);
        break;

    case 'p':
        system("CLS");
        cout <<  "Mark orders paid or picked up" << endl;
        system("PAUSE");
        store_status_menu(0);
        break;

    case 'b':
        lUI.login_portal(0);
        break;

    default:
        phone_menu(1);
        break;
    }
}

