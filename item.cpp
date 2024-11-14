#include <iostream> 
#include "objects.hpp"
#include <typeinfo>

Item::Item(const std::string &name, const std::string &description, int calories, float weight) {
    //this-> makes sure we are modifying this specific version of Item class, and not the data members from the .hpp file
    this->name = name;       
    this->description = description;
    this->calories = calories;
    this->weight = weight;
    bool isEdible; 

    if (name.empty() || description.empty()) {
        throw std::runtime_error("String is blank");
    }

    if (typeid(calories) != typeid(int)) {
        throw std::invalid_argument("Incorrect value type for calories"); 
    }

    if (calories < 0 || calories > 1000) {
        throw std::out_of_range("Value must be within the range of acceptable calories");
    }

    if (calories == 0) {
        isEdible = false;
    } else {
        isEdible = true;
    }

    if (typeid(weight) != typeid(float)) {
        throw std::invalid_argument("Incorrect value type for weight"); 
    }
    
}

int main() {
    std::string name;
    std::string description;
    int calories; 
    float weight;

    std::cout << "Enter a name: "; 
    std::cin >> name;

    return 0;
}