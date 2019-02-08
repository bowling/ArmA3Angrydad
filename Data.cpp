///////////////////////////////////////////////////////////////////////////////
// File Name:      Data.cpp
//
// Editor:		   Michael Redbourne (UNB Computer Science - mredbour@unb.ca)
//
///////////////////////////////////////////////////////////////////////////////

#include "Data.hpp"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

Data::Data(string NAME, string HTML) {
    name = NAME;
    //all the html of the website
    html = HTML;
    fillData();
}

/* Optimized to ignore irrelevant data. */
void Data::fillData() {
    string currentPlace = "yfs_l84_" + name;
	string changePlace = "yfs_c63_" + name;
	size_t addingSize = changePlace.size () + 2;
    size_t indexCurrent = html.find(currentPlace) + addingSize;
    string currentS = html.substr(indexCurrent, 6);
    current = std::stod(currentS);
}

/* Rewritten from Consonle output to File Output */
/* Rewritten to meet ArmA 3 HPP requirements */
void Data::printData() {
	/* File Stream */
	ofstream stockExchange;
	stockExchange.open("StockExchangePrices.hpp", ios::out | ios::app); // Output and append file of all content.
	if(stockExchange.is_open()){
		stockExchange << "class " << name << "quality = 1; price = " << current << "; sellPrice = " << current << ";\n";
	}
	else{
		perror("Error Opening File");
	}
	
	/*
    std::cout << "\n" << name << ":" << std::endl;
    std::cout << "\tCURRENT\t\t" << current << "\n\tLOW\t\t\t" << low <<
                "\n\tHIGH\t\t" << high << "\n\tCHANGE\t\t" << sign << chg <<
                "\n\t%CHANGE\t\t" << sign << pChg << "%" << std::endl;
	*/
}