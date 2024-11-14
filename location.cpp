#include "objects.hpp"
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <iostream>

// Constructor takes in a name and description for a location and automatically 
// sets the visited status to false
Location::Location(const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;
    this->visited = false;
}

// Setters
// Keys for the location map are the direction that are in the form 
// North, East, South, West.
// Blank strings or already added keys raise errors
void Location::add_location(const std::string& direction, const Location& location) {
    try {
        if (direction.size() == 0) { // Throws error if direction key is blank
            throw std::runtime_error("String is blank");
        } else if (this->neighbors.count(direction) == 1) { // Throws error if direction key already exists
            throw std::runtime_error("Key already exists");
        } else {
            this->neighbors.insert(std::pair{direction, location});
        }
    }
}

void Location::add_npc(const NPC& npc) {
    this->npcs.push_back(npc);
}

void Location::add_item(const Item& item) {
    this->items.push_back(item);
}

// set_visited can only change visited status to true
void Location::set_visited() {
    this->visited = true;
}

// Getters
std::map<std::string, std::reference_wrapper<Location> > Location::get_locations() {
    return this->neighbors;
}

std::vector<std::reference_wrapper<NPC> > Location::get_npcs() {
    return this->npcs;
}

std::vector<std::reference_wrapper<Item> > Location::get_items() {
    return this->items;
}

bool Location::get_visited() {
    return this->visited;
}

// TESTING CODE
int main(int argc, char** argv) {
    Location House = Location::Location("A House", "A very standard house that you could see anywhere in america");
    Location Shop = Location::Location("A Shop", "A very standard shop that looks like the sign says MEEJER");

    House.add_location("W", Shop);
    House.add_location("E", Shop);
    House.add_location("W", Shop);
}
