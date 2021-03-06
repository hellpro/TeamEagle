#include "order_functions.h"

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

    OrderHandler orderhandler;
    orderhandler.generate_order_no(order);
    cout << "Order #" << order.get_order_number() << endl;

    add_pizzas(order);
    system("clear");

    print_order(order);
    if (order.get_order_count() > 0) {
        cout << "Is this the correct order? (y/n) ";
        if (yes()) {
            orderhandler.add_order(order);
            return false;
        }
        else {
            cout << "Order was not added" << endl;
            cout << "Retry? (y/n) ";
            if (yes()) {
                return true;
            }
        }
    }
        cout << "The order is empty, retry?" << endl;
        if (yes()) {
            return true;
    }
    return false;
}
void add_pizzas(Order& order) {

    OrderHandler orderhandler;
    PizzaType pizzatype;


    pizzatype = menu_or_special();


    bool user_choice;
    do
    {
        /*if (orderhandler.max_order_count(order)) {
            cout << "Maximum order has been reached!" << endl;
            break;
        }*/
        if (pizzatype == menu_pizza) {
            add_menu_pizza(order);

        }
        if (pizzatype == special_pizza) {
            add_special_pizza(order);
        }
        cout << "Do you wish to add more pizzas to the order?";
        user_choice = yes();
        if (user_choice) {
            pizzatype = menu_or_special();
        }

    }while(user_choice);
}


PizzaType menu_or_special() {

    PizzaType pizzatype;

    bool quit = false;
            char type;

    while (!quit) {
         cout << "Press m for menu pizza, s for special pizza: ";
        cin >> type;
        if (type == 'm') {
            pizzatype = menu_pizza;
            quit = true;
        }
        else if (type == 's') {

            pizzatype = special_pizza;
            quit = true;
        }
        else {
            cout << "Wrong choice, insert any key to try again or r to return to menu.";
            char in;
            cin >> in;
            if (in == 'r') {//Temporary until it is known where to return.
                exit(0);
            }
        }
    }
    return pizzatype;
}
void add_menu_pizza(Order& order) {
    Pizza pizza;
    PizzaHandler pizzahandler;

    string pizza_name;
    cout << "Enter name of pizza: ";
    cin >> pizza_name;

    try {
        pizza = pizzahandler.get_menu_pizza(pizza_name);
        print_pizza(pizza);
        cout << "Do you want to add this pizza? (y/n) ";
        if (yes()) {
            order.add_pizza(pizza);
        }
    }
    catch(InvalidName e) {
        cout << "Pizza not on menu!" << endl;
    }
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

    print_pizza(pizza);
    cout << "Do you want to add this pizza to the order? (y/n) ";
    if(yes()) {
        order.add_pizza(pizza);
    }
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

    topping_vector = toppings_handler.get_topping_list();

    for(unsigned int i = 0; i < topping_vector.size(); i++) {
        cout << topping_vector[i];

    }

}

void print_menu_pizza_list() {
    PizzaHandler pizza_handler;
    vector<Pizza> pizza_vector;

    pizza_vector = pizza_handler.get_pizza_list();

    for(unsigned int i = 0; i < pizza_vector.size(); i++) {
        cout << pizza_vector[i];
    }
}
