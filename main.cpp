///////////////////////////////////////////////////////////////////////////////
// File Name:      main.cpp
//
// Editor:		   Michael Redbourne (UNB Computer Science - mredbour@unb.ca)
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "curl.h"
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "Data.hpp"

//CurlObj is used to get the html from the given webpage
class CurlObj {
public:
    /**
     * @brief Constructor for a curl object.
     *
     * @param url The url of the page to scrape.
     */
    CurlObj (std::string url) {
        curl = curl_easy_init();
        if (!curl) {
            throw std::string ("Curl did not initialize.");
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlObj::curlWriter);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_perform(curl);
    };
    
    static int curlWriter(char *data, int size, int nmemb, std::string *buffer) {
        int result = 0;
        if (buffer != NULL) {
            buffer->append(data, size * nmemb);
            result = size * nmemb;
        }
        
        return result;
    }
    
    std::string getData() {
        return curlBuffer;
    }
    
protected:
    CURL * curl;
    std::string curlBuffer;
};
//credit to stack overflow for help on the CurlObj class

int main() {
    
    //the tickers of companies
    std::vector<std::string> names;
    std::string numCompaniesString;
    
	/* Hardcoded Companies */
    std::string AMZN ("AMZN"); // Amazon
	std::transform(AMZN.begin(), AMZN.end(), AMZN.begin(), ::tolower);
	names.push_back(AMZN);

    std::string GOOGL ("GOOGL"); // Google
	std::transform(GOOGL.begin(), GOOGL.end(), GOOGL.begin(), ::tolower);
	names.push_back(GOOGL);

	std::string AAPL ("AAPL"); // Apple
	std::transform(AAPL.begin(), AAPL.end(), AAPL.begin(), ::tolower);
	names.push_back(AAPL);

	std::string CRM ("CRM"); // SalesForce
	std::transform(CRM.begin(), CRM.end(), CRM.begin(), ::tolower);
	names.push_back(CRM);

	std::string ORCL ("ORCL"); // Oracle "Java"
	std::transform(ORCL.begin(), ORCL.end(), ORCL.begin(), ::tolower);
	names.push_back(ORCL);
    
    std::cout << "Please wait for your data. This may take a few seconds." << std::endl << std::endl;
    
    std::vector<Data> dataObjs;
    /* Delete the file before file output. */
	if(remove("StockExchangePrices.hpp") != 0){
		perror("Error Deleting File");
	}
	else{
		puts("Successfully Deleted File");
	}
    //get all the data and print it out
    for (size_t i = 0; i < names.size(); i++) {
        std::string name = names[i];
        std::string address = "https://finance.yahoo.com/quotes/" + name;
        CurlObj temp(address);
        try {
            Data dta = Data(name, temp.getData());
            dta.printData();
        } catch (std::exception e) {
            std::cout << "\n" << name << " is not a valid ticker." << std::endl;
        }
    }
    
    std::cout << std::endl;
    
    return 0;
}