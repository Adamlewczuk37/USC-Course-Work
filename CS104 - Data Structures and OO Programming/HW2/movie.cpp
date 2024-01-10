#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre_, const std::string rating_):
Product("movie", name, price, qty){
	this->genre_ = genre_;
	this->rating_ = rating_;
}

Movie::~Movie(){

}

std::string Movie::getGenre() const {
	return genre_;
}

std::string Movie::getRating() const {
	return rating_;
}

void Movie::dump(std::ostream& os) const {
	Product::dump(os);
	os << genre_ << endl << rating_ << endl;
}

std::string Movie::displayString() const {
	std::string ret;
	std::string name = getName();
	std::string genre = getGenre();
	std::string rating = getRating();
	std::string temp = to_string(price_);
	int ind = temp.find(".");
	temp = temp.substr(0, ind + 3);
	ret.append(name);
	ret.append("\nGenre: ");
	ret.append(genre);
	ret.append(" Rating: ");
	ret.append(rating);
	ret.append("\n");
	ret.append(temp);
	ret.append(" ");
	temp = to_string(qty_);
	ret.append(temp);
	ret.append(" left.");

	return ret;
}

std::set<std::string> Movie::keywords(){
	std::string name = getName();
	std::string genre = getGenre();
	genre = convToLower(genre);
	std::set<std::string> st = parseStringToWords(name);
	st.insert(genre);

	return st;
}