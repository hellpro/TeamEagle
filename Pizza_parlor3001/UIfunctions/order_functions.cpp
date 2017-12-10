#include "order_functions.h"

#include "ValidationFunctions.h"

void print_orders(Order_Status status) {

    OrderHandler orderhandler;
    int ordercount = orderhandler.get_order_count();

    Order temp_order;

    for (int i = 0; i < ordercount; i ++) {
       switch (status) {
            case delivered:
                 if (orderhandler.get_orders().at(i).delivered()) {

                     print_order(orderhandler.get_orders().at(i));
                 }
                 break;
            case not_delivered:
                 if (!orderhandler.get_orders().at(i).delivered()) {

                     print_order(orderhandler.get_orders().at(i));
                 }
                break;
            case all:
                print_order(orderhandler.get_orders().at(i));
                break;
        }
    }
}
bool new_order() {

    Order order;
    string select;
    bool cont = 1;

    OrderHandler orderhandler;
    orderhandler.generate_order_no(order);
    cout << "Order #" << order.get_order_number() << endl;

    add_pizzas(order);
    system("CLS");

    print_order(order);
    if (order.get_order_count() > 0) {
        do{
            try{
                cout << "Is this the correct order? (y/n) ";
                cin >> select;
                select = tolower(select[0]);
                validate_bool_question(select);
                cont = 0;
            }
            catch(InvalidBoolException e) {
                cont = 1;
                cout << e.get_err() << endl;
            }
        } while(cont);

        if (select == "y") {
            orderhandler.add_order(order);
            return false;
        } else {
            cout << "Order was not added" << endl;
                return true;

        }

    }
    return false;
}

void add_pizzas(Order& order) {

    OrderHandler orderhandler;
    PizzaType pizzatype;
    char run = '\0';


    pizzatype = menu_or_special(run);

    string run_menu;
    bool cont_menu = 1;
    bool cont = 1;
    if(run != 'b'){
        run = '\b';
        do {
            if (pizzatype == menu_pizza) {
                add_menu_pizza(order);

            }
            if (pizzatype == special_pizza) {
                add_special_pizza(order);
            }

            do{
                try{
                    cout << "Do you wish to add more pizzas to the order (y/n)? ";
                    cin >> run_menu;
                    run_menu = tolower(run_menu[0]);
                    validate_bool_question(run_menu);
                    cont = 0;
                    if(run_menu == "y") {
                        cont_menu = 1;
                    } else {
                        cont_menu = 0;
                    }
                }
                catch(InvalidBoolException e) {
                    cont = 1;
                    cout << e.get_err() << endl;
                }
            } while(cont);

        } while(cont_menu);
    }
}


PizzaType menu_or_special(char& run) {

    PizzaType pizzatype;

    bool quit = false;
    string type;
    bool cont;

    do {
        do{
            try{
                cout << "Input 'M' for menu pizza or 'C' for a custom pizza (B to go back): ";
                cin >> type;
                validate_char(type);
                cont = 0;
            }
            catch(InvalidCharException e) {
                cont = 1;
                cout << e.get_err() << endl;
            }
        } while(cont);

        type = tolower(type[0]);

        if (type == "m") {
            pizzatype = menu_pizza;
            quit = true;
        } else if (type == "c") {
            pizzatype = special_pizza;
            quit = true;
        } else if (type == "b") {
            run = 'b';
            quit = true;
        }

    } while (!quit && type != "b");
    return pizzatype;
}


void add_menu_pizza(Order& order) {
    Pizza pizza;
    PizzaHandler pizzahandler;

    bool cont = 0;
    string pizza_name;
    do{
        try{
            system("CLS");
            print_menu_pizza_list();
            cout << "Enter name of pizza: ";
            cin.ignore();
            getline(cin, pizza_name, '\n');
            validate_int_string(pizza_name);
            cont = 0;
            pizza = pizzahandler.get_menu_pizza(pizza_name);
            order.add_pizza(pizza);
        }
        catch(InvalidName) {
            cont = 1;
            cout << "Pizza not on menu!" << endl;
            pause_screen();
        }
        catch(InvalidAlphaNumException e) {
            cont = 1;
            cout << e.get_err() << endl;
            pause_screen();
        }

    }while(cont);

}

void toppings_to_special(Pizza& pizza) {

    PizzaHandler pizzahandler;
    ToppingsHandler toppingshandler;

    string topping_name = " ";
    cout << "Enter toppings, insert q when finished: ";
    cin >> topping_name;

    while (topping_name != "q") {
        try {
            pizza.add_topping(toppingshandler.get_topping(topping_name));
        }
        catch(InvalidName e) {
            cout << "Topping not on list!" << endl;
        }

        cout << "Enter next topping: ";
        cin >> topping_name;

        if (pizzahandler.max_toppings(pizza)) {
            cout << "Maximum topping has been reached." << endl;
            break;
        }
    }

}
void add_special_pizza(Order& order) {
    Pizza pizza;
    PizzaHandler pizzahandler;

    pizza.set_name("Special order");
    toppings_to_special(pizza);

    pizza.set_price(pizzahandler.calc_price(pizza));

    bool cont = 1;
    string input;

    do{
        try{
            print_pizza(pizza);
            cout << "Do you want to add this pizza to the order? (y/n) ";
            getline(cin, input, '\n');
            validate_bool_question(input);
            cont = 0;
        }
        catch(InvalidBoolException e) {
            cont = 1;
            cout << e.get_err() << endl;
        }
    } while(cont);
        order.add_pizza(pizza);

}

bool yes() {
    char input;
    cin >> input;
    if (input == 'y') {
        return true;
    }
    else if (input == 'n') {
        return false;
    }
        cout << "Please select either (y) or (n) " << endl;
        return yes();
}

void print_pizzas_toppings(Pizza pizza) {


    Toppings* top = pizza.get_toppings();
    int toppingcount = pizza.get_toppingcount();
    int comma_count = toppingcount - 1;
    for (int i = 0; i < toppingcount; i++) {
        cout << top[i].get_name();
        if (comma_count > 0) {
            cout << ", ";
        }
        comma_count--;
    }
    cout << "."  << endl;
}
void print_pizza(Pizza pizza) {
    cout << "*" << pizza.get_name() <<endl;
    print_pizzas_toppings(pizza);
    cout << "Price: " << pizza.get_price() << endl;
}

void print_order(Order order) {
    cout << "Order #" << order.get_order_number() << endl;
    print_lines(10);
    Pizza* pizzas_in_order = order.get_pizzas_in_order();
    Pizza temp_pizza;

    int endl_count = order.get_order_count() - 1;

    for (int i = 0; i < order.get_order_count(); i++) {
        print_pizza(pizzas_in_order[i]);
        if (endl_count > 0)
            cout << endl;
        endl_count--;
    }
   print_lines(10);
   cout << "Total price: " << order.get_total() << endl;
   print_lines(10);
}

void print_current_orders(char& refresh) {

    OrderHandler orderhandler;
    int ordercount = orderhandler.get_order_count();

    Order temp_order;
    int counter = 2;

    for (int i = 0; i < ordercount; i ++) {
        if (counter == 0) {
            cout << "Press n to get the next screen or enter number of order\n";
            cin >> refresh;
            if (isdigit(refresh)) {
                break;
            }
        }
        print_order(orderhandler.get_orders().at(i));
        counter--;
    }
    cin >> refresh;
}
void mark_delivered() {

    int remove_order_nr;

    cout << "Press (p) to print current orders, or insert the number of order to mark ready: ";
    string remove_order;
    cin >> remove_order;
    char first_digit;
    if (remove_order == "p") {
        print_current_orders(first_digit);
    }
    remove_order_nr = atoi(remove_order.c_str());

    OrderHandler orderhandler;
    if (!orderhandler.delivered(remove_order_nr)) {
        cout << "Order nr not on list!" << endl;
    }
}
void print_lines (int line_count) {
    for (int i = 0; i <line_count; i++) {
        cout << "-";
    }
    cout << endl;
}

void print_topping_list() {
    ToppingsHandler toppings_handler;
    vector<Toppings> topping_vector;

    system("CLS");

    cout << "---All toppings on menu---" << endl;

    topping_vector = toppings_handler.get_topping_list();

    for(unsigned int i = 0; i < topping_vector.size(); i++) {
        cout << topping_vector[i].get_price() << " ISK, ";
        cout << topping_vector[i].get_name() << endl;

    }
    cout << endl;
}

void print_menu_pizza_list() {
    PizzaHandler pizza_handler;
    vector<Pizza> pizza_vector;

    system("CLS");

    pizza_vector = pizza_handler.get_pizza_list();
    cout << "---All pizzas on menu---" << endl;

    for(unsigned int i = 0; i < pizza_vector.size(); i++) {
        cout << pizza_vector[i].get_price() << " ISK, ";
        cout << pizza_vector[i].get_name() << ", ";
        cout << pizza_vector[i].get_toppings_print(pizza_vector[i]) << endl;
    }
    cout << endl;
}

void print_sizes() {
    PizzaSizeHandler size_handler;
    vector<PizzaSize> size_vector;

    size_vector = size_handler.get_size_list();

    system("CLS");

    cout << "---Print all pizza sizes---" << endl;

    cout << "See all sizes:" << endl;
    for(unsigned int i = 0; i < size_vector.size(); i++){
        cout << size_vector[i].get_price() << " ISK, ";
        cout << size_vector[i].get_size() << "\"" << endl;
    }
    cout << endl;
     pause_screen();
}

void print_size_with_numbers() {
    PizzaSizeHandler pizza_handler;
    vector<PizzaSize> size_vector;

    size_vector = pizza_handler.get_size_list();

    for(unsigned int i = 0; i < size_vector.size(); i++) {
        cout << "[" << i + 1 << "]\t";
        cout << size_vector[i].get_price() << " ISK, ";
        cout << size_vector[i].get_size() << "\"" << endl;
    }
}