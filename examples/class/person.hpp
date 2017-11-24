
#ifndef PERSON_HPP
#define PERSON_HPP

#include <algorithm> // for std::move



// Generated dependencies

#include <string>


class Person {
    
    int age;
    
    std::string name;
    
public:
    
    int get_age() const {return age;}
    void set_age(int age) {this->age = std::move(age);}
    
    std::string get_name() const {return name;}
    void set_name(std::string name) {this->name = std::move(name);}
    
};

#endif