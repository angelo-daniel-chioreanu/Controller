#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>

#include "controller.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fixed;
using std::setprecision;

int main(int argc, char* argv[])
{
	Controller* pCtrl = NULL;

	string fileName;
	
	cout << "*** Cryo-cooler controller ***" << endl;
	cout << "Please provide the calibration file name: ";
	cin >> fileName;

	try
	{
		pCtrl = new Controller(fileName);
	}
	catch (...)
	{
		cout << "Failed to load the calibration file!" << endl;
		exit(EXIT_FAILURE);
	}

	if (pCtrl != NULL)
	{		
		string inputCmd;
		float inputVal;

		cout << "Press 'q' to quit, 'v' to convert voltage and 't' to convert temperature." << endl;

		do
		{
			cout << "Command: ";
			cin >> inputCmd;
		
			if (inputCmd == "v")
			{
				cout << "Voltage (mV): ";
				cin >> inputVal;
				cout << "Temperature (K): " << fixed << setprecision(2) << pCtrl->convertmVtoK(inputVal) << endl;
			}
			else if (inputCmd == "t")
			{
				cout << "Temperature (K): ";
				cin >> inputVal;
				cout << "Voltage (mV): " << fixed << setprecision(3) << pCtrl->convertKtomV(inputVal) << endl;
			} 
		}
		while (inputCmd != "q");

		delete pCtrl;
	}
}
