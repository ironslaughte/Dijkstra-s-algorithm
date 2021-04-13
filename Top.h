#pragma once
#include <string>

struct Top {
	std::string city; 
	int price = 0; // flight price (edge weight)
	//bool visit = false; // Is the node visited

	Top() {
		city = " ";
		price = 0;
	}

	Top(std::string City, int Price = 0) {
		city = City;
		price = Price;		
	}
};