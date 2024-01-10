#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "book.h"
using namespace std;

Book::Book(const std::string name, double price, int qty, std::string author_, std::string isbn_) : 
Product("book", name, price, qty){
	this->author_ = author_;
	this->isbn_ = isbn_;
}

Book::~Book(){

}

std::string Book::getAuthor() const {
	return author_;
}

std::string Book::getisbn() const {
	return isbn_;
}

void Book::dump(std::ostream& os) const {
	Product::dump(os);
	os << isbn_<< endl << author_ << endl;
}

std::string Book::displayString() const {
	std::string ret;
	std::string name = getName();
	std::string author = getAuthor();
	std::string isbn = getisbn();
	std::string temp = to_string(price_);
	int ind = temp.find(".");
	temp = temp.substr(0, ind + 3);
	ret.append(name);
	ret.append("\nAuthor: ");
	ret.append(author);
	ret.append(" ISBN: ");
	ret.append(isbn);
	ret.append("\n");
	ret.append(temp);
	ret.append(" ");
	temp = to_string(qty_);
	ret.append(temp);
	ret.append(" left.");

	return ret;
}

std::set<std::string> Book::keywords(){
	std::string name = getName();
	std::string isbn = getisbn();
	std::string author = getAuthor();
	std::set<std::string> st = parseStringToWords(name);
	std::set<std::string> st1 = parseStringToWords(author);
	st.insert(isbn);
	st = setUnion(st, st1);

	return st;
}