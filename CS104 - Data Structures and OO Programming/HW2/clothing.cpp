#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string brand_, const std::string size_):
Product("clothing", name, price, qty){
	this->brand_ = brand_;
	this->size_ = size_;
}

Clothing::~Clothing(){

}

std::string Clothing::getBrand() const {
	return brand_;
}

std::string Clothing::getSize() const {
	return size_;
}

void Clothing::dump(std::ostream& os) const {
	Product::dump(os);
	os << size_ << endl << brand_ << endl;
}

std::string Clothing::displayString() const {
	std::string ret;
	std::string name = getName();
	std::string size = getSize();
	std::string brand = getBrand();
	std::string temp = to_string(price_);
	int ind = temp.find(".");
	temp = temp.substr(0, ind + 3);
	ret.append(name);
	ret.append("\nSize: ");
	ret.append(size);
	ret.append(" Brand: ");
	ret.append(brand);
	ret.append("\n");
	ret.append(temp);
	ret.append(" ");
	temp = to_string(qty_);
	ret.append(temp);
	ret.append(" left.");

	return ret;
}

std::set<std::string> Clothing::keywords(){
	std::string name = getName();
	std::string brand = getBrand();
	std::set<std::string> st1 = parseStringToWords(brand);
	std::set<std::string> st = parseStringToWords(name);
	st = setUnion(st, st1);

	return st;
}