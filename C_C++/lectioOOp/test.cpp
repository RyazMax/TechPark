#include <iostream>
#include <string>

#define WHISK 1

class Animal {

	public:
	virtual void feed() {std::cout<<"feed animal\n";}
};


class Cat : public Animal {
	public:
		void feed() {std::cout<<"feed cat\n";}
};

int main() {
	Cat c;

	Animal *a = &c;

	a->feed();

	return 0;
}
