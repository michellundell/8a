/**
 * @brief This program will demonstrate the C++ features listed in menu
 */

#include <iostream>
#include <limits>
using namespace std;

string menu = "\n\
 1 C++ class constructor \n\
 2 C++ class destructor \n\
 3 C++ inheritance \n\
 4 C++ overloading methods \n\
 5 C++ Reference \n\
 6 C++ friend \n\
 7 C++ overloading input output operators << and >> \n\
 8 C++ Function Templates \n\
 9 C++ Class Templates \n\
 10 C++ std::list \n\
 11 C++ List with custom class, std::list \n\
 12 C++ Exception handling \n\
 13 C++ new, delete  \n\
 14 C++ Initialization Operator \n\
 15 C++ Assignment Operator \n\
 16 C++ Function Call Operator \n\
 17 C++ Subscript Operator \n\
 18 C++ Increment Operator \n\
 19 C++ Decrement Operator \n\
 20 Quit\n\nEnter your choice:";

/**
* @brief pause program until user press enter
*/
void press_any_key()
{
   cout << "Press Enter to Continue";
   cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

/**
* Show feature ClassConstructor
*/

class ClassContructorClass {
};

void showFeatureClassConstructor()
{
	cout << "C++ feature class constructor" << endl;

	// implement some code that use a class constructor

	press_any_key();
}


/**
* @brief Show feature .....
*/




/**
* @brief program main entry
*/

int main(int argc, char **argv)
{
	string str;
	int choice = -1;
	do {
		cout << menu;
    		getline(cin, str);
		choice = stoi(str);
		switch(choice) {
			case 1:
				// call a function that shows the feature ...
				showFeatureClassConstructor();
			break;
			case 2:
				// call a function that shows the feature ...
			break;
			case 3:
				// call a function that shows the feature ...
			break;
			case 4:
				// call a function that shows the feature ...
			break;
			case 5:
				// call a function that shows the feature ...
			break;
			case 6:
				// call a function that shows the feature ...
			break;
			case 7:
				// call a function that shows the feature ...
			break;
			case 8:
				// call a function that shows the feature ...
			break;
			case 9:
				// call a function that shows the feature ...
			break;
			case 10:
				// call a function that shows the feature ...
			break;
			case 11:
				// call a function that shows the feature ...
			break;
			case 12:
				// call a function that shows the feature ...
			break;
			case 13:
				// call a function that shows the feature ...
			break;
			case 14:
				// call a function that shows the feature ...
			break;
			case 15:
				// call a function that shows the feature ...
			break;
			case 16:
				// call a function that shows the feature ...
			break;
			case 17:
				// call a function that shows the feature ...
			break;
			case 18:
				// call a function that shows the feature ...
			break;
			case 19:
				// call a function that shows the feature ...
			break;
		}
	} while( choice != 20 );
	return(0);
}


