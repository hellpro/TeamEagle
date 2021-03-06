#include "order_functions.h"

#include "ValidationFunctions.h"

void print_orders(Order_Status status, OrderHandler& orderhandler) {

    int ordercount = orderhandler.get_order_count();

    Order temp_order;

    for (int i = 0; i < ordercount; i ++) {
       switch (status) {
            case delivered:
                 if (orderhandler.get_orders().at(i).get_delivered()) {

                     print_order(orderhandler.get_orders().at(i));
                 }
                 break;
            case not_delivered:
                 if (!orderhandler.get_orders().at(i).get_delivered()) {

                     print_order(orderhandler.get_orders().at(i));
                 }
                break;
            case all:
                print_order(orderhandler.get_orders().at(i));
                break;
        }
    }
}

bool new_order(OrderHandler& orderhandler, PizzaHandler& pizzahandler, ToppingsHandler& toppingshandler, PizzaBottomHandler& bottomhandler) {

    Order order;
    string select;
    bool cont = 1;
    bool skip = 1;

    orderhandler.generate_order_no(order);
    cout << "Order #" << order.get_order_number() << endl;

    add_pizzas(order, orderhandler, pizzahandler, toppingshandler, bottomhandler);
    clear();

    if(!skip) {
        sent_or_picked_up(order);

        comment(order);

        print_order(order);
        if (order.get_order_count() > 0) {
            do{
                try{
                    cout << "Is this the correct order? (y/n) ";
                    getline(cin, select, '\n');
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

    }
    return false;
}

void sent_or_picked_up(Order& order) {
    string input;
    bool cont = 1;

    do{
        try{
            cout << "Should the order be delivered to you (y/n)? ";
            cin >> ws;
            getline(cin, input, '\n');
            validate_bool_question(input);
            cont = 0;
        }
        catch(InvalidBoolException e) {
            clear();
            cont = 1;
            cout << e.get_err() << endl;
        }
    } while(cont);

    if(input == "y") {
        order.set_sent();
        set_delivery_addresse(order);
    }

}

void set_delivery_addresse(Order& order) {
    bool cont = 1;
    string input;
    do{
        try{
            cout << "Please enter your address (max 25 characters): ";
            cin >> ws;
            getline(cin, input);
            validate_addresse(input);
            cont = 0;
        }
        catch(InvalidAddresseException e) {
            clear();
            cont = 1;
            cout << e.get_err() << endl;
        }
    } while (cont);
    order.set_addresse(input);
}

bool add_pizzas(Order& order, OrderHandler& orderhandler, PizzaHandler& pizzahandler, ToppingsHandler& toppingshandler, PizzaBottomHandler& bottomhandler) {

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
                add_menu_pizza(order, pizzahandler, bottomhandler);

            }
            if (pizzatype == special_pizza) {
                add_special_pizza(order, pizzahandler, toppingshandler);
            }

            do{
                try{
                    cout << "Do you wish to add more pizzas to the order (y/n)? ";
                    getline(cin, run_menu, '\n');
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
    } else {
        return 0;
    }
    return 1;
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
                cin >> ws;
                getline(cin, type, '\n');
                validate_char(type);
                cont = 0;
                type = tolower(type[0]);

                if(type != "m" && type != "c" && type != "b") {
                    clear();
                    cont = 1;
                    cout << "Input is not a valid option!" << endl;
                }
                //Special case
            }
            catch(InvalidCharException e) {
                clear();
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

void add_menu_pizza(Order& order, PizzaHandler& pizzahandler, PizzaBottomHandler& bottomhandler) {
    Pizza pizza;

    bool cont = 0;
    string pizza_name;
    do{
        try{
            clear();
            print_menu_pizza_list(pizzahandler);
            cout << "Enter name of pizza: ";
            cin >> ws;
            getline(cin, pizza_name, '\n');
            validate_int_string(pizza_name);
            cont = 0;
            pizza = pizzahandler.get_menu_pizza(pizza_name);
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
    string input;
    do{
        try{
            print_sizes_numbers(bottomhandler);
            cout << "Please select a size with the number in front of it: ";
            cin >> ws;
            getline(cin, input, '\n');
            validate_int(input);
            cont = 0;
        }
        catch(InvalidNumberException e) {
            cont = 1;
            cout << e.get_err() << endl;
        }
    } while(cont);

    pizzahandler.add_bottom_to_pizza(pizza, input);

    order.add_pizza(pizza);


}

void toppings_to_special(Pizza& pizza, PizzaHandler& pizzahandler, ToppingsHandler& toppingshandler) {


    clear();
    print_topping_list(toppingshandler);

    string topping_name = " ";
    cout << "Input topping name, input q when finished: ";
    getline(cin, topping_name, '\n');

    while (topping_name != "q") {
        try {
            pizza.add_topping(toppingshandler.get_topping(topping_name));
        }
        catch(InvalidName e) {
            cout << "Topping not on list!" << endl;
        }

        cout << "Enter next topping: ";
        getline(cin, topping_name, '\n');

        if (pizzahandler.max_toppings(pizza)) {
            cout << "Maximum topping has been reached." << endl;
            break;
        }
    }

}

void add_special_pizza(Order& order, PizzaHandler& pizzahandler, ToppingsHandler& toppingshandler) {
    Pizza pizza;

    pizza.set_name("Special order");
    toppings_to_special(pizza, pizzahandler,toppingshandler);

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
    cout << "Price: " << pizza.get_price() + pizza.get_bottom().get_price() << " ISK" << endl;
    cout << "Size : " << pizza.get_bottom().get_size() << "\"" << endl;
}

void print_order(Order order) {
    cout << "\033[1;31m Order # \033[0m\ " << order.get_order_number() << endl;

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
    cout << is_paid(order) << endl;
    cout << is_ready(order) << endl;
    cout << is_sent(order) << endl;
    cout << is_comment(order) << endl;

    print_lines(10);
    cout << endl;
}

void print_current_orders(int& refresh, string next, OrderHandler& orderhandler, bool skipdelivered, bool skippaid) {
    int temp = refresh;
    int next_num = 0;
    Order temp_order;
    vector<Order> orders = orderhandler.get_orders();

    if(orders.size() == 1) {
        next_num = 1;
        temp = 0;
        refresh = 0;

    } else {
        if(next == "n" && refresh < (int)orders.size()) {
            next_num = 2;
        } else if(next == "n") {
            refresh = 0;
            temp = 0;
            next_num = 2;
        } else {
            refresh -= 2;
            temp -=2;
            next_num = 2;
        }
    }


    if(skippaid) {
        for (; refresh < temp + next_num; refresh++) {
            if(refresh == orders.size()) {
                break;
            }
                if(!orders.at(refresh).get_paid()) {
                    print_order(orders.at(refresh));
                }
        }
    }

    else if(skipdelivered) {
        for (refresh; refresh < temp + next_num; refresh++) {
            if(refresh == orders.size()) {
                break;
            }
                if(!orders.at(refresh).get_delivered()) {
                    print_order(orders.at(refresh));
                }
        }
    }
}

void mark_paid(OrderHandler& orderhandler) {

    int remove_order_nr;
    string remove_order;
    int first_digit = 0;
    bool cont = 1;
    string next = "n";

    do{
        try{
            clear();
            cont = 1;
            print_current_orders(first_digit, next, orderhandler, true, true);
            cout << "Input number order to mark delivered (n for next page, q to quit): ";
            cin >> ws;
            getline(cin, remove_order, '\n');

            for(unsigned int i = 0; i < remove_order.length(); i++) {
                remove_order[i] = tolower(remove_order[i]);
            }
            validate_int_p(remove_order);

            if(isdigit(remove_order[0])) {
                next = "p";
                remove_order_nr = stoi(remove_order);
                orderhandler.paid(remove_order_nr);
            }
            else if(remove_order == "q") {
                cont = 0;
            } else if(remove_order == "n") {
                next = "n";
            } else {
                next = "p";
                system("PAUSE");
            }
        }
        catch(InvalidAlphaNumException e) {
            clear();
            cont = 1;
            next = "p";
            cout << "Input was not valid" << endl;
            pause_screen();
        }
        catch(InvalidNumberException e) {
            cout << "Order number not on list!" << endl;
        }
    } while(cont);
}

void mark_delivered(OrderHandler& orderhandler) {

    int remove_order_nr;
    string remove_order;
    int first_digit = 0;
    bool cont = 1;
    string next = "n";

    do{
        try{
            clear();
            cont = 1;
            print_current_orders(first_digit, next, orderhandler, false, true);
            cout << "Input number order to mark delivered (n for next page, q to quit): ";
            cin >> ws;
            getline(cin, remove_order, '\n');

            for(unsigned int i = 0; i < remove_order.length(); i++) {
                remove_order[i] = tolower(remove_order[i]);
            }
            validate_int_p(remove_order);

            if(isdigit(remove_order[0])) {
                next = "p";
                remove_order_nr = stoi(remove_order);
                orderhandler.delivered(remove_order_nr);
            }
            else if(remove_order == "q") {
                cont = 0;
            } else if(remove_order == "n") {
                next = "n";
            } else {
                next = "p";
                system("PAUSE");
            }
        }
        catch(InvalidAlphaNumException e) {
            clear();
            cont = 1;
            next = "p";
            cout << "Input was not valid" << endl;
            pause_screen();
        }
        catch(InvalidNumberException e) {
            cout << "Order number not on list!" << endl;
        }
    } while(cont);

}



void print_lines (int line_count) {
    for (int i = 0; i <line_count; i++) {
        cout << "-";
    }
    cout << endl;
}

void print_topping_list(ToppingsHandler& toppingshandler) {
    vector<Toppings> topping_vector;

    clear();

    cout << "---All toppings on menu---" << endl;

    topping_vector = toppingshandler.get_topping_list();

    for(unsigned int i = 0; i < topping_vector.size(); i++) {
        cout << topping_vector[i].get_price() << " ISK, ";
        cout << topping_vector[i].get_name() << endl;

    }
    cout << endl;
}

void print_navigation (Print& print, print_item type) {

    string input;
    int k = 0;
    while(input[0] != 'b') {

        clear();
        print.get(current_screen);

        cin >> input;
        if (input[0] == 'n') {
            print.get(next_screen);
        }
        if (input[0] == 'p') {
            print.get(previous_screen);
        }
        if (type == top || type == pizz) {
            if (input[0] == 'd') {
                print.get(z_to_a);
            }
            if (input[0] == 'a') {
                print.get(a_to_z);
            }
            if (input[0] == 'h') {
                print.get(price_from_high);
            }
            if (input[0] == 'l') {
                print.get(price_from_low);
            }
            if (input[0] == 'k')  {

                if (k % 2 == 0)
                    print.set_price(price);
                else
                    print.set_price(no_price);

                print.get(current_screen);
                k++;
            }
        }
    }
}
void print_menu_pizza_list(PizzaHandler& pizza_handler) {

    clear();
    Print print;

    print.set(4, alph_asc,price,header, pizz);

    print.pizza_settings(true, false);

    print.prompt_user(true);

    print_navigation(print, pizz);

    clear();
}

void print_sizes(PizzaBottomHandler& bottomhandler) {
    vector<PizzaBottom> size_vector;

    size_vector = bottomhandler.get_size_list();

    clear();

    cout << "---Print all pizza sizes---" << endl;

    cout << "See all sizes:" << endl;
    for(unsigned int i = 0; i < size_vector.size(); i++){
        cout << size_vector[i].get_price() << " ISK, ";
        cout << size_vector[i].get_size() << "\"" << endl;
    }
    cout << endl;
     //pause_screen();
}

void print_sizes_numbers(PizzaBottomHandler& bottomhandler) {
    vector<PizzaBottom> size_vector;

    size_vector = bottomhandler.get_size_list();

    clear();

    cout << "---Print all pizza sizes---" << endl;

    cout << "See all sizes:" << endl;
    for(unsigned int i = 0; i < size_vector.size(); i++){
        cout << "[" << i + 1 << "]" << " ";
        cout << size_vector[i + 1].get_price() << " ISK, ";
        cout << size_vector[i + 1].get_size() << "\"" << endl;
    }
    cout << endl;
     pause_screen();
}

void print_size_with_numbers(PizzaBottomHandler& bottomhandler) {
    vector<PizzaBottom> size_vector;

    size_vector = bottomhandler.get_size_list();

    for(unsigned int i = 0; i < size_vector.size(); i++) {
        cout << "[" << i + 1 << "]\t";
        cout << size_vector[i].get_price() << " ISK, ";
        cout << size_vector[i].get_size() << "\"" << endl;
    }
}

string is_paid(Order& order) {
    if(order.get_paid()) {
        return "Order paid";
    } else {
        return "Order not paid";
    }
}

string is_ready(Order& order) {
    if(order.get_ready()) {
        return "Order is ready";
    } else {
        return "Order in progress";
    }
}

string is_sent(Order& order) {
    string temp;
    if(order.get_sent()) {
        temp = "Deliver to: " + order.get_addresse();
    } else {
        temp = "Picked up at: local"; ///+ future pickup location
    }

    return temp;
}

void comment(Order& order) {
    clear();
    bool cont = 1;
    string input;
    do{
        try{
            cout << "Do you have any special requests (y/n)? ";
            cin >> ws;
            getline(cin, input, '\n');
            validate_bool_question(input);
            cont = 0;
        }
        catch(InvalidBoolException e) {
            clear();
            cont = 1;
            cout << e.get_err() << endl;
        }
    } while(cont);

    if(input == "y") {
        add_a_comment(order);
    } else {
        order.set_comment(" ");
    }

}

void add_a_comment(Order& order) {
    string temp;
    cout << "comment: ";
    cin >> ws;
    getline(cin, temp, '\n');
    order.set_comment(temp);
}

string is_comment(Order& order) {

    string temp = order.get_comment();

    if(order.get_comment_length() <= 1) { //Since comment[0] is the null term.
        return "No comment.";
    }

    return "Comment: " + order.get_comment();
}
