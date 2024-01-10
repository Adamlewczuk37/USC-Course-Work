#include "product.h"
#include "util.h"
#include <string>
#include <set>
#include <vector>
#include <iostream>

class Book: public Product {
public:
	Book(const std::string name, double price, int qty, std::string author_, std::string isbn_);
	~Book();
	std::set<std::string> keywords();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	std::string getAuthor() const;
	std::string getisbn() const;
private:
	std::string author_;
	std::string isbn_;
};