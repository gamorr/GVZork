#include <iostream> 
#include "objects.hpp"

Item::Item(const std::string &name, const std::string &description, int calories, float weight)
{
    //this-> makes sure we are modifying this specific version of Item class, and not the data members from the .hpp file
    this->name = name;       
    this->description = description;
    this->calories = calories;
    this->weight = weight;

    if (name.empty() || description.empty()) {
        throw std::runtime_error("String is blank");
    }

    if (calories < 0 || calories > 1000) {
        throw std::out_of_range("Value must be within the range of acceptable calories");
    }

    if (typeid(calories) != typeid(int)){
        throw std::invalid_argument("Incorrect value type for calories");       
    }

}

int main() 
{
    Item beefStew("Beef Stew", "Be Careful! It is boiling hot for some reason because the chef didn't care to let it sit out long enough", 450, 0.5);
    std::cout << beefStew << std::endl;

    return 0;
}
