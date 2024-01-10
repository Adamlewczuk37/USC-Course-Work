#include "product.h"
#include "util.h"
#include <string>
#include <set>
#include <vector>
#include <iostream>

class Clothing: public Product {
public:
	Clothing(const std::string name, double price, int qty, std::string brand_, std::string size_);
	~Clothing();
	std::set<std::string> keywords();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	std::string getBrand() const;
	std::string getSize() const;
private:
	std::string size_;
	std::string brand_;
};