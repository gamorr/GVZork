#include "objects.hpp"
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
    // Need to raise exceptions for blank strings and already added keys
    


    this->neighbors.insert(std::pair{direction, location});
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
std::map<string, Location> Location::get_locations() {
    return this->neighbors;
}

std::vector<NPC> Location::get_npcs() {
    return this->npcs;
}

std::vector<Items> Location::get_items() {
    return this->items;
}

bool Location::get_visited() {
    return this->visited;
}
