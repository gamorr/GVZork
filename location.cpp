#include "objects.hpp"
#include "item.h"
#include "npc.h"
#include <string>
#include <vector>
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
            throw(0);
        } else if (this->neighbors.count(direction) == 1) { // Throws error if direction key already exists
            throw(1);
        } else {
            // this->neighbors[direction] = location;
        }
    } catch (int error) {
        if (error == 0) {
            std::cout << "Error - String is blank." << std::endl;
        }
        else {
            std::cout << "Error - Key already exists." << std::endl;
        }
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
std::map<std::string, Location> Location::get_locations() {
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

