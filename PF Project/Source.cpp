#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

// Structures

struct Rooms {
	int room_Number;
	char room_status[25] = "Avaliable";
	float room_price;
};

struct customers {
	char customer_cnic[25];
	char first_name[25];
	char last_name[25];
	char address[50];
	int days_stay;
	char room_name[25];
	float bill;
	Rooms room;
};

////////////////////////////////////////////// Functions

/////////////////////////// User Management
// Check In
void checkIn() {
	cout << "Note: " << endl
		<< "Rent for Each Day is $100" << endl;
	customers customer, compare;
	fstream checkIn;
	int flag = 0;
	checkIn.open("Customer Record.dat", ios::in, ios::binary);
	cout << "CNIC: ";
	cin >> customer.customer_cnic;
	if (checkIn.is_open()) {
		while (checkIn.read((char*)&compare, sizeof(customers))) {
			if (compare.customer_cnic == customer.customer_cnic) {
				cerr << "This Record Already Exist!!!" << endl;
				flag = 1;
			}
		}
		checkIn.close();
	}
	if (flag == 0) {
		cout << "First Name: ";
		cin >> customer.first_name;
		cout << "Last Name: ";
		cin >> customer.last_name;
		cout << "Address: ";
		cin >> customer.address;
		cout << "Days to Stay: ";
		cin >> customer.days_stay;
		customer.bill = customer.days_stay * 100.0;
		checkIn.open("Customer Record.dat", ios::app, ios::binary);
		if (checkIn.is_open()) {
			checkIn.write((const char*)&customer, sizeof(customers));
			checkIn.close();
		}
		else {
			cerr << "Error In Opening File!!!" << endl;
		}
	}
}

// View Records
void viewRecords() {
	fstream viewRecords;
	customers customer;
	viewRecords.open("Customer Record.dat", ios::in, ios::binary);
	if (viewRecords.is_open()) {
		cout << "\t\t\t\t\t============View All Records============" << endl
			<< "CNIC\t\t\tName\t\t\tAddress\t\t\tDays to Stay\t\t\tBill" << endl
			<< "==============================================================================================================" 
			<< endl;
		while (viewRecords.read((char*)&customer, sizeof(customers))) {
			cout << customer.customer_cnic << "\t\t\t" << customer.first_name << " " << customer.last_name << "\t\t"
				<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t\t$" << customer.bill << endl;
		}
		viewRecords.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

// Search Customer
void searchCustomer() {
	int choice;
	do {
		customers customer;
		fstream searchContent;
		cout << "1. Search by CNIC" << endl
			<< "2. Search by Name" << endl
			<< "3. Exit Instance..." << endl
			<< "Choose from Above: ";
		cin >> choice;
		switch (choice) {
		case 1: {
			char cnic[25];
			cout << "CNIC: ";
			cin >> cnic;
			searchContent.open("Customer Record.dat", ios::in | ios::binary);
			if (searchContent.is_open()) {
				cout << "\t\t\t\t\t============Search Customers============" << endl
					<< "CNIC\t\t\tName\t\t\tAddress\t\t\tDays to Stay\t\t\tBill" << endl
					<< "=============================================================================================================="
					<< endl;
				while (searchContent.read((char*)&customer, sizeof(customers))) {
					if (strcmp(cnic, customer.customer_cnic) == 0) {
						cout << customer.customer_cnic << "\t\t\t" << customer.first_name << " " << customer.last_name << "\t\t"
							<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t\t$" << customer.bill << endl;
					}
					else {
						cerr << "Record Not Found!!!!" << endl;
						break;
					}
				}
				searchContent.close();
			}
			else {
				cerr << "File not Found!!!!" << endl;
			}
			break;
		}
		case 2:
			char name[25];
			cout << "Name: ";
			cin >> name;
			searchContent.open("Customer Record.dat", ios::in | ios::binary);
			if (searchContent.is_open()) {
				cout << "\t\t\t\t\t============Search Customers============" << endl
					<< "CNIC\t\t\tName\t\t\tAddress\t\t\tDays to Stay\t\t\tBill" << endl
					<< "=============================================================================================================="
					<< endl;
				while (searchContent.read((char*)&customer, sizeof(customers))) {
								// strcmp refers to String Compare
								// this function return 0 if val is found
								// and return 1 if val is not found
								// arrays are actually like pointers
								// if(name == customer.first_name)	actually compares memory
								// addresses of both arrays
					if ((strcmp(name, customer.first_name) == 0) || (strcmp(name, customer.last_name) == 0)) {
						cout << customer.customer_cnic << "\t\t\t" << customer.first_name << " " << customer.last_name << "\t\t"
							<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t\t$" << customer.bill << endl;
					}
					else {
						cerr << "Record Not Found!!!!" << endl;
						break;
					}
				}
				searchContent.close();
			}
			else {
				cerr << "Error in opening File!!!" << endl;
			}
			break;
		case 3:
			break;
		default:
			cerr << "Invalid Input!!!" << endl;
		}
	} while (choice != 3);
}

// Modify Customer Record
void modifyCustomer() {
	customers customer, modify;
	int pos = 0;		// posotion
	char cnic[25];
	cout << "Enter the CNIC to Modify: ";
	cin >> cnic;
	fstream modifyContact;
	modifyContact.open("Customer Record.dat", ios::in | ios::binary | ios::out);
	if (modifyContact.is_open()) {
		cout << "CNIC: ";
		cin >> modify.customer_cnic;
		cout << "First Name: ";
		cin >> modify.first_name;
		cout << "Last Name: ";
		cin >> modify.last_name;
		cout << "Address: ";
		cin >> modify.address;
		cout << "Days to Stay: ";
		cin >> modify.days_stay;
		modify.bill = modify.days_stay * 100;
		while (modifyContact.read((char*)&customer, sizeof(customers))) {
			if (strcmp(cnic, customer.customer_cnic) == 0) {
				modifyContact.seekp(pos * sizeof(customer));	// moving pointer to specific Position
				modifyContact.write((const char*)&modify, sizeof(customers));	// to overwrite to existing text...
				break;
			}
			else {
				cerr << "Record Not Found!!!" << endl;
				break;
			}
			pos++;
		}
		modifyContact.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

// Delete Customer Record
void deleteCustomer() {
	char cnic[25];
	fstream deleteCustomer, temp;
	customers customer, temp_customer;
	deleteCustomer.open("Customer Record.dat", ios::in | ios::binary);
	if (deleteCustomer.is_open()) {
		cout << "Enter Your ID: ";
		cin >> cnic;
		while (deleteCustomer.read((char*)&customer, sizeof(customers))) {
			if (strcmp(cnic, customer.customer_cnic) == 0) {
				continue;
			}
			else {
				temp.open("temp.dat", ios::app | ios::binary);
				if (temp.is_open()) {
					temp.write((const char*)&customer, sizeof(customers));
					temp.close();
				}
				else {
					cerr << "Error in deleting Record!!!" << endl;
				}
			}
		}
		deleteCustomer.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
	remove("Customer Record.dat");
	if (rename("temp.dat", "Customer Record.dat") == 0) {
		cout << "Record Sucessfully Deleted!!!" << endl;
	}
}

// Customer Management
void customerManagement() {
	int choice;
	do {
		cout << "1. Check In" << endl
			<< "2. View Record All of Customer" << endl
			<< "3. Search Customer" << endl
			<< "4. Modify Customer" << endl
			<< "5. Checkout" << endl
			<< "6. Exit Instance..." << endl
			<< "Enter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			checkIn();
			break;
		case 2:
			viewRecords();
			break;
		case 3:
			searchCustomer();
			break;
		case 4:
			modifyCustomer();
			break;
		case 5:
			deleteCustomer();
			break;
		case 6:
			break;
		default:
			cerr << "Invalid Input !!!" << endl;
		}
	} while (choice != 6);
}

///////////////////////////////////////// Room Management

// Add Room
void addRoom() {
	fstream addroom;
	Rooms room;
	addroom.open("Rooms Record.dat", ios::app | ios::binary);
	if (addroom.is_open()) {
		cout << "Room Number: ";
		cin >> room.room_Number;
		cout << "Room Price: ";
		cin >> room.room_price;
		addroom.write((const char*)&room, sizeof(room));
		addroom.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

//	View all Records of Room
void viewRoom() {
	fstream viewRecord;
	Rooms roomRecord;
	viewRecord.open("Rooms Record.dat", ios::in, ios::binary);
	if (viewRecord.is_open()) {
		cout << "\t\t\t\t\t============View Rooms============" << endl
			<< "Room Number\t\t\tRoom Price\t\t\tRoom Status\t\t\t" << endl
			<< "=============================================================================================================="
			<< endl;
			while (viewRecord.read((char*)&roomRecord, sizeof(Rooms))) {
				cout << roomRecord.room_Number << "\t\t\t\t" << roomRecord.room_price
					<< "\t\t\t\t" << roomRecord.room_status << endl;
			}
		viewRecord.close();
	}
	else {
		cerr << "Error In Opening File!!!" << endl;
	}
}

// Modify Room
void modifyRoom() {
	fstream modifyRoom;
	Rooms roomRecord;
	modifyRoom.open()
}

// Room Management
void roomManagement() {
	int choice;
	do {
		cout << "1. Add Room" << endl
			<< "2. View All Rooms Record" << endl
			<< "3. Search Room" << endl
			<< "4. Modify Room" << endl
			<< "5. Delete Room" << endl
			<< "6. Exit Instance" << endl
			<< "Choose from Above: ";
		cin >> choice;
		switch (choice) {
		case 1:
			addRoom();
			break;
		case 2:
			viewRoom();
			break;
		case 3:
		case 4:
		case 5:
		case 6:;
		}
	} while (choice != 6);
}

/////////////////////////////////////// Main Function
void main() {
	int choice;
	do {
		cout << "1. Customer Management" << endl
			<< "2. Room Management" << endl
			<< "3. Income Record" << endl
			<< "4. Exit Program..." << endl
			<< "Enter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			customerManagement();
			break;
		case 2:
			roomManagement();
			break;
		case 3:
		case 4:
			break;
		default:
			cerr << "Invalid Input !!!" << endl;
		}
	} while (choice != 4);
}