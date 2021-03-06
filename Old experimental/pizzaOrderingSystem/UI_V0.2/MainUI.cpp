#include "MainUI.h"
#include <iostream>
#include "ManagerUI.h"

using namespace std;

    ManagerUI manager("Menu:", "Pizza information", "Toppings", "Pizza size", "Make a new pizza");
    ManagerUI topping_menu("Toppings:", "Add toppings", "Remove toppings", "See all toppings");
    ManagerUI info_menu("Info:", "Toppings", "Pizzas", "Pizza sizes");
    ManagerUI new_pizza_menu("Create a new pizza:", "Create pizza", "Remove pizza", "See all pizas");
    //UI var. for Manager
    ManagerUI baker_menu("Baker:", "Toggle in oven", "Toggle ready");
    //Baker UI
    ManagerUI phone_status_menu("Get status of:", "Current orders", "Pizzas", "Toppings");
    ManagerUI phone_menu("Phone orders: ", "New order", "Get all orders", "status");
    //Telephone clerk
    ManagerUI clerk_order_menu("Orders:", "Option A", "Option B", "Option C");
    ManagerUI clerk_status_menu("Get status of:", "Current orders", "Pizzas", "Toppings");
    ManagerUI clerk_menu("Salesman orders: ", "New order", "Get all orders", "status", "Order details");
    //Sales clerk
    //global decl. of UI elements

MainUI::MainUI()
{
    run = 0;
}

void MainUI::print_selector(bool run) {
    system("CLS");

    char selector = ' ';

    cout << "Welcome to pizza & co." << endl << endl;

    cout << "----LOGIN SELECTOR----" << endl;
    cout << "(m) Manager" << endl;
    cout << "(b) Baker" << endl;
    cout << "(t) Telephone operator" << endl;
    cout << "(s) Sales clerk" << endl;
    cout << "(q) Quit" << endl;
    if(run){
        cout << "Incorrect input!" << endl;
    }
    cout << ": ";

    cin >> selector;
    selector = lower(selector);

    switch(selector) {
    case 'm':
            manager_selector(selector);
            ///The manager selection UI page
        break;
    case 'b':
            baker_ui();
            ///The baker menu page
        break;
    case 't':
        system("CLS");
        phone_selector(selector);
        break;
    case 's':
        system("CLS");
        clerk_selector(selector);
        system("PAUSE");
        break;
    case 'q':
        terminate();
        break;
    default:
        system("CLS");
        print_selector(1);
        break;
    }

}

char MainUI::lower(char instring) {
    StdInput s;
    instring = s.to_lower_case(instring);
    return instring;
}

void MainUI::terminate(){
    system("CLS");
    char cont;

    cout << "Are you sure you want to quit (y/n)? ";
        cin >> cont;
        cont = lower(cont);

    if(cont == 'y'){
        cout << "Good Bye!" << endl;
        exit(0);
    }
    print_selector(0);
    //Double check if user wants to quit, else runs the
    //manager UI again
}

void MainUI::manager_selector(bool selectorn) {
    ret_val = manager.menuUI(0);

    if(ret_val == 99) {
        print_selector(0);
        ///Returns to User selector

    } else if(ret_val == 1) {
        ret_val = info_menu.menuUI(0);
        info_creator(ret_val);
        ///To pizza info menu

    } else if(ret_val == 2) {
        ret_val = topping_menu.menuUI(0);
        topping_creator(ret_val);
        ///To topping menu

    } else if(ret_val == 3) {
        ///To size menu

    } else if(ret_val == 4) {
        ret_val = new_pizza_menu.menuUI(0);
        pizza_creator(ret_val);
        ///To create a new pizza menu
    }


}

void MainUI::info_creator(int ret_val) {
    if(ret_val == 99) {
        manager_selector(0);
        //Go one level up, to manager menu
    } else if(ret_val == 1) {
        cout << "Print toppings: " << endl;
        system("CLS");
        handler.print_toppings();
        system("PAUSE");
        manager_selector(0);
        //print all toppings
    } else if(ret_val == 2) {
        system("CLS");
        cout << "Print all pizzas: " << endl;
        system("PAUSE");
        manager_selector(0);
        //print all pizza sizes
    } else if(ret_val == 3) {
        system("CLS");
        cout << "Print all pizza sizes: " << endl;
        system("PAUSE");
        manager_selector(0);
        //print all pre-made pizzas
}
}

void MainUI::topping_creator(int ret_val) {
    char cont = 0;
    if(ret_val == 99) {
        manager_selector(0);
        //Go one level up, to manager menu
    } else if(ret_val == 1) {
        cout << "Add toppings" << endl;
        do{
            handler.create_topping();
            do{
                cout << "Do you want to input more Toppings (y/n)? ";
                cin >> cont;
                cont = lower(cont);
            } while(cont == 'y' && cont == 'n');
        } while(cont == 'y');
        manager_selector(0);
        //Add toppings
    } else if(ret_val == 2) {
        system("CLS");
        cout << "remove toppings" << endl;
        system("PAUSE");
        manager_selector(0);
        //remove toppings
    } else if(ret_val == 3) {
        system("CLS");
        cout << "All toppings" << endl;
        handler.print_toppings();
        system("PAUSE");
        manager_selector(0);
        //see all toppings
    }
}

void MainUI::pizza_creator(int ret_val) {
    if(ret_val == 99) {
        manager_selector(0);
        //Go one level up, to manager menu
    } else if(ret_val == 1) {
        system("CLS");
        cout << "Create a new pizza: Missing handler" << endl;
        system("PAUSE");
        manager_selector(0);
        //Add toppings
    } else if(ret_val == 2) {
        system("CLS");
        cout << "Remove an old pizza: Missing handler";
        system("PAUSE");
        //remove toppings
    } else if(ret_val == 3) {
        system("CLS");
        cout << "See all pizzas: Missing handler" << endl;
        system("PAUSE");
        manager_selector(0);
        //see all toppings
    }
}

void MainUI::baker_ui(){
    char cont;
    system("CLS");

    cout << "Print out list of pizzas her" << endl;

    ret_val = baker_menu.menuUI(0);

    if(ret_val == 99) {
        print_selector(0);
        ///Returns to User selector

    } else if(ret_val == 1) {
        ///MISSING FUNCTION CALLS
        do{
            do{
                system("CLS");
                cout << "Print out list of pizzas her" << endl;
                cout << "Do you want to toggle another pizza in oven (y/n)? ";
                cin >> cont;
                cont = lower(cont);
            } while(cont == 'y' && cont == 'n');
        } while(cont == 'y');
        baker_ui();
        ///Toggle in oven

    } else if(ret_val == 2) {
        ///MISSING FUNCTION CALLS
        do{
            do{
                system("CLS");
                cout << "Print out list of pizzas her" << endl;
                cout << "Do you want to toggle more pizzas ready (y/n)? ";
                cin >> cont;
                cont = lower(cont);
            } while(cont == 'y' && cont == 'n');
        } while(cont == 'y');

        baker_ui();
        ///Toggle ready
    }
}


void MainUI::phone_selector(bool selector) {
    ret_val = phone_menu.menuUI(0);

    if(ret_val == 99) {
        print_selector(0);
        ///Returns to User selector

    } else if(ret_val == 1) {
        cout << "New order function" << endl;
        system("PAUSE");
        phone_selector(1);
        ///New order menu

    } else if(ret_val == 2) {
        cout << "Get all current orders" << endl;
        system("PAUSE");
        phone_selector(0);
        ///To topping menu

    } else if(ret_val == 3) {
        ret_val = phone_status_menu.menuUI(0);
        phone_status_ui(ret_val);
        phone_selector(0);
        ///To size menu
    }

}

void MainUI::phone_status_ui(int ret_val) {
    if(ret_val == 99) {
        phone_selector(0);
        //Go one level up, to manager menu
    } else if(ret_val == 1) {
        system("CLS");
        cout << "Current orders: missing function call" << endl;
        system("PAUSE");
        phone_status_ui(0);
        //Add toppings
    } else if(ret_val == 2) {
        system("CLS");
        cout << "Pizza list: missing function call" << endl;
        system("PAUSE");
        phone_status_ui(0);
        //remove toppings
    } else if(ret_val == 3) {
        system("CLS");
        cout << "Topping list: missing function call" << endl;
        system("PAUSE");
        phone_status_ui(0);
        //see all toppings
    }
}

void MainUI::clerk_selector(bool selector) {
    ret_val = clerk_menu.menuUI(0);

    if(ret_val == 99) {
        print_selector(0);
        ///Returns to User selector

    } else if(ret_val == 1) {
        cout << "New order function" << endl;
        system("PAUSE");
        clerk_selector(1);
        ///New order menu

    } else if(ret_val == 2) {
        cout << "Get all current orders" << endl;
        system("PAUSE");
        clerk_selector(0);
        ///To topping menu

    } else if(ret_val == 3) {
        ret_val = clerk_order_menu.menuUI(0);
        clerk_status_ui(ret_val);
        clerk_selector(0);
        ///To order completion menu

    } else if(ret_val == 4) {
        ret_val = clerk_status_menu.menuUI(0);
        clerk_status_ui(ret_val);
        clerk_selector(0);
        ///To size menu
    }

}

void MainUI::clerk_status_ui(int ret_val) {
    if(ret_val == 99) {
        clerk_selector(0);
        //Go one level up, to manager menu
    } else if(ret_val == 1) {
        system("CLS");
        cout << "Current orders: missing function call" << endl;
        system("PAUSE");
        clerk_status_ui(0);
        //Add toppings
    } else if(ret_val == 2) {
        system("CLS");
        cout << "Pizza list: missing function call" << endl;
        system("PAUSE");
        clerk_status_ui(0);
        //remove toppings
    } else if(ret_val == 3) {
        system("CLS");
        cout << "Topping list: missing function call" << endl;
        system("PAUSE");
        clerk_status_ui(0);
        //see all toppings
    }
}

