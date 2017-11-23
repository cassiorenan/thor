#include <iostream>

#include "person.hpp"

int main() {
	Person foo;
	foo.set_name("John Doe");
	foo.set_age(42);
	std::cout << foo.get_name() << " is " << foo.get_age() << " years old.";
}