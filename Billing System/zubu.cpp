#include <iostream>
#include <fstream>
#include "zubu.h"
using namespace std; 

void Zubu::menu() {

	start: 
	int choice = 0; 
	string email; 
	string password; 

	cout << "-------------------------------------------\n";
	cout << "\t Zubu Ramen Main Menu" << endl; 
	cout << endl << "1) Administator" << endl; 
	cout << endl << "2) Buyer" << endl; 
	cout << endl << "3) Exit" << endl; 
	cout << endl << "Please selet: ";
	cin >> choice;

	if (choice == 1) {
		cout << endl << "Please Login" << endl; 
		cout << endl << "Email: "; 
		cin >> email; 
		cout << endl << "Password: ";
		cin >> password;

		if (email == "zubu@ramen" && password == "12345")
		{
			administrator();
		}
		else {
			cout << "Invalid Email/Password" << endl;
		}

	}
	else if (choice == 2) {
		customers(); 
	}
	else if (choice == 3) {
		exit(0);
	}
	else {
		cout << "Please select from the following options!" << endl; 
	}
	goto start;
}

void Zubu::administrator() {

	start:
	int choice = 0;
	
	cout << "-------------------------------------------\n";
	cout << "\t Administrator Main Menu" << endl;
	cout << endl << "1) Add a Product " << endl; 
	cout << endl << "2) Modify a Product" << endl; 
	cout << endl << "3) Remove a Product" << endl; 
	cout << endl << "4) Back to Main Menu" << endl; 
	cout << endl << "Please selet: ";
	cin >> choice;

	if (choice == 1) {
		add(); 
	}
	else if (choice == 2) {
		edit(); 
	}
	else if (choice == 3) {
		removeProduct(); 
	}
	else if (choice == 4) {
		menu();
	}
	else {
		cout << "Please select from the following options!" << endl;
	}

	goto start;

}

void Zubu::customers() {
	
	start:
	int choice = 0; 

	cout << "-------------------------------------------\n";
	cout << "\t Customers Main Menu" << endl;
	cout << endl << "1) Buy a Product " << endl;
	cout << endl << "2) Back to Main Menu " << endl;
	cout << endl << "Please selet: ";
	cin >> choice; 

	if (choice == 1) {
		printReceipt();
	}
	else if (choice == 2) {
		menu();
	}
	else {
		cout << "Please select from the following options!" << endl;
	}
	goto start;

}

void Zubu::add() {

	start:
	fstream value; 
	int newCode; 
	int token = 0; 
	float newPrice;
	float newDiscount; 
	string newName;

	cout << "-------------------------------------------\n";
	cout << "\t Add NEW Product" << endl;
	cout << "Product Code of the Product: "; 
	cin >> code; 
	cout << endl << "Name of the Product: ";
	cin >> productName; 
	cout << endl << "Price of the Product: ";
	cin >> price; 
	cout << endl << "Discount on the Product: "; 
	cin >> discount; 

	value.open("database.txt", ios::in);

	if (!value) {
		value.open("database.txt", ios::app | ios::out);
		value << " " << code << " " << productName << " " << price << " " << discount << endl;
		value.close();
	}
	else {
		value >> newCode >> newName >> newPrice >> newDiscount; 

		while(!value.eof()) {
			if (newCode == code) {
				token++;
			} 
			value >> newCode >> newName >> newPrice >> newDiscount;
		}
		value.close();
	}

	if (token == 1) {
		goto start;
	}
	else {
		value.open("database.txt", ios::app | ios::out);
		value << " " << code << " " << productName << " " << price << " " << discount << endl;
		value.close();

	}

	cout << endl << "Product Inserted to Stock!" << endl; 

}

void Zubu::edit() {

	fstream data1, data2;
	int productKey = 0;
	int token = 0; 
	int newCode; 
	float newPrice; 
	float newDiscount;
	string newName; 

	cout << "-------------------------------------------\n";
	cout << "\t Edit a Product Record" << endl;
	cout << "Product Code of the Product: "; 
	cin >> productKey; 
	
	data1.open("database.txt", ios::in);

	if (!data1) {
		cout << endl << "File Does Not Exist!" << endl; 
	}
	else {
		data2.open("databaseTEMP.txt", ios::app | ios::out);

		data1 >> code >> productName >> price >> discount; 
		while (!data1.eof()) {
			if (productKey == code) {
				cout << endl << "\t New Product Code: "; 
				cin >> newCode; 
				cout << endl << "\t Name of the Product: ";
				cin >> newName;
				cout << endl << "\t Price of the Product: ";
				cin >> newPrice; 
				cout << endl << "\t Discount of the Product: ";
				cin >> newDiscount;

				data2 << " " << newCode << " " << newName << " " << newPrice << " " << newDiscount << endl;
				
				cout << "Record Edited!" << endl; 
				token++;
				break;
			}
			else {
				data2 << " " << code << " " << productName << " " << price << " " << discount << endl; 
			}
			data1 >> code >> productName >> price >> discount; 
		}
		data1.close(); 
		data2.close(); 

		remove("database.txt");
		rename("databaseTEMP.txt", "databgase.txt");

		if (token == 0) {
			cout << endl << "Record Not Found!" << endl; 
		}
	}
}

void Zubu::removeProduct() {

	fstream data1, data2; 
	int productKey; 
	int token = 0; 

	cout << "-------------------------------------------\n";
	cout << "\t Delete Products" << endl;
	cout << "Product Code of the Product: ";
	cin >> productKey; 

	data1.open("database.txt", ios::in);

	if (!data1) {
		cout << "File Does Not Exist!" << endl; 
	}
	else {
		data2.open("databaseTEMP.txt", ios::app | ios::out);
		data1 >> code >> productName >> price >> discount; 

		while (!data1.eof()) {
			if (code == productKey) {
				cout << endl << "Product Deleted Successfully!" << endl; 
				token++; 
			}
			else {
				data2 << " " << code << " " << productName << " " << price << " " << discount << endl; 
			}
			data1 >> code >> productName >> price >> discount;
		}
		data1.close(); 
		data2.close(); 

		remove("database.txt");
		rename("databaseTEMP.txt", "database.txt");
		
		if (token == 0)
			cout << endl << "Record Not Found " << endl; 
	}
}

void Zubu::list() {

	fstream value; 
	value.open("database.txt", ios::in); 

	cout << "-------------------------------------------\n";
	cout << "\t List of Products" << endl;
	cout << "Product Code \t  Product Name \t  Product Price" << endl; 
	value >> code >> productName >> price >> discount; 

	while (!value.eof()) {
		cout << code << "\t\t" << productName << "\t\t" << price << endl; 
		value >> code >> productName >> price >> discount;
	}
	value.close();
}

void Zubu::printReceipt() {

	fstream value; 

	int arrCode[100] {};
	int arrQuantity[100] {};
	char choice = 0; 
	int index = 0; 
	float amount = 0;
	float disc = 0; 
	float total = 0;

	cout << "-------------------------------------------\n";
	cout << "\t RECEIPT" << endl;

	value.open("database.txt", ios::in);
	if (!value) {
		cout << "Empty Database!" << endl;
	}
	else {
		value.close();

		list();
		cout << "-------------------------------------------\n";
		cout << endl << "Please Place The Order  " << endl;
		cout << "-------------------------------------------\n";

		do {
			start:
			cout << endl << "Enter the Product Code: ";
			cin >> arrCode[index];

			cout << endl << "Enter the Quantity: ";
			cin >> arrQuantity[index];

			for (int i = 0; i < index; i++)
			{
				if (arrCode[index] == arrCode[i]) {
					cout << "Duplicate Product Code!" << endl;
					cout << "Please Try Again!" << endl;
					goto start;
				}
			}
			index++;
			cout << endl << "Do you want to buy another Product? If Yes then press y, If No then press n";
			cin >> choice;

		} while (choice == 'y');
		
		cout << endl << endl << "\t\t Receipt" << endl; 
		cout << endl << "Product Code \t Product Name \t Produce Quantity \t Price \t Total \t Total With Discount" << endl; 

		for (int i = 0; i < index; i++) {
			value.open("database.txt", ios::in); 
			value >> code >> productName >> price >> discount; 

			while (!value.eof()) {
				if (code == arrCode[i]) {
					amount = price * arrQuantity[i];
					disc = amount - (amount * disc / 100); 
					total = total + disc;
					cout << endl << code << "\t\t" << productName << "\t\t" << arrQuantity[i] << "\t\t" << amount << "\t\t" << disc;
				}
				value >> code >> productName >> price >> discount; 
			}
		}
		value.close(); 
	}

	cout << endl << "-------------------------------------------\n";
	cout << endl << "Total Amount: " << total << endl;
}