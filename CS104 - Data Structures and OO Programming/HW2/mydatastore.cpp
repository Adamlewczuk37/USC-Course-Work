#include <iostream>
#include <sstream>
#include "mydatastore.h"
#include "util.h"
//#include "map"
using namespace std;

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product* p) {
	products.insert(p);
	std::set<std::string> keywords = p->keywords();
	typename std::set<std::string>:: iterator it;
	for (it = keywords.begin(); it != keywords.end(); it++){
		if (keywordToProducts.find(*it) == keywordToProducts.end()){
			std::set<Product*> temp;
			temp.insert(p);
			keywordToProducts.insert(std::make_pair(*it, temp));
		} else {
			keywordToProducts.find(*it)->second.insert(p);
		}
	}
}

void MyDataStore::addUser(User* u) {
	users.insert(u);
	std::deque<Product*> products;

	userToCart.insert(std::pair<User*, std::deque<Product*>>(u, products));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::set<Product*> ret;
	std::set<Product*> temp;
	std::string keyword;
	for (unsigned int i = 0; i < terms.size(); i++){
		keyword = terms[i];
		temp.clear();
		if (keywordToProducts.find(keyword) != keywordToProducts.end()){
			temp = keywordToProducts.find(keyword)->second;
		}
		if (type == 0){
			if (i == 0){
				ret = temp;
			} else {
				ret = setIntersection(ret, temp);
			}
		} else if (type == 1){
			if (i == 0){
				ret = temp;
			} else {
				ret = setUnion(ret, temp);
			}
		}
	}

	std::vector<Product*> r;
	r.assign(ret.begin(), ret.end());
	return r;
}

void MyDataStore::addCart (Product* p, std::string username) {
	typename std::map<User*, std::deque<Product*>>:: iterator it;
	std::deque<Product*> cart;
	for (it = userToCart.begin(); it != userToCart.end(); it++){
		if (it->first->getName() == username){
			cart = it->second;
			break;
		}
	}
	cart.push_back(p);
	for (it = userToCart.begin(); it != userToCart.end(); it++){
		if (it->first->getName() == username){
			it->second = cart;
			break;
		}
	}
}

void MyDataStore::purchaseCart (std::string username) {
	typename std::map<User*, std::deque<Product*>>:: iterator it;
	std::deque<Product*> cart;
	User* u;
	for (it = userToCart.begin(); it != userToCart.end(); it++){
		if (it->first->getName() == username){
			cart = it->second;
			u = it->first;
			break;
		}
	}

	Product* p;
	double amount = u->getBalance();
	double itemAmount;
	int qty;
	for (unsigned int i = 0; i < cart.size(); i++){
		p = cart[i];
		amount = u->getBalance();
		itemAmount = p->getPrice();
		qty = p->getQty();
		if ((qty > 0) && (amount >= itemAmount)){
			p->subtractQty(1);
			u->deductAmount(itemAmount);
		}

	}

	for (it = userToCart.begin(); it != userToCart.end(); it++){
		if (it->first->getName() == username){
			it->second = cart;
			break;
		}
	}
}

void MyDataStore::viewCart (std::string username) {
	typename std::map<User*, std::deque<Product*>>:: iterator it;
	std::deque<Product*> cart;
	for (it = userToCart.begin(); it != userToCart.end(); it++){
		if (it->first->getName() == username){
			cart = it->second;
			break;
		}
	}
	Product* p;
	std::string disp;
	int temp;
	for (unsigned int i = 0; i < cart.size(); i++){
		if (i > 0){
			cout << endl;
		}
		p = cart.at(i);
		disp = p->displayString();
		temp = i + 1;
		cout << "Item " << temp << endl;
		cout << disp << endl;
	}
}

void MyDataStore::dump(std::ostream& ofile) {
	typename std::set<User*>:: iterator uit;
	typename std::set<Product*>:: iterator pit;
	Product* p;
	User* u;

	ofile << "<products>" << endl;
	for (pit = products.begin(); pit != products.end(); pit++){
		p = *pit;
		p->dump(ofile);
		delete p;
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (uit = users.begin(); uit != users.end(); uit++){
		u = *uit;
		u->dump(ofile);
		delete u;
	}
	ofile << "</users>" << endl;
}