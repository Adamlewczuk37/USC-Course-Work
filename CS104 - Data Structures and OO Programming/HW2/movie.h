#include "product.h"
#include "util.h"
#include <string>
#include <set>
#include <vector>
#include <iostream>

class Movie: public Product {
public:
	Movie(const std::string name, double price, int qty, std::string genre_, std::string rating_);
	~Movie();
	std::set<std::string> keywords();
	std::string displayString() const;
	void dump(std::ostream& os) const;
	std::string getGenre() const;
	std::string getRating() const;
private:
	std::string genre_;
	std::string rating_;
};