#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include "Order.h"

Order::Order() {
	this ->order_ready = false;
	this ->order_delivered = false;
	this ->order_paid = false;
	this ->order_sent = false;
	this ->pizzas_in_order_count = 0;
	this ->comment[0] = '\0';
	this ->delivery_addresse[0] = '\0';
}
Pizza* Order::get_order() {

	return this->pizzas_in_order;
}

void Order::set_delivered() {

	this ->order_delivered = true;
}

bool Order::delivered() {

	return this ->order_delivered;
}

int Order::get_order_count() {

	return this ->pizzas_in_order_count;
}

ostream& operator <<(ostream& outs, Order& order) {

    outs << "Order nr #" << order.order_number << endl;

		for (int i = 0; i < order.pizzas_in_order_count; i++) {

			outs << order.pizzas_in_order[i] << endl;
		}
    return outs;
}

istream& operator >>(istream& ins, Order& order) {

	Pizza temp;
	ins >> temp;
	int index = order.pizzas_in_order_count;
	order.pizzas_in_order[index] = temp;
	order.pizzas_in_order_count++;

	return ins;
}
void Order::all_pizzas_ready() {

	bool temp = true; //Temporary until pizzahandler is ready.
	int ready_count = 0;
	for (int i = 0; i < pizzas_in_order_count; i++) {
		if (temp) {
			//Remember ->pizzas_in_order[i].get_status() == read
			ready_count++;
		}
	}
	if (ready_count == pizzas_in_order_count) {

		this ->order_ready = true;
	}
}
bool Order::ready() {

	all_pizzas_ready();
	return this ->order_ready;
}
void Order::set_order_number(int number) {

	this ->order_number = number;
}

int Order::get_order_number() {
    return this ->order_number;
}
void Order::add_pizza(Pizza pizza) {
	if(pizzas_in_order_count <= MAX_ORDER_SIZE) {

		this ->pizzas_in_order[this ->pizzas_in_order_count] = pizza;
        this ->pizzas_in_order_count++;
	}

	else {
		cout << "Order has reached maximum size for pizzas!" << endl;
	}
}

void Order::add_side_order(SideOrders sideorder) {
	if(side_orders_in_order <= MAX_ORDER_SIZE) {

		this ->side_orders[this ->side_orders_in_order] = sideorder;
        this ->side_orders_in_order++;
	}

	else {
		cout << "Maximum number of side orders reached!" << endl;
	}
}

int Order::get_max_orders() {
    return this ->MAX_ORDER_SIZE;
}
Pizza* Order::get_pizzas_in_order() {
    Pizza* new_list = this ->pizzas_in_order;
    return new_list;
}
double Order::get_total() {
    calulate_total();
    return this ->total_price;
}
void Order::calulate_total()  {

    double order_calc = 0;
    for (int i = 0; i < pizzas_in_order_count; i++ ) {
        order_calc += pizzas_in_order[i].get_price();
    }
    this ->total_price = order_calc;
}

void Order::set_paid() {
    this -> order_paid = true;
}

bool Order::set_ready() {
    this -> order_ready = true;
}

bool Order::get_paid() {
    if(this -> order_paid) {
        return true;
    }
    return false;
}

bool Order::get_ready() {
    if(this -> order_ready) {
        return true;
    }
    return false;
}

bool Order::get_sent() {
    if(this -> order_sent) {
        return true;
    }
    return false;
}

void Order::set_sent() {
    this -> order_sent = true;
}

void Order::set_addresse(string input) {
    for(unsigned int i = 0; i < input.length(); i++) {
        this ->delivery_addresse[i] = input [i];
    }
}

string Order::get_addresse() {
    string temp;
    for(unsigned int i = 0; i < sizeof(delivery_addresse); i++) {
        temp += delivery_addresse[i];
    }
    return temp;
}

void Order::set_comment(string input) {
    for(unsigned int i = 0; i < input.length(); i++) {
        this ->comment[i] = input [i];
    }
}

string Order::get_comment() {
    string temp;
    for(unsigned int i = 0; i < sizeof(comment); i++) {
        temp += comment[i];
    }
    return temp;
}

#endif
