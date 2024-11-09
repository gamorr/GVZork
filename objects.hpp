#ifndef             __H__OBJECTS__
#define             __H__OBJECTS__

#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>


class Item {
    public: 
        std::string name;
        std::string description;
        int calories;
        float weight;
        Item(const std::string &name, const std::string &description, int calories, float weight);
        
        friend std::ostream& operator<<(std::ostream& os, const Item& item){
            os << item.name << " (" << item.calories << " calories" << ")" << " - " << item.weight << " lb " << "- " << item.description << std::endl;
            return os;
        }
};



#endif
