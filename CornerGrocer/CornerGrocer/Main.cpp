//Kody Greenberg for CS 210 12/7/2022 Main.cpp

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <conio.h>

using namespace std;

//This function calls the python function by the same name to read the file and output a list - OPTION 1
void ReadFile(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	//to have c++ import correctly I have added this code
	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

//This function calls a python function of the same name and searches a product and returns the number of times it was purchased - OPTION 2
int SelectItem(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	//to have c++ import correctly I have added this code
	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

//This function calls a python function of the same name to create a new file and write the contents of products list to it - OPTION 3
void CreateFile(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	//to have c++ import correctly I have added this code
	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

//this function takes a selected item and returns the value to display the amount of times it was bought. 
void DisplaySelectedItem(string item, int amount) {
	string selectedItem = item;
	// For loop takes the user input and turns it all to lower case
	for (int i = 0; i < item.length(); ++i) {
		selectedItem[i] = tolower(selectedItem[i]);
	}
	selectedItem[0] = toupper(selectedItem[0]); // Turns the first char to upper case
	// If statement displays the item and amount only if the item amount does not eqaul 0
	if (amount >= 1) {
		cout << setfill(' ') << setw(57) << right << "|=================================|" << endl;
		cout << setfill(' ') << setw(57) << right << "|  Selected Item Purchased Today  |" << endl;
		cout << setfill(' ') << setw(57) << right << "|=================================|" << endl;
		cout << setfill(' ') << setw(43) << right << "|    Item of Choice: " << setfill(' ') << setw(13) << left <<selectedItem << "|" << endl;
		cout << setfill(' ') << setw(57) << right << "|---------------------------------|" << endl;
		cout << setfill(' ') << setw(57) << right << "|     ITEM      |     QUANTITY    |" << endl;
		cout << setfill(' ') << setw(57) << right << "|---------------|-----------------|" << endl;
		cout << setfill(' ') << setw(23) << "|" << setfill(' ') << setw(10) << selectedItem << setfill(' ') << setw(6) << "|" << setfill(' ')<< setw(9) << amount << setfill(' ') << setw(9) << "|" << endl;
		cout << setfill(' ') << setw(57) << right << "|---------------------------------|" << endl;
		cout << "To clear the screen and continue: ";
		system("pause");
		system("cls");//clears screen
	}
	else {
		cout << endl;
		cout << setfill(' ') << setw(64) << right << "|==============================================|" <<endl;
		cout << setfill(' ') << setw(73) << "|  \x1b[91mSelected Item Has Not Been Purchased Today\x1b[0m  |" << endl;
		cout << setfill(' ') << setw(64) << right << "|==============================================|" << endl;
		cout << endl;
		cout << "To clear the screen and continue: ";
		system("pause");
		system("cls");//clears screen
	}
	return;
}

// This function is used to display what is current going on after a menu selection has occured
void SpecialProgramDisplay(string display) {
	if (display == "Exit") {
		cout << "|\x1b[92mExited Program Successfully\x1b[0m|" << endl;
		cout << "|===============================================================================|" << endl;
	}
	else if (display == "File") {
		cout << "|\x1b[92mFrequency.dat File Successfully Created\x1b[0m|" << endl;
		cout << "\x1b[0;36m|===============================================================================|" << endl;
	}
	else if (display == "Error") {
		cout << "|\x1b[91mError Opening Frequency.dat File\x1b[0m|" << endl;
		cout << "|===============================================================================|" << endl;
	}
	return;
}

// This function is used to display a histogram representation of the list of products purchased
void HistogramDisplay() {
	// Declared variables
	ifstream inFS;
	string item;
	int amount, padding;
	// Opens the file frequency.dat (Created by the python script after selcting option 3)
	inFS.open("frequency.dat");
	if (!inFS.is_open()) { // Verifies the file is open if not sends an error message
		SpecialProgramDisplay("Error");
	}else { // If file is open this section prints out a list of items purchased and the histogram representation of them
		cout << setfill(' ') << setw(57) << right << "|===============================|" << endl;
		cout << setfill(' ') << setw(57) << right << "|   Items Purchased Histogram   |" << endl;
		cout << setfill(' ') << setw(57) << right << "|===============================|" << endl;
		cout << setfill(' ') << setw(57) << right << "|    ITEM     |    QUANTITY     |" << endl;
		cout << setfill(' ') << setw(57) << right << "|-------------|-----------------|" << endl;
		// This section iterates through the whole file while the stream is good and prints out the item and the amount in histogram form
		while (!inFS.eof() && inFS.good()) {
			inFS >> item;
			inFS >> amount; 
			if (!inFS.fail()) { 
				cout << setfill(' ') << setw(25) << right << "|" << setfill(' ') << setw(13) << right << item << "| "; 
				//converted charecter to a smiley face. Set int = to ascii table for smiley face, then made it a char to print the char value.
				int sml = 1;
				char ch = sml;
				for (int i = 0; i < amount; ++i) { 
					cout << ch; 
				}
				padding = (17 - amount); 
				cout << setfill(' ') << setw(padding) << right << "|" << endl; 
			}
		}
		cout << setfill(' ') << setw(61) << right << "|-------------------------------|\x1b[0m" << endl;
	}
	inFS.close(); 
	cout << "To clear the screen and continue: ";
	system("pause");
	system("cls");//clears screen
}



//displays a menu with options
void MenuDisplay() {
	//given a line break with a tilde to show the menu has started
	for (int i = 0; i <= 119; i++) {
		cout << "~";
	}
	cout << "\nPlease indicate what you would like to do," << endl;
	cout << "If you would like to see what all was purchased in a given day type \"1\"" << endl;
	cout << "If you would like to see how many times a specific item was purchased in a given day type \"2\"" << endl;
	cout << "If you would like to create a histogram of all items purchased in a given day, along with the number of times each item was purchased type \"3\"" << endl;
	cout << "If you would like to exit the program type \"4\"" << endl;
}

void MenuSelection() {
	int userInput, itemAmount;
	string selectedItem;
	bool exitLoop;

	//used a do while loop so itll run until valid input is given and stop if option 4 is used. 
	cout << "\x1b[0;36mWelcome to the Corner Grocer App!\x1b[0m" << endl;
	do {
		MenuDisplay(); // call to menu display function
		cout << "Enter selection here >> ";
		exitLoop = false;

		cin >> userInput;
		cin.clear();
		cin.ignore(INT_MAX, '\n'); // to ignore the remainder of the stream
		// Switch statement used to validate user input
		switch (userInput){

		case 1: // This case calls the readfile function to display the file from python
		ReadFile("ReadFile");
		cout << "To clear the screen and continue: ";
		system("pause");
		system("cls");//clears screen
		break;

		case 2: // This case calls the displayselecteditem function to get an amount of time purchased for a specific item returned from python and displayed in c++
			cout << "What Item would you like to view? ";
			getline(cin, selectedItem);
			itemAmount = SelectItem("SelectItem", selectedItem);
			
			DisplaySelectedItem(selectedItem, itemAmount);
			break;

		case 3: // This case creates a new file in python and then reads the file in c++ and displays a histogram representation
		CreateFile("CreateFile");
		SpecialProgramDisplay("File");
		Sleep(1000);
		HistogramDisplay();
		break;

		case 4: // This case exits the program - OPTION 4
		SpecialProgramDisplay("Exit");
		exitLoop = true;
		break;

		default: // Default case runs if input is invalid
			system("cls");
			cout << "\x1b[91mERROR: INPUT INVALID, please use only an integer from 1-4 and no letters\x1b[0m" << endl;
			Sleep(1000);
			break;
		}
	} while (!exitLoop); // While loop is maintained open until case 4 is reached and exitLoop is true
	return;
}


void main()
{
	MenuSelection();
}