#ifndef ORDERREPO_H
#define ORDERREPO_H

#include "Order.h"
#include <fstream>
#include <string>
#include <vector>
enum ListType{current, archived};

class OrderRepo {

public:
	OrderRepo();
	//Currently empty initializer.
	~OrderRepo();
	//Currently empty destructor.
	/*void current_write(Order orders);
	//Appends orders to a binary file located in the home directory.
	Order* current_read();
	//Return value is a dynamic array where each element is an occurrence
	//of a current Order currently contained in "current_orders.dat" in the home folder.
	//The allocated memory must be deleted where the pointer is received.

	Order* archived_read();
	//Return value is a dynamic array where each element is an occurrence
	//of an archived Order currently contained in "archived_orders.dat" in the home folder.
	//The allocated memory must be deleted where the pointer is received
	int get_archived_count() const;
	//Returns the size of the above list
    //void move_to_archived(int order_number);
	//Moves an order in the current order to archived order.
	void overwrite_list(Order* order, int list_count);
	//Rewrites the "current_orders.dat" with order.*/
	void write_archive(vector<Order> orders, string location);

	vector<Order> read_archive(string location);

    vector<Order> read(string location);
    //Return value is a vector where each element is an occurrence
	//of a Order currently contained in "order.dat" in the home folder.
	void write(Order& order, string location);
	//Appends order to a binary file located in the home directory.
	void overwrite(vector<Order> orders, string location);
    //Rewrites a new file the same size as the parameter orders, and replaces
    //the file with the content of the parameter.
    int get_current_count(string location) const;
	//Returns the size of the above list


private:

	Order orders;
	Order* list;
	//For dumping list.
	int archived_list_count;
	int current_list_count;
	int list_count;

};

#endif // ORDERREPO_H
