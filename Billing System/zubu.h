#include <iostream>
#include <fstream>
using namespace std;

class Zubu {
public:
	void menu();
	void administrator();

	void customers();
	void add();
	void edit();
	void removeProduct();
	void list();
	void printReceipt();


private:
	int code;
	float price;
	float discount;
	string productName;
};

