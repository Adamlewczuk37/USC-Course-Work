#include "datastore.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <deque>
using namespace std;

class MyDataStore: public DataStore {
public:
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addCart(Product* p, std::string username);
	void purchaseCart(std::string username);
	void viewCart(std::string username);
	std::set<User*> users;
private:
	std::set<Product*> products;
	std::map<User*, std::deque<Product*>> userToCart;
	std::map<std::string, std::set<Product*>> keywordToProducts;
};