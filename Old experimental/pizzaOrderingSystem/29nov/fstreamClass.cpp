#include "fstreamClass.h"
void FstreamClass::print_list()
{
	for (int i = 0; i < topping_list_size; i++) {
		cout << topping_list[i] << endl;
	}
}


FstreamClass::FstreamClass()
{
	//
}
FstreamClass::~FstreamClass()
{
	delete[] topping_list;
}
void FstreamClass ::write_toppings()
{
	cin >> topping;
	ofstream fout("toppings.dat", ios::binary|ios::app);
	fout.write((char*)(&topping), sizeof(Toppings));
	fout.close();
}
void FstreamClass::read_toppings()
{
	
	ifstream fin("toppings.dat", ios::binary);
		

	
	if (fin.is_open()) {
		fin.seekg(0, fin.end);
		int record_count = fin.tellg() / sizeof(Toppings);
		fin.seekg(0, fin.beg);

		topping_list_size = record_count;
		
		topping_list = new Toppings[record_count];
		
		
		fin.read((char*)(topping_list), sizeof(Toppings)*record_count);
		
		fin.close();


	}

//	return &topping_list;
}
/*write_sizes();
read_sizes();
write_pizzas();
read_pizzas();*/
   
