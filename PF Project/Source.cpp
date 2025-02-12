#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

// Structures

struct Rooms {
	int room_Number;
	bool room_status = true;
	float room_price;
	int room_catagory;		// 1 for VIP, 2 for Medium, 3 for Basic 
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
	int service_charges = 0;
	int check_in_date;
	int check_in_month;
	int check_in_year;
};

////////////////////////////////////////////// Functions


/////////////////////////// User Management
// Check In
void checkIn() {
	cout << "\t\t\t\t\t=================Check In=======================" << endl;
	int pos = 0;	// position of pointer
	customers customer, compare, compare_room;
	Rooms Room_rec;	// Room Record
	fstream checkIn, Room;
	fstream customer_record;	// for Permanent Record

	fstream room_redudancy_check; // File Pointer checking for room redudancy
	int flag = 0;
	int customer_flag = 0;
	checkIn.open("Customer Record.dat", ios::in, ios::binary);
	cout << "CNIC: ";
	cin >> customer.customer_cnic;
	if (checkIn.is_open()) {
		while (checkIn.read((char*)&compare, sizeof(customers))) {
			if (strcmp(customer.customer_cnic, compare.customer_cnic) == 0) {
				customer.room.room_catagory;
				cerr << "This Record Already Exist!!!" << endl;
				flag = 1;
				break;
			}
		}
		checkIn.close();
	}
	if (flag == 0) {
		char service_choice;		// Choice for Services
		int room_flag = 0;	// to check that room exist or not!!
		int room_same_flag = 0;	// Check that room is same or not!!
		cout << "First Name: ";
		cin >> customer.first_name;
		cout << "Last Name: ";
		cin >> customer.last_name;
		cout << "Address: ";
		cin >> customer.address;
		cout << "Days to Stay: ";
		cin >> customer.days_stay;
		cout << "Room Number: ";
		cin >> customer.room.room_Number;

		// Date, month year
		do {
			flag = 0;
			cout << "Date: ";
			cin >> customer.check_in_date;
			cout << "Month: ";
			cin >> customer.check_in_month;
			cout << "Year: ";
			cin >> customer.check_in_year;
			
			if ((customer.check_in_month == 1 || customer.check_in_month == 3 || customer.check_in_month == 5
				|| customer.check_in_month == 7 || customer.check_in_month == 8 || customer.check_in_month == 10
				|| customer.check_in_month == 12) && customer.check_in_date <= 31) {
				flag = 1;
			}
			else if ((customer.check_in_month == 4 || customer.check_in_month == 6 || customer.check_in_month == 9
				|| customer.check_in_month == 11) && customer.check_in_date <= 30) {
				flag = 1;
			}
			// Checking leapb year or not!!!
			else if (customer.check_in_month == 2) {
				if (customer.check_in_year % 4 == 0) {
					if (customer.check_in_year % 100 == 0) {
						if (customer.check_in_year % 400) {
							if (customer.check_in_date <= 29) {
								flag = 1;
							}
						}
						else {
							if (customer.check_in_date <= 28) {
								flag = 1;
							}
						}
					}
					else {
						if (customer.check_in_date <= 29) {
							flag = 1;
						}
					}
				}
				else {
					if (customer.check_in_date <= 28) {
						flag = 1;
					}
				}
			}
			else {
				cout << "Invalid Input!!!" << endl;
			}
		} while (flag != 1);
		

		// Adjusting room in Customer Record
		Room.open("Rooms Record.dat", ios::in | ios::binary | ios::out);
		if (Room.is_open()) {
			while (Room.read((char*)&Room_rec, sizeof(Rooms))) {
				if (Room_rec.room_Number == customer.room.room_Number) {
					customer.room.room_price = Room_rec.room_price;
					Room_rec.room_status = false;
					Room.seekp(pos * sizeof(Rooms));
					Room.write((char*)&Room_rec, sizeof(Rooms));
					room_flag = 1;
					break;
				}
				pos++;
			}
			Room.close();
		}
		// Checking for room redudancy
		room_redudancy_check.open("Customer Record.dat", ios::binary | ios::in);
		if (room_redudancy_check.is_open()) {
			while (room_redudancy_check.read((char*)&compare_room, sizeof(customers))) {
				if (compare_room.room.room_Number == customer.room.room_Number) {
					room_same_flag = 1;
					break;
				}
			}
		}
		
		if (room_flag == 1 && room_same_flag == 0) {

			cout << "\t\t\t\t\t=================Services=======================" << endl;
			// Food Services
			do {
				cout << "Food ($100 | (y / n)): ";
				cin >> service_choice;
				if (service_choice == 'y' || service_choice == 'Y') {
					customer.service_charges = customer.service_charges + 100;
				}
				else if (service_choice == 'N' || service_choice == 'n') {
					customer.service_charges = customer.service_charges + 0;
				}
			} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');

			// Gym Access
			do {
				cout << "Gym ($200 | (y / n)): ";
				cin >> service_choice;
				if (service_choice == 'y' || service_choice == 'Y') {
					customer.service_charges = customer.service_charges + 200;
				}
				else if (service_choice == 'N' || service_choice == 'n') {
					customer.service_charges = customer.service_charges + 0;
				}
			} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');

			// Fun Area Access
			do {
				cout << "Fun Area Access ($50 | (y / n)): ";
				cin >> service_choice;
				if (service_choice == 'y' || service_choice == 'Y') {
					customer.service_charges = customer.service_charges + 50;
				}
				else if (service_choice == 'N' || service_choice == 'n') {
					customer.service_charges = customer.service_charges + 0;
				}
			} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');

			customer.bill = (customer.days_stay * customer.room.room_price) + customer.service_charges;
			checkIn.open("Customer Record.dat", ios::app | ios::binary | ios::in);
			if (checkIn.is_open()) {
					checkIn.write((const char*)&customer, sizeof(customers));
					checkIn.close();
					customer_flag = 1;
			}
			else {
				cerr << "Error In Opening File!!!" << endl;
			}
			customer_record.open("Customers.dat", ios::app | ios::binary);
			if (customer_record.is_open()) {
				customer_record.write((const char*)&customer, sizeof(customers));
				customer_record.close();
			}
			else {
				cerr << "Customer Record not Maintained!!!" << endl;
			}
		}
		else if(room_flag == 0){
			cerr << "Room Does not Exist!!!" << endl;
		}
		else if (room_same_flag == 1) {
			cerr << "Room is not Avaliable!!!" << endl;
		}
		else {
			cerr << "Something Went Wrong!!!" << endl;
		}
		// cheking record updated or not
		if (customer_flag == 1) {
			cerr << "Record Updated!!!" << endl;
		}
		else{
			cerr << "Something Went Wrong!!!" << endl;
		}
	}
}

// View Records
void viewRecords() {
	cout << "\t\t\t\t\t=================View Record=======================" << endl;
	fstream viewRecords;
	customers customer;
	viewRecords.open("Customer Record.dat", ios::in, ios::binary);
	if (viewRecords.is_open()) {
		cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
			<< "==================================================================================================================================================="
			<< endl;
		while (viewRecords.read((char*)&customer, sizeof(customers))) {
			cout << customer.customer_cnic << "\t\t" << customer.first_name << " " << customer.last_name << "\t\t"
				<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t$" << customer.bill << "\t\t"
				<< customer.room.room_Number << "\t\t" << customer.check_in_date << "-" << customer.check_in_month
				<< "-" << customer.check_in_year << endl;
		}
		viewRecords.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

// Search Customer
void searchCustomer() {
	cout << "\t\t\t\t\t=================Search Record=======================" << endl;
	char choice;
	do {
		system("cls");
		customers customer;
		fstream searchContent;
		cout << "1. Search by CNIC" << endl
			<< "2. Search by Name" << endl
			<< "3. Exit Instance..." << endl
			<< "Choose from Above: ";
		cin >> choice;
		switch (choice) {
		case '1': {
			system("cls");
			cout << "\t\t\t\t\t=================Search By CNIC=======================" << endl;

			char cnic[25];
			cout << "CNIC: ";
			cin >> cnic;
			searchContent.open("Customer Record.dat", ios::in | ios::binary);
			if (searchContent.is_open()) {
				cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
					<< "==================================================================================================================================================="
					<< endl;
				while (searchContent.read((char*)&customer, sizeof(customers))) {
					if (strcmp(cnic, customer.customer_cnic) == 0) {
						cout << customer.customer_cnic << "\t\t" << customer.first_name << " " << customer.last_name << "\t\t"
							<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t$" << customer.bill << "\t\t"
							<< customer.room.room_Number << endl;
					}
				}
				searchContent.close();
			}
			else {
				cerr << "File not Found!!!!" << endl;
			}
			system("pause");
			break;
		}
		case '2':
			system("cls");
			cout << "\t\t\t\t\t=================Search By Name=======================" << endl;

			char name[25];
			cout << "Name: ";
			cin >> name;
			searchContent.open("Customer Record.dat", ios::in | ios::binary);
			if (searchContent.is_open()) {
				cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
					<< "==================================================================================================================================================="
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
							<< customer.address << "\t\t\t" << customer.days_stay << "\t\t\t\t$" << customer.bill << "\t\t\t"
							<< customer.room.room_Number << endl;
					}
				}
				searchContent.close();
			}
			else {
				cerr << "Error in opening File!!!" << endl;
			}
			system("pause");
			break;
		case '3':
			break;
		default:
			cerr << "Invalid Input!!!" << endl;
		}
	} while (choice != '3');
}

// Modify Customer Record
void modifyCustomer() {
	char service_choice;
	cout << "\t\t\t\t\t=================Modify Record=======================" << endl;
	int pos = 0;	// Position of file pointer...
	int flag_record_rpt = 0;	// flag for record repetition
	customers customer, modify, compare;
	Rooms room_record, room_record_copy;	// for Copying data of room temporary
	int flag = 0;
	int pos_for_room = 0;		// posotion for room
	char cnic[25];
	fstream modifyCustomer, compareRecord, room_rec;	// file pointers
	cout << "Enter the CNIC to Modify: ";
	cin >> cnic;

	modifyCustomer.open("Customer Record.dat", ios::in | ios::binary | ios::out);
	if (modifyCustomer.is_open()) {
		cout << "CNIC: ";
		cin >> modify.customer_cnic;
		compareRecord.open("Customer Record.dat", ios::in | ios::binary);
		if (compareRecord.is_open()) {
			while (compareRecord.read((char*)&compare, sizeof(customers))) {
				if (strcmp(modify.customer_cnic, compare.customer_cnic) == 0) {
					cout << "Record Already Exist" << endl;
					flag_record_rpt = 1;
					break;
				}
			}
		}
		if (flag_record_rpt == 0) {
			int room_flag = 0;
			cout << "First Name: ";
			cin >> modify.first_name;
			cout << "Last Name: ";
			cin >> modify.last_name;
			cout << "Address: ";
			cin >> modify.address;
			cout << "Days to Stay: ";
			cin >> modify.days_stay;
			cout << "Room Number: ";
			cin >> modify.room.room_Number;

			// Modify Date, month year
			do {
				flag = 0;
				cout << "Date: ";
				cin >> modify.check_in_date;
				cout << "Month: ";
				cin >> modify.check_in_month;
				cout << "Year: ";
				cin >> modify.check_in_year;
				if ((modify.check_in_month == 1 || modify.check_in_month == 3 || modify.check_in_month == 5
					|| modify.check_in_month == 7 || modify.check_in_month == 8 || modify.check_in_month == 10
					|| modify.check_in_month == 12) && modify.check_in_date <= 31) {
					flag = 1;
				}
				else if ((modify.check_in_month == 4 || modify.check_in_month == 6 || modify.check_in_month == 9
					|| modify.check_in_month == 11) && modify.check_in_date <= 30) {
					flag = 1;
				}
				else if (modify.check_in_month == 2) {
					if (modify.check_in_year % 4 == 0) {
						if (modify.check_in_year % 100 == 0) {
							if (modify.check_in_year % 400) {
								if (modify.check_in_date <= 29) {
									flag = 1;
								}
							}
							else {
								if (modify.check_in_date <= 28) {
									flag = 1;
								}
							}
						}
						else {
							if (modify.check_in_date <= 29) {
								flag = 1;
							}
						}
					}
					else {
						if (modify.check_in_date <= 28) {
							flag = 1;
						}
					}
				}
			} while (flag != 1);



			room_rec.open("Rooms Record.dat", ios::binary | ios::in | ios::out);
			if (room_rec.is_open()) {
				while (room_rec.read((char*)&room_record, sizeof(Rooms))) {
					if (modify.room.room_Number == room_record.room_Number) {
						modify.room.room_price = room_record.room_price;
						room_record.room_status = false;
						room_rec.seekp(pos_for_room * sizeof(Rooms));
						room_rec.write((char*)&room_record, sizeof(Rooms));
						room_flag = 1;
						break;
					}
					pos_for_room++;
				}
				room_rec.close();
			}


			if (room_flag == 1) {
				cout << "\t\t\t\t\t=================Services=======================" << endl;
				// Food Services
				do {
					cout << "Food ($100 | (y / n)): ";
					cin >> service_choice;
					if (service_choice == 'y' || service_choice == 'Y') {
						customer.service_charges = customer.service_charges + 100;
					}
					else if (service_choice == 'N' || service_choice == 'n') {
						customer.service_charges = customer.service_charges + 0;
					}
				} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');

				// Gym Access
				do {
					cout << "Gym ($200 | (y / n)): ";
					cin >> service_choice;
					if (service_choice == 'y' || service_choice == 'Y') {
						customer.service_charges = customer.service_charges + 200;
					}
					else if (service_choice == 'N' || service_choice == 'n') {
						customer.service_charges = customer.service_charges + 0;
					}
				} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');

				// Fun Area Access
				do {
					cout << "Fun Area Access ($50 | (y / n)): ";
					cin >> service_choice;
					if (service_choice == 'y' || service_choice == 'Y') {
						customer.service_charges = customer.service_charges + 50;
					}
					else if (service_choice == 'N' || service_choice == 'n') {
						customer.service_charges = customer.service_charges + 0;
					}
				} while (service_choice != 'Y' && service_choice != 'y' && service_choice != 'n' && service_choice != 'N');
				modify.bill = (modify.days_stay * modify.room.room_price) + (modify.service_charges);

				while (modifyCustomer.read((char*)&customer, sizeof(customers))) {
					if (strcmp(cnic, customer.customer_cnic) == 0) {
						room_record_copy.room_Number = customer.room.room_Number;	// fetching room number;
						modifyCustomer.seekp(pos * sizeof(customer));	// moving pointer to specific Position
						modifyCustomer.write((const char*)&modify, sizeof(customers));	// to overwrite to existing text...
						flag = 0;
						break;
					}
					else {
						flag = 1;
					}
					pos++;
				}
				if (flag == 1) {
					cerr << "Record Not Found!!!" << endl;
				}
				else {
					cerr << "Record Updated Successfully!!!" << endl;
				}
				
				room_rec.open("Rooms Record.dat", ios::binary | ios::in | ios::out);
				if (room_rec.is_open()) {
					pos = 0;
					while (room_rec.read((char*)&room_record, sizeof(Rooms))) {
						if (room_record.room_Number == room_record_copy.room_Number) {
							room_record.room_status = true;
							room_rec.seekp(pos * sizeof(Rooms));
							room_rec.write((char*)&room_record, sizeof(Rooms));
							break;
						}
						pos++;
					}
				}
			}
			else {
				cout << "Room Does not Exist!!!" << endl;
			}
		}
		modifyCustomer.close();
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

// Delete Customer Record
void deleteCustomer() {
	cout << "\t\t\t\t\t=================Checkout=======================" << endl;
	int flag = 0;
	char cnic[25];
	fstream deleteCustomer, temp, room;
	fstream income_record;
	customers customer, temp_customer;
	Rooms Room_record;	// for Room Record
	int room_number, room_price;
	
	

	deleteCustomer.open("Customer Record.dat", ios::in | ios::binary);
	if (deleteCustomer.is_open()) {
		cout << "Enter Your CNIC: ";
		cin >> cnic;
		while (deleteCustomer.read((char*)&customer, sizeof(customers))) {
			if (strcmp(cnic, customer.customer_cnic) == 0) {
				room_number = customer.room.room_Number;
				flag = 1;
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
		if (flag == 1) {
			room.open("Rooms Record.dat", ios::in | ios::binary | ios::out);
			if (room.is_open()) {
				int pos = 0;
				while (room.read((char*)&Room_record, sizeof(Rooms))) {
					if (room_number == Room_record.room_Number) {
						Room_record.room_status = true;
						room_price = Room_record.room_price;	// accesing room Price
						room.seekp(pos * sizeof(Rooms));
						room.write((char*)&Room_record, sizeof(Rooms));
						break;
					}
					pos++;
				}
			}
			deleteCustomer.close();
			remove("Customer Record.dat");
			if (rename("temp.dat", "Customer Record.dat") == 0) {
				cout << "Record Sucessfully Deleted!!!" << endl;
			}
		}
		else {
			cerr << "Record Does not Exist!!!" << endl;
		}
	}
	else {
		cout << "Error in Opening File!!!" << endl;
	}		
}

// Customer Management
void customerManagement() {
	char choice;
	do {
		system("cls");
		cout << "\t\t\t\t\t=================Customer Management=======================" << endl
			<< "1. Check In" << endl
			<< "2. View Record All of Customer" << endl
			<< "3. Search Customer" << endl
			<< "4. Modify Customer" << endl
			<< "5. Checkout" << endl
			<< "6. Exit Instance..." << endl
			<< "Enter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case '1':
			system("cls");
			checkIn();
			system("pause");
			break;
		case '2':
			system("cls");
			viewRecords();
			system("pause");
			break;
		case '3':
			system("cls");
			searchCustomer();
			system("pause");
			break;
		case '4':
			system("cls");
			modifyCustomer();
			system("pause");
			break;
		case '5':
			system("cls");
			deleteCustomer();
			system("pause");
			break;
		case '6':
			system("cls");
			break;
		default:
			system("cls");
			cerr << "Invalid Input !!!" << endl;
			system("pause");
		}
	} while (choice != '6');
}

///////////////////////////////////////// Room Management

// Add Room
void addRoom() {
	cout << "\t\t\t\t\t=================Add Room=======================" << endl;
	int flag = 0;
	fstream addroom, compare;
	Rooms room, compareRoom;

	addroom.open("Rooms Record.dat", ios::app | ios::binary);
	if (addroom.is_open()) {
		cout << "Room Number: ";
		cin >> room.room_Number;
		compare.open("Rooms Record.dat", ios::in | ios::binary);
		if (compare.is_open()) {
			while (compare.read((char*)&compareRoom, sizeof(Rooms))) {
				if (room.room_Number == compareRoom.room_Number) {
					cout << "Room Already Exist!!!" << endl;
					flag = 1;
				}
			}
		}
		else {
			cout << "Something Went Wrong!!!" << endl;
		}
		if (flag == 0) {
			cout << "Room Price: ";
			cin >> room.room_price;
			if (room.room_price > 1000) {
				room.room_catagory = 1;
			}
			else if (room.room_price > 500 && room.room_price <= 1000) {
				room.room_catagory = 2;
			}
			else {
				room.room_catagory = 3;
			}
			addroom.write((const char*)&room, sizeof(room));
			addroom.close();
			cerr << "Record Updated!!!" << endl;
		}
		else {
			cerr << "Something Went Wrong!!!" << endl;
		}
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
			<< "Room Number\t\t\tRoom Price\t\t\tRoom Status\t\t\tCatagory" << endl
			<< "=============================================================================================================="
			<< endl;
			while (viewRecord.read((char*)&roomRecord, sizeof(Rooms))) {
				cout << roomRecord.room_Number << "\t\t\t\t" << roomRecord.room_price
					<< "\t\t\t\t";
				if (roomRecord.room_status == false) {
					cout << "Not Avaliable" << "\t\t\t";
				}
				else {
					cout << "Avaliable" << "\t\t\t";
				}

				if (roomRecord.room_catagory == 1) {
					cout << "VIP" << endl;
				}
				else if (roomRecord.room_catagory == 2) {
					cout << "Medium" << endl;
				}
				else if(roomRecord.room_catagory == 3){
					cout << "Basic" << endl;
				}
			}
		viewRecord.close();
	}
	else {
		cerr << "Error In Opening File!!!" << endl;
	}
}

// Search Room
void searchRoom() {
	bool flag_customer = false;
	cout << "\t\t\t\t\t=================Search Room=======================" << endl;
	string first_name, last_name;
	int flag = 0;	// flag to check record exist or not
	fstream searchRoom, customer_file;
	Rooms roomRecord;
	customers customer;
	int room_number;
	cout << "Room Number: ";
	cin >> room_number;
	searchRoom.open("Rooms Record.dat", ios::in | ios::binary);
	if (searchRoom.is_open()) {
		cout << "Room Number\t\t\tRoom Price\t\t\tRoom Status\t\t\tCatagory\t\tCustomer Name" << endl
			<< "========================================================================================================================================"
			<< endl;
		while (searchRoom.read((char*)&roomRecord, sizeof(Rooms))) {
			customer_file.open("Customer Record.dat", ios::binary | ios::in);
			if (customer_file.is_open()) {
				while (customer_file.read((char*)&customer, sizeof(customers))) {
					if (room_number == customer.room.room_Number) {
						first_name = customer.first_name;
						last_name = customer.last_name;
						flag_customer = true;
					}
				}
			}
			else {
				cerr << "Error In opening file!!!" << endl;
			}
			if (room_number == roomRecord.room_Number) {
				cout << roomRecord.room_Number << "\t\t\t\t" << roomRecord.room_price
					<< "\t\t\t\t";
				if (roomRecord.room_status == false) {
					cout << "Not Avaliable" << "\t\t\t";
				}
				else {
					cout << "Avaliable" << "\t\t\t";
				}

				if (roomRecord.room_catagory == 1) {
					cout << "VIP\t\t";
				}
				else if (roomRecord.room_catagory == 2) {
					cout << "Medium\t\t";
				}
				else if (roomRecord.room_catagory == 3) {
					cout << "Basic\t\t";
				}
				if (flag_customer == true) {
					cout << first_name << " " << last_name;
				}
				cout << endl;
				flag = 1;
				break;
			}
		}
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
	if (flag == 0) {
		cerr << "Record not Found!!" << endl;
	}
}
// Modify Room
void modifyRoom() {
	cout << "\t\t\t\t\t=================Modify Room=======================" << endl;
	int flag_compare = 0;
	int pos = 0;
	int room_number;
	fstream modify, compare;
	Rooms room, Content;
	modify.open("Rooms Record.dat", ios::in | ios::binary | ios::out);
	if (modify.is_open()) {
		cout << "Room Number to Modify: ";
		cin >> room_number;
		cout << "Room Number: ";
		cin >> Content.room_Number;
		compare.open("Rooms Record.dat", ios::in | ios::binary);
		if (compare.is_open()) {
			while (compare.read((char*)&room, sizeof(Rooms))) {
				if (Content.room_Number == room.room_Number) {
					cout << "Record Already Exist" << endl;
					flag_compare = 1;
					break;
				}
			}
			compare.close();
		}
		if (flag_compare == 0) {
			cout << "Room Price: ";
			cin >> Content.room_price;

			if (Content.room_price > 1000) {
				Content.room_catagory = 1;
			}
			else if (Content.room_price > 500 && Content.room_price <= 1000) {
				Content.room_catagory = 2;
			}
			else {
				Content.room_catagory = 3;
			}


			while (modify.read((char*)&room, sizeof(Rooms))) {
				if (room_number == room.room_Number) {
					modify.seekp(pos * sizeof(Rooms));
					modify.write((const char*)&Content, sizeof(Content));
					cerr << "Record Updated!!!" << endl;
					break;
				}
				pos++;
			}
		}
		modify.close();
	}
}

// Delete Room
void deleteRoom() {
	cout << "\t\t\t\t\t=================Delete Room=======================" << endl;
	int flag = 0;	// Flag for Customer Redudancy
	fstream delRoom, newData;	// Delete Room
	Rooms room;
	fstream customer;	// Customer Record
	customers customer_rec;		// Customer Record Struct
	int room_number;
	delRoom.open("Rooms Record.dat", ios::in | ios::binary);
	if (delRoom.is_open()) {
		cout << "Room Number: ";
		cin >> room_number;

		// checking customer exist or not!!!
		customer.open("Customer Record.dat", ios::in | ios::binary);
		if (customer.is_open()) {
			while (customer.read((char*)&customer_rec, sizeof(customers))) {
				if (customer_rec.room.room_Number == room_number) {
					cerr << "Kindly, Delete Customer CNIC " << customer_rec.customer_cnic << " to delete Room!!!" << endl;
					flag = 1;
					break;
				}
			}
			customer.close();
		}
		if (flag == 0) {
			newData.open("Temp Room.dat", ios::app | ios::binary);
			if (newData.is_open()) {
				while (delRoom.read((char*)&room, sizeof(Rooms))) {
					if (room_number == room.room_Number) {
						continue;
					}
					else {
						newData.write((const char*)&room, sizeof(Rooms));
					}
				}
				newData.close();
			}
			delRoom.close();
			remove("Rooms Record.dat");
			if (rename("Temp Room.dat", "Rooms Record.dat") == 0) {
				cout << "Record Sucessfully Deleted!!!" << endl;
			}
		}
	}
}

// Show room By catagory
void roomCatagory() {
	cout << "\t\t\t\t\t=================Show Room By Status=======================" << endl;
	char choice;
	Rooms room_rec;
	fstream Room;
	
	do {
		system("cls");
		cout << "1. Show Avaliable Rooms" << endl
			<< "2. Show Unavaliable Rooms" << endl
			<< "3. Exit Instance" << endl
			<< "Choose from Above: ";
		cin >> choice;

		switch (choice) {
		case '1':
			system("cls");
			cout << "\t\t\t\t\t=================Show Avaliable Rooms=======================" << endl;
			Room.open("Rooms Record.dat", ios::in | ios::binary);
			if (Room.is_open()) {
				cout << "Room Number\t\t\tRoom Price\t\t\tRoom Status\t\t\tCatagory" << endl
					<< "=============================================================================================================="
					<< endl;
				while (Room.read((char*)&room_rec, sizeof(Rooms))) {
					if (room_rec.room_status == true) {
						cout << room_rec.room_Number << "\t\t\t\t" << room_rec.room_price
							<< "\t\t\t\t";
						if (room_rec.room_status == false) {
							cout << "Not Avaliable" << "\t\t\t";
						}
						else {
							cout << "Avaliable" << "\t\t\t";
						}

						if (room_rec.room_catagory == 1) {
							cout << "VIP" << endl;
						}
						else if (room_rec.room_catagory == 2) {
							cout << "Medium" << endl;
						}
						else if (room_rec.room_catagory == 3) {
							cout << "Basic" << endl;
						}
					}
				}
				system("pause");
				Room.close();
			}
			else {
				cerr << "Error in Opening File!!!" << endl;
			}
			break;
		case '2':
			system("cls");
			cout << "\t\t\t\t\t=================Show Unavaliable Rooms=======================" << endl;
			Room.open("Rooms Record.dat", ios::in | ios::binary);
			if (Room.is_open()) {
				cout << "Room Number\t\t\tRoom Price\t\t\tRoom Status\t\t\tCatagory" << endl
					<< "=============================================================================================================="
					<< endl;
				while (Room.read((char*)&room_rec, sizeof(Rooms))) {
					if (room_rec.room_status == false) {
						cout << room_rec.room_Number << "\t\t\t\t" << room_rec.room_price
							<< "\t\t\t\t";
						if (room_rec.room_status == false) {
							cout << "Not Avaliable" << "\t\t\t";
						}
						else {
							cout << "Avaliable" << "\t\t\t";
						}

						if (room_rec.room_catagory == 1) {
							cout << "VIP" << endl;
						}
						else if (room_rec.room_catagory == 2) {
							cout << "Medium" << endl;
						}
						else if (room_rec.room_catagory == 3) {
							cout << "Basic" << endl;
						}
					}
				}
				Room.close();
			}
			else {
				cerr << "Error in Opening File!!!" << endl;
			}
			system("pause");
			break;
		case '3':
			system("cls");
			break;
		default:
			system("cls");
			cout << "Invalid Input" << endl;
			system("pause");
		}
	} while (choice != '3');

}

// Room Management
void roomManagement() {
	char choice;
	do {
		system("cls");
		cout << "\t\t\t\t\t=================Room Management=======================" << endl
			<< "1. Add Room" << endl
			<< "2. View All Rooms Record" << endl
			<< "3. Search Room" << endl
			<< "4. Modify Room" << endl
			<< "5. Delete Room" << endl
			<< "6. Room Criteria" << endl
			<< "7. Show Room By Status..." << endl
			<< "8. Exit Instance" << endl
			<< "Choose from Above: ";
		cin >> choice;
		switch (choice) {
		case '1':
			system("cls");
			addRoom();
			system("pause");
			break;
		case '2':
			system("cls");
			viewRoom();
			system("pause");
			break;
		case '3':
			system("cls");
			searchRoom();
			system("pause");
			break;
		case '4':
			system("cls");
			modifyRoom();
			system("pause");
			break;
		case '5':
			system("cls");
			deleteRoom();
			system("pause");
			break;
		case '6':
			system("cls");
			cout << "\t\t\t\t\t=================Room Catagory Criteria=======================" << endl
				<< "Room Price Above $1000 ---------> VIP" << endl
				<< "Room Price Above $500  ---------> Medium" << endl
				<< "Room Price Below $500  ---------> Basic" << endl;
			system("pause");
			break;
		case '7':
			system("cls");
			roomCatagory();
			break;
		case '8':
			system("cls");
			break;
		default:
			system("cls");
			cout << "Invalid Input!!!" << endl;
			system("pause");
		}
	} while (choice != '8');
}

//////////////////////////////////////////////// View Customer Record

// View All Record
void viewCustomer_Record() {
	cout << "\t\t\t\t\t=================View All Records=======================" << endl;
	customers Record;
	fstream viewCustomer;
	viewCustomer.open("Customers.dat", ios::binary | ios::in);
	if (viewCustomer.is_open()) {
		cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
			<< "==================================================================================================================================================="
			<< endl;
		while (viewCustomer.read((char*)&Record, sizeof(customers))) {
			cout << Record.customer_cnic << "\t\t" << Record.first_name << " " << Record.last_name << "\t\t"
				<< Record.address << "\t\t\t" << Record.days_stay << "\t\t\t$" << Record.bill << "\t\t"
				<< Record.room.room_Number << "\t\t" << Record.check_in_date << "-" << Record.check_in_month
				<< "-" << Record.check_in_year << endl;
		}
		viewCustomer.close();
	}
	else {
		cerr << "Error in Opeing File!!!" << endl;
	}
}

// Search By ID
void SearchCustomer_Record_ID() {
	cout << "\t\t\t\t\t=================Search Record by CNIC=======================" << endl;
	int flag = 0;
	customers Record;
	fstream searchCustomer;
	char cnic[25];
	cout << "CNIC: ";
	cin >> cnic;
	searchCustomer.open("Customers.dat", ios::binary | ios::in);
	if (searchCustomer.is_open()) {
		cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
			<< "==================================================================================================================================================="
			<< endl;
		while (searchCustomer.read((char*)&Record, sizeof(customers))) {
			if (strcmp(Record.customer_cnic, cnic) == 0) {
				cout << Record.customer_cnic << "\t\t" << Record.first_name << " " << Record.last_name << "\t\t"
					<< Record.address << "\t\t\t" << Record.days_stay << "\t\t\t$" << Record.bill << "\t\t"
					<< Record.room.room_Number << "\t\t" << Record.check_in_date << "-" << Record.check_in_month
					<< "-" << Record.check_in_year << endl;
				flag = 1;
			}
		}
		if (flag == 0) {
			cerr << "Record Not Found!!!" << endl;
		}
	}
	else {
		cerr << "Error in Opening File!!!" << endl;
	}
}

// Search by Name
void SearchCustomer_Record_Name() {
	cout << "\t\t\t\t\t=================Seaech Record By Name=======================" << endl;
	int flag = 0;
	fstream searchCustomer;
	customers Record;
	char name[25];
	cout << "Name: ";
	cin >> name;
	searchCustomer.open("Customers.dat", ios::binary | ios::in);
	if (searchCustomer.is_open()) {
		cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
			<< "==================================================================================================================================================="
			<< endl;
		while (searchCustomer.read((char*)&Record, sizeof(customers))) {
			if ((strcmp(Record.first_name, name) == 0) || (strcmp(Record.last_name, name) == 0)) {
				cout << Record.customer_cnic << "\t\t" << Record.first_name << " " << Record.last_name << "\t\t"
					<< Record.address << "\t\t\t" << Record.days_stay << "\t\t\t$" << Record.bill << "\t\t"
					<< Record.room.room_Number << "\t\t" << Record.check_in_date << "-" << Record.check_in_month
					<< "-" << Record.check_in_year << endl;
				flag = 1;
			}
		}

		if (flag == 0) {
			cerr << "Record Not Found!!!" << endl;
		}
	}
}

// Search By Date

void SearchCustomer_Record_Date() {
	cout << "\t\t\t\t\t=================Search Record By Date=======================" << endl;
	int flag = 0;
	int flag_found_rcd = 0;	// to check that record is found or not
	int date, month, year;
	fstream searchCustomer;
	customers Record;
	do {
		cout << "Date: ";
		cin >> date;
		cout << "Month: ";
		cin >> month;
		cout << "Year: ";
		cin >> year;
		if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
			&& date > 31) {
			flag = 1;
		}
		else if ((month == 4 || month == 6 || month == 9 || month == 11) && date > 30) {
			flag == 1;
		}
		else if (month == 2) {
			if (year % 4 == 0) {
				if (year % 100 == 0) {
					if (year % 400) {
						flag = 1;
					}
					else {
						flag = 0;
					}
				}
				else {
					flag = 1;
				}
			}
			else {
				flag = 0;
			}
		}
	} while (flag != 0);
	searchCustomer.open("Customers.dat", ios::binary | ios::in);
	if (searchCustomer.is_open()) {
		cout << "CNIC\t\tName\t\t\tAddress\t\t\tDays to Stay\t\tBill\t\tRoom Number\t(Check In) DD-MM-YYYY" << endl
			<< "==================================================================================================================================================="
			<< endl;
		while (searchCustomer.read((char*)&Record, sizeof(customers))) {
			if ((Record.check_in_date == date) && (Record.check_in_month == month) && (Record.check_in_year == year)) {
				cout << Record.customer_cnic << "\t\t" << Record.first_name << " " << Record.last_name << "\t\t"
					<< Record.address << "\t\t\t" << Record.days_stay << "\t\t\t$" << Record.bill << "\t\t"
					<< Record.room.room_Number << "\t\t" << Record.check_in_date << "-" << Record.check_in_month
					<< "-" << Record.check_in_year << endl;
				flag_found_rcd = 1;
			}
		}
		if (flag_found_rcd == 0) {
			cerr << "Record Not Found!!!" << endl;
		}
	}
}

// View Customer Record
void customerRec() {
	char choice;
	do {
		system("cls");
		cout << "1. View all Record" << endl
			<< "2. Search By CNIC" << endl
			<< "3. Search By Name" << endl
			<< "4. Search By Date" << endl
			<< "5. Exit Instance" << endl
			<< "Choose form Above: ";
		cin >> choice;
		switch (choice) {
		case '1':
			system("cls");
			viewCustomer_Record();
			system("pause");
			break;
		case '2':
			system("cls");
			SearchCustomer_Record_ID();
			system("pause");
			break;
		case '3':
			system("cls");
			SearchCustomer_Record_Name();
			system("pause");
			break;
		case '4':
			system("cls");
			SearchCustomer_Record_Date();
			system("pause");
			break;
		case '5':
			system("cls");
			break;
		default:
			system("cls");
			cerr << "Invalid Input" << endl;
			system("pause");
		}
	} while (choice != '5');
}


/////////////////////////////////////// Main Function
void main() {
	char choice;
	do {
		cout << "\t\t\t\t\t=================Hotel Management System=======================" << endl
			<< "1. Customer Management" << endl
			<< "2. Room Management" << endl
			<< "3. View Customer Record" << endl
			<< "4. Exit Program..." << endl
			<< "Enter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case '1':
			system("cls");
			customerManagement();
			break;
		case '2':
			system("cls");
			roomManagement();
			break;
		case '3':
			system("cls");
			customerRec();
			break;
		case '4':
			break;
		default:
			cerr << "Invalid Input !!!" << endl;
		}
	} while (choice != '4');
}