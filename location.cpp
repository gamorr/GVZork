#include "objects.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>

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
    if (direction.empty()) { // Throws error if direction key is blank
        throw std::runtime_error("String is blank");
    } else if (this->neighbors.count(direction) == 1) { // Throws error if direction key already exists
        throw std::runtime_error("Key already exists");
    } else {
        this->neighbors.insert({direction,location});
    }
}

void Location::add_npc(NPC npc) {
    this->npcs.push_back(npc);
}

void Location::add_item(Item item) {
    this->items.push_back(item);
}

// set_visited can only change visited status to true
void Location::set_visited() {
    this->visited = true;
}

// Getters
std::string Location::get_name() {
    return this->name;
}

std::string Location::get_desc() {
    return this->description;
}

std::map<std::string, std::reference_wrapper<Location> > Location::get_locations() {
    return this->neighbors;
}

std::vector<NPC> Location::get_npcs() {
    return this->npcs;
}

std::vector<Item> Location::get_items() {
    return this->items;
}

bool Location::get_visited() const{
    return this->visited;

}

int main(int argc, char** argv){
    Location House("A House", "A standard midwestern house with a MAGA sign out front =(");
    Location Store("Harrys", "A very small party store facing away from the road.\nThere is 2 year old expired sour cream inside");
    House.add_location("West", Store);
    Store.add_location("East", Store);
    House.add_location("West", Store);



    return 0;
}
