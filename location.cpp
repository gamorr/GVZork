/**
 * Authors:   Harrison Waldon, Gavin Morrow, Gavin Cowan
 * Created:   11.9.2024
 **/

#include "objects.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <algorithm>


// Constructor takes in a name and description for a location and automatically 
// sets the visited status to false
Location::Location(const std::string& name, const std::string& description) {
    this->name = name;
    this->description = description;
    this->visited = false;
}

// Default Constructor
Location::Location(){
    this->name = "Unnamed";
    this->description = "None";
    this->visited = false;
}



// Setters
// Keys for the location map are the direction that are in the form 
// North, East, South, West.
// Blank strings or already added keys raise errors
void Location::add_location(const std::string& direction, Location* location) {
    if (direction.empty()) { // Throws error if direction key is blank
        throw std::runtime_error("String is blank");
    } else if (this->neighbors.count(direction) == 1) { // Throws error if direction key already exists
        throw std::runtime_error("Key already exists");
    } else {
        this->neighbors.insert(make_pair(direction,location));
    }
}

void Location::add_npc(NPC& npc) {
    this->npcs.push_back(std::ref(npc));
}

void Location::add_item(Item& item) {
    this->items.push_back(std::ref(item));
}

// Remove item from a location
void Location::remove_item(Item& item) {
    for(auto it = this->items.begin(); it != this->items.end(); ++it) {
        if (it->get().get_name() == item.get_name()) {
            this->items.erase(it);
            break;
        }
    }
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

std::map<std::string, Location*> Location::get_locations() {
    return this->neighbors;
}

std::vector<std::reference_wrapper<NPC> > Location::get_npcs() {
    return this->npcs;
}

std::vector<std::reference_wrapper<Item> > Location::get_items() {
    return this->items;
}

bool Location::get_visited() const{
    return this->visited;

}