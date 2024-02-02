#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "controller.h"

Controller::Controller(std::string fileNameCalibration)
{
	std::cout << "Controller loading sensor calibration from file '" << fileNameCalibration << "'" << std::endl;

	loadCalibrationTable(fileNameCalibration);
}

Controller::~Controller()
{
	std::cout << "*** Good-bye! ***" << std::endl;
}

void Controller::loadCalibrationTable(std::string fileName)
{
	std::ifstream file;
	std::string line;

	file.open(fileName);

	if (!file.is_open())
		throw "Error reading file.";

	float temperature, voltage, slope;

	getline(file, line); // read header

	while(file >> temperature >> voltage >> slope)
	{
		tableCalibrationSortedByT.push_back(Calibration(temperature, voltage, slope));
	}

	tableCalibrationSortedByV = tableCalibrationSortedByT;

	sort(tableCalibrationSortedByV.begin(), tableCalibrationSortedByV.end(), compareCalibrationByV);
	sort(tableCalibrationSortedByT.begin(), tableCalibrationSortedByT.end(), compareCalibrationByT);
}

float Controller::convertmVtoK(float voltage)
{
	Calibration cal = findClosestCalibrationByV(voltage / 1000);

	float temperature = cal.temperature + (voltage  - cal.voltage * 1000) / cal.slope;

	return temperature;
}

float Controller::convertKtomV(float temperature)
{
	Calibration cal = findClosestCalibrationByT(temperature);

	float voltage = cal.voltage * 1000 + cal.slope * (temperature - cal.temperature);

	return voltage;
}

Calibration Controller::findClosestCalibrationByV(float voltage)
{
	std::pair<std::vector<Calibration>::iterator, std::vector<Calibration>::iterator> bounds;

	Calibration cal = Calibration(0, voltage, 0);

	bounds = equal_range(tableCalibrationSortedByV.begin(), tableCalibrationSortedByV.end(), cal, compareCalibrationByV);

	if (std::abs((*bounds.first).voltage - voltage) < std::abs((*bounds.second).voltage - voltage))
		cal = *bounds.first;
	else
		cal = *bounds.second;

	return cal;
}

Calibration Controller::findClosestCalibrationByT(float temperature)
{
	std::pair<std::vector<Calibration>::iterator, std::vector<Calibration>::iterator> bounds;

	Calibration cal = Calibration(temperature, 0, 0);

        bounds = equal_range(tableCalibrationSortedByT.begin(), tableCalibrationSortedByT.end(), cal, compareCalibrationByT);

        if (std::abs((*bounds.first).temperature - temperature) < std::abs((*bounds.second).temperature - temperature))
                cal = *bounds.first;
        else
                cal = *bounds.second;

        return cal;
}

/* Unit Tests */
void printCalibrationTables(Controller* pCtrl)
{
        std::cout << "tableCalibrationSortedByT" << std::endl;

        for(auto cal : pCtrl->tableCalibrationSortedByT)
        {
                std::cout << std::fixed << std::setprecision(2) << cal.temperature << "\t" << std::setprecision(6) << cal.voltage << "\t" << std::setprecision(2) << cal.slope << std::endl;
        }

        std::cout << "tableCalibrationSortedByV" << std::endl;

        for(auto cal : pCtrl->tableCalibrationSortedByV)
        {
                std::cout << std::fixed << std::setprecision(2) << cal.temperature << "\t" << std::setprecision(6) << cal.voltage << "\t" << std::setprecision(2) << cal.slope << std::endl;
        }	
}

